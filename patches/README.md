# Qin platform patches

Run `python3 device/qin/qin2pro/patches/apply.py --dry-run` from the LOS root
to validate the patch series. Run without `--dry-run` to apply it. Already
applied patches are skipped. All checks finish before any patch is applied.

The series records the platform changes used by the tested LOS19.1 build:

- frameworks/native: optional mapper 3/4 probes and the old Surface constructor
  symbol required by the stock IMS JNI library.
- frameworks/base: let explicit `persist.sysui.strictmode=false` disable
  SystemUI's eng flashing diagnostics.
- frameworks/av: stop audio HAL version iteration at the null sentinel.
- hardware/interfaces: stock audio V4_0 HidlUtils ABI shim with the P-layout
  audio_config write, refresh asynchronously registered Wi-Fi interfaces,
  guard Bluetooth close after failed initialization, and avoid fatal startup
  when a GateKeeper HAL cannot be opened.
- system/security: keep keystore2 services available without hardware KeyMint.

The GateKeeper guard returns ERROR_NOT_IMPLEMENTED when no HAL exists; it
does not implement password verification. Software gatekeeper is packaged
separately. Hardware TEE/KeyMint remains unavailable on this bring-up.

No external/drm_hwcomposer patch is required for the Qin module. The tested
module builds display/BufferInfoQin.cpp with upstream drm_hwcomposer instead
of the older BufferInfoLibdrm experiment.
