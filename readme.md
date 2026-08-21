# Seeed Studio reCamera Hardware

English | [简体中文](README-CN.md)

![reCamera Pro](assets/recamera_series.jpg)

This repository is the hardware documentation and design-resource hub for the
Seeed Studio reCamera product matrix:

- **reCamera 2002 / 2002w** (SG2002), a modular platform.
- **reCamera Pro** (RV1126B), a higher-performance integrated platform.

reCamera 2002 / 2002w and reCamera Pro are concurrently sold product families
for different application and performance requirements. This repository does
not describe them as replacement generations.

## Product matrix

| | reCamera 2002 / 2002w | reCamera Pro |
| --- | --- | --- |
| Processor | Sophgo SG2002 | Rockchip RV1126B |
| CPU | Dual C906 RISC-V cores | Quad-core Cortex-A53 at 1.2GHz |
| AI acceleration | 1 TOPS INT8 | 3 TOPS NPU |
| Memory | 256MB | 2GB / 4GB LPDDR4 |
| Standard camera | OV5647, 5MP | SC850SL, 8MP, 4K at 30fps |
| Hardware model | Interchangeable core, sensor, and base boards | Integrated camera with expansion interfaces |
| Documentation | [reCamera 2002 hardware](hardware/recamera-2002/) | [reCamera Pro hardware](hardware/recamera-pro/) |

### reCamera 2002 / 2002w

| Standard reCamera 2002 | reCamera 2002 HQ PoE | reCamera Gimbal 2002w |
| --- | --- | --- |
| [![reCamera 2002w](hardware/recamera-2002/images/recamera-2002w.jpg)](https://www.seeedstudio.com/reCamera-2002-64GB-p-6252.html) | [![reCamera 2002 HQ PoE](hardware/recamera-2002/products/hq-poe/images/product.jpg)](https://www.seeedstudio.com/reCamera-2002-HQ-PoE-64GB-p-6557.html) | [![reCamera Gimbal 2002w](hardware/recamera-2002/products/gimbal/images/product.jpg)](https://www.seeedstudio.com/reCamera-Gimbal-2002w-64GB-p-6403.html) |
| Fixed camera; B101 base | GC2053 sensor; Ethernet and PoE | Two-axis brushless gimbal; B401 CAN base |

The repository contains editable KiCad sources, schematic PDFs, mechanical
files, and revision notes for the C1 core, S-series sensor boards, B-series base
boards, and Gimbal mechanical/power hardware. See the
[reCamera 2002 / 2002w product index](hardware/recamera-2002/products/).

### reCamera Pro

[![reCamera Pro](hardware/recamera-pro/images/product-hero.png)](https://www.seeedstudio.com/reCamera-Pro-2GB.html)

[Buy reCamera Pro 2GB from Seeed Studio](https://www.seeedstudio.com/reCamera-Pro-2GB.html)

The repository currently provides an official-specification snapshot, polished
storefront product images, and technical interface images for reCamera Pro. Editable Pro PCB and
mechanical source files should be added only when an approved hardware release
is available.

## Repository layout

```text
.
|-- hardware/
|   |-- recamera-2002/       # reCamera 2002 family board and mechanical sources
|   `-- recamera-pro/        # reCamera Pro family specifications and images
|-- docs/                    # Official sources and maintenance policy
|-- .github/workflows/       # Repository administration
|-- CONTRIBUTING.md
`-- LICENSE
```

## Scope

This is a **pure hardware repository**. 
If you need to access software-related repositories, please visit the official website.
[reCamera document](https://wiki.seeedstudio.com/recamera/)Obtain these resources from the Seeed Studio software repository.

Gimbal and HQ PoE are product forms within the reCamera 2002 family. Their
product-specific hardware is documented under `hardware/recamera-2002/products/`
and linked to shared boards.

## Source of truth

Hardware summaries are reviewed against official Seeed Studio product and Wiki
pages. See [docs/OFFICIAL_SOURCES.md](docs/OFFICIAL_SOURCES.md) for the source
list and review date. A currently shipped product page takes precedence over a
repository snapshot when specifications or available configurations change.

Contributions must follow [CONTRIBUTING.md](CONTRIBUTING.md). Unless a file says
otherwise, repository content is provided under the [Apache License 2.0](LICENSE).
