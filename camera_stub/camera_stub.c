/*
 * Minimal camera_module_t for Qin 2 Pro.
 *
 * The real camera stack (dcam/csi/isp kernel drivers) is absent, so the
 * stock SPRD camera module cannot work.  This module advertises a single
 * BACK camera that cannot be opened, but which reports a flash unit so
 * that CameraService's torch path reaches set_torch_mode() — which we
 * implement by driving the torch LED sysfs node directly.
 */
#define LOG_TAG "qin_camera_stub"
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <hardware/camera_common.h>
#include <hardware/hardware.h>
#include <system/camera_metadata.h>
#include <log/log.h>

#define TORCH_BRIGHTNESS "/sys/class/leds/flashlight/brightness"

static camera_module_callbacks_t* g_cb;
static pthread_mutex_t g_lock = PTHREAD_MUTEX_INITIALIZER;
static int g_torch_on;

static int stub_get_number_of_cameras(void) {
    ALOGI("get_number_of_cameras -> 1");
    return 1;
}

/* Build the minimal static metadata CameraService needs to accept the
 * device as a flash-capable BACK camera. */
static camera_metadata_t* build_characteristics(void) {
    camera_metadata_t* m = allocate_camera_metadata(64, 512);
    if (!m) return NULL;

    const uint8_t level = ANDROID_INFO_SUPPORTED_HARDWARE_LEVEL_LEGACY;
    add_camera_metadata_entry(m, ANDROID_INFO_SUPPORTED_HARDWARE_LEVEL, &level, 1);

    const uint8_t facing = ANDROID_LENS_FACING_BACK;
    add_camera_metadata_entry(m, ANDROID_LENS_FACING, &facing, 1);

    const int32_t orientation = 90;
    add_camera_metadata_entry(m, ANDROID_SENSOR_ORIENTATION, &orientation, 1);

    const uint8_t flash = 1;
    add_camera_metadata_entry(m, ANDROID_FLASH_INFO_AVAILABLE, &flash, 1);

    const uint8_t cap = ANDROID_REQUEST_AVAILABLE_CAPABILITIES_BACKWARD_COMPATIBLE;
    add_camera_metadata_entry(m, ANDROID_REQUEST_AVAILABLE_CAPABILITIES, &cap, 1);

    const int32_t max_regions[] = {0, 0, 0}; /* ae, awb, af */
    add_camera_metadata_entry(m, ANDROID_CONTROL_MAX_REGIONS, max_regions, 3);

    const uint8_t modes[] = {ANDROID_CONTROL_MODE_AUTO};
    add_camera_metadata_entry(m, ANDROID_CONTROL_AVAILABLE_MODES, modes, 1);
    add_camera_metadata_entry(m, ANDROID_CONTROL_AVAILABLE_SCENE_MODES,
                              (const uint8_t[]){ANDROID_CONTROL_SCENE_MODE_DISABLED}, 1);
    add_camera_metadata_entry(m, ANDROID_CONTROL_AVAILABLE_EFFECTS,
                              (const uint8_t[]){ANDROID_CONTROL_EFFECT_MODE_OFF}, 1);

    /* 576x1440 sensor-ish active array + basic pixel array so stream
     * config queries have something to chew on (no real streams). */
    const int32_t array[] = {0, 0, 576, 1440};
    add_camera_metadata_entry(m, ANDROID_SENSOR_INFO_PRE_CORRECTION_ACTIVE_ARRAY_SIZE, array, 4);
    add_camera_metadata_entry(m, ANDROID_SENSOR_INFO_ACTIVE_ARRAY_SIZE, array, 4);
    const int32_t pixsize[] = {576, 1440};
    add_camera_metadata_entry(m, ANDROID_SENSOR_INFO_PIXEL_ARRAY_SIZE, pixsize, 2);
    const float fsize[] = {0.576f, 1.44f};
    add_camera_metadata_entry(m, ANDROID_SENSOR_INFO_PHYSICAL_SIZE, fsize, 2);
    const float focal[] = {3.5f};
    add_camera_metadata_entry(m, ANDROID_LENS_INFO_AVAILABLE_FOCAL_LENGTHS, focal, 1);
    const float apertures[] = {2.2f};
    add_camera_metadata_entry(m, ANDROID_LENS_INFO_AVAILABLE_APERTURES, apertures, 1);
    const int32_t range[] = {15, 30};
    add_camera_metadata_entry(m, ANDROID_CONTROL_AE_AVAILABLE_TARGET_FPS_RANGES, range, 2);
    add_camera_metadata_entry(m, ANDROID_SCALER_AVAILABLE_MAX_DIGITAL_ZOOM,
                              (const float[]){1.0f}, 1);
    return m;
}

static int stub_get_camera_info(int camera_id, struct camera_info* info) {
    ALOGI("get_camera_info id=%d info=%p", camera_id, info);
    if (camera_id != 0 || !info) return -EINVAL;
    static camera_metadata_t* chars;
    pthread_mutex_lock(&g_lock);
    if (!chars) chars = build_characteristics();
    pthread_mutex_unlock(&g_lock);
    if (!chars) return -ENOMEM;

    info->facing = CAMERA_FACING_BACK;
    info->orientation = 90;
    /* HAL3 marker so the provider lists the device; open() still fails. */
    info->device_version = CAMERA_DEVICE_API_VERSION_3_4;
    info->static_camera_characteristics = chars;
    info->resource_cost = 0;
    info->conflicting_devices = NULL;
    info->conflicting_devices_length = 0;
    return 0;
}

static int stub_set_callbacks(const camera_module_callbacks_t* callbacks) {
    pthread_mutex_lock(&g_lock);
    g_cb = (camera_module_callbacks_t*)callbacks;
    pthread_mutex_unlock(&g_lock);
    return 0;
}

static void notify_torch(int on) {
    camera_module_callbacks_t* cb;
    pthread_mutex_lock(&g_lock);
    cb = g_cb;
    pthread_mutex_unlock(&g_lock);
    if (cb && cb->torch_mode_status_change) {
        cb->torch_mode_status_change(cb, "0",
            on ? TORCH_MODE_STATUS_AVAILABLE_ON : TORCH_MODE_STATUS_AVAILABLE_OFF);
    }
}

static int stub_set_torch_mode(const char* camera_id, bool enabled) {
    if (!camera_id || strcmp(camera_id, "0")) return -EINVAL;
    int fd = open(TORCH_BRIGHTNESS, O_WRONLY | O_CLOEXEC);
    if (fd < 0) {
        ALOGE("torch open %s failed: %s", TORCH_BRIGHTNESS, strerror(errno));
        return -EIO;
    }
    const char* v = enabled ? "128" : "0";
    if (write(fd, v, strlen(v)) < 0) {
        ALOGE("torch write failed: %s", strerror(errno));
        close(fd);
        return -EIO;
    }
    close(fd);
    pthread_mutex_lock(&g_lock);
    g_torch_on = enabled;
    pthread_mutex_unlock(&g_lock);
    notify_torch(enabled);
    ALOGI("torch %s", enabled ? "ON" : "OFF");
    return 0;
}

static int stub_open_legacy(const hw_module_t* m, const char* id,
                            uint32_t v, hw_device_t** d) {
    (void)m; (void)id; (void)v; (void)d;
    return -ENODEV; /* no usable camera without dcam/csi drivers */
}

static int stub_camera_device_open(const hw_module_t* m, const char* id,
                                   hw_device_t** d) {
    (void)m; (void)id; (void)d;
    return -ENODEV;
}

static int stub_init(camera_module_t* m) { (void)m; ALOGI("module init"); return 0; }
static void stub_get_vendor_tag_ops(vendor_tag_ops_t* ops) {
    if (ops) memset(ops, 0, sizeof(*ops));
}

static hw_module_methods_t s_methods = {
    .open = stub_camera_device_open,
};

camera_module_t HAL_MODULE_INFO_SYM = {
    .common = {
        .tag = HARDWARE_MODULE_TAG,
        .module_api_version = CAMERA_MODULE_API_VERSION_2_4,
        .hal_api_version = HARDWARE_HAL_API_VERSION,
        .id = CAMERA_HARDWARE_MODULE_ID,
        .name = "Qin stub camera",
        .author = "qin2pro-port",
        .methods = &s_methods,
        .dso = NULL,
        .reserved = {0},
    },
    .get_number_of_cameras = stub_get_number_of_cameras,
    .get_camera_info = stub_get_camera_info,
    .set_callbacks = stub_set_callbacks,
    .get_vendor_tag_ops = stub_get_vendor_tag_ops,
    .open_legacy = stub_open_legacy,
    .set_torch_mode = stub_set_torch_mode,
    .init = stub_init,
    .get_physical_camera_info = NULL,
    .is_stream_combination_supported = NULL,
    .notify_device_state_change = NULL,
};
