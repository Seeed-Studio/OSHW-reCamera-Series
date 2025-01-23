# reCamera Gimbal Programmable Development Kit V1.1🎨

## 🔥Introduction

Welcome to reCamera Gimbal Programmable Development Kit V1.1. We provide sample code to debug the gimbal motor's operation and status output. We offer program entry points to drive the gimbal motor using CAN, enabling precise control and functionality.

<img src="static/reCamera-Gimbal-3.png" alt="reCamera" style="width: 80%;" />

## Gimbal Preview
![alt text](./static/image-11.png)

Gimbal Dashboard includes camera preview, model confidence Settings, gimbal control, gimbal calibration, object tracking and motor sleep.

You can download the [flow.json file](./src/Dashboard/Gimbal_DashboardV0.1.json) to deploy to your reCamera device.

To run this routine, [download](./src/Executable%20program/) and copy the file from the `reCamera_Gimbal\src\Executable program\` directory to `/home/recamera/` on your device. 
The source code for these programs can be found [here](./src/).
## 🎈Instructions for using

### Motor ID Set

![Connect of Devices](static/connection.png)

ID changes can be made using MS_Motor/LK motor tool [V2.35.exe](MotorTools/CN/KY%20motor%20tool%20V2.35.exe). Connect the PC (Windows) to the USB-CAN module, with H, L, and GND of the USB-CAN module connected to H, L, and V- of the motor. Connect the positive and negative terminals of a 12V power supply to V+ and V- of the motor to enable parameter changes. For further instructions on using LK motor tool V2.35.exe, refer to MotorTools/EN/Upper_monitor_motor_debuging_instruction.pdf. 

Only two motors are used in this head, so it is sufficient to set the IDs of the two motors to 01 and 02 respectively.


## Hardware Overview

To enable the reCamera to drive the gimbal motor, the reCamera's base board needs to be replaced to [B4_CAN](https://github.com/Seeed-Studio/OSHW-reCamera-Series) to enable CAN communication.

Up             |  Bottom
:-------------------------:|:-------------------------:
![Up](./static/Gimbal_A.png)  |  ![Bottom](./static/Gimbal_B.png)


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

## Deploy in reCamera

It is recommended to use **Ubuntu 20.04** to configure this gimbal, as it will be needed for the cross-compilation part. If you don't have Ubuntu 20.04, you can configure [**TinyCC**](https://community.milkv.io/t/tinycc-milkv-duo-c/271) on reCamera.


### Cross-Compilation

Open a terminal in any directory on your Ubuntu system.

```
sudo apt install vim
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

Go back to the Seeed_reCamera_Gimbal directory. Compile Deploy_Linux_CAN_Final.c and run it.

```
riscv64-unknown-linux-musl-gcc -o Deploy Deploy_Linux_CAN_Final.c
```

Open a terminal in the directory where Deploy is stored.

```
scp ./Deploy root@192.168.42.1:~/
```

```
ssh root@192.168.42.1
```


```
./Deploy <degree1> <degree2>

Example: ./Deploy 0 0
```


### TinyCC Compilation

Open a terminal in the directory where Deploy_Linux.c is stored.

```
cd ./reCamera_Deploy
scp ./Deploy_Linux_CAN_Final.c root@192.168.42.1:~/
```

```
ssh root@192.168.42.1
```

The serial port name can be obtained by terminal. It is usually ttyS0.

```
ls /dev/ttyS*
```

Open Deploy_Linux_CAN_Final.c and change the serial port name on line 160. 

```
vi ./Deploy_Linux_CAN_Final.c
```

<p float="left">
  <img src="static/TF4.png" width="500" />
</p>

Compile Deploy_Linux_CAN_Final and run it.

```
cd ~/
tcc -o test Deploy_Linux.c
./test
```


<p float="left">
  <img src="static/TF2.png" width="300" />
  <img src="static/TF3.png" width="300" />
</p>


## Deploy to Upper Monitor


### Upper Monitor Control

#### Python

Open a terminal in the root directory while making sure Python is installed.

```
python Deploy_Python.py
```

Then just enter the angle (0-360 degrees) for both motors.

<p float="left">
  <img src="static/TF1.jpg" width="300" />
</p>

#### C++

Make sure your system ([Win](https://cloud.tencent.com/developer/article/1500352) or Linux) has g++ installed, open a terminal in the root directory.

*Win*

Open Deploy_Win.cpp and change the serial port name on line 125. The serial port name can be obtained by opening the Device Manager.

```
g++ Deploy_Win.cpp -o Deploy_Win.exe
```

*Linux*

Open Deploy_Linux.cpp and change the serial port name on line 160. The serial port name can be obtained by terminal.

```
ls /dev/ttyUSB*
```

```
g++ Deploy_Linux.cpp -o Deploy_Linux
./Deploy_Linux
```

<p float="left">
  <img src="static/TF2.png" width="300" />
  <img src="static/TF3.png" width="300" />
</p>


----

## 🔥Gimbal STP

You can [download the STP file](./Model) of this gimbal for 3D printing and assemble it. 

<img src="static/image-10.png" alt="reCamera" style="width:75%;" />

| Preview | Models |
| ------- | ------ |
| <img src="static/image.png" alt="image" style="width:33%;" /> | [Download](./Model/recamera-yantai_arm_30.stp)       |
| <img src="static/image-1.png" alt="image" style="width:33%;" /> | [Download](./Model/platform-box_29.stp)              |
| <img src="static/image-2.png" alt="image" style="width:33%;" /> | [Download](./Model/bottom-plate_10.stp)              |
| <img src="static/image-3.png" alt="image" style="width:33%;" /> | [Download](./Model/brushlessmotor-ms3506_4.stp)      |
| <img src="static/image-4.png" alt="image" style="width:33%;" /> | [Download](./Model/brushlessmotor-ms3008v2_2.stp)    |
| <img src="static/image-5.png" alt="image" style="width:33%;" /> | [Download](./Model/recamera-gimbalcover-4040_20.stp) |
| <img src="static/image-6.png" alt="image" style="width:33%;" /> | [Download](./Model/can-case_3.stp)                   |
| <img src="static/image-7.png" alt="image" style="width:33%;" /> | [Download](./Model/recamera-middleframe-4040-1_27.stp)|
| <img src="static/image-8.png" alt="image" style="width:33%;" /> | [Download](./Model/recamera-sensorcover-4040-1_36.stp)|
| <img src="static/image-9.png" alt="image" style="width:33%;" /> | [Download](./Model/glass-4040_6.stp)                 |

