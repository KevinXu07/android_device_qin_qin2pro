#include <aidl/android/hardware/light/BnLights.h>
#include <android-base/file.h>
#include <android-base/logging.h>
#include <android/binder_manager.h>
#include <android/binder_process.h>
#include <mutex>

using aidl::android::hardware::light::BnLights;
using aidl::android::hardware::light::HwLight;
using aidl::android::hardware::light::HwLightState;
using aidl::android::hardware::light::LightType;

class QinLights final : public BnLights {
 public:
    ndk::ScopedAStatus getLights(std::vector<HwLight>* lights) override {
        HwLight panel;
        panel.id = 0;
        panel.ordinal = 1;
        panel.type = LightType::BACKLIGHT;
        *lights = {panel};
        return ndk::ScopedAStatus::ok();
    }
    ndk::ScopedAStatus setLightState(int id, const HwLightState& state) override {
        if (id != 0) return ndk::ScopedAStatus::fromExceptionCode(EX_UNSUPPORTED_OPERATION);
        const uint32_t rgb = static_cast<uint32_t>(state.color);
        const int brightness = (77 * ((rgb >> 16) & 255) +
                                150 * ((rgb >> 8) & 255) + 29 * (rgb & 255)) >> 8;
        std::lock_guard<std::mutex> lock(mMutex);
        if (!android::base::WriteStringToFile(std::to_string(brightness) + "\n",
                "/sys/class/backlight/sprd_backlight/brightness")) {
            PLOG(ERROR) << "Cannot set Qin panel brightness";
            return ndk::ScopedAStatus::fromServiceSpecificError(errno);
        }
        return ndk::ScopedAStatus::ok();
    }
 private:
    std::mutex mMutex;
};

int main() {
    ABinderProcess_setThreadPoolMaxThreadCount(0);
    auto lights = ndk::SharedRefBase::make<QinLights>();
    const std::string instance = std::string(QinLights::descriptor) + "/default";
    CHECK(AServiceManager_addService(lights->asBinder().get(), instance.c_str()) == STATUS_OK);
    ABinderProcess_joinThreadPool();
    return EXIT_FAILURE;
}
