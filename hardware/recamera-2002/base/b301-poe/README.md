# B301 PoE base-board reference design

B301 adds Ethernet data and PoE-powered operation for an SG2002 reCamera. The
files here are an open-hardware **reference design** and must not be assumed to
be electrically or mechanically identical to every shipped reCamera HQ PoE
revision.

Editable KiCad sources are in [PCB](PCB/), enclosure files are in
[3D_Printed_Case](3D_Printed_Case/), and design images are in [static](static/).

> [!CAUTION]
> PoE input design involves safety, thermal, isolation, surge, and compliance
> requirements. Review the actual PSE/PD class, component ratings, isolation
> boundaries, heat dissipation, and IEEE 802.3 requirements before building.
> The powered reCamera endpoint is the **PD**; do not describe it as a PSE.

For a commercial reCamera HQ PoE product, follow its dedicated
[official quick-start guide](https://wiki.seeedstudio.com/recamera_hq_poe_getting_started/).
