# Qin Marlin2 protocol compatibility

Apply `0001-marlin2-protocol-compatibility.patch` to the separate
`wcn_mod` checkout at commit `ac29360` (branch `qin2pro-marlin2`).
This replaces the earlier scan-only patch; do not apply both. It is
not an Android platform patch handled by `patches/apply.py`.

Use `git apply --check` then `git apply` on an unmodified base checkout.
The working checkout already contains these changes. Build against the
prepared Qin 4.14 kernel output and its matching Module.symvers:

```sh
export PATH="$LOS_ROOT/prebuilts/gcc/linux-x86/aarch64/aarch64-linux-android-4.9/bin:$PATH"
export ARCH=arm64 CROSS_COMPILE=aarch64-linux-android-
export BSP_BOARD_WLAN_DEVICE=marlin3_sipc
export BSP_BOARD_UNISOC_WCN_SOCKET=sipc
export BSP_MODULES_OUT="$LOS_ROOT/wcn_mod"
cd "$LOS_ROOT/wcn_mod/wlan"
make -C "$LOS_ROOT/kernel/sprd/qin2pro/out" M="$PWD" modules KCFLAGS="-Wno-error"
```

Copy `sprdwl_ng.ko` to the vendor repository's
`proprietary/vendor/lib/modules/sprdwl_ng.ko`, then rebuild systemimage.
The verified prebuilt SHA256 is `1bd85b0ac74fd8f83b73490dc92b0d94cfc41678c054332a5fb498aed8329b2a`.

Firmware/stock-module analysis established these Marlin2 differences:

- SCAN: ten-byte prefix and SSIDs, without the Marlin3 5 GHz tail.
- No SAE or random-scan command support; do not advertise those features.
- Extended Capabilities IE 127: probe/association payload cannot exceed
  seven bytes (firmware host_config.c:2573, function 0x3439c). Shorten this
  IE and its wire length while preserving all other IEs, including RSN.
- OPEN: use fixed interface modes (STA=1, P2P device=4), not dynamic
  contexts opened at zero. Accept replies/events for the full mode range.
- DATA: inline Ethernet in swcnblk channel 8 (STA/AP) or 9 (P2P), not
  Marlin3 command 72 or MSDU address descriptors. The wire has a 32-byte
  transport reserve, an 8-byte data header, 2-byte alignment, a separate
  32-byte data headroom, then Ethernet. Both reserves are required.
- KEY: eight sequence bytes; prefix including subcommand is 19 bytes.
  Marlin3's 16-byte field shifts cipher and key material by eight bytes.
- GET_STATION: eight bytes. LLSTAT: packed 89 bytes, one-byte signed RSSI
  and 17-byte AC entries. Convert explicitly; do not invent an RX rate.

Live verification on 2026-10-09: directed scan, WPA2/CCMP four-way
handshake, DHCP, gateway/public ping, 1500-byte IP packets, DNS and
verified HTTPS all passed against the user's authorized 2.4 GHz AP.
The same final module is installed on the phone and in the vendor tree.
Transient TX reserve switches, wildcard overrides and packet tracing
were removed. This is STA WPA2 validation; SAE, hotspot and P2P data
operation have not been validated. See the workspace connectivity report
for logs and the separate Android Google-probe reachability issue.

This verification used the current eng/permissive diagnostic installation.
The final target remains userdebug/enforcing. Full `m selinux_policy`
passes after correcting unused WCN labels; enforcing device regression
and a complete newly built system image are still required.
