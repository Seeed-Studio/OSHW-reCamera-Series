# Introduction

<a href="url"><img src="./statics/reCamera-1.png" height="auto" width="auto" style="border-radius:40px"></a>


**reCamera** is an open source AI camera. The project provides a convenient solution for people who use custom DIY cameras. The feature of this project is that not only does the **RISC-V** system provide an AI recognition solution for edge cameras, but we also open source the related application projects of the camera and the model design of the electronic circuit and 3D shell. We provide a **model transformation tool**, users can quantify and transplant the traditional recognition model according to their needs. In addition, we reserve all interfaces of the processor, and users can personalize the external interfaces according to their projects and requirements.

## reCamera Core

reCamera Core is a core module design based on SG2002 open source chip.
SG2002 equipped with high-performance RISC-V and ARM cores, it provides a fully open-source, ecosystem-rich deep learning vision processor that delivers 1.0 TOPS computing power@INT8.


<a href="url"><img src="./statics/SG2002.png" height="auto" width="auto" style="border-radius:10px"></a>

As the name suggests, this is an open source camera core board. The core board contains the core processor, EMMC storage, and WiFi chip. The core module led all the pins of the processor out through two BtoB sockets.
Through this interface, junior electronics engineers can customize their exclusive cameras by designing SensorBoard and BaseBoard.

<a href="url"><img src="./statics/BTB_Connector.png" height="auto" width="auto" style="border-radius:10px"></a>


## Application:


### [reCamera Gimbal](https://github.com/AllenKon/Seeed_reCamera_Gimbal)

Open source Gimbal solution made using reCamera.

<a href="url"><img src="./statics/reCamera-Gimbal-1.png" height="auto" width="auto" style="border-radius:40px"></a>

### [reCamera Robot Arm]()

waiting...

## SensorBoard

| Board         | Features                           | To do list                                                   |
| ------------- | ---------------------------------- | ------------------------------------------------------------ |
| [S1_OV5647](./S1_OV5647/) | 500w pixels  <br />Rolling Shutter | Home Surveillance<br />PTZ Camera<br />Handheld Camera       |
| S2_IMX335     | 500w pixels  <br />Rolling Shutter | Machine Vision Systems<br />Robot<br />Biometrics            |
| S3_SC130GS    | 100w pixels<br />Global Shutter    | Machine Vision Systems,<br />IoT Camera,<br />Industrial Camera |

### S1_OV5647

> overview
> 
![img](./statics/S1_ov5647.png)

>schematic

![img](./statics/S1_ov5647_Sch.png)

> features:

<div>

<table ><tbody>
<tr >
    <td >SENSOR</td>
    <td class="dbon">ov5647</td>
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
    <td  colspan="3">1920 x 1080p @30, 1280 x 720p @60, 640 x 480p @60, 640 x 480p @90</td>
</tr></tbody>
</table>
</div>

- 4 x LED fill lights
- 1 x microphone
- 1 x speaker
- 3 x LED indicator

### S2_IMX335
> overview

> schematic

> features:

### S3_SC130GS

> overview

> schematic

> features:

## BaseBoard
### B1_Default

> overview
>

<center class="third">
  <img src="./statics/B1_Default_Upper.png" width="200"><img src="./statics/B1_Default_Bottom.png" width="200">
</center>


>schematic

![img](./statics/B1_Default_sch.png)

> features:

- 4 x type-c
- 1 x Single Port Transformer Module
- 1 x SD card reader

### B2_POE

> overview

<center class="third">
  <img src="./statics/B1_Default_Upper.png" width="200"><img src="./statics/B1_Default_Bottom.png" width="200">
</center>


>schematic

![img](./statics/B1_Default_sch.png)

> features:

- 4 x type-c
- 1 x Single Port Transformer Module
- 1 x SD card reader



## Related Porjects:

### [reCamera OS](https://github.com/Seeed-Studio/reCamera-OS)

This is the default buildroot system running in reCamera.

### [reCamera Web]

- [Backend](https://github.com/Seeed-Studio/sscma-example-sg200x)
- [Frontend]()

This is the default Web backend running in reCamera OS. It provides user with a web interface for network configuration, live view, web ssh and other security configuration.
