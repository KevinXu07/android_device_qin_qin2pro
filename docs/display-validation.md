# Display validation, 2026-10-09

The tested build is lineage_qin2pro-eng with Linux 4.14.199. A complete
system update through stock recovery44 was verified by reading back the
system partition hash, then normal reboot reached boot_completed=1.

The user exercised desktop, notification shade and Settings and confirmed
that dynamic corruption, wallpaper shrinking, washed-out colors and the
red diagnostic border had all disappeared. GE8322 hardware rendering and
normal mixed composition remain active. The active DRM plane is LINEAR,
AB24, 576 x 1440, pitch 2304; HWC failed commit count was zero.

## Artifact SHA256

| Artifact | SHA256 |
| --- | --- |
| sparse system.img | 9f8d7832b1ee40b9926945ae0871a6756ed171dee96edba62470d15803c99275 |
| raw system / flashed partition | f677d29e5f801c7fd760ac9496b58066686f1e0550e15d63a14a2d18f58f4ccc |
| boot v100 | 72a8d52e492b4a3f5d57e637f227ad39c07bfd1deb04c183ee2ff1b4dfc37949 |
| hwcomposer.sp9863a 64-bit | 9ec9e4376e04a5cc78c94f6b689cc797d466484ea0773d194ffe3009332b266e |
| hwcomposer.sp9863a 32-bit | f47a10f4b3b9fefe1a5fd3aea854e2580d43ebdd9652b7ab278fbae7781bc287 |
| SystemUI.apk | 114d533a8f020e69fec956ce994c958dc6bc8e5a8be9f93d67ba3428d932293e |

Sparse system size is 1923301992 bytes, raw is 3145728000 bytes and boot is
36700160 bytes. Decode sparse before dd. Preserve stock recovery44.

## Diagnosis and remaining anomaly

The original 0x198000000020 modifier report was an incorrect handle cast
reading IMG bpp=32 and flags=0x1980. Compression was established separately
by a gralloc allocation comparison: application format 0x1101 changed to
0x101 when DisableFBCDC was enabled. A CPU-written linear color/checkerboard
scanout was also confirmed clean on the physical display.

Before the final image, restarting SurfaceFlinger exposed a bufferpool32
library cache page zeroed at file offset 0x22000. The on-disk image and source
file were correct; dropping caches immediately restored the correct file
hash. Its cause is unresolved. The final normal boot has the correct hash,
which does not prove this latent issue fixed. Avoid repeated SurfaceFlinger
restarts; switch the live composition debug flag with `service call
SurfaceFlinger 1008 i32 1` and restore with `1008 i32 0` when needed.
