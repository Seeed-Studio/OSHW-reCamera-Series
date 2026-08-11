# C1-2002 / C1-2002w 核心板

[English](README.md) | 简体中文

C1 核心板采用 Sophgo SG2002 SoC，配有 256MB 内存和 8GB 或 64GB eMMC，是 reCamera 2002 基础版系列的计算核心。

## 版本

| 版本 | 无线器件配置 |
| --- | --- |
| C1-2002 | 不安装无线模块；向底板提供额外 SDIO/UART 信号 |
| C1-2002w | Wi-Fi/蓝牙模块、板载天线和 I-PEX 连接器 |

两个版本源自相同的 PCB 设计。不能根据存储容量判断无线支持，是否带无线功能由 `w` 后缀区分。

## 资源

- [原理图 PDF](static/reCamera_Core_2002w_8GB_v1.2_SCH_PDF_241014.pdf)
- [板对板连接器示意图](static/BTB_Connector.png)
- 机械文件位于 [3D_Printed_Case](3D_Printed_Case/)。

提供的原理图属于文件名中注明的历史版本。维修或制造前，请先确认实物板卡版本。
