# Seeed Studio reCamera 硬件资料库

[English](README.md) | 简体中文

![reCamera Pro](assets\recamera_series.jpg)

本仓库是 Seeed Studio reCamera 产品矩阵的硬件说明与设计资料中心：

- **reCamera 2002 / 2002w**（SG2002）：基于 SG2002 模块化平台。
- **reCamera Pro**（RV1126B）：基于 RV1126B 高性能平台。
reCamera 2002 / 2002w 与 reCamera Pro 是面向不同应用和性能需求、持续并行
销售的产品系列；这里不使用代际或替代关系描述它们。

## 产品矩阵

| | reCamera 2002 / 2002w | reCamera Pro |
| --- | --- | --- |
| 处理器 | Sophgo SG2002 | Rockchip RV1126B |
| CPU | 双 C906 RISC-V 核心 | 1.2GHz 四核 Cortex-A53 |
| AI 算力 | 1 TOPS INT8 | 3 TOPS NPU |
| 内存 | 256MB | 2GB / 4GB LPDDR4 |
| 标准摄像头 | OV5647，5MP | SC850SL，8MP，4K@30fps |
| 硬件形态 | 可互换核心板、传感器板和底板 | 集成式摄像头与扩展接口 |
| 资料入口 | [reCamera 2002 硬件](hardware/recamera-2002/) | [reCamera Pro 硬件](hardware/recamera-pro/) |

### reCamera 2002 / 2002w

| 标准版 reCamera 2002 | reCamera 2002 HQ PoE | reCamera Gimbal 2002w |
| --- | --- | --- |
| [![reCamera 2002w](hardware/recamera-2002/images/recamera-2002w.jpg)](https://www.seeedstudio.com/reCamera-2002-64GB-p-6252.html) | [![reCamera 2002 HQ PoE](hardware/recamera-2002/products/hq-poe/images/product.jpg)](https://www.seeedstudio.com/reCamera-2002-HQ-PoE-64GB-p-6557.html) | [![reCamera Gimbal 2002w](hardware/recamera-2002/products/gimbal/images/product.jpg)](https://www.seeedstudio.com/reCamera-Gimbal-2002w-64GB-p-6403.html) |
| 固定式摄像头；B101 底板 | GC2053 传感器；以太网与 PoE | 双轴无刷云台；B401 CAN 底板 |

仓库保留 C1 核心板、S 系列传感器板和 B 系列底板的 KiCad 源文件、
原理图 PDF、机械文件和版本说明，并恢复云台机械结构与电源板硬件资料。详见
[reCamera 2002 / 2002w 在售产品索引](hardware/recamera-2002/products/)。

### reCamera Pro

[![reCamera Pro](hardware/recamera-pro/images/product-hero.png)](https://www.seeedstudio.com/reCamera-Pro-2GB.html)

[前往 Seeed Studio 购买 reCamera Pro 2GB](https://www.seeedstudio.com/reCamera-Pro-2GB.html)

仓库当前保留 reCamera Pro 官方硬件规格快照、商城产品展示图和技术接口图。只有在
可公开的硬件版本获得批准后，才应添加 Pro PCB 或机械源文件。

## 仓库结构

```text
.
|-- hardware/
|   |-- recamera-2002/       # reCamera 2002 系列板卡与机械源文件
|   `-- recamera-pro/        # reCamera Pro 系列规格与官方图片
|-- docs/                    # 官方信息源与维护规范
|-- .github/workflows/       # 仓库管理
|-- CONTRIBUTING.md
`-- LICENSE
```

## 范围

这是一个**纯硬件仓库**，如果需要访问软件相关仓库，请从官方
[reCamera 文档](https://wiki.seeedstudio.com/cn/recamera/)和 Seeed Studio 软件仓库获取这些资源。

Gimbal 与 HQ PoE 是 reCamera 2002 系列的产品形态。它们的专用硬件归入
`hardware/recamera-2002/products/`，并关联共用板卡资料。

## 信息优先级

硬件摘要依据 Seeed Studio 官方产品页和 Wiki 维护。详见
[docs/OFFICIAL_SOURCES-CN.md](docs/OFFICIAL_SOURCES-CN.md)。当规格或销售配置变化时，
当前在售产品页优先于仓库快照。

贡献前请阅读 [CONTRIBUTING-CN.md](CONTRIBUTING-CN.md)。除非文件另有说明，本仓库内容
按 [Apache License 2.0](LICENSE) 提供。
