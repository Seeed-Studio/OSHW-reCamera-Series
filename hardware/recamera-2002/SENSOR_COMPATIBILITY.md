# SG2002 sensor-driver compatibility

This is a driver-level snapshot for the C1 SG2002 core board. It does not mean
that every sensor is electrically compatible with the reCamera board-to-board
connector or available as a finished Seeed module.

Last repository review: **2026-08-04**

| Vendor group | Supported driver identifiers |
| --- | --- |
| GalaxyCore / IMGDS / Nextchip / PICO / SOI | `gcore_gc2053`, `gcore_gc2053_slave`, `gcore_gc2053_1L`, `gcore_gc2083`, `gcore_gc2093`, `gcore_gc2093_slave`, `gcore_gc4653`, `gcore_gc4653_slave`, `gcore_gc2145`, `gcore_gc4023`, `gcore_gc1054`, `imgds_mis2008`, `nextchip_n5`, `nextchip_n6`, `pico_384`, `pico_640`, `soi_f23`, `soi_f35`, `soi_f35_slave`, `soi_h65`, `soi_f37p`, `soi_k06`, `soi_q03`, `soi_q03p` |
| OmniVision / Pixelplus / Techpoint / Lontium | `ov_os02d10`, `ov_os02d10_slave`, `ov_os02k10_slave`, `ov_os04c10`, `ov_os04c10_slave`, `ov_os08a20`, `ov_os08a20_slave`, `ov_os04a10`, `ov_ov4689`, `ov_ov5647`, `ov_ov7251`, `pixelplus_pr2020`, `pixelplus_pr2100`, `techpoint_tp2850`, `techpoint_tp2863`, `techpoint_tp2825`, `lontium_lt6911` |
| Sony | `sony_imx290_2L`, `sony_imx307`, `sony_imx307_slave`, `sony_imx307_2L`, `sony_imx307_sublvds`, `sony_imx327`, `sony_imx327_slave`, `sony_imx327_2L`, `sony_imx327_sublvds`, `sony_imx334`, `sony_imx335`, `sony_imx347`, `sony_imx385`, `sony_imx327_fpga` |
| SmartSens | `sms_sc035hgs`, `sms_sc200ai`, `sms_sc401ai`, `sms_sc850sl`, `sms_sc3335`, `sms_sc3335_slave`, `sms_sc3336`, `sms_sc4210`, `sms_sc8238`, `sms_sc5336_2L`, `sms_sc501ai_2L`, `sms_sc301iot`, `sms_sc500ai`, `sms_sc035gs`, `sms_sc035gs_1L`, `sms_sc1346_1L`, `sms_sc1346_1L_slave`, `sms_sc2331_1L`, `sms_sc2335`, `sms_sc2336`, `sms_sc2336p`, `sms_sc4336`, `sms_sc4336p`, `sms_sc3332` |

The standard Basic product ships with the **S101 OV5647** module. This
repository also contains module-level material for GC2053.
For the current kernel configuration and driver source, consult the maintained
[reCamera-OS repository](https://github.com/Seeed-Studio/reCamera-OS).
