# Contributing

English | [简体中文](CONTRIBUTING-CN.md)

## Scope

This repository accepts hardware documentation and design resources for:

- reCamera 2002 / 2002w and compatible modular hardware.
- reCamera Pro and approved integrated hardware resources.

Application code, firmware images, Node-RED flows, AI models, datasets, and
software demos belong in their dedicated repositories and will not be accepted
here.

## Directory rules

- Put SG2002 platform resources under `hardware/recamera-2002/`.
- Put RV1126B reCamera Pro resources under `hardware/recamera-pro/`.
- Keep PCB sources, mechanical sources, and board-local images beside the board
  they document.
- Each hardware directory must state the product/board name, revision, source
  status, and whether it is shipped hardware, an optional module, or a reference
  design.

## Pull-request checklist

1. Cite the official Seeed product page, Wiki page, or approved engineering
   release and record the date checked.
2. Keep English and Simplified Chinese index documents synchronized.
3. Verify every relative Markdown link.
4. For manufacturing data, include editable sources when approved and identify
   the exact board revision. Do not present an engineering prototype as a
   currently shipped revision.
5. Do not commit generated exports when an editable source already exists,
   editor metadata, credentials, or unrelated binary archives.

Before commercial manufacture, independently validate the BOM, PCB stack-up,
DRC, thermal design, power integrity, isolation, regulatory requirements, and
the revision marking on the physical product.
