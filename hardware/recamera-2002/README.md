# reCamera 2002 / 2002w hardware

English | [简体中文](README-CN.md)

The reCamera 2002 / 2002w platform is built from three interchangeable layers:
a C1 core board, an S-series sensor board, and a B-series base board.

![reCamera 2002w](images/recamera-2002w.jpg)

## Currently sold product forms

| Product form | Key hardware difference | Product documentation |
| --- | --- | --- |
| reCamera 2002 / 2002w | Fixed camera using S101 and B101 | [Standard camera](products/#standard-recamera-2002--2002w) |
| reCamera 2002 HQ PoE | S401 GC2053, M12 lens, B301 Ethernet/PoE base | [HQ PoE](products/hq-poe/) |
| reCamera Gimbal 2002w | S101, B401 CAN base, two-axis brushless gimbal and power board | [Gimbal](products/gimbal/) |

These are three product forms within the same SG2002-based reCamera 2002 family.

## Standard fixed-camera configurations

| Product | Core | eMMC | Wireless | Sensor | Base |
| --- | --- | ---: | --- | --- | --- |
| reCamera 2002 8GB | C1-2002 | 8GB | No | S101 OV5647 | B101 |
| reCamera 2002 64GB | C1-2002 | 64GB | No | S101 OV5647 | B101 |
| reCamera 2002w 8GB | C1-2002w | 8GB | Wi-Fi / Bluetooth | S101 OV5647 | B101 |
| reCamera 2002w 64GB | C1-2002w | 64GB | Wi-Fi / Bluetooth | S101 OV5647 | B101 |

## Hardware resources

| Layer | Board | Status | Directory |
| --- | --- | --- | --- |
| Core | C1-2002 / C1-2002w | Standard shipped core | [core/c1-2002](core/c1-2002/) |
| Sensor | S101 OV5647 | Standard shipped sensor | [sensors/s101-ov5647](sensors/s101-ov5647/) |
| Sensor | S201 IMX335 | Optional/documented module; verify availability | Design files not present in this repository |
| Sensor | S301 SC130GS | Optional/documented module; verify availability | Design files not present in this repository |
| Sensor | S401 GC2053 | Used by HQ/PoE variants | [sensors/s401-gc2053](sensors/s401-gc2053/) |
| Base | B101 | Standard shipped base | [base/b101-default](base/b101-default/) |
| Base | B201 vertical USB-C | Reference/prototype design | [base/b201-vertical-usb-c](base/b201-vertical-usb-c/) |
| Base | B301 PoE | Reference design; verify against commercial revision | [base/b301-poe](base/b301-poe/) |
| Base | B401 CAN | Gimbal CAN base; source files use earlier B4 naming | [base/b401-can](base/b401-can/) |

See [SENSOR_COMPATIBILITY.md](SENSOR_COMPATIBILITY.md) for the SG2002
driver-level sensor snapshot. Driver presence does not guarantee a purchasable
module or electrical compatibility with the reCamera connector.

## File conventions

- `PCB/`: editable KiCad sources and approved original archives.
- `3D_Printed_Case/`: STEP, STL, or 3MF mechanical files.
- `static/` or `statics/`: board diagrams and schematic PDFs.

Confirm the physical board revision before using these files for repair or
manufacture.
