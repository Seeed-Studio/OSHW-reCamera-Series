# Introduction

<a href="url"><img src="./statics/reCamera-1.png" height="auto" width="auto" style="border-radius:40px"></a>

<div align="center">
<a href="https://discord.gg/agHdBMYGZK"><img alt="Discord" src="https://img.shields.io/discord/862602258452578314?label=Join%20Community"></a>
<a href="https://x.com/seeedstudio" ><img src="https://img.shields.io/twitter/follow/seeedstudio.svg?style=social" /> </a>
<br>
<a href="https://www.reddit.com/r/Seeed_Studio/submit/?type=TEXT" target="_blank"><img alt="Share on Reddit" src="https://img.shields.io/twitter/url?url=https%3A%2F%2Fwww.reddit.com%2Fr%2FSeeed_Studio%2F&style=social&logo=Reddit&label=Reddit"></a>&nbsp;
<a href="https://www.linkedin.com/shareArticle?mini=true&url=https%3A//github.com/Seeed-Studio/OSHW-reCamera-Series" target="_blank"><img alt="Share on LinkedIn" src="https://img.shields.io/twitter/url?url=https%3A%2F%2Fwww.linkedin.com%2Fcompany%2F1475165%2Fadmin%2Fdashboard%2F&style=social&logo=LinkedIn&label=LinkedIn"></a>&nbsp;
<a href="https://www.facebook.com/sharer/sharer.php?u=https%3A//github.com/Seeed-Studio/OSHW-reCamera-Series" target="_blank"><img alt="Share on Facebook" src="https://img.shields.io/twitter/url?url=https%3A%2F%2Fwww.facebook.com%2Fseeedstudiosz%2F&style=social&logo=Facebook&label=Facebook"></a>&nbsp;
<a href="https://t.me/share/url?text=Awesome%20communication%20engine!&url=https%3A%2F%2Fgithub.com%2FSeeed-Studio%2FOSHW-reCamera-Series" target="_blank"><img alt="Share on Telegram" src="https://img.shields.io/twitter/url?url=https%3A%2F%2Fwww.facebook.com%2Fseeedstudiosz%2F&style=social&logo=Telegram&label=Telegram"></a>&nbsp;
<a href="https://wa.me/?text=Awesome%20communication%20engine!%5Cn%20https%3A%2F%2Fgithub.com%2FSeeed-Studio%2FOSHW-reCamera-Series" target="_blank"><img alt="Share on Whatsapp" src="https://img.shields.io/twitter/url?url=https%3A%2F%2Fwww.facebook.com%2Fseeedstudiosz%2F&style=social&logo=Whatsapp&label=Whatsapp"></a>&nbsp;
<a href="mailto:?subject=Awesome%20Physical%20AI%20Agent&body=Checkout%20this%20awesome%20physical%20ai%20agent%3A%0Ahttps%3A//github.com/Seeed-Studio/OSHW-reCamera-Series" target="_blank"><img alt="Share on Mail" src="https://img.shields.io/twitter/url?url=https%3A%2F%2Fwww.facebook.com%2Fseeedstudiosz%2F&style=social&logo=GMail&label=GMail"></a>
<br>
<a href="https://github.com/Seeed-Studio/OSHW-reCamera-Series/stargazers"><img alt="GitHub Repo stars" src="https://img.shields.io/github/stars/Seeed-Studio/OSHW-reCamera-Series"></a>
<a href="https://github.com/Seeed-Studio/OSHW-reCamera-Series/network/members"><img alt="GitHub forks" src="https://img.shields.io/github/forks/Seeed-Studio/OSHW-reCamera-Series">
</a>
<a href="https://github.com/Seeed-Studio/OSHW-reCamera-Series/pulls"><img alt="GitHub Pull Requests" src="https://img.shields.io/github/issues-pr/Seeed-Studio/OSHW-reCamera-Series?label=pull%20request"></a>
<a href="https://github.com/Seeed-Studio/OSHW-reCamera-Series/issues"><img alt="GitHub Issues" src="https://img.shields.io/github/issues/Seeed-Studio/OSHW-reCamera-Series"></a>
<a href="https://github.com/Seeed-Studio/OSHW-reCamera-Series/graphs/contributors"><img alt="GitHub contributors" src="https://img.shields.io/github/contributors/Seeed-Studio/OSHW-reCamera-Series"></a>
<a href="https://github.com/Seeed-Studio/OSHW-reCamera-Series/blob/main/LICENSE"><img alt="GitHub License" src="https://img.shields.io/github/license/Seeed-Studio/OSHW-reCamera-Series"></a>

</div>

## ✨ What's reCamera? 

reCamera is a combination of a **processor** and a **camera sensor**.

This combination makes reCamera a standalone system that can handle basic detection and control tasks on its own.

## 💡 Why we make reCamera? 

Today, as processors (both SOC and MCU) are becoming smaller and more powerful, it is now possible to combine the processor with camera sensors. In fact, many IPCs (IP cameras) are already using this design to accelerate AI detection on edge devices.

So today, we introduce reCamera, an open-source camera platform for everyone to play with. We have divided this project into 3 interchangeable parts:

<a href="url"><img src="./statics/Modular_Design.png" height="auto" width="auto" style="border-radius:40px"></a>
- Core Board
- Sensor Board
- Base Board

This design allows you to easily change the interfaces and camera sensors to suit your needs. We hope that these components can be freely combined in any way.

By building this hardware platform and ecosystem, we enable other applications to grow on this platform without the need to worry about changing from one platform to another in the future.

The engineering focus on modularity, high performance, and ease of use ensures that reCamera serves as a powerful platform for developers and makers. This design streamlines complex hardware processes, allowing users to integrate vision AI capabilities into their systems efficiently and creatively. 

We've taken care of the intricate hardware work, freeing up time for user innovation. The modular design enables users to rapidly switch cameras and customize interfaces, transforming development from months to weeks only!

## Core Board

| Board         | Features                           | Version Info |
| ------------- | ---------------------------------- | ------------ |
| [C1_2002w](./C1_2002/)    | eMMC <br />WIFI/BLE module <br /> OnBoard antenna <br /> External antenna connector| 1.2 |
| [C1_2002](./C1_2002/)       | eMMC <br />Extra SDIO to base board <br /> Extra UART to base board | 1.2 |

### 💡 [C1_2002w](./C1_2002(w)/C1_Readme.md)


### ⚙️ overview
  
Up             |  Bottom
:-------------------------:|:-------------------------:
![Up](./statics/C1_2002w_Up.png)  |  ![Bottom](./statics/C1_2002w_Bottom.png)


## Sensor Board

| Board         | Features                           | Latest Version                                                   |
| ------------- | ---------------------------------- | ------------------------------------------------------------ |
| [S1_OV5647](./S1_OV5647/) | 5MP  <br />Rolling Shutter | 1.2 |
| [S2_IMX335](./S2_IMX335/)     | 5MP  <br />Rolling Shutter | 1.0 |
| [S3_SC130GS](./S3_SC130GS/)    | 1MP <br />Global Shutter    | 1.0 |
----
[Sensor Driver Support List](./Sensor_Suppoeted_List.md)

### 💡 [S1_OV5647](./S1_OV5647\S1_Readme.md)
---
### ⚙️ overview

![img](./statics/S1_ov5647.png)

### ⚙️ features:

<div>

<table ><tbody>
<tr >
    <td >SENSOR</td>
    <td class="dbon">OV5647</td>
    <td class="dbon">CMOS SIZE</td>
    <td class="dbon">1/4 inch</td>
</tr>
<tr >
    <td class="dbon">PIXELS</td>
    <td class="dbon">5MP</td>
    <td class="dbon">APERTURE</td>
    <td class="dbon">F2.4</td>
</tr>
<tr >
    <td >FOCAL LENGTL</td>
    <td class="dbon">3.89mm</td>
    <td class="dbon">FIELD OF VIEW</td>
    <td >72.9°</td>
</tr>
<tr >
    <td >DISTORTION</td>
    <td >&lt;1.5%</td>
    <td >DEPTH OF FIELD</td>
    <td >20cm ~∞</td>
</tr>
<tr >
    <td >IMAGE</td>
    <td  colspan="3">2592 x 1944 still picture resolution</td>
</tr>
<tr >
    <td >VIDEO</td>
    <td  colspan="3">1920 x 1080p @30fps, 1280 x 720p @60fps, 640 x 480p @60fps, 640 x 480p @90fps</td>
</tr></tbody>
</table>
</div>

- 4 x LED fill lights
- 1 x microphone
- 1 x speaker
- 3 x LED indicator

### 💡 [S2_IMX335](./S2_IMX335\readme.md)
### ⚙️ overview

![image](./statics/S2_IMX335_overview.png)



### ⚙️ features:


<div>

<table ><tbody>
<tr >
    <td >SENSOR</td>
    <td class="dbon">IMX335</td>
    <td class="dbon">CMOS SIZE</td>
    <td class="dbon">1/2.8 inch</td>
</tr>
<tr >
    <td class="dbon">PIXELS</td>
    <td class="dbon">5MP</td>
    <td >Focusing</td>
    <td >manually focusing</td>
</tr>
<tr >
    <td >FOCAL LENGTL</td>
    <td class="dbon">3.91mm</td>
    <td class="dbon">FIELD OF VIEW</td>
    <td >106°(D) 92.6°(H) 48.6°(V)</td>
</tr>
<tr >
    <td >IMAGE</td>
    <td  colspan="3">2592 x 1944 still picture resolution</td>
</tr>
<tr >
    <td >VIDEO</td>
    <td  colspan="3">2592 × 1944p @20fps;1920 × 1080p @30fps;1280 × 720p @30fps</td>
</tr></tbody>
</table>
</div>


### 💡 [S3_SC130GS](./S3_SC130GS\readme.md)

### ⚙️ overview

![image](./statics/S3_SC130GS_overview.png)


### ⚙️ features:


<div>

<table ><tbody>
<tr >
    <td >SENSOR</td>
    <td class="dbon">SC130GS</td>
    <td class="dbon">CMOS SIZE</td>
    <td class="dbon">1/2.7 inch</td>
</tr>
<tr >
    <td class="dbon">PIXELS</td>
    <td class="dbon">1.3MP</td>
    <td >Output Format</td>
    <td >RAW MONO/RGB</td>
</tr>
<tr >
    <td >Package</td>
    <td class="dbon">64 pin CLCC</td>
    <td class="dbon">Package Size</td>
    <td >13mm x 13mm</td>
</tr>
<tr >
    <td >IMAGE</td>
    <td  colspan="3"> 1280H x 1024</td>
</tr>
<tr >
    <td >VIDEO</td>
    <td  colspan="3"> 1280H x 1024 @240fps</td>
</tr></tbody>
</table>
</div>


## Base Board


| Board         | Features                           | Version Info |
| ------------- | ---------------------------------- | ------------ |
| B1_Default    | Single Port Transformer Module <br /> SD card reader <br /> Type-C port <br /> UART| 1.2 |
| B2_Vertical-mounted Type-C      | Single Port Transformer Module <br /> SD card reader <br /> Type-C port <br /> UART| 0.1 |
| B3_POE    | Power over Ethernet(POE) <br /> UART| 0.1 |
| B4_Gyro      | DC-DC converter <br /> CAN port <br /> UART | 0.1 |

### 💡 [B1_Default](./B1_Default\B1_Readme.md)

### ⚙️ overview

![image](./statics/B1_Default_overview.png)



### ⚙️ features:

- 1 x Type-C port for power input and communication.
- 1 x Single Port Transformer Module for Ethernet communication support.
- 1 x SD card reader for data storage and exchange.

### 💡 [B2_Vertical-mounted Type-C](./B2_Vertical Type-C\B2_Readme.md)

### ⚙️ overview

![images](./statics/B2_Vertical-mounted_Type-C_overview.png)

### ⚙️ features:

- 1 x Type-C port for power input and communication.
- 1 x Single Port Transformer Module for Ethernet communication support.
- 1 x SD card reader for data storage and exchange.

### 💡 [B3_POE](./B3_POE\B3_Readme.md)

### ⚙️ overview

Up             |  Bottom
:-------------------------:|:-------------------------:
![Up](./statics/B3_POE_Upper.png)  |  ![Bottom](./statics/B3_POE_Bottom.png)


### ⚙️ features:

- 1 x RJ45 port for 802.3af PSE.
- 1 x UART port.

### 💡 [B4_Gyro](./B4_CAN\B4_Readme.md)

### ⚙️ overview

![images](./statics/B4_Gyro_overview.png)

### ⚙️ features:

- 1 x CAN port.
- 1 x Gyroscope sensor.
- 1 x UART port.


## reCamera Softwares

### [reCamera OS](https://github.com/Seeed-Studio/reCamera-OS)

This is the default buildroot system running in reCamera.

### reCamera Web

Currently remaking with Node-red Dashboard.

This is the default Web backend running in reCamera OS. It provides user with a web interface for network configuration, live view, web ssh and other security configuration.

## Related Projects

### [reCamera Gimbal](https://github.com/AllenKon/Seeed_reCamera_Gimbal)

Open source Gimbal solution made using reCamera.

![image](./statics/reCamera-Gimbal.jpg)

### reCamera Industrial 

![image](./statics/industrial.jpg)

WIP..

### [reCamera Robot Arm]()

![image](./statics/reCamera_Robot_Arm.JPG)

WIP..
