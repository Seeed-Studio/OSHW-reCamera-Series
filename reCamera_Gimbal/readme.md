# 🎨 reCamera Gimbal Programmable Development Kit 

## 🔥Introduction
Welcome to the reCamera Gimbal Programmable Development Kit. This kit provides resources and tools for developers to control and customize the reCamera Gimbal. It includes sample code for debugging gimbal motor operations and status outputs, offering program entry points to drive the gimbal motor using CAN for precise control and functionality.

<img src="static/reCamera-Gimbal-3.png" alt="reCamera" style="width: 80%;" />

## Table of Contents

- [🔩 Pre-requisite](#-pre-requisite)
- [🪢 Gimbal Dashboard Preview with Node-RED ](#-gimbal-dashboard-preview-with-node-red)
- [⚙️ Hardware Overview](#-hardware-overview)
- [💡 Custom Development](#-custom-development)
- [🔥 Gimbal STP](#-gimbal-stp)
- [📀 Flash motors firmware](#-flash-motors-firmware)


## 🔩 Pre-requisite
- reCamera OS 0.2.0
- 12V 2A power supply
- USB Type-C cable

## 🪢 Gimbal Dashboard Preview with Node-RED
![alt text](./static/gimbal_dashboard_preview.png)

Gimbal Node-REd Dashboard includes camera preview, model confidence/IoU Settings, gimbal manual control, object auto-tracking and shortcut buttons such as sleep, standby, calibration and Emergency Stop. The PID settings are also included for fine-tuning as each device is self-assembled.

You can see how to deploy json flow on Node-RED [here](https://github.com/jby5122/OSHW-reCamera-Series/tree/main/Node-RED_Flow#%EF%B8%8F-how-to-deploy-dashboard-flow). 

- View [Gimbal Dashboard V1.0.json](./src/Dashboard/Gimbal_DashboardV1.0.json) (PID settings are also included)
- View [Motor_PID_Config.json](./src/Dashboard/Motor_PID_Config.json) (Individual PID settings for each motor in case you want to add this to your own flow)


## Hardware Overview

To enable the reCamera to drive the gimbal motor, the reCamera's base board needs to be replaced to [B4_CAN](https://github.com/Seeed-Studio/OSHW-reCamera-Series/tree/main/reCamera_Base_Board/B4_CAN) to enable CAN communication.

Up             |  Bottom
:-------------------------:|:-------------------------:
![Up](./static/Gimbal_font.png)  |  ![Bottom](./static/Gimbal_back.png)


You can use the Debugging Port connections to control the motor and communicate with the reCamera via the upper monitor. Alternatively, you can control the motor directly through the reCamera.



| **Processing System**                |                                                         |                                                         |
| ------------------------------------ | ------------------------------------------------------- | ------------------------------------------------------- |
| SOC                                  | SG2002                                                  |                                                         |
| CPU                                  | C906@1GHZ + C906@700MHz                                 |                                                         |
| AI Performance                       | 1 Tops @ Int8                                           |                                                         |
| MCU                                  | 8051 @ 8KB SRAM                                         |                                                         |
| Operating System                     | Linux                                                   |                                                         |
| Memory                               | 256 MB                                                  |                                                         |
| Video Encoder                        | 5MP @ 30Fps                                             |                                                         |
| **Basic**                            |                                                         |                                                         |
| Camera Sensor                        | OV5647                                                  |                                                         |
| eMMC                                 | 8GB / 64GB                                              |                                                         |
| Power Supply                         | 12-24V DC Jack to XT30 connector                        |                                                         |
| Power Consumption(static)            | 12V,185mA; 24V,150mA                                    |                                                         |
| **Interface**                        |                                                         |                                                         |
| USB                                  | USB 2.0 Type-C                                          |                                                         |
| Wireless                             | Wi-Fi 2.4G/5G Bluetooth 4.2/5.0                         |                                                         |
| Button                               | 1 x Reboot Button, 1 x User Button                      |                                                         |
| Fill LEDs                            | 4 x 0.3w White Light                                    |                                                         |
| LED                                  | 1 x Power Indicator, 2 x IO programmable indicator      |                                                         |
| Mic                                  | On-Board Mic                                            |                                                         |
| Speaker                              | External Speaker                                        |                                                         |
| **Motor Spec**                       | MS3008                                                  | MS3506                                                  |
| Turns                                | 54                                                      | 60                                                      |
| Rated Voltage(V)                     | 12                                                      | 12                                                      |
| Max Speed(rpm)                       | 2000                                                    | 2100                                                    |
| Rated Torque(N.m)                    | 0.04                                                    | 0.05                                                    |
| Rated Speed(rpm)                     | 1160                                                    | 1250                                                    |
| Rated Current(A)                     | 0.64                                                    | 0.79                                                    |
| Max Power(W)                         | 4.6                                                     | 6.4                                                     |
| Motor Poles                          | 14                                                      | 14                                                      |
| Operating temperature (℃)            | -25~60                                                  | -25~60                                                  |
| Motor Weight(g)                      | 49                                                      | 63                                                      |
| Drive Input Voltage (V)              | 6~16                                                    | 6~16                                                    |
| Communication                        | CAN                                                     | CAN                                                     |
| Communication Frequency (Hz)         | CAN@1Mbps:2KHz                                          | CAN@1Mbps:2KHz                                          |
| Encoder                              | 15 bit Magnetic Encoder                                 | 15 bit Magnetic Encoder                                 |
| CAN Baut Rate                        | 100K、125K、250K、500K、1M                              | 100K、125K、250K、500K、1M                              |
| Control Mode                         | Open Loop(24KHz) /Speed Loop(4KHz) /Position Loop(2KHz) | Open Loop(24KHz) /Speed Loop(4KHz) /Position Loop(2KHz) |
| **Ambient Conditions**               |                                                         |                                                         |
| Operating Temperature                | -20～50 ℃                                               |                                                         |
| Operating Humidity                   | 0～90%                                                  |                                                         |
| **Others**                           |                                                         |                                                         |
| Heat Dissipation                     | Fanless                                                 |                                                         |
| Warranty                             | 1 years                                                 |                                                         |
| **Mechanical**                       |                                                         |                                                         |
| Finished ProductDimension(W x H x D) | 68x112x71mm                                             |                                                         |
| Enclosure                            | Polyamide(PA) Nylon                                     |                                                         |
| Weight(Net)                          | 230g                                                    |                                                         |

## 💡 Custom Development

First, you need to prepare a linux operating system to compile the program.
To compile a binary that can run on reCamera, [the cross-compiler tool](https://github.com/sophgo/host-tools/tree/bd66fcc8ed918eac4d6ac076ff8b1da7290b66cb) for riscv needs to be downloaded. 



### Cross-Compilation

Open a terminal in any directory on your Ubuntu system.
You can download host-tools by running this command on your linux system:

```bash
sudo apt install vim
sudo apt install git
git clone https://github.com/sophgo/host-tools.git
```

After the download is complete go to the file "/host-tools/gcc/riscv64-linux-musl-x86_64/bin"

<p float="left">
  <img src="static\path.png" width="800" />
</p>

Enter "pwd" to see the absolute path and copy it.

```
pwd
```

<p float="left">
  <img src="static\gcc_com.png" width="800" />
</p>

```
cd
vim .bashrc
```

<p float="left">
  <img src="static\export_path.png" width="800" />
</p>

Based on the previous “pwd” command, add the following to the end of the file 

```
export PATH=$PATH:/home/kong/Downloads/host-tools/gcc/riscv64-linux-musl-x86_64/bin
```

Click esc and type “:wq” to save the .bashrc.

```
source .bashrc
```

Go back to the OSHW-reCamera-Series/reCamera_Gimbal/src/send directory. Compile can_send.c and run it.

```
riscv64-unknown-linux-musl-gcc can_send.c -o can_send
```

Open a terminal in the directory where can_send is stored.

```
scp ./can_send root@192.168.42.1:~/
```

```
ssh root@192.168.42.1
```


```
touch Angle.txt 
./can_send

echo "1_90_90+2_90_90" >> Angle.txt
```


## 🔥 Gimbal STP

You can [download the STP file](./3D_Printed_Case) of this gimbal for 3D printing and assemble it. 

<img src="static/image-10.png" alt="reCamera" style="width:75%;" />

| Preview | Models |
| ------- | ------ |
| <img src="static/image.png" alt="image" style="width:33%;" /> | [Download](./3D_Printed_Case/recamera-yantai_arm_30.stp)       |
| <img src="static/image-1.png" alt="image" style="width:33%;" /> | [Download](./3D_Printed_Case/platform-box_29.stp)              |
| <img src="static/image-2.png" alt="image" style="width:33%;" /> | [Download](./3D_Printed_Case/bottom-plate_10.stp)              |
| <img src="static/image-3.png" alt="image" style="width:33%;" /> | [Download](./3D_Printed_Case/brushlessmotor-ms3506_4.stp)      |
| <img src="static/image-4.png" alt="image" style="width:33%;" /> | [Download](./3D_Printed_Case/brushlessmotor-ms3008v2_2.stp)    |
| <img src="static/image-5.png" alt="image" style="width:33%;" /> | [Download](./3D_Printed_Case/recamera-gimbalcover-4040_20.stp) |
| <img src="static/image-6.png" alt="image" style="width:33%;" /> | [Download](./3D_Printed_Case/can-case_3.stp)                   |
| <img src="static/image-7.png" alt="image" style="width:33%;" /> | [Download](./3D_Printed_Case/recamera-middleframe-4040-1_27.stp)|
| <img src="static/image-8.png" alt="image" style="width:33%;" /> | [Download](./3D_Printed_Case/recamera-sensorcover-4040-1_36.stp)|
| <img src="static/image-9.png" alt="image" style="width:33%;" /> | [Download](./3D_Printed_Case/glass-4040_6.stp)                 |

## 📀 Flash motors firmware

### Motor ID Set

![Connect of Devices](static/connection.png)

ID changes can be made using MS_Motor/LK motor tool [V2.35.exe](MotorTools/CN/KY%20motor%20tool%20V2.35.exe). Connect the PC (Windows) to the USB-CAN module, with H, L, and GND of the USB-CAN module connected to H, L, and V- of the motor. Connect the positive and negative terminals of a 12V power supply to V+ and V- of the motor to enable parameter changes. For further instructions on using LK motor tool V2.35.exe, refer to MotorTools/EN/Upper_monitor_motor_debuging_instruction.pdf. 

Only two motors are used in this head, so it is sufficient to set the IDs of the two motors to 01 and 02 respectively.

### How to update motor firmware
WIP...