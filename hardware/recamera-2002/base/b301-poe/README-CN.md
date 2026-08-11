# B301 PoE 底板参考设计

[English](README.md) | 简体中文

B301 为 SG2002 reCamera 增加以太网数据传输和 PoE 供电。本目录文件属于开源硬件**参考设计**，不能假定其电气和机械结构与所有出货的 reCamera HQ PoE 版本完全相同。

可编辑 KiCad 源文件位于 [PCB](PCB/)，外壳文件位于 [3D_Printed_Case](3D_Printed_Case/)，设计图片位于 [static](static/)。

> [!CAUTION]
> PoE 输入设计涉及安全、热管理、隔离、浪涌和合规要求。制造前须检查实际 PSE/PD 等级、器件额定值、隔离边界、散热和 IEEE 802.3 要求。接受供电的 reCamera 端是 **PD**，不应将其称为 PSE。

使用商业版 reCamera HQ PoE 产品时，请遵循其专用的[官方快速入门指南](https://wiki.seeedstudio.com/recamera_hq_poe_getting_started/)。
