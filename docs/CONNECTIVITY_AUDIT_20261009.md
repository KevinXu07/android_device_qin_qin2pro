# Qin 2 Pro LOS19.1：Wi-Fi、蓝牙、手电筒和相机复核

日期：2026-10-09。最新状态以本文件及 AGENTS.md 末节为准。取证目录：`E:\code\qin2pro\work\connectivity-audit-20261009`。本文不保存测试网络密码。

> 中午后续修复：Wi-Fi 已通过 WPA2、DHCP、DNS、公网 ping、HTTPS 和关闭/开启后的自动重连。完整 selinux_policy 构建检查已通过。请以本文末节“Wi-Fi 连接修复实测”覆盖此前的失败状态；蓝牙冷启动、真实手电筒驱动、相机及 enforcing 实机回归仍待完成。

## 当前设备与结论

用户已通过监控确认禁用错误 OCP 节点后的屏幕正常。当前设备仍使用 #125 diagnostic boot、原 eng system、全局 permissive；本轮只更新 Wi-Fi 库/模块及蓝牙初始化属性，没有换成 userdebug/enforcing，也没有改 system/recovery 分区布局。最终目标继续保持 userdebug + enforcing。

| 功能 | 上一个 agent 的成果 | 本轮复核 |
| --- | --- | --- |
| Wi-Fi | shim、接口重新枚举、配置文件修正已在手机上 | 模块自动加载及 Marlin2 协议修正已实装；WPA2、DHCP、DNS、HTTPS、自动重连通过，详见末节 |
| 蓝牙 | INI 双路径和设备节点权限已存在 | 原配置开机第一次会 HCI 超时，stock HAL close 崩溃后重试 ON。本轮延长初始化等待，首次启用 ON、崩溃 0 次；开机自动启用复测另记 |
| 手电筒 | 新增了 OCP8137 驱动 | 硬件对象错误。真实启用的是 AW3641/WD3124DA；未移植真实驱动、没有 flashlight LED 节点，仍不可用 |
| 相机 | stock HAL/blob 已打包 | `dumpsys media.camera` 为 0 个相机，缺少 DCAM/CSI/ISP/sensor 驱动及相应设备节点，仍不可用 |

## Wi-Fi 自动加载修正（已验证）

设备树原先没有 `WIFI_DRIVER_MODULE_PATH/NAME`。AOSP `wifi_load_driver` 因条件编译成为空操作，服务随后调用 SPRD blob 的 `wifi_wait_for_driver_ready`，只会轮询不存在的 wlan0。wcn.rc 又取消了 insmod，造成双方都没有加载模块。shim 修复 NULL 回调与本问题是不同层。

已在 `device/qin/qin2pro/BoardConfig.mk` 固化：

```make
WIFI_DRIVER_MODULE_PATH := /vendor/lib/modules/sprdwl_ng.ko
WIFI_DRIVER_MODULE_NAME := sprdwl_ng
WIFI_DRIVER_FW_PATH_PARAM := /data/vendor/wifi/fwpath
WIFI_DRIVER_FW_PATH_STA := sta_mode
WIFI_DRIVER_FW_PATH_AP := ap_mode
WIFI_DRIVER_FW_PATH_P2P := p2p_mode
```

`m libwifi-hal` 编译成功，新 32/64 位库已装到手机。先关闭 Wi-Fi、停 HAL、成功卸载模块，再只启动 HAL/开启 Wi-Fi，模块自动加载、wlan0 UP、driver.status=ok、扫描出真实 AP；正常重启日志也证明 DriverTool 自动插入模块。保留单一加载者，wcn.rc 不要再加重复 insmod。

64 位新 libwifi-hal.so SHA256：`04c0945bd5904ff627dc45f1f941936673f03d615e5a6bc301356ab1ab4951c9`。

## 用户授权热点连接：未通过，新的确定证据

测试 SSID 为 `バンドリ！`，BSSID 20:3a:eb:e9:37:10、信道 8、RSSI 约 -54 dBm，WPA2/WPA3 transition。密码只通过连接命令提供，没有写入本文件或设备源码。每轮失败后已忘记测试配置，避免开机自动连接导致 CP 再次断言。

1. 原模块：Android 把 WPA2 自动升级成 SAE。连接触发定向扫描后约 50ms，CP 报 `WCN Assert in host_config.c line 2573, 0`。后续 CMD11/CMD25 超时是固件断言的后果；不是 DHCP 或密码认证失败。
2. 对照原厂 4.4 模块反汇编，SCAN 的报文是 10 字节头加 SSID 列表（随机 MAC 开启时另加 6B MAC）。移植模块错误附加 Marlin3 5GHz 尾字段。已去掉此字段，并停止声明无法实现的 SAE/random-scan 能力。新日志确认 KeyMgmt 变为 WPA_PSK，但定向扫描仍断言，故不能把去尾字段认作完整修复。
3. 临时只把 SSID 过滤列表清空做对照：普通扫描成功，supplicant 进入 Trying to associate，CMD10 CONNECT 获得响应，约 100ms 后 CP 在同一位置断言。表明问题还涉及后续连接兼容性，而不只是扫描参数。
4. 原厂模块 DWARF 证明 CONNECT 的长度确为 82B，成员偏移与当前结构一致；不能凭猜测缩短 CONNECT 报文。

尚未达到关联成功，未获取 DHCP 地址，未做互联网验证。**上一个 agent 的“Wi-Fi 全链打通”只能解释为扫描链通过。** 需继续对照原厂命令/事件、管理帧、crypto/AKM 与 CP 协议。

最终源码已经移除临时 wildcard 覆盖与 QINSCN 报文打印，保留真实扫描协议/能力修正。外置模块源码在 `/home/kevin/los/wcn_mod`，补丁副本和编译说明保存在设备树 `patches/wcn_mod/`，不属于 `patches/apply.py` 的 Android 平台系列。新模块已同步 vendor prebuilt，SHA256：`444b8994d94d9176e854a8b223acd8d56cb4a7ba813345240a84fd616b9d279a`。

关键证据：`logcat-connect.txt`、`logcat-connect-scan-test.txt`、`dmesg-connect-wildcard.txt`、`stock-wifi-protocol.asm`、`stock-protocol-types.txt`。

## 蓝牙初始化时序

原手机第一次开机 HCI 超时，随后 stock `android.hardware.bluetooth@1.0-impl-unisoc.so` 的 close 路径 SIGABRT；框架重试后 ON。上一个 agent 对 AOSP bluetooth_hci.cc 的 close 空指针保护并不改变实际运行的 stock -unisoc 库。

`system/bt/hci/src/hci_layer.cc` 默认 `DEFAULT_STARTUP_TIMEOUT_MS=2900`，支持 `bluetooth.enable_timeout_ms` 覆盖。实测成功初始化从 hci_module_start_up 到 event_finish_startup 为 **3.574s**（其中 HIDL getService 约 2s、WCN 固件约 1.5s），已超过默认值。

已固化到设备树 device.mk：`PRODUCT_SYSTEM_PROPERTIES += bluetooth.enable_timeout_ms=90000`，只延长初始化，不改变普通 HCI 命令超时。适配历史上较慢的 Marlin2 固件冷启动。手动在新启动的设备上设置后第一次启用蓝牙即 ON、崩溃 0 次；曾将属性写入当前测试 system 的 build.prop 做开机复测。

`m out/target/product/qin2pro/system/build.prop` 编译通过并确认包含该属性。但本次自动启用复测遇到 zygote 的 `ANDROID_DATA environment variable unset` 崩溃循环，没有 system_server，不能计为蓝牙开机验证通过。已保存完整日志并恢复修改前 build.prop 做单变量复查，随后重新达到 boot_completed=1、zygote running、bootanim stopped。属性本身与环境导入的因果关系尚未确认，不要把这个启动失败归因于 HCI。

当前手机 build.prop 已恢复原份，超时属性仅再次通过 setprop 临时设置为 90000；设备树的 PRODUCT_SYSTEM_PROPERTIES 和编译出的 userdebug build.prop 保留此修正。**完整新镜像的冷启动验证仍待进行，当前旧 eng system 的反复手改试验不能代替这一步。** 环境失败日志在 `logcat-bt-timeout-coldboot.txt`、`dmesg-bt-timeout-coldboot.txt`，恢复后的检查在 `rollback-latest.txt`。

早前 classic startDiscovery 返回 true，扫描结束仍 ON，但本轮没有发现附近设备。**配对、数据传输、A2DP 音频均未验证。** stock HAL 失败后的 close 健壮性问题仍存在，延长等待只能避免本次初始化过早超时。

关键证据：`bluetooth-coldboot-tombstone.txt`、`bt-timeout-probe-events.txt`、`dmesg-bt-extended-timeout.txt`、`bt-discovery.txt`。

## Enforcing 策略检查

自动加载模块的实测日志有 `hal_wifi_default -> vendor_file:system module_load` 拒绝，当前因为 permissive 没有拦住。已在源码用 vendor_kernel_modules 标签标记 sprdwl_ng.ko，并只为该标签授权读取/加载，补 sys_module 能力。fwpath 使用单独 qin_wifi_fwpath_file 类型授权读写。BoardConfig 里的旧 permissive/user cmdline 也已修正为 enforcing 与 TARGET_BUILD_VARIANT。

本轮 `m sepolicy_neverallows sepolicy vendor_file_contexts` 编译通过。**完整 `m selinux_policy` 没有通过**：原有 `/data/misc/wcn` 和 `/data/wcn` 的 sprd_data_file 标签缺少 core_data_file_type，sepolicy_tests 拒绝。这个 type 与标签来自上一个 agent 的策略，不能宣称整体严格策略完成；不能通过禁用检查或放宽 neverallow 掩盖。

当前手机没有安装这份新策略，尚未进行 enforcing 实机回归。v102 老镜像本身还有 su/backuptool permissive 域，最终严格目标需另行落实。

## 源码/镜像与后续注意

- 新设备树、vendor 模块、外置 WCN 源码修改尚未 commit/push；原有 #125 启动修正也仍未 commit/push。
- `flashable-userdebug-v102/system.img` 是旧快照，**不含本轮 Wi-Fi 自动加载/新模块/蓝牙超时修正**；不要拿它刷机后宣称复现了本轮结果。需重编 systemimage。
- 重编之前先处理完整 SELinux 测试的遗留失败；最终应配套已经准备的 enforcing 修正 boot，继续抓真实 AVC。
- 手电筒只可依据 stock 启用的 AW3641/WD3124DA 节点和 GPIO 72/73 设计真实驱动。不要重新启用 OCP，不要在用户不在现场时猜 GPIO 拉高。
- 相机需要完整内核子系统移植；0 个相机不是单补 XML 或拷 HAL 能解决的。

## 本轮结束时的实机状态

最终检查 uptime=313.87s、boot_completed=1、eng/permissive，系统已恢复正常启动。Wi-Fi 开启、自动加载的新库/模块 hash 与源码产物一致，扫描仍能看到授权热点；没有保存网络，不会自动重试失败连接。蓝牙 ON，本次使用原 build.prop 的开机记录仍有首次超时后重试 1 次，不能把这次记录说成“0 崩溃”。当前运行期已临时设置新超时，等待 clean 新镜像验证。最终本次启动 dmesg 未发现 CP fw assert；临时 BT 探针 jar 已移除。

证据文件：`final-runtime.txt`、`bluetooth-final.txt`、`dmesg-final.txt`。手机不是留在启动失败状态。


## Wi-Fi 连接修复实测（2026-10-09 中午，覆盖此前失败结论）

### 根因与修复

用 IDA 分析原厂 4.4 `sprdwl_ng.ko`（有 DWARF）及 Marlin2 固件，逐步对应真实失败位置；本轮不是通过清空 SSID 或忽略错误绕过关联。

1. **host_config.c:2573 的断言**：固件 `sub_3439C`（0x3439c）遍历 Extended Capabilities IE（ID 127），payload 长度大于 7 就跳到 0x34556 的断言（line 0xa0d=2573）。Android12 的 probe/association IE 超过这个上限。`sprdwl_set_ie` 对这两类 IE 验证链条并把该 IE 缩至 7B，更新其长度与命令总长；保留后面的 RSN 等 IE。定向扫描与 CONNECT 随即不再断言。
2. **STA/P2P 地址互相覆盖**：Marlin2 的 OPEN 使用固定 mode，原厂 `sprdwl_init_fw` 把 mode 同时放在 common header 和 payload。移植驱动沿用 Marlin3 的“ctx=0 打开，再从响应申请 ctx”，结果 P2P 覆盖 STA MAC；AP 的 EAPOL 接收地址变成 12:df…，wlan0 为 10:df…，不能进入 supplicant。修正固定 STA=1、P2P-device=4，并放开对应响应/事件的合法 mode 范围，收到握手第 1 步。
3. **发送通路协议不符**：Marlin3 EAPOL/ARP 走 command 72，普通数据走 MSDU/物理地址描述符，Marlin2 均不采用。恢复 inline Ethernet 和内核 **swcnblk**（不是普通 sblock）。原厂 `sprdwl_sipc_msg_send` 在 block 开头留 32B transport reserve；原厂 `sprdwl_sipc_reserv_len` 返回 32，`sprdwl_send_data` 还在 data header/2B alignment 后、Ethernet 前留另一段 32B。完整线格式：**transport 32 + data header 8 + alignment 2 + data headroom 32 + Ethernet**，plen 不含 transport，但含 data headroom。两个 32B 不能混为一个；补齐后完成 2/4、3/4、4/4 握手。临时单改 transport reserve=0 的失败对照已撤掉，源码没有该开关。
4. **KEY 结构错位**：原厂 keyseq 是 8B，含 subcommand 的 KEY 前缀 19B（cipher@17、key_len@18、key@19）。移植驱动用 16B keyseq，固件收到错误 cipher/key，因此四次握手完成后 DHCP 无回复。恢复 8B，并把 cfg80211 的 6B CCMP 序列号安全补零，DHCP OFFER/ACK 随即到达。
5. **信号/速率/统计布局不同**：原厂 GET_STATION 是 8B（rate、signal、noise、reserved、txfailed），不是两个现代 rate_info。LLSTAT 是 packed 89B、RSSI 是 signed 1B、每个 AC 为 17B；此前读出 RSSI=0、RX=6553Mbps 和数亿计数。现按原厂字段转换，恢复约 −53～−55dBm、26～39Mbps 和合理计数；固件没有 RX rate，明确不提供该字段。LLSTAT 按原厂返回累计计数，让 Android 自己取差值。

### 最终模块验证

- 授权热点 `バンドリ！`，2.4GHz 信道8，WPA2-PSK/CCMP：supplicant COMPLETED，四次握手完成，PTK/GTK 安装。
- DHCP：`192.168.5.34/24`，gateway/DNS `192.168.5.1`，租期86400s；OFFER/ACK 有实际日志。
- 最终模块网关 ping 5/5、公网 `1.1.1.1` ping 5/5 均无丢包；1472B payload 的 ICMP（1500B IP、DF）3/3 通过。
- 设备上 curl 使用 wlan0，正常 DNS/TLS 验证请求 `https://www.baidu.com/`，HTTP200、2443B；未使用 `-k`。
- 清理诊断代码并换回最终模块后复测通过，测试期间 BT 同时 ON；没有新的 CP assert。延迟在部分样本中达数百毫秒，尚未做吞吐/长时/休眠压力测试。

### 联网探测与自动重连

Android 的 Google HTTPS generate_204 在当前网络超时（DNS 给出不可用地址），HTTP 探测204、普通 HTTPS能访问，NetworkMonitor 判断 PARTIAL_CONNECTIVITY，并将热点标成 NO_INTERNET_PERMANENT。因此第一次 Wi-Fi 关闭/开启未自动重连，不能误诊成驱动卸载失败。

临时 root Java 工具通过正式 `IConnectivityManager.setAcceptPartialConnectivity(network106,true,true)` 为**这个已验证可上网的授权热点**保存“继续使用”选择，相当于系统提示框里的保持连接。随后关闭/开启 Wi-Fi，未再次发 connect-network，自动关联并拿到相同 DHCP 地址。探针 jar 已从手机移除；没有全局关闭探测或在源码改第三方探测地址。这个网络的接受选择存在 userdata，不随 systemimage 分发。新用户/新热点仍需正常处理 Google 探测可达性或选择保持连接。

### 源码、补丁与严格版构建

外置源码：`/home/kevin/los/wcn_mod/wlan/marlin3_pcie/` 的 cfg80211.c、cmdevt.c/h、main.c、txrx.c、vendor.c。非 SIPC 路径保留原协议；本 Qin SIPC 变体按 Marlin2 工作。移除了 QINTX/transport 测试开关和 wildcard 覆盖。

设备树快照：`patches/wcn_mod/0001-marlin2-protocol-compatibility.patch` **替代**旧 scan-only 文件，适用于 `ac29360`。已在临时干净基线 `git apply --check`、应用补丁后逐字节比对六个源文件，完全一致。不要两个补丁叠加，也不要在已修改的工作目录再次强行应用。

vendor prebuilt、已构建文件与手机 `/vendor/lib/modules/sprdwl_ng.ko` SHA256 一致：`1bd85b0ac74fd8f83b73490dc92b0d94cfc41678c054332a5fb498aed8329b2a`（11948504B）。prebuilt 已同步到 `vendor/qin/qin2pro/proprietary/vendor/lib/modules/`。本轮源码和模块修复由本次提交保存；完整 systemimage 尚未重编，v102 仍是旧快照。

SELinux 的两个旧 `/data/wcn`、`/data/misc/wcn` 目录在本机均不存在，也没有被当前移植配置创建；移除它们错误的 vendor sprd_data_file 标签，保留平台 core-data 默认标签，并把 vendor WCN 命名空间设为 `/data/vendor/wcn`。没有添加 core/vendor violator 或关闭测试。**`lunch lineage_qin2pro-userdebug; m -j8 selinux_policy` 全部成功（37s），含 neverallow、contexts、sepolicy_tests 与 Treble 26～31 检查。** 手机仍用旧 eng/permissive 策略；这只是源码构建检查通过，最终 userdebug/enforcing 镜像及真实 AVC 回归尚未完成。

证据：`firmware-extcap-assert.txt`、`dmesg-extcap-associated.txt`、`handshake-pass-before-key-fix.txt`、`dhcp-key-fixed.txt`、`wifi-final-live.txt`、`https-final.txt`、`ping-*-final.txt`、`wifi-autoreconnect-final.txt`、`wifi-autoreconnect-events.txt`、`build-wifi-policy.log`。IDA 分析用 ELF 包装仅供解析，绝不能刷入设备。

蓝牙仍 ON，冷启动和配对/A2DP未完成。真实 AW3641 手电筒、DCAM/CSI/ISP 相机栈仍未移植；不能把本轮 Wi-Fi 成功当成其余三项全部修好。
