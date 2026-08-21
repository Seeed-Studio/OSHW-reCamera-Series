# reCamera 2002 / 2002w 硬件

[English](README.md) | 简体中文

reCamera 2002 / 2002w 平台由三层可互换模块组成：C1 核心板、S 系列传感器板与
B 系列底板。

![reCamera 2002w](images/recamera-2002w.jpg)

## 当前在售产品形态

| 产品形态 | 主要硬件差异 | 产品说明 |
| --- | --- | --- |
| reCamera 2002 / 2002w | 使用 S101 与 B101 的固定式摄像头 | [标准版](products/#standard-recamera-2002--2002w) |
| reCamera 2002 HQ PoE | S401 GC2053、M12 镜头、B301 以太网/PoE 底板 | [HQ PoE](products/hq-poe/) |
| reCamera Gimbal 2002w | S101、B401 CAN 底板、双轴无刷云台与电源板 | [Gimbal](products/gimbal/) |

三者都是基于 SG2002 的 reCamera 2002 系列产品形态。

## 标准固定式摄像头配置

| 产品 | 核心板 | eMMC | 无线 | 传感器 | 底板 |
| --- | --- | ---: | --- | --- | --- |
| reCamera 2002 8GB | C1-2002 | 8GB | 无 | S101 OV5647 | B101 |
| reCamera 2002 64GB | C1-2002 | 64GB | 无 | S101 OV5647 | B101 |
| reCamera 2002w 8GB | C1-2002w | 8GB | Wi-Fi / 蓝牙 | S101 OV5647 | B101 |
| reCamera 2002w 64GB | C1-2002w | 64GB | Wi-Fi / 蓝牙 | S101 OV5647 | B101 |

## 硬件资料

| 层级 | 板卡 | 状态 | 目录 |
| --- | --- | --- | --- |
| 核心板 | C1-2002 / C1-2002w | 标准出货核心板 | [core/c1-2002](core/c1-2002/) |
| 传感器 | S101 OV5647 | 标准出货传感器 | [sensors/s101-ov5647](sensors/s101-ov5647/) |
| 传感器 | S201 IMX335 | 可选/已记录模块；请确认供货 | 本仓库暂无设计文件 |
| 传感器 | S301 SC130GS | 可选/已记录模块；请确认供货 | 本仓库暂无设计文件 |
| 传感器 | S401 GC2053 | 用于 HQ/PoE 变体 | [sensors/s401-gc2053](sensors/s401-gc2053/) |
| 底板 | B101 | 标准出货底板 | [base/b101-default](base/b101-default/) |
| 底板 | B201 垂直 USB-C | 参考/原型设计 | [base/b201-vertical-usb-c](base/b201-vertical-usb-c/) |
| 底板 | B301 PoE | 参考设计；需与商用版本核对 | [base/b301-poe](base/b301-poe/) |
| 底板 | B401 CAN | 云台 CAN 底板；源文件沿用早期 B4 命名 | [base/b401-can](base/b401-can/) |

SG2002 驱动层传感器快照见 [SENSOR_COMPATIBILITY-CN.md](SENSOR_COMPATIBILITY-CN.md)。
存在驱动不代表一定有可购买模块，也不代表一定与 reCamera 板对板接口电气兼容。

## 文件约定

- `PCB/`：可编辑 KiCad 源文件和已批准的原始压缩包。
- `3D_Printed_Case/`：STEP、STL 或 3MF 机械文件。
- `static/` 或 `statics/`：板卡示意图和原理图 PDF。

用于维修或制造前，请先确认实物板卡版本。
