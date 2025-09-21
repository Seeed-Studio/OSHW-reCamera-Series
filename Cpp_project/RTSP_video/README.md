# Video Demo

## Overview

**Video Demo** is an example application demonstrating how to use the **Sophgo SDK** to capture video frames from a camera, save them in different formats, and stream video over RTSP (Real-Time Streaming Protocol). This application shows how to initialize the video, configure the channels, and handle video frame processing.

## Getting Started

Before building this solution, ensure that you have set up the **Sophgo SDK** environment as described in the main project documentation.

This includes:

- Setting up **Sophgo SDK**
- Configuring the SDK path
- Preparing the necessary toolchain

If you haven't completed these steps, follow the instructions in the main project README before proceeding.

## Building & Installing

### 1. Navigate to the `video_demo` Solution

```bash
cd solutions/video_demo
```

### 2. Build the Application

```bash
mkdir build
cd build
cmake ..
make
```

### 3. Run the Application

To run the application, use the following command:

```bash
./video_demo
```

## Expected Output

Upon executing the application, the following occurs:

1. The application sets up signal handlers to gracefully exit upon receiving termination signals (SIGINT, SIGTERM).
2. The video is initialized and configured for three channels with different formats and frame rates:
   - **Channel 0**: RGB888 format, 1920x1080 resolution, 10 FPS
   - **Channel 1**: NV21 format, 1920x1080 resolution, 5 FPS
   - **Channel 2**: H.264 format, 1920x1080 resolution, 30 FPS
3. Depending on the channel:
   - For **Channel 0** and **Channel 1**: Frames are saved in RGB and NV21 formats, respectively.
   - For **Channel 2**: Frames are streamed over RTSP.
4. The application runs indefinitely until interrupted.

### Example Output Messages

During execution, you may see log messages indicating the processing of frames and the status of file saving:

```
start save file to /userdata/local/VENC0_0.h264
save frame to /mnt/sd/0_1920x1080.rgb
```

## Conclusion

This example serves as a basic introduction to using the Sophgo SDK for video processing and streaming. Users can modify the code and adapt it for their specific needs, experimenting with different video formats and streaming configurations.

For further details on the Sophgo SDK, refer to the official documentation provided with the SDK.