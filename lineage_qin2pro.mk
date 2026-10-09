#
# Copyright (C) 2026 The LineageOS Project
#
# SPDX-License-Identifier: Apache-2.0
#

# Bring-up build: expose the Android system over USB as soon as init reaches
# the USB setup, without waiting for a Settings toggle or RSA authorization.
# This must be set before vendor/lineage common products are inherited so the
# common.mk ADB policy also selects ro.adb.secure=0.
WITH_ADB_INSECURE := true

$(call inherit-product, $(SRC_TARGET_DIR)/product/core_64_bit.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/full_base_telephony.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/product_launched_with_p.mk)

# 1GB RAM device: Android Go defaults (low_ram, InProcessNetworkStack,
# speed-profile system server, minimized debug info)
$(call inherit-product, build/target/product/go_defaults.mk)

# Inherit device configuration
$(call inherit-product, device/qin/qin2pro/device.mk)

# Inherit from the vendor tree
$(call inherit-product, vendor/qin/qin2pro/qin2pro-vendor.mk)

# Inherit LineageOS common phone stuff
$(call inherit-product, vendor/lineage/config/common_full_phone.mk)

# System-side diagnostic ADB.  The vendor USB rc already has an adb-only
# configfs path; these properties make init select it at boot.  service.adb.root
# keeps the debug adbd at uid 0 so logcat/pstore can be collected directly.
PRODUCT_SYSTEM_DEFAULT_PROPERTIES += \
    ro.debuggable=1 \
    ro.adb.secure=0 \
    persist.sys.usb.config=adb \
    service.adb.root=1 \
    ro.hardware.egl=POWERVR_ROGUE

## Device identifier
PRODUCT_NAME := lineage_qin2pro
PRODUCT_DEVICE := qin2pro
PRODUCT_BRAND := Qin
PRODUCT_MODEL := Qin 2 Pro
PRODUCT_MANUFACTURER := DuoQin

PRODUCT_BUILD_PROP_OVERRIDES += \
    TARGET_DEVICE=s9863a1h10 \
    PRODUCT_NAME=s9863a1h10_Natv \
    PRIVATE_BUILD_DESC="s9863a1h10_Natv-user 9 PPR1.180610.011 251 release-keys"

# Property overrides for build fingerprint consistency
PRODUCT_BUILD_PROP_OVERRIDES += \
    BUILD_FINGERPRINT="Qin/s9863a1h10_Natv/s9863a1h10:9/PPR1.180610.011/251:user/release-keys" \
    NEXT_BUILD_FINGERPRINT="Qin/s9863a1h10_Natv/s9863a1h10:9/PPR1.180610.011/251:user/release-keys"

PRODUCT_GMS_CLIENTID_BASE := android-duoqin
