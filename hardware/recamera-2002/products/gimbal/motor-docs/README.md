# Gimbal motor protocol documents

English | [简体中文](README-CN.md)

This directory contains third-party motor interface documentation required for
the reCamera Gimbal 2002w hardware.

## CAN protocol V2.36

- File: [CAN_Protocol_DescriptionV2.36.pdf](CAN_Protocol_DescriptionV2.36.pdf)
- Document title: *Motor CAN bus communication protocol V2.36*
- Document branding: K TECH / Shanghai Yikong Technology
- Applies to: the supplier's MS/MF/MH/MG motor-drive protocol; reCamera Gimbal
  uses MS-series brushless motors, including MS3008 and MS3506
- Repository provenance: originally added in commit `c9b9ed0` on 2025-04-01

The document describes CAN identifiers, baud rates, motor status and error
frames, start/stop commands, torque/speed/position control, encoder calibration,
PID parameters, and persistent motor settings. It is provided as a supplier
reference and must not be presented as a CAN protocol designed by Seeed Studio.

The PDF contains its own supplier copyright and usage notice. Preserve the
original document unchanged and confirm redistribution authorization before any
external republication outside this repository.
