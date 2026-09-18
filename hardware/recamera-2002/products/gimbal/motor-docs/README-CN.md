# 云台电机协议资料

[English](README.md) | 简体中文

本目录保存 reCamera Gimbal 2002w 硬件集成所需的第三方电机接口资料。

## CAN 协议 V2.36

- 文件：[CAN_Protocol_DescriptionV2.36.pdf](CAN_Protocol_DescriptionV2.36.pdf)
- 文档标题：*Motor CAN bus communication protocol V2.36*
- 文档标识：K TECH / Shanghai Yikong Technology
- 适用范围：供应商 MS/MF/MH/MG 系列电机驱动协议；reCamera Gimbal 使用的 MS 系列无刷电机包括 MS3008 和 MS3506

文档包含 CAN 标识符、波特率、电机状态与错误帧、启停命令、转矩/速度/位置
控制、编码器校准、PID 参数和电机参数持久化等内容。它作为供应商参考资料保存，
不应表述为 Seeed Studio 自行定义的 CAN 协议。

PDF 自带供应商版权和使用声明。应保持原文件不变；如需在本仓库之外再次发布，
请先确认相应的再分发授权。
