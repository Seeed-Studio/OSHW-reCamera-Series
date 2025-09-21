# reCamera Workshop

![image-20250918174652892](.\image-20250918174652892.png)

This is the flowchart of this Workshop. If you encounter any problems, you can ask the **staff** and explain **which step and which option** operation you were performing when the problem occurred. So that we can quickly help you identify the problem.

### **catalog**

- **[Step 1: Dataset Collection](# Step 1: Dataset Collection)**
  - [Option1: Download Dataset from Roboflow Cloud Platform](# Option1: Download Dataset from Roboflow Cloud Platform)
  - [Option2: Annotation with CVAT Platform](# Option2: Annotation with CVAT Platform)
  - [Option3: Annotation with SpireView SoftWare(Only for windows)](# Option3: Annotation with SpireView SoftWare(Only for windows))

- **[Step 2: Training Yolo11n model](# Step 2: Training Yolo11n model)**
- **[Step 3: Model conversion and deployment](# Step 3: Model conversion and deployment)**
- **[Step 4: Deployed in reCamera](# Step 4: Deployed in reCamera)**
  - [Option1: reCamera Default](# Option1: reCamera Default)
  - [Option2:  reCamera Microscope](# Option2:  reCamera Microscope)
  - [Option3:  reCamera HD POE](# Option3:  reCamera HD POE)
  - [Option4:  reCamera Gimbal](# Option4:  reCamera Gimbal)



## **Step 1: Dataset Collection**

### Option1: Download Dataset from Roboflow Cloud Platform

Roboflow inference server supports dataset download (free), training and deployment (paid) for various computer vision models. Users can also upload their own datasets for annotation and training (paid). Here we'll only download free datasets and perform training on our own servers.

#### Step1: Network

**Note**: Disconnect reCamera before downloading data.

Visit: <https://universe.roboflow.com/>

#### Step2: Login

Use GitHub account or email to login.

<div style="text-align: center;">
    <img src="./d1.png" alt="Demo" width="600" />
</div>


#### Step3: Download Public Dataset

Search for your desired dataset name, preferably selecting datasets with 1000-2000 images.

<div style="text-align: center;">
    <img src="./d2.png" alt="Demo" width="600" />
</div>


Click the dataset and wait for full page loading. You might see "Fork project" or "Download project" - don't click them. Find "Dataset" in left toolbar and click "Download dataset":

<div style="text-align: center;">
    <img src="./d3.png" alt="Demo" width="600" />
</div>
<div style="text-align: center;">
    <img src="./d4.png" alt="Demo" width="600" />
</div>


Select the third option:

<div style="text-align: center;">
    <img src="./d5.png" alt="Demo" width="600" />
</div>


Choose YOLOv11 and download zip package, click continue:

<div style="text-align: center;">
    <img src="./d6.png" alt="Demo" width="600" />
</div>
<div style="text-align: center;">
    <img src="./d7.png" alt="Demo" width="600" />
</div>

Ignore the final popup by closing it directly:

<div style="text: center;">
    <img src="./d8.png" alt="Demo" width="600" />
</div>

You'll see the dataset package downloaded in your browser:

<div style="text-align: center;">
    <img src="./d9.png" alt="Demo" width="600" />
</div>


Dataset structure:

``` 
data/                  # Dataset root
├── test/              # Test set
│   ├── images/    # Images
│   └── labels/    # Labels
│── train/              # Training set
│   ├── images/    # Images
│   └── labels/    # Labels
│
│── valid/              # Validation set
│   ├── images/    # Images
│   └── labels/    # Labels
│
│── data.yaml # Configuration: dataset paths, classes and metadata
│
└── README.md  # Documentation
```

<div style="text-align: center;">
    <img src="./d10.png" alt="Demo" width="600" />
</div>
The successfully downloaded **“.zip”** compressed folder you have will be used in [**Step 2: Training Yolo11n model**](# Step 2: Training Yolo11n model ). Now we can proceed to training.

### Option2: Annotation with CVAT Platform

For manual annotation, use CVAT platform to annotate your own images and export datasets in multiple formats.

#### Login

Visit: cvat.ai

<div style="text-align: center;">
    <img src="./b1.png" alt="Demo" width="600" />
</div>

Click "start for free" and choose login method.

<div style="text-align: center;">
    <img src="./b2.png" alt="Demo" width="600" />
</div>


Create new project and add label names:

<div style="text-align: center;">
    <img src="./b21.png" alt="Demo" width="600" />
</div>
<div style="text-align: center;">
    <img src="./b22.png" alt="Demo" width="600" />
</div>


Create new task, name it, select your project, and upload images:

<div style="text-align: center;">
    <img src="./b3.png" alt="Demo" width="600" />
</div>
<div style="text-align: center;">
    <img src="./b4.png" alt="Demo" width="600" />
</div>


Enter Jobs section and click images to annotate:

<div style="text-align: center;">
    <img src="./b5.png" alt="Demo" width="600" />
</div>


Annotation interface:

<div style="text-align: center;">
    <img src="./b6.png" alt="Demo" width="600" />
</div>


Use SAM model for automatic segmentation:

<div style="text-align: center;">
    <img src="./b7.png" alt="Demo" width="600" />
</div>


For object detection, use auto-detection tool (supports YOLO-compatible objects):

<div style="text-align: center;">
    <img src="./b8.png" alt="Demo" width="600" />
</div>


For custom objects, use manual bounding boxes:

<div style="text-align: center;">
    <img src="./b9.png" alt="Demo" width="600" />
</div>


Edit annotations on right panel:

<div style="text-align: center;">
    <img src="./b10.png" alt="Demo" width="600" />
</div>


Save annotations from top-left:

<div style="text-align: center;">
    <img src="./b11.png" alt="Demo" width="600" />
</div>


Mark task as completed:

<div style="text-align: center;">
    <img src="./b14.png" alt="Demo" width="600" />
</div>
<div style="text-align: center;">
    <img src="./b15.png" alt="Demo" width="600" />
</div>


Export dataset:

<div style="text-align: center;">
    <img src="./b12.png" alt="Demo" width="600" />
</div>

Choose "Ultralytics YOLO Detection Track 1.0" format:

<div style="text-align: center;">
    <img src="./ultra.png" alt="Demo" width="600" />
</div>


Download package:

<div style="text-align: center;">
    <img src="./b13.png" alt="Demo" width="600" />
</div>


The downloaded files (without images) need manual organization:

<div style="text-align: center;">
    <img src="./s1.png" alt="Demo" width="600" />
</div>


Organize files according to Method 1's structure:

<div style="text-align: center;">
    <img src="./s2.png" alt="Demo" width="600" />
</div>
<div style="text-align: center;">
    <img src="./s3.png" alt="Demo" width="600" />
</div>


Example data.yaml:

```
train: ../train/images # Modify according to actual path
val: ../valid/images
test: ../test/images

nc: 1
names: ['missing hole'] # Replace with your labels

roboflow:
  workspace: rf-projects
  project: pcb-holes
  version: 4
  license: CC BY 4.0
  url: https://universe.roboflow.com/rf-projects/pcb-holes/dataset/4
```

Finally, compress the file into a **“.zip“** folder. This will be used in [**Step 2: Training Yolo11n model**](# Step 2: Training Yolo11n model ).
![image-20250918153954024](.\image-20250918153954024.png)

### Option3: Annotation with SpireView SoftWare(Only for windows)

For manual annotation, use SpireView  to annotate your own images and export datasets in multiple formats.

This is a locally downloaded app and it is currently only compatible with Windows systems. 

- Download link: https://files.seeedstudio.com/wiki/reCamera/models/SpireView-v5.3.2.zip

- The open-source of the SpireView project: [jario-jin/SpireView](https://github.com/jario-jin/SpireView)

#### How to use

**Step 1** :Create an empty folder according to the structure of the dataset. 

- The images can be downloaded from the internet or taken by oneself. There are no specific requirements for the proportion, format or size of the images.
- Place the pictures you have collected in the ratio of 1:7:2 into the file directories of test, train, and valid.

```bash
data/                  # Dataset root
├── test/              # Test set
│── train/              # Training set
│── valid/              # Validation set
│── data.yaml # Configuration: dataset paths, classes and metadata
```

**Step 2** : Open the SpireView software and label the images within each of the three datasets.

- The methods for data annotation are the same. Remember to modify the directory locations of test、train、valid  when annotating the test, train, and valid sets of pictures.
- The saved directory was set to the directories of the "test", "train" and "valid" folders.
- The location to open the image is the directory location of the image data you have divided proportionally.

![labeling.jpg](.\labeling.jpg)

![image-20250917144353471](.\image-20250917144353471.png)

- After marking the data, press "Ctrl + O" on the keyboard. Select the Yolo format and the "Copy imgs" option as shown in the figure. Then click OK.

![image-20250917151313434](.\image-20250917151313434.png)

After annotation, only the "Yolo_images" and "Yolo_labels" directories will be retained in the directory. The other files can be deleted. 

- As shown in the figure: **Only keep the two folders within the red frame.** 
- Rename the folders to "images" and "labels"

![image-20250917151732550](.\image-20250917151732550.png)

- Finally, remember to add the content of the data.yaml file:

```bash
train: ../train/images 
val: ../valid/images
test: ../test/images

nc: 2  							#labels number
names: ['hamburger','pizza'] 	# Replace with your labels
```

- The content of the "names" label is the same as that within the green box:
  ![image-20250917152217435](.\image-20250917152217435.png)

The final directory structure of your dataset is as follows:

```bash
data/                  # Dataset root
├── test/              # Test set
│   ├── images/    # Images
│   └── labels/    # Labels
│── train/              # Training set
│   ├── images/    # Images
│   └── labels/    # Labels
│
│── valid/              # Validation set
│   ├── images/    # Images
│   └── labels/    # Labels
│
│── data.yaml # Configuration: dataset paths, classes and metadata
```

Finally, compress the file into a **“.zip“** folder. This will be used in [**Step 2: Training Yolo11n model**](# Step 2: Training Yolo11n model ).

## **Step 2: Training Yolo11n model**

Ultralytics Yolo has established an online [Ultralytics HUB](https://hub.ultralytics.com/signin) for training models. By uploading the dataset, one can quickly train the model and export it in different formats.

### Step 1: Login

- You can register an account using Google, GitHub or Apple ID or your email address.

![image-20250918151625487](.\image-20250918151625487.png)

- After registration, log in to the platform.

- After successful login, the WorkEmail is your account.

![image-20250918152536455](.\image-20250918152536455.png)

### Step 2： Upload the dataset

![image-20250918155143713](.\image-20250918155143713.png)



![image-20250918155625232](.\image-20250918155625232.png)



![image-20250918155942638](.\image-20250918155942638.png)



![image-20250918160227678](.\image-20250918160227678.png)

**Finally**, here you can see that after you upload the dataset, we will proceed to the next step.

![image-20250918160357106](.\image-20250918160357106.png)



### Step 3: Create a project



![image-20250918161844891](.\image-20250918161844891.png)



![image-20250918162050356](.\image-20250918162050356.png)



![image-20250918162202397](.\image-20250918162202397.png)



![image-20250918162237854](.\image-20250918162237854.png)



![image-20250918162404818](.\image-20250918162404818.png)



![image-20250918162612764](.\image-20250918162612764.png)



![image-20250918162821216](.\image-20250918162821216.png)



![image-20250918163030763](.\image-20250918163030763.png)

**Finally**, as shown in the picture, you can proceed to the next step.

![image-20250918164440854](.\image-20250918164440854.png)

The **[Ultralytics Hub](https://hub.ultralytics.com/signin)** platform charges based on the time spent on model training. The price is very favorable. We warmly welcome everyone to use the Ultralytics Hub to train their own models.

![image-20250918165046842](.\image-20250918165046842.png)

### Step 4: Download the ONNX model

![image-20250918165608160](.\image-20250918165608160.png)



![image-20250918165743421](.\image-20250918165743421.png)



![image-20250918165952370](.\image-20250918165952370.png)

**Finally**, we need to organize a file structure to prepare for the next step.

- The pictures in the **COCO2017** file can be used to copy the pictures in your **Dataset**. 100 pictures are required.
- The images within the **"image"** file can copy the images from your **Dataset**. You need to provide 1 image and rename it as **"test.img"**.
- Place the **onnx** model file you just downloaded in the **Workspace** file.

```bash
model_yolo11n/
├── COCO2017/           # Calibration dataset (100 imgs)
|   └── Calibration1.img
|		Calibration2.img
|		...
|		Calibration100.img
|		
├── image/              # Test images (1 imgs)
|   └── test.img
└── Workspace/
    └── yolo11n_food.onnx    # ONNX model (The downloaded ONNX model)

```

After preparing this file, proceed to the **[Step 3: Model conversion and deployment](# Step 3: Model conversion and deployment)**



## **Step 3: Model conversion and deployment**

### Set up the working environment

**Notice:** Your computer is running the **Linux** system or you can use **WSL**.

**If you don't have the technical capability, please send the folder prepared in the previous step to the on-site staff. And skip "Step 3: Model conversion and deployment".**

The staff will assist you in performing the necessary model conversion and will send you a file ending with **"cvimodel"**. This will be used in **[Step 4: Deployed in reCamera](# Step 4: Deployed in reCamera)**.

#### Step1: Installation in a Docker Image 

Download the required image from [DockerHub (click here)](https://hub.docker.com/r/sophgo/tpuc_dev) and we recommend using **version 3.1**:

```bash
docker pull sophgo/tpuc_dev:v3.1
```



If you are using Docker for the first time, you can run the following commands for installation and configuration (only needed for the first-time setup):

```bash
sudo apt install docker.io
sudo systemctl start docker
sudo systemctl enable docker
sudo groupadd docker
sudo usermod -aG docker $USER
newgrp docker
```



Then create a container in the current directory as follows:

```bash
docker run --privileged --name MyName -v $PWD:/workspace -it sophgo/tpuc_dev:v3.1
```



Replace `"MyName"` with the desired name for your container

Use `pip` to install `tpu_mlir` inside the Docker container, just like in `Method 1`:

```bash
pip install tpu_mlir[all]==1.7
```



#### Step2: Preparing the Workspace

Create the `model_yolo11n` directory at the same level as `tpu-mlir`. The image files are usually part of the model’s training dataset, used for calibration during the subsequent quantization process. Enter the following command in the terminal:

```bash
git clone -b v1.7 --depth 1 https://github.com/sophgo/tpu-mlir.git
cd tpu-mlir
source ./envsetup.sh
./build.sh
```

Copy the **[model_yolo11n](# Step 4: Download the ONNX model)** prepared in the previous step to the **tpu-mlir** directory.

```bash
cd model_yolo11n
cd Workspace
```


Make sure there are no missing items in your folder:

```bash
model_yolo11n/
├── COCO2017/           # Calibration dataset (100 imgs)
|   └── Calibration1.img
|		Calibration2.img
|		...
|		Calibration100.img
|		
├── image/              # Test images (1 imgs)
|   └── test.img
└── Workspace/
    └── yolo11n_food.onnx    # ONNX model (The downloaded ONNX model)
```

### Start model conversion

#### Step1： ONNX→MLIR Conversion

Execute in Workspace:

```bash
model_transform \
  --model_name yolo11n \
  --model_def yolo11n_food.onnx \
  --input_shapes "[[1,3,640,640]]" \
  --mean "0.0,0.0,0.0" \
  --scale "0.0039216,0.0039216,0.0039216" \
  --keep_aspect_ratio \
  --pixel_format rgb \
  --output_names "/model.23/cv2.0/cv2.0.2/Conv_output_0,/model.23/cv3.0/cv3.0.2/Conv_output_0,/model.23/cv2.1/cv2.1.2/Conv_output_0,/model.23/cv3.1/cv3.1.2/Conv_output_0,/model.23/cv2.2/cv2.2.2/Conv_output_0,/model.23/cv3.2/cv3.2.2/Conv_output_0" \
  --test_input ../image/test.jpg \
  --test_result yolo11n_top_outputs.npz \
  --mlir yolo11n.mlir
  
model_transform \
  --model_name yolo11n \
  --model_def yolov9_19.onnx \
  --input_shapes "[[1,3,640,640]]" \
  --mean "0.0,0.0,0.0" \
  --scale "0.0039216,0.0039216,0.0039216" \
  --keep_aspect_ratio \
  --pixel_format rgb \
  --output_names "/model.23/cv2.0/cv2.0.2/Conv_output_0,/model.23/cv3.0/cv3.0.2/Conv_output_0,/model.23/cv2.1/cv2.1.2/Conv_output_0,/model.23/cv3.1/cv3.1.2/Conv_output_0,/model.23/cv2.2/cv2.2.2/Conv_output_0,/model.23/cv3.2/cv3.2.2/Conv_output_0" \
  --test_result yolo11n_top_outputs.npz \
  --mlir yolo11n.mlir
  
model_deploy \
  --mlir yolo11n.mlir \
  --quant_input \
  --quantize F16 \
  --customization_format RGB_PACKED \
  --processor cv181x \
  --test_reference yolo11n_top_outputs.npz \
  --fuse_preprocess \
  --tolerance 0.99,0.9 \
  --model yolo11n_pizza_f16.cvimodel
```

#### Step2：Generate Calibration Table

```bash
run_calibration \
  yolo11n.mlir \
  --dataset ../COCO2017/images \
  --input_num 100 \
  -o yolo11n_calib_table
```

#### Step3：Compile INT8 Model

```bash
model_deploy \
  --mlir yolo11n.mlir \
  --quantize INT8 \
  --quant_input \
  --processor cv181x \
  --calibration_table yolo11n_calib_table \
  --test_input ../image/0101.jpg \
  --test_reference yolo11n_top_outputs.npz \
  --customization_format RGB_PACKED \
  --fuse_preprocess \
  --aligned_input \
  --model yolo11n_sym_int8.cvimodel
```

**Finally**, download the model file ending with **`cvimode`** to your computer. This file will be used in the next step.

![image-20250918172004887](.\image-20250918172004887.png)

**If you want to know more, Reference [wiki](https://wiki.seeedstudio.com/recamera_model_conversion/) or [Chinese guide](https://blog.csdn.net/D777777777777/article/details/149200276?spm=1001.2014.3001.5502) for Complete online materials**



## **Step 4: Deployed in reCamera**

### Option1: reCamera Default

#### Step1:

- Make sure you have a reCamera device and a Type-C cable.

<img src=".\\image-20250916145844604.png" alt="image-20250916145844604" style="zoom:33%;" />

- Connect the USB cable from reCamera to your PC.
  
  <img src=".\\image-20250916150122897.png" alt="image-20250916150122897" style="zoom:33%;" />

#### Step2: Deploy the model to reCamera

-  Visit `192.168.42.1` to view the loading page for reCamera. The logged-in **user** is: `root` ; the **password** is: `recamera.1`

![image-20250916163922968](.\\image-20250916163922968.png)

![image-20250916164111563](.\\image-20250916164111563.png)

![image-20250916164323357](.\\image-20250916164323357.png)

![image-20250916164605325](.\\image-20250916164605325.png)

![image-20250916165159291](.\\image-20250916165159291.png)

![image-20250916165315002](.\\image-20250916165315002.png)

![image-20250916165614859](.\\image-20250916165614859.png)

![image-20250916170221913](.\\image-20250916170221913.png)

```bash 
http://192.168.42.1/#/workspace   //Workspace link, upload model
http://192.168.42.1/#/dashboard   //Preview video link for shooting
http://192.168.42.1/#/network     //Back-end web page link, which can be configured for network settings, firmware updates, etc.

For more reCamera usage tutorials, please visit: https://wiki.seeedstudio.com/recamera_develop_with_node-red/
```



### Option2:  reCamera Microscope

#### Step1

Make sure your Device list:

- reCamera POE
- 3D Printer x2
- M12 lens x2
- M12 Lens Extension Bracket x3
- microscope holder
- 12V power adapter
- Type-C cable

![image-20250916181501348](.\\image-20250916181501348.png)

**As shown in the figure, assemble the bracket, connect it to the 12V power supply, and install the 3D printed part.**

![image-20250916181710125](.\\image-20250916181710125.png)

As shown in the figure, the microscope kit contains two lenses. You need to remove the wide-angle lens and replace it with the other two lenses.

![image-20250916181945699](.\\image-20250916181945699.png)

#### Step2

##### Option1: Lens 1: Use of the microscope lens

As shown in the figure, remove the microscope lens, install three lens extension adapters, and then install lens 1.

![image-20250916182307461](.\\image-20250916182307461.png)

As shown in the figure, **connect the computer using a USB cable.**

 Visit `192.168.42.1` to view the loading page for reCamera. The logged-in **user** is: `root` ; the **password** is: `recamera.1`



![image-20250916182526749](.\\image-20250916182526749.png)

If this prompt appears, please click "Cancel".

![image-20250916173741710](.\\image-20250916173741710.png)

You can obtain a specimen section from the staff and place it on the stage. By adjusting the positions of the camera and the objects, one can view the images of the microscopic world.

![image-20250916174515742](.\\image-20250916174515742.png)





##### Option2: Lens 2: Use PCB micro-lens

As shown in the figure, remove the microscope lens, install one lens extension adapter, and then install lens 2.

![image-20250916183322865](.\\image-20250916183322865.png)

As shown in the figure, **connect the computer using a USB cable.**

 Visit `192.168.42.1` to view the loading page for reCamera. The logged-in **user** is: `root` ; the **password** is: `recamera.1`

![image-20250916183224595](.\\image-20250916183224595.png)

If this prompt appears, please click "Cancel".

![image-20250916173741710](.\\image-20250916173741710.png)

By adjusting the position of the camera and the object, people can now see the details of the PCB.

![image-20250916174804728](.\\image-20250916174804728.png)

For model deployment, please refer to [Deploy the model to reCamera.](#Deploy-the-model-to-reCamera)

### Option3:  reCamera HD POE

#### Step 1

- Make sure you have a reCamera HD POE device and a Type-C cable.

<img src=".\\image-20250917100232816.png" alt="image-20250917100232816" style="zoom:33%;" />

- Connect the USB cable from reCamera to your PC.

<img src=".\\image-20250916150122897.png" alt="image-20250916150122897" style="zoom:33%;" />

#### Step 2: View the preview

- Visit `192.168.42.1` to view the loading page for reCamera. The logged-in **user** is: `root` ; the **password** is: `recamera.1`

- For model deployment or login operations, please refer to [Deploy the model to reCamera.](#Deploy-the-model-to-reCamera)

- The software of the reCamera HD POE version is the same as that of the reCamera Default version. However, this version of the device has a clearer CMOS and a wider-angle lens.

![image-20250917101250846](.\\image-20250917101250846.png)

> Step3 

**The following introduces the new features of the POE equipment hardware. However, this content is not related to this workshop and is provided for reference only.**

Devices of the POE version support the POE function and can be powered by the network cables of the POE switch.

![image-20250917102116142](.\\image-20250917102116142.png)

You can access the backend of the device using the IP address allocated by the router.

![image-20250917102737014](.\\image-20250917102737014.png)

If you are unable to view the IP address of the router, you can also access the [address](http://192.168.42.1/#/network) by connecting the device via a USB cable and then view the IPv4 address. 

![image-20250917103057065](.\\image-20250917103057065.png)

The POE version of the device also has 3 custom IO ports and a serial port.

- 490、487、488 are both configurable as input or output IO ports. The numbers represent the configuration numbers within the chip.

![image-20250917103312258](.\\image-20250917103312258.png)



### Option4:  reCamera Gimbal

#### Step1:

- Make sure you have a reCamera Gimbal device, a 12V DC power adapter  and a Type-C cable.

<img src=".\\image-20250917105125132.png" alt="image-20250917105125132" style="zoom:33%;" />

- First, connect the 12V power adapter to the reCamera Gimbal. Then, wait for the motor of the Gimbal to complete the calibration.
   (**Notice The 12V power adapter must be connected to the Gimbal first; otherwise, the motor will not be able to initialize successfully.**)

<img src=".\\image-20250917105338466.png" alt="image-20250917105338466" style="zoom:33%;" />

- Then connect the USB cable from reCamera Gimbal to your PC.

<img src=".\\image-20250916150122897.png" alt="image-20250916150122897" style="zoom:33%;" />

#### Step2: View the preview

- Visit `192.168.42.1` to view the loading page for reCamera. The logged-in **user** is: `root` ; the **password** is: `recamera.1`

- For model deployment or login operations, please refer to [Deploy the model to reCamera.](#Deploy-the-model-to-reCamera)

- The preview of reCamera Gimbal is similar to that of reCamera, but it also includes the functions of motor control and object tracking.

![image-20250917110022368](.\\image-20250917110022368.png)

## Notice

If your computer has trouble accessing the internet after connecting to reCamera, you can refer to this wiki for solutions:
[FAQs | Seeed Studio Wiki](https://wiki.seeedstudio.com/recamera_network_connection/)