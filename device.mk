# WiFi
PRODUCT_PACKAGES +=     wpa_supplicant     wpa_cli     hostapd     libwpa_client     android.hardware.wifi@1.0-service     libhidltransport     libhidltransport.vendor

#
# Copyright (C) 2026 The LineageOS Project
#
# SPDX-License-Identifier: Apache-2.0
#

DEVICE_PATH := device/qin/qin2pro

# Keep this product debug-only even when a caller chooses a user lunch target.
# lineage_qin2pro.mk also sets it before inheriting Lineage's common product
# rules, which disables RSA authorization in the generated system properties.
WITH_ADB_INSECURE := true

# No fingerprint sensor on this device
PRODUCT_PACKAGES -= \
    android.hardware.biometrics.fingerprint@2.1-service

# First-stage fstab (system-as-root, read from /system/etc/fstab.$(TARGET_BOOTLOADER_BOARD_NAME))
PRODUCT_COPY_FILES += \
    $(DEVICE_PATH)/fstab.s9863a1h10:$(TARGET_COPY_OUT_SYSTEM)/etc/fstab.s9863a1h10

# Device overlays (navbar enable for gesture navigation)
PRODUCT_PACKAGE_OVERLAYS += $(DEVICE_PATH)/overlay

# The recovery image rule copies recovery.fstab to /system/etc/recovery.fstab
# and recovery/root into the ramdisk. /etc is a symlink to /system/etc.

# Treble / VINTF: A9 vendor under A12 platform, do not enforce manifest
PRODUCT_ENFORCE_VINTF_MANIFEST_OVERRIDE := false
DEVICE_MANIFEST_FILE += vendor/qin/qin2pro/proprietary/vendor/etc/vintf/manifest.xml
DEVICE_MATRIX_FILE += vendor/qin/qin2pro/proprietary/vendor/etc/vintf/compatibility_matrix.xml
PRODUCT_COMPATIBLE_PROPERTY_OVERRIDE := true

# Audio: configuration comes from vendor
USE_XML_AUDIO_POLICY_CONF := 1

# Skip images we do not ship (stock vendor/product/dtb/dtbo are kept)
PRODUCT_BUILD_SUPER_PARTITION := false

# Qin2Pro WIP: replacement HAL services validated on device (stock vendor impls
# crash under A12). Software gatekeeper + AOSP health 2.1 keep locksettings and
# BatteryService alive; audio impl/effect/libeffects blobs in the vendor tree
# have been replaced with AOSP builds (same install paths).
PRODUCT_PACKAGES +=     android.hardware.gatekeeper@1.0-service.software     android.hardware.health@2.1-service     android.hardware.health@2.1-impl     android.hardware.cas@1.2-service     android.hardware.radio.deprecated@1.0

# 32-bit vendor variants of the HIDL/base libs needed by the stock 32-bit
# audio service + audio.primary.sp9863a (prebuilt binaries carry no dep info,
# so every NEEDED entry must be requested explicitly).
PRODUCT_PACKAGES += \
    android.hardware.audio@2.0.vendor \
    android.hardware.audio@4.0.vendor \
    android.hardware.audio.common@2.0.vendor \
    android.hardware.audio.common@4.0.vendor \
    android.hardware.audio.common-util.vendor \
    android.hardware.audio.common@2.0-util.vendor \
    android.hardware.audio.common@4.0-util.vendor \
    android.hardware.audio@4.0-util.vendor \
    android.hardware.audio.effect@2.0.vendor \
    android.hardware.audio.effect@4.0.vendor \
    android.hardware.audio.effect@4.0-util.vendor \
    android.hardware.bluetooth.a2dp@1.0.vendor \
    android.hardware.soundtrigger@2.0.vendor \
    android.hardware.soundtrigger@2.1.vendor \
    android.hidl.allocator@1.0.vendor \
    android.hidl.memory@1.0.vendor \
    android.hardware.power@1.0.vendor \
    android.hardware.power@1.1.vendor \
    android.hardware.power@1.2.vendor \
    libaudioutils.vendor \
    libbase.vendor \
    libbinder.vendor \
    libc++.vendor \
    libcutils.vendor \
    libexpat.vendor \
    libfmq.vendor \
    libhardware.vendor \
    libhardware_legacy.vendor \
    libhidlbase.vendor \
    libhidlmemory.vendor \
    libhwbinder.vendor \
    liblog.vendor \
    libmedia_helper.vendor \
    libtinyalsa.vendor \
    libutils.vendor

# Init scripts: device init at root (auto-imported as /init.<ro.hardware>.rc),
# watchdog/PVR helper rc under /system/etc/init (top-level only is scanned).
PRODUCT_COPY_FILES +=     $(DEVICE_PATH)/rootdir/init.s9863a1h10.rc:$(TARGET_COPY_OUT_ROOT)/init.s9863a1h10.rc     $(DEVICE_PATH)/rootdir/qin_wd.rc:$(TARGET_COPY_OUT_SYSTEM)/etc/init/qin_wd.rc

# Consumer IR blaster (vendor IR HAL is registered); without this feature XML
# system_server dies in ConsumerIrService.
PRODUCT_COPY_FILES +=     $(DEVICE_PATH)/configs/android.hardware.consumerir.xml:$(TARGET_COPY_OUT_SYSTEM)/etc/permissions/android.hardware.consumerir.xml

# DRM HWC with the stock IMG handle ABI; SPRD DPU cannot decode IMG FBCDC.
PRODUCT_PACKAGES += hwcomposer.sp9863a
PRODUCT_COPY_FILES += \
    $(DEVICE_PATH)/configs/powervr.ini:$(TARGET_COPY_OUT_SYSTEM)/vendor/etc/powervr.ini

# DPU r2p0 programs layer size from src_w/src_h and has no per-plane scaler.
# Let the existing drm_hwcomposer scaling policy send scaled layers to GPU.
PRODUCT_VENDOR_PROPERTIES += vendor.hwc.drm.scale_with_gpu=1

# Retain startup logs across boots during display bring-up.
PRODUCT_COPY_FILES += \
    $(DEVICE_PATH)/rootdir/qin_gpu_debug.rc:$(TARGET_COPY_OUT_SYSTEM)/etc/init/qin_gpu_debug.rc

# Legacy IMG EGL labels app buffers as linear; A12 color conversion washes
# out GPU composition. Validated by comparing mixed and all-client output.
PRODUCT_SYSTEM_PROPERTIES += \
    ro.surface_flinger.use_color_management=false \
    persist.sysui.strictmode=false
