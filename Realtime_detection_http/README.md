---
description: This wiki demonstrates how to use YOLO to detect objects in real time on reCamera with C++. 
title: Real-time YOLO object detection using reCamera based on Cpp
keywords:
  - Http
  - reCamera
  - Object detecton
  - YOLO
  - C++
image: https://files.seeedstudio.com/wiki/wiki-platform/S-tempor.png
slug: /real_time_yolo_object_detection_using_recamera_based_on_cpp
last_update:
  date: 06/26/2025
  author: Liangyuxin

no_comments: false # for Disqus
---

# Real-time YOLO object detection using reCamera based on Cpp

This document demonstrates how to implement real-time photo capture, YOLO object detection, and result access by HTTP with C++ based on cross-compilation on reCamera terminals. This approach avoids the overheating issues encountered when using Node-RED on reCamera. You can refer to this document to modify the C++ code for customized computer vision applications.

## Environment Preparation
### Pre-compilation

First, you need to refer to the "Develop with C/C++" document to configure the cross-compilation environment on your linux. 
**Note**: Reconfigure the path after each boot:
```
export SG200X_SDK_PATH=$HOME/recamera/sg2002_recamera_emmc/
export PATH=$HOME/recamera/host-tools/gcc/riscv64-linux-musl-x86_64/bin:$PATH
```
Then,enter the **Realtime_detection_http** folder under **[sscma-example-sg200x/solutions/](https://github.com/Seeed-Studio/sscma-example-sg200x/tree/main/solutions)**, and compile it.​

```
cd sscma-example-sg200x/solutions/Realtime_detection_http/
mkdir build && cd build
cmake ..
make
```
The presence of the green executable file **Realtime_detection_http** in the build directory indicates successful compilation:
<div align="center"><img width={600} src="https://files.seeedstudio.com/wiki/reCamera/Real_time_YOLO_object_detection_using_reCamera_based_on_Cpp/1.png" /></div>

Then open the reCamera terminal, and copy the executable file to the reCamera terminal directory.​
```
 sudo scp Realtime_detection_http recamera@192.168.42.1:/home/recamera/
```
### ReCamera Preparation
1.Download the **YOLOv11** which has been deployed from **[On Device Models](https://wiki.seeedstudio.com/recamera_on_device_models/)**, then copy the model's **.cvimodel** file to your reCamera terminal:**/home/recamera/**.
2.Before executing the code, please access the reCamera [workspace](http://192.168.42.1/#/workspace) to terminate the process (refer to **[Develop with c/c++](https://wiki.seeedstudio.com/recamera_develop_with_c_cpp)**) to prevent memory consumption.
3.Then navigate to **/etc/init.d/**, copy both the **S93sscma-supervisor** and **S91sscma-node** folders to **/home/recamera/** or another location for backup, and delete the original **S93sscma-supervisor** and **S91sscma-node** folders to prevent memory consumption and program occupation.​

```
cd /etc/init.d/
sudo scp S93sscma-supervisor /home/recamera/
sudo scp S91sscma-node /home/recamera/
sudo rm -r S93sscma-supervisor
sudo rm -r S91sscma-node
```
## Run the program

Run the program as administrator under the **/home/recamera/** on the reCamera terminal​:
```
sudo ./Realtime_detection_http
```

## Results

The terminal displays the following, indicating normal program operation: 
<div align="center"><img width={600} src="https://files.seeedstudio.com/wiki/reCamera/Real_time_YOLO_object_detection_using_reCamera_based_on_Cpp/2.png" /></div>

You can access http://192.168.42.1/modeldetector via web browser or Postman.The reCamera will immediately capture a photo and return objects detected by YOLOv11.​
Browser:

<div align="center"><img width={600} src="https://files.seeedstudio.com/wiki/reCamera/Real_time_YOLO_object_detection_using_reCamera_based_on_Cpp/3.png" /></div>

Postman:
<div align="center"><img width={600} src="https://files.seeedstudio.com/wiki/reCamera/Real_time_YOLO_object_detection_using_reCamera_based_on_Cpp/4.png" /></div>

The returned information includes the following data:​​
- **Code**:1 (Running)
- **Msg**: Error messages
- **Initialize_camera_duration**:Camera initialization duration is displayed only during the first access.​
- **Initialize_model_duration**:Model initialization duration is displayed only during the first access.​
- **Data**:
    - ​**Score**: Detection confidence score (0-1)
    - **Target**: Name of detected object
    - **Box**:[x1, y1, x2, y2]​: Detection box coordinates (in pixels representing [left, top, right, bottom] edges)
    - ​**Center**:[x, y]​: Normalized center position of the detection box (ratio relative to image width/height)
    - ​**Size**:[w, h]​: Normalized width and height of the detection box (ratio relative to image dimensions)
    - **Release_duration**: Time taken to clear camera cache (ms)
    - ​**Capture_duration**: Image acquisition duration (ms)
    - ​**Image_preprocessing_duration**: Image preparation before inference duration (ms)
    - **Detection_duration**: Model detection duration (ms) (Including Preprocessing,Inference,Postprocessing)
- ​**Duration**: Total program execution time (ms)
- **Timestamp**: Unix timestamp 

The terminal will display:​
- Camera initialization parameters​:
    - Resolution: **1920×1080**
    - Frame rate: **5 fps**
    - Capture channel: **Channel 2**
- Captured image size (e.g. **Jpeg size: 216149 (pixels)**)
- ​Memory usage (MB) during different steps：
    - Pre-capture (**Memory usage**)
    - Releasing (**Memory usage_during_**)
    - Post-capture (**Memory usage_after**)
    - After image preprocessing (**Memory usage_before_model**)
    - After model detection (**Memory usage_after_model**)
- Model detection duration (ms)
    - Preprocessing (e.g.**pre: 9ms**)
    - Inference (e.g.**infer: 40ms**)
    - Postprocessing (e.g.**post:395ms**)

<div align="center"><img width={600} src="https://files.seeedstudio.com/wiki/reCamera/Real_time_YOLO_object_detection_using_reCamera_based_on_Cpp/5.png" /></div>


<div align="center"><img width={600} src="https://files.seeedstudio.com/wiki/reCamera/Real_time_YOLO_object_detection_using_reCamera_based_on_Cpp/6.png" /></div>



On the reCamera terminal, detected images can be automatically saved:​
<div align="center"><img width={600} src="https://files.seeedstudio.com/wiki/reCamera/Real_time_YOLO_object_detection_using_reCamera_based_on_Cpp/7.jpg" /></div>

You can continuously access it with your device to obtain real-time detection results for applications such as intelligent security and surveillance.

You can modify the returned message's format in **registerModelDetector()** (**Realtime_detection_http/src/http.cpp**) and **model_detector()** (**Realtime_detection_http/src/model_detector.cpp**).
You can also use your own deployed model when calling the **initialize_model(const std::string& model_path)** in **registerModelDetector()**, and modify the camera initialization settings in **initialize_camera()**(**Realtime_detection_http/src/model_detector.cpp**):

<div align="center"><img width={600} src="https://files.seeedstudio.com/wiki/reCamera/Real_time_YOLO_object_detection_using_reCamera_based_on_Cpp/8.png" /></div>


After detection, you can press Ctrl+C to terminate the operation.​The program will stop the camera.​

<div align="center"><img width={600} src="https://files.seeedstudio.com/wiki/reCamera/Real_time_YOLO_object_detection_using_reCamera_based_on_Cpp/9.png" /></div>

## Tech Support & Product Discussion

Thank you for choosing our products! We are here to provide you with different support to ensure that your experience with our products is as smooth as possible. We offer several communication channels to cater to different preferences and needs.

<div class="button_tech_support_container">
<a href="https://forum.seeedstudio.com/" class="button_forum"></a> 
<a href="https://www.seeedstudio.com/contacts" class="button_email"></a>
</div>

<div class="button_tech_support_container">
<a href="https://discord.gg/eWkprNDMU7" class="button_discord"></a> 
<a href="https://github.com/Seeed-Studio/wiki-documents/discussions/69" class="button_discussion"></a>
</div>