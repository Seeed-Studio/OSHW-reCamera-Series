# Introduction

<a href="url"><img src="./statics/reCamera-1.png" height="auto" width="auto" style="border-radius:40px"></a>

## reCamera Core

reCamera Core is a core module design based on SG2002 open source chip.
SG2002 equipped with high-performance RISC-V and ARM cores, it provides a fully open-source, ecosystem-rich deep learning vision processor that delivers 1.0 TOPS computing power@INT8.
s
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

## BaseBoard
### B1_Default

### B2_POE





## Related Porjects:

[sscma Link](https://github.com/Seeed-Studio/sscma-example-sg200x)