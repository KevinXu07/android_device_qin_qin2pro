#include <aidl/android/hardware/light/BnLights.h>
#include <android-base/file.h>
#include <android-base/logging.h>
#include <android/binder_manager.h>
#include <android/binder_process.h>
#include <atomic>
#include <mutex>
#include <thread>

using aidl::android::hardware::light::BnLights;
using aidl::android::hardware::light::FlashMode;
using aidl::android::hardware::light::HwLight;
using aidl::android::hardware::light::HwLightState;
using aidl::android::hardware::light::LightType;

namespace {

constexpr const char* kBacklightNode =
        "/sys/class/backlight/sprd_backlight/brightness";
constexpr const char* kLedNodes[] = {
        "/sys/class/leds/sc27xx:red",
        "/sys/class/leds/sc27xx:green",
        "/sys/class/leds/sc27xx:blue",
};

bool writeNode(const std::string& path, const std::string& value) {
    return android::base::WriteStringToFile(value, path);
}

}  // namespace

class QinLights final : public BnLights {
 public:
    ~QinLights() override { stopBlinkLocked(); }

    ndk::ScopedAStatus getLights(std::vector<HwLight>* lights) override {
        HwLight panel;
        panel.id = 0;
        panel.ordinal = 1;
        panel.type = LightType::BACKLIGHT;
        HwLight notif;
        notif.id = 1;
        notif.ordinal = 2;
        notif.type = LightType::NOTIFICATIONS;
        HwLight battery;
        battery.id = 2;
        battery.ordinal = 3;
        battery.type = LightType::BATTERY;
        *lights = {panel, notif, battery};
        return ndk::ScopedAStatus::ok();
    }

    ndk::ScopedAStatus setLightState(int id, const HwLightState& state) override {
        std::lock_guard<std::mutex> lock(mMutex);
        LOG(INFO) << "setLightState id=" << id << " color=" << std::hex << state.color
                  << " flash=" << static_cast<int>(state.flashMode)
                  << " on=" << std::dec << state.flashOnMs << " off=" << state.flashOffMs;
        switch (id) {
            case 0:
                return setBacklight(state);
            case 1:
            case 2:
                return setRgbLed(state);
            default:
                return ndk::ScopedAStatus::fromExceptionCode(EX_UNSUPPORTED_OPERATION);
        }
    }

 private:
    ndk::ScopedAStatus setBacklight(const HwLightState& state) {
        const uint32_t rgb = static_cast<uint32_t>(state.color);
        const int brightness = (77 * ((rgb >> 16) & 255) +
                                150 * ((rgb >> 8) & 255) + 29 * (rgb & 255)) >> 8;
        if (!writeNode(kBacklightNode, std::to_string(brightness) + "\n")) {
            PLOG(ERROR) << "Cannot set Qin panel brightness";
            return ndk::ScopedAStatus::fromServiceSpecificError(errno);
        }
        return ndk::ScopedAStatus::ok();
    }

    // Called with mMutex held.
    void stopBlinkLocked() {
        mBlinkRunning = false;
        if (mBlinkThread.joinable()) {
            mBlinkThread.join();
        }
    }

    // Called with mMutex held.
    ndk::ScopedAStatus setRgbLed(const HwLightState& state) {
        stopBlinkLocked();
        const uint32_t rgb = static_cast<uint32_t>(state.color);
        const int channels[] = {
                static_cast<int>((rgb >> 16) & 255),
                static_cast<int>((rgb >> 8) & 255),
                static_cast<int>(rgb & 255),
        };
        const bool flash = state.flashMode != FlashMode::NONE &&
                (state.flashOnMs > 0 || state.flashOffMs > 0);
        if (flash) {
            // Software blink: the SC27xx hw_pattern attribute is only created
            // when the kernel "pattern" trigger binds, and it comes up
            // root:root 0644 which this service cannot write. Toggling the
            // brightness node needs no extra permissions.
            mBlinkRunning = true;
            mBlinkThread = std::thread([this, state] { blinkLoop(state); });
            return ndk::ScopedAStatus::ok();
        }
        for (int i = 0; i < 3; i++) {
            if (!writeNode(std::string(kLedNodes[i]) + "/brightness",
                           std::to_string(channels[i]) + "\n")) {
                PLOG(ERROR) << "Cannot set " << kLedNodes[i];
                return ndk::ScopedAStatus::fromServiceSpecificError(errno);
            }
        }
        return ndk::ScopedAStatus::ok();
    }

    void blinkLoop(HwLightState state) {
        const int on = state.flashOnMs > 0 ? state.flashOnMs : 1000;
        const int off = state.flashOffMs > 0 ? state.flashOffMs : 1000;
        const uint32_t rgb = static_cast<uint32_t>(state.color);
        const int channels[] = {
                static_cast<int>((rgb >> 16) & 255),
                static_cast<int>((rgb >> 8) & 255),
                static_cast<int>(rgb & 255),
        };
        while (mBlinkRunning) {
            for (int i = 0; i < 3; i++) {
                writeNode(std::string(kLedNodes[i]) + "/brightness",
                          std::to_string(channels[i]) + "\n");
            }
            if (!sleepInterruptible(on)) break;
            for (int i = 0; i < 3; i++) {
                writeNode(std::string(kLedNodes[i]) + "/brightness", "0\n");
            }
            if (!sleepInterruptible(off)) break;
        }
    }

    // Sleep in small slices so a new state can interrupt the blink quickly.
    bool sleepInterruptible(int ms) {
        while (ms > 0 && mBlinkRunning) {
            const int slice = ms > 50 ? 50 : ms;
            std::this_thread::sleep_for(std::chrono::milliseconds(slice));
            ms -= slice;
        }
        return mBlinkRunning;
    }

    std::mutex mMutex;
    std::atomic<bool> mBlinkRunning{false};
    std::thread mBlinkThread;
};

int main() {
    android::base::InitLogging(nullptr, android::base::LogdLogger());
    ABinderProcess_setThreadPoolMaxThreadCount(0);
    auto lights = ndk::SharedRefBase::make<QinLights>();
    const std::string instance = std::string(QinLights::descriptor) + "/default";
    CHECK(AServiceManager_addService(lights->asBinder().get(), instance.c_str()) == STATUS_OK);
    ABinderProcess_joinThreadPool();
    return EXIT_FAILURE;
}
