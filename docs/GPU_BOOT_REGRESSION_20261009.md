# Qin 2 Pro 启动竖条纹回归核查（2026-10-09）

最终构建目标仍为 **userdebug + SELinux enforcing**。本轮没有把最终配置改回 permissive。

## 手机实际安装内容

手机由用户手动进入原厂 recovery44，先通过 adb root 只读取证。随后用户选择只刷测试 boot 做单变量验证；system 未写入，原厂 recovery 未写入。

- boot 分区完整 SHA256：`2d04756e3170a0d383bbb5a3b670bddf7584ef2e90f7859592db47eb6f836a51`，与 v101 完全一致。
- 内核版本 #123，Image SHA256：`964eafd42e7e11a29181a0a2aa3a5ef7caf885785ca5a717bbad5fef00002b6f`。
- boot header 与内核嵌入 DT 的 SELinux 参数均为 **permissive**。
- system/build.prop 仍是 `ro.build.type=eng` / `lineage_qin2pro-eng`。
- 新 v102 userdebug/enforcing 配套镜像尚未安装。因此不能把本次冻结归因于 userdebug 或 enforcing。
- v100、v101 嵌入 DTB 完全一致。v101 新增了内核内置手电筒驱动。
- userdata 的 kmsg_boot、qin-gpu-boot.log 等均来自之前正常的 #122 / v100 启动；pstore 只有极少 recovery 内容。尚无本次失败启动的有效内核日志。

## 已确认的硬件配置错误

从原厂 recovery 正在使用的 `/sys/firmware/fdt` 提取原厂 DTB，并读取原厂 GPIO 占用记录：

- `/soc/ap-apb/i2c@70900000/flash-ic@63`：OCP8137，**原厂 status="disabled"**。
- 原厂实际启用的是根节点 `/aw3641@0`，flash IC="3641"，compatible="sprd,flash-wd3124da"，使用 AP GPIO 72（torch）和 73（flash）。
- 原厂 GPIO 76 是音量下键输入，原厂运行时 debugfs 显示 `Volume Down Key in hi`。
- 移植的 BSP OCP8137 节点缺少 status 属性，默认成为启用状态，配置 AP GPIO 88/89/76/141。
- v100 无 OCP8137 驱动，错误节点没有驱动响应；v101 添加 `CONFIG_QIN_FLASH_TORCH=y` 和 qin_flash.c，probe 会请求这四根线作为输出并拉低，而且没有验证 IC 是否实际存在。

因此，先前交接资料的“本机手电筒是 OCP8137”判断需要纠正。新驱动会操作本机另一组 GPIO，这是确定的硬件配置错误。后续单变量启动恢复成功，支持它是 v101 的启动回归点。**没有证据证明这些 GPIO 直接连接 LCD，也尚未确定错误电平造成停滞的具体硬件机制。**

GPIO 数字这里指 AP GPIO 控制器内偏移。4.14 的 Linux 全局 GPIO 基号与原厂不同，不能用动态编号（例如 281）推断板级连线。

## 源码修正

1. 恢复 OCP8137 `status="disabled"`，与原厂 DT 一致。没有将 AW3641 错套到 OCP 驱动；真实手电筒移植需单独处理。
2. kernel repo 的 qin2pro-dtb/merged-qin414.dts 同步到当前实际打包的完整 DTS。原快照落后于已验证的配置，缺少显示 PHY 参数、WCN 控制值及 WLAN 保留内存等修正。
3. make_dtb.py 改为编译已维护的 merged-qin414.dts，支持 Windows / WSL。旧 BSP 转换脚本保留为 make_dtb_legacy.py，仅作历史参考；不要使用它覆盖最新完整 DTS。
4. qin2pro-dtb/merged-qin414.dtb 与 arch/arm64/kernel/qin2pro_merged.dtb 更新为 enforcing 修正版。
5. 每次更新嵌入 DTB，仍需移除 out/arch/arm64/kernel/qin2pro_embedded_dtb.o 后重新编 Image。构建脚本使用 set -euo pipefail，不再用 tail 管道掩盖 make 失败。

以上源码变更尚未 commit/push。

## 已生成并验证的 boot

目录：`E:\code\qin2pro\work\gpu-userdebug-regression-20261009\`。

| 文件 | 用途 | SHA256 |
|---|---|---|
| boot-flash-fixed-diagnostic/boot.img | 与手机当前 v101 保持相同 SELinux/boot 参数，DT 仅新增 OCP disabled，用于隔离因果；不作为最终发布配置 | 43a76aa410fa9bf2192f13149096ac0ef67e637caa3804d062246353b4bf05bb |
| boot-flash-fixed-enforcing/boot.img | 配合 userdebug system 使用，保留 enforcing | 454d81448ecaf7c8564ec14ba4b5757dd6050149711cca27748ee905016839a7 |

- 两次内核构建成功；模块 ABI module_layout CRC 保持 0x26ae0566。
- 两个 boot 均 header_version=1、无 ramdisk、36,700,160 字节。
- avbtool verify_image 验证签名、footer、boot hash 全部通过。
- 解析 Image 中的真实嵌入 FDT 后，按节点/属性对照：diagnostic 相对 v101、enforcing 相对 v102，均仅新增 OCP 节点 status；bootargs 及显示/WCN/内存布局属性均不变。
- 新 make_dtb.py 从 repo 的完整 DTS 编译输出，与实际 enforcing 内核嵌入 DTB SHA256 一致：`c011c675cc9fd871bed41838797c71e089cac6230edce700ef6a691003ff6094`。

## 配套 userdebug system 检查

只读 debugfs 检查 `LOS19.1-输出/flashable-userdebug-v102/system.img`：

- ro.build.type=userdebug，scale_with_gpu=1，use_color_management=false，DisableFBCDC=1，StrictMode 红框配置关闭。
- HWC64 SHA256 为 `9ec9e4376e04a5cc78c94f6b689cc797d466484ea0773d194ffe3009332b266e`，与之前实机正常显示的版本一致。
- fstab 无 vendor/product 软链挂载项。
- sepolicy-analyze permissive 的结果为 `su`、`backuptool`。这份镜像可用于全局 enforcing 调试，但不能称作“零 permissive 域”的最终严格版本。需继续审查并验证策略，不能只看 bootargs。

## 待做

- 用户已选择只刷测试 boot。完整写入并确认 boot 分区 hash 为 `43a76aa410fa9bf2192f13149096ac0ef67e637caa3804d062246353b4bf05bb`；misc 的 command/status 原为空，无需改写。只读挂载已卸载，手机已重启。
- **测试成功**：新内核 #125、ADB root、sys.boot_completed=1、SurfaceFlinger running、PowerVR Rogue GE8322；截图显示正常锁屏。45 秒内未枚举 ADB，随后在约两分钟内观察到系统已完整启动。
- 从三个 Image 中提取 IKCONFIG：v100→v101 唯一配置差异为新增 CONFIG_QIN_FLASH_TORCH=y；v101→本次测试的配置完全相同。测试内核的运行时 OCP 节点 status=disabled，驱动目录无 I2C 设备绑定、无 flashlight LED 节点。
- 本次真实日志保存为 test-dmesg.txt、test-logcat.txt，截图为 test-screen.png；本次日志中未查到 kernel panic、DPU update timeout 或压缩 header/payload error。用户随后通过监控确认屏幕正常，未在现场做动态操作测试。
- 当前手机仍是测试用的原 eng/permissive 组合；enforcing 修正 boot 已准备，需配套 userdebug system 后实机验证。尚未执行这一步。
- enforcing 实机阶段应按具体 AVC 修正标签/权限，保持 neverallow 检查；不要以全局 permissive 或无边界 allow 代替修复。
- 更换完整 system 需用可靠的非 RAM 暂存或分块传输；3 GB raw 镜像不能直接 push 到本机的 RAM /tmp。

取证文件、原 boot 备份、原厂 DT/GPIO、构建日志、语义比较脚本均保存在同一目录及 work/ 下。
