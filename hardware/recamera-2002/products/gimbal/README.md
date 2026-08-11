# reCamera Gimbal 2002w hardware

English | [简体中文](README-CN.md)

[![reCamera Gimbal 2002w](images/product.jpg)](https://www.seeedstudio.com/reCamera-Gimbal-2002w-64GB-p-6403.html)

Gimbal is the motion-enabled form of the first-generation reCamera 2002w. Its
two brushless motors provide 360° yaw and 180° pitch, while the B401 base board
uses CAN to connect the camera and motor system.

| Item | Hardware |
| --- | --- |
| Camera stack | [C1-2002w](../../core/c1-2002/) + [S101 OV5647](../../sensors/s101-ov5647/) |
| Gimbal base | [B401 CAN](../../base/b401-can/) |
| Motor interface | CAN; official specification lists up to 1Mbps |
| Motion | 360° yaw, 180° pitch |
| Power | 12V DC jack to XT30 through the dedicated power board |
| Mechanical source | [STEP/3MF files](mechanical/) |
| Power-board source | [KiCad and schematic files](power-board/PCB/) |

Only hardware design resources are stored here. Motor utilities, binaries,
firmware, Node-RED flows, and control examples remain outside this repository's
scope.

- [Buy reCamera Gimbal 2002w](https://www.seeedstudio.com/reCamera-Gimbal-2002w-64GB-p-6403.html)
- [Official hardware Wiki](https://wiki.seeedstudio.com/recamera_gimbal_hardware_and_specs/)
