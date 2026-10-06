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

# The recovery image rule copies recovery.fstab to /system/etc/recovery.fstab
# and recovery/root into the ramdisk. /etc is a symlink to /system/etc.

# Treble / VINTF: A9 vendor under A12 platform, do not enforce manifest
PRODUCT_ENFORCE_VINTF_MANIFEST_OVERRIDE := false
PRODUCT_COMPATIBLE_PROPERTY_OVERRIDE := true

# Audio: configuration comes from vendor
USE_XML_AUDIO_POLICY_CONF := 1

# Skip images we do not ship (stock vendor/product/dtb/dtbo are kept)
PRODUCT_BUILD_SUPER_PARTITION := false
