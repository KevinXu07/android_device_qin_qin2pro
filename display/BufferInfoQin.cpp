/*
 * Copyright (C) 2026 The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */
#define LOG_TAG "hwc-bufferinfo-qin"

#include "bufferinfo/BufferInfoGetter.h"
#include "utils/log.h"

namespace android {

class BufferInfoQin : public LegacyBufferInfoGetter {
 public:
  int ConvertBoInfo(buffer_handle_t handle, hwc_drm_bo_t *bo) override {
    // IMG exports one fd. Its two unused fd slots are stored as ints[0:1].
    // Remaining layout, verified against allocations from stock gralloc:
    // [4] usage, [5:6] width/height, [7] format, [8] bpp,
    // [13] pixel stride, [16] vertical stride. The tail holds private data.
    if (!handle || !bo || handle->numFds != 1 ||
        handle->numInts < 31 || handle->numInts > 33)
      return -EINVAL;
    const int *pi = &handle->data[handle->numFds];
    if (pi[0] != -1 || pi[1] != -1 ||
        pi[5] <= 0 || pi[5] >= 8192 || pi[6] <= 0 || pi[6] >= 8192 ||
        pi[13] < pi[5] || pi[13] >= 8192 || pi[16] < pi[6] ||
        handle->data[0] < 0 || (pi[8] != 16 && pi[8] != 32))
      return -EINVAL;

    // Match the IMG importer: reject compression/layout bits beyond 0x10f.
    // SPRD XFBC does not decode IMG FBCDC. Unsupported buffers must go
    // through GPU client composition into the raw framebuffer target.
    if (pi[7] & ~0x10f)
      return -EINVAL;

    const uint32_t hal_format = pi[7] & 0xf;
    uint32_t format = ConvertHalFormatToDrm(hal_format);
    if (format == DRM_FORMAT_INVALID)
      return -EINVAL;
    if ((pi[8] == 16) != (hal_format == HAL_PIXEL_FORMAT_RGB_565))
      return -EINVAL;

    bo->width = pi[5];
    bo->height = pi[6];
    bo->hal_format = hal_format;
    bo->usage = pi[4];
    bo->prime_fds[0] = handle->data[0];
    bo->pitches[0] = pi[13] * (pi[8] >> 3);
    bo->offsets[0] = 0;
    // A libdrm handle cast reads IMG bpp+flags as 0x198000000020.
    // There is no DRM modifier field at that location in this ABI.
    bo->modifiers[0] = DRM_FORMAT_MOD_LINEAR;
    bo->format = format;
    return 0;
  }
};

LEGACY_BUFFER_INFO_GETTER(BufferInfoQin);

}  // namespace android
