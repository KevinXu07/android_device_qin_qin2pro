# Qin 2 Pro LineageOS 19.1 device tree

Unofficial bring-up for DuoQin Qin 2 Pro (`s9863a1h10`, Unisoc SC9863A,
PowerVR Rogue GE8322, 576 x 1440 panel). The tested build on 2026-10-09 is
`lineage_qin2pro-eng` with the diagnostic boot. The final build target is
`lineage_qin2pro-userdebug` with SELinux enforcing; its device regression
remains pending.

## Sources and build

Place the repositories in a LineageOS 19.1 checkout:

| Repository | Checkout path | Branch |
| --- | --- | --- |
| [Device](https://github.com/KevinXu07/android_device_qin_qin2pro) | device/qin/qin2pro | lineage-19.1 |
| [Vendor](https://github.com/KevinXu07/android_vendor_qin_qin2pro) | vendor/qin/qin2pro | lineage-19.1 |
| [Kernel](https://github.com/KevinXu07/android_kernel_qin_qin2pro) | kernel/sprd/qin2pro | qin2pro-bringup |

Apply the platform patch series before building:

```sh
python3 device/qin/qin2pro/patches/apply.py --dry-run
python3 device/qin/qin2pro/patches/apply.py
source build/envsetup.sh
lunch lineage_qin2pro-eng
m systemimage
```

See [patches/README.md](patches/README.md) for the platform ABI and startup
fixes. The kernel is a 4.14.199 SPRD port. The tested boot packaging uses
header version 1, an embedded board DTB, no ramdisk and AVB signing.
Keep the original 4.4.147 recovery44 as the recovery channel.

## Image layout

This build uses merged system-as-root: `/vendor` points to `/system/vendor`
and `/product` points to `/system/product`. Vendor COPY targets must be
`system/vendor/...` to enter system.img; neither symlink belongs in the
first-stage fstab. Data is f2fs. VINTF enforcement is disabled for bring-up.
Source boot arguments select SELinux enforcing. The phone still uses the
previous eng/permissive installation for isolated hardware tests.

## Display fixes verified on the device

- `display/BufferInfoQin.cpp` builds 32/64-bit hwcomposer.sp9863a using the
  actual IMG gralloc handle ABI, real pixel stride and LINEAR scanout.
- `configs/powervr.ini` disables FBCDC application allocations; IMG FBCDC
  cannot be decoded by the SPRD DPU's XFBC engine.
- `vendor.hwc.drm.scale_with_gpu=1` routes scaled layers to GPU composition
  because DPU r2p0 has no per-plane scaler.
- `ro.surface_flinger.use_color_management=false` avoids the washed-out
  output observed with the legacy IMG EGL/dataspace path.
- StrictMode properties and the SystemUI patch disable the red diagnostic
  border while retaining the eng default for other builds when unset.

The complete system image was flashed through recovery44 and its entire
partition SHA256 checked. After normal reboot: boot_completed=1, ADB root,
GE8322 GLES, normal mixed composition and audio services were verified. The
user confirmed that dynamic corruption, wallpaper shrinking, washed-out
colors and red borders had all disappeared. See
[docs/display-validation.md](docs/display-validation.md) for artifact hashes
and the unresolved SurfaceFlinger warm-restart cache anomaly.

## Other bring-up status

Touch and hardware keys work. Audio uses the stock primary and patched
stock V4.0 impl with the audio ABI compatibility shim. Wi-Fi now passes directed scans, WPA2/CCMP, DHCP, DNS, public ping,
HTTPS and reconnect after toggling Wi-Fi. The external Marlin2 driver patch
is in [patches/wcn_mod](patches/wcn_mod/README.md); the vendor module matches
the tested build. Bluetooth is ON with an extended HCI startup timeout;
clean-image cold boot, pairing and A2DP remain unverified. Software gatekeeper, health HAL and the keystore2
fallback keep the framework booting without hardware TEE/KeyMint.
Camera/ISP support, modem calls and remaining platform features are WIP.

`rootdir/` starts ADB, loads pvrsrvkm, cancels the kernel boot watchdog once
SurfaceFlinger runs and records rolling startup logs. Only AOSP configfs rc
binds the ADB-only gadget, avoiding competing root/vendor handlers.

## Latest regression and connectivity results

- [Connectivity audit](docs/CONNECTIVITY_AUDIT_20261009.md): firmware/stock
  protocol evidence, Wi-Fi validation, Bluetooth limitations and full
  userdebug `selinux_policy` build success. The latest section supersedes
  the earlier failed connection attempts.
- [Boot regression](docs/GPU_BOOT_REGRESSION_20261009.md): stock-disabled
  OCP8137 must stay disabled. The maintained DTS preserves display/WCN
  corrections and is compiled without rerunning the old BSP generator.

The actual AW3641/WD3124DA torch driver and camera kernel stack are still
missing. A complete new system image and enforcing device tests remain
required; successful policy compilation alone is not runtime validation.
