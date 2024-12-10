# reCamera Gimbal Programmable Development Kit V1.1🎨

## 🔥Introduction

Welcome to reCamera Gimbal Programmable Development Kit V1.1. We provide sample code to debug the gimbal motor's operation and status output. We offer program entry points to drive the gimbal motor using CAN, enabling precise control and functionality.

![reCamera](static/reCamera-Gimbal-3.png)

## Gimbal STL

You can [download the STP file](./Model) of this gimbal for 3D printing and assemble it. 

![reCamera](static/image-1.png)

| Preview | Models |
| ------- | ------ |
| ![image](image.png)        | [Download](./Model/recamera-yantai_arm_30.stp)       |
| ![alt text](image-1.png)   | [Download](./Model/platform-box_29.stp)              |
| ![alt text](image-2.png)   | [Download](./Model/bottom-plate_10.stp)              |
| ![alt text](image-3.png)   | [Download](./Model/brushlessmotor-ms3506_4.stp)      |
| ![alt text](image-4.png)   | [Download](./Model/brushlessmotor-ms3008v2_2.stp)    |
| ![alt text](image-5.png)   | [Download](./Model/recamera-gimbalcover-4040_20.stp) |
| ![alt text](image-6.png)   | [Download](./Model/can-case_3.stp)                   |
| ![alt text](image-7.png)   | [Download](./Model/recamera-middleframe-4040-1_27.stp)|
| ![alt text](image-8.png)   | [Download](./Model/recamera-sensorcover-4040-1_36.stp)|
| ![alt text](image-9.png)   | [Download](./Model/glass-4040_6.stp)                 |



## Instructions for using

### Motor ID Set

![Connect of Devices](static/Connect.png)

ID changes can be made using MS_Motor/LK motor tool V2.35.exe. Connect the PC (Windows) to the USB-RS485 module, with A, B, and GND of the USB-RS485 module connected to A, B, and V- of the motor. Connect the positive and negative terminals of a 12V power supply to V+ and V- of the motor to enable parameter changes. For further instructions on using LK motor tool V2.35.exe, refer to MS_Motor/Upper_monitor_motor_debuging_instruction.pdf. 

Only two motors are used in this head, so it is sufficient to set the IDs of the two motors to 01 and 02 respectively.

### USB-RS485 Analyzer

If you want a RS485 Bus Analyzer to debug your RS485 Bus, this [USB-RS485 Analyzer](https://www.seeedstudio.com/USB-TO-RS232--RS485--TTL-Industrial-Isolated-Converter-p-3231.html) is recommended.

<p float="left">
  <img src="https://media-cdn.seeedstudio.com/media/catalog/product/cache/bb49d3ec4ee05b6f018e93f896b8a25d/h/t/httpsstatics3.seeedstudio.comseeedfile2018-12bazaar1004130_usbtors232485ttl01.jpg" width="300" />
</p>


## Hardware Overview

To enable the reCamera to drive the gimbal motor, the reCamera's base board needs to be replaced to [B4_Gyro](https://github.com/Seeed-Studio/OSHW-reCamera-Series) to enable CAN communication.

![B4_Gyro_Overview](static/B4_Gyro_overview.png)

You can use the Debugging Port connections to control the motor and communicate with the reCamera via the upper monitor. Alternatively, you can control the motor directly through the reCamera.

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

