// SPDX-License-Identifier: Apache-2.0
// Qin 2 Pro SC27xx input-FF vibrator. The stock timed_output HAL cannot
// operate the mainline sc27xx-vibra input device.
#define LOG_TAG "QinVibrator"
#include <android/hardware/vibrator/1.0/IVibrator.h>
#include <hidl/HidlTransportSupport.h>
#include <log/log.h>
#include <dirent.h>
#include <fcntl.h>
#include <linux/input.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <algorithm>
#include <chrono>
#include <condition_variable>
#include <cstring>
#include <mutex>
#include <string>
#include <thread>

using namespace android::hardware::vibrator::V1_0;
using android::hardware::Return;
using android::hardware::Void;

class QinVibrator final : public IVibrator {
public:
    QinVibrator() {
        DIR* dir = opendir("/dev/input");
        if (!dir) return;
        while (auto* entry = readdir(dir)) {
            if (strncmp(entry->d_name, "event", 5)) continue;
            std::string path = std::string("/dev/input/") + entry->d_name;
            int fd = open(path.c_str(), O_RDWR | O_CLOEXEC);
            if (fd < 0) continue;
            char name[128] = {};
            if (ioctl(fd, EVIOCGNAME(sizeof(name)), name) >= 0 &&
                    !strcmp(name, "sc27xx:vibrator")) {
                mFd = fd;
                ALOGI("Using %s (%s)", path.c_str(), name);
                break;
            }
            close(fd);
        }
        closedir(dir);
        if (mFd >= 0) mWorker = std::thread([this] { timerLoop(); });
    }
    ~QinVibrator() override {
        {
            std::lock_guard<std::mutex> lock(mMutex);
            mExit = true;
            stopLocked();
            mCondition.notify_all();
        }
        if (mWorker.joinable()) mWorker.join();
        if (mEffectId >= 0) ioctl(mFd, EVIOCRMFF, mEffectId);
        if (mFd >= 0) close(mFd);
    }
    bool ready() const { return mFd >= 0; }
    Return<Status> on(uint32_t timeoutMs) override {
        std::lock_guard<std::mutex> lock(mMutex);
        if (!timeoutMs) return stopLocked();
        if (mFd < 0) return Status::UNKNOWN_ERROR;
        struct ff_effect effect = {};
        effect.type = FF_RUMBLE;
        effect.id = mEffectId;
        // This SC27xx driver is an on/off motor and reads weak_magnitude.
        effect.u.rumble.strong_magnitude = 0xffff;
        effect.u.rumble.weak_magnitude = 0xffff;
        effect.replay.length = std::min(timeoutMs, uint32_t(UINT16_MAX));
        if (ioctl(mFd, EVIOCSFF, &effect) < 0) {
            ALOGE("EVIOCSFF: %s", strerror(errno));
            return Status::UNKNOWN_ERROR;
        }
        mEffectId = effect.id;
        // FF replay length is 16-bit; repeat long requests and stop exactly
        // at the framework's deadline using an interruptible monotonic timer.
        int repeats = (uint64_t(timeoutMs) + effect.replay.length - 1) / effect.replay.length;
        if (!sendLocked(repeats)) return Status::UNKNOWN_ERROR;
        mDeadline = std::chrono::steady_clock::now() + std::chrono::milliseconds(timeoutMs);
        mActive = true;
        ++mGeneration;
        mCondition.notify_all();
        return Status::OK;
    }
    Return<Status> off() override {
        std::lock_guard<std::mutex> lock(mMutex);
        return stopLocked();
    }
    Return<bool> supportsAmplitudeControl() override { return false; }
    Return<Status> setAmplitude(uint8_t) override { return Status::UNSUPPORTED_OPERATION; }
    Return<void> perform(Effect, EffectStrength, perform_cb callback) override {
        callback(Status::UNSUPPORTED_OPERATION, 0);
        return Void();
    }
private:
    bool sendLocked(int value) {
        struct input_event event = {};
        event.type = EV_FF;
        event.code = mEffectId;
        event.value = value;
        return TEMP_FAILURE_RETRY(write(mFd, &event, sizeof(event))) == sizeof(event);
    }
    Status stopLocked() {
        mActive = false;
        ++mGeneration;
        mCondition.notify_all();
        if (mFd < 0) return Status::UNKNOWN_ERROR;
        return mEffectId < 0 || sendLocked(0) ? Status::OK : Status::UNKNOWN_ERROR;
    }
    void timerLoop() {
        std::unique_lock<std::mutex> lock(mMutex);
        while (!mExit) {
            mCondition.wait(lock, [this] { return mExit || mActive; });
            if (mExit) break;
            auto generation = mGeneration;
            if (!mCondition.wait_until(lock, mDeadline,
                    [this, generation] { return mExit || mGeneration != generation; }))
                stopLocked();
        }
    }
    int mFd = -1;
    int mEffectId = -1;
    bool mExit = false;
    bool mActive = false;
    uint64_t mGeneration = 0;
    std::chrono::steady_clock::time_point mDeadline;
    std::mutex mMutex;
    std::condition_variable mCondition;
    std::thread mWorker;
};

int main() {
    android::hardware::configureRpcThreadpool(1, true);
    android::sp<QinVibrator> vibrator = new QinVibrator();
    if (!vibrator->ready()) { ALOGE("SC27xx vibrator not found"); return 1; }
    if (vibrator->registerAsService() != android::OK) return 1;
    android::hardware::joinRpcThreadpool();
    return 1;
}
