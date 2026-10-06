# Qin 2 Pro (qin2pro) — LineageOS 19.1 device tree

Unofficial LineageOS 19.1 bring-up for the DuoQin Qin 2 Pro
(`s9863a1h10`, Unisoc SC9863A "SharkL3", 2 GB RAM, 1440x576 display).

## Sources

* Kernel: Motorola `kernel-sprd`, branch `R-11-release-RONS`
  (Linux 4.14.199, includes SPRD BSP with `sp9863a-1h10` board support).
  Lives at `kernel/sprd/qin2pro` in the LOS tree.
* Vendor: proprietary blobs extracted from the stock Android 9 firmware
  (`s9863a1h10_Natv-user-gms_SHARKL3_9863A_9.pac`), unpacked with the
  custom `pac_table2.py`/`pac_extract*.py` tools in the build workspace.
* Stock layout: **system-as-root** (boot.img contains only the kernel),
  separate `dtb`/`dtbo` partitions whose blobs are merged by the stock
  bootloader — so this tree ships a kernel-only boot image and leaves
  dtb/dtbo/vendor partitions untouched.

## Notes

* `vendor` (A9, VNDK 28) runs under the A12 platform with
  `PRODUCT_ENFORCE_VINTF_MANIFEST_OVERRIDE=false` and a permissive
  SELinux cmdline flag for bring-up.
* Data is f2fs, fallback ext4; cache/prodnv ext4.
* Lunch target: `lineage_qin2pro-userdebug`.
