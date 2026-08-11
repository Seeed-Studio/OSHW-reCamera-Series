# C1-2002 / C1-2002w core board

The C1 core board uses the Sophgo SG2002 SoC with 256MB memory and 8GB or
64GB eMMC. It is the compute board in the reCamera 2002 Basic series.

## Variants

| Variant | Wireless population |
| --- | --- |
| C1-2002 | No wireless module; exposes additional SDIO/UART signals to the base |
| C1-2002w | Wi-Fi/Bluetooth module, onboard antenna, and I-PEX connector |

Both variants originate from the same PCB design. Do not infer wireless support
from storage capacity; the `w` suffix identifies the wireless version.

## Resources

- [Schematic PDF](static/reCamera_Core_2002w_8GB_v1.2_SCH_PDF_241014.pdf)
- [Board-to-board connector diagram](static/BTB_Connector.png)
- Mechanical files are in [3D_Printed_Case](3D_Printed_Case/).

The supplied schematic is a named historical revision. Confirm the fitted
board revision before using it for repair or manufacturing.
