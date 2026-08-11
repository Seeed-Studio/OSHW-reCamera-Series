# SG2002 传感器驱动兼容性

[English](SENSOR_COMPATIBILITY.md) | 简体中文

本页是 C1 SG2002 核心板的驱动层兼容性快照。列出驱动并不表示对应传感器与 reCamera 板对板连接器在电气上兼容，也不表示 Seeed 已提供相应成品模块。

仓库最后核对日期：**2026-08-04**

| 厂商类别 | 支持的驱动标识符 |
| --- | --- |
| GalaxyCore / IMGDS / Nextchip / PICO / SOI | `gcore_gc2053`、`gcore_gc2053_slave`、`gcore_gc2053_1L`、`gcore_gc2083`、`gcore_gc2093`、`gcore_gc2093_slave`、`gcore_gc4653`、`gcore_gc4653_slave`、`gcore_gc2145`、`gcore_gc4023`、`gcore_gc1054`、`imgds_mis2008`、`nextchip_n5`、`nextchip_n6`、`pico_384`、`pico_640`、`soi_f23`、`soi_f35`、`soi_f35_slave`、`soi_h65`、`soi_f37p`、`soi_k06`、`soi_q03`、`soi_q03p` |
| OmniVision / Pixelplus / Techpoint / Lontium | `ov_os02d10`、`ov_os02d10_slave`、`ov_os02k10_slave`、`ov_os04c10`、`ov_os04c10_slave`、`ov_os08a20`、`ov_os08a20_slave`、`ov_os04a10`、`ov_ov4689`、`ov_ov5647`、`ov_ov7251`、`pixelplus_pr2020`、`pixelplus_pr2100`、`techpoint_tp2850`、`techpoint_tp2863`、`techpoint_tp2825`、`lontium_lt6911` |
| Sony | `sony_imx290_2L`、`sony_imx307`、`sony_imx307_slave`、`sony_imx307_2L`、`sony_imx307_sublvds`、`sony_imx327`、`sony_imx327_slave`、`sony_imx327_2L`、`sony_imx327_sublvds`、`sony_imx334`、`sony_imx335`、`sony_imx347`、`sony_imx385`、`sony_imx327_fpga` |
| SmartSens | `sms_sc035hgs`、`sms_sc200ai`、`sms_sc401ai`、`sms_sc850sl`、`sms_sc3335`、`sms_sc3335_slave`、`sms_sc3336`、`sms_sc4210`、`sms_sc8238`、`sms_sc5336_2L`、`sms_sc501ai_2L`、`sms_sc301iot`、`sms_sc500ai`、`sms_sc035gs`、`sms_sc035gs_1L`、`sms_sc1346_1L`、`sms_sc1346_1L_slave`、`sms_sc2331_1L`、`sms_sc2335`、`sms_sc2336`、`sms_sc2336p`、`sms_sc4336`、`sms_sc4336p`、`sms_sc3332` |

标准基础版产品随附 **S101 OV5647** 模块。本仓库还提供 GC2053 的模块级资料。当前内核配置和驱动源码请以持续维护的 [reCamera-OS 仓库](https://github.com/Seeed-Studio/reCamera-OS)为准。
