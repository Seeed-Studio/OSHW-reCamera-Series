#include <chrono>
#include <fstream>
#include <iostream>
#include <numeric>
#include <stdio.h>
#include <string>
#include <opencv2/opencv.hpp>
#include <sscma.h>
#include <vector>
#include <thread>       // 解决std::this_thread错误

#include <ClassMapper.h>    
#include <unistd.h>





class ColorPalette {
public:
    static std::vector<cv::Scalar> getPalette() {
        return palette;
    }

    static cv::Scalar getColor(int index) {
        return palette[index % palette.size()];
    }

private:
    static const std::vector<cv::Scalar> palette;
};

const std::vector<cv::Scalar> ColorPalette::palette = {
    cv::Scalar(0, 255, 0),     cv::Scalar(0, 170, 255), cv::Scalar(0, 128, 255), cv::Scalar(0, 64, 255),  cv::Scalar(0, 0, 255),     cv::Scalar(170, 0, 255),   cv::Scalar(128, 0, 255),
    cv::Scalar(64, 0, 255),    cv::Scalar(0, 0, 255),   cv::Scalar(255, 0, 170), cv::Scalar(255, 0, 128), cv::Scalar(255, 0, 64),    cv::Scalar(255, 128, 0),   cv::Scalar(255, 255, 0),
    cv::Scalar(128, 255, 0),   cv::Scalar(0, 255, 128), cv::Scalar(0, 255, 255), cv::Scalar(0, 128, 128), cv::Scalar(128, 0, 255),   cv::Scalar(255, 0, 255),   cv::Scalar(128, 128, 255),
    cv::Scalar(255, 128, 128), cv::Scalar(255, 64, 64), cv::Scalar(64, 255, 64), cv::Scalar(64, 64, 255), cv::Scalar(128, 255, 255), cv::Scalar(255, 255, 128),
};

cv::Mat preprocessImage(cv::Mat& image, ma::Model* model) {
    int ih = image.rows;
    int iw = image.cols;
    int oh = 0;
    int ow = 0;

    if (model->getInputType() == MA_INPUT_TYPE_IMAGE) {
        oh = reinterpret_cast<const ma_img_t*>(model->getInput())->height;
        ow = reinterpret_cast<const ma_img_t*>(model->getInput())->width;
    }

    cv::Mat resizedImage;
    double resize_scale = std::min((double)oh / ih, (double)ow / iw);
    int nh              = (int)(ih * resize_scale);
    int nw              = (int)(iw * resize_scale);
    cv::resize(image, resizedImage, cv::Size(nw, nh));
    int top    = (oh - nh) / 2;
    int bottom = (oh - nh) - top;
    int left   = (ow - nw) / 2;
    int right  = (ow - nw) - left;

    cv::Mat paddedImage;
    cv::copyMakeBorder(resizedImage, paddedImage, top, bottom, left, right, cv::BORDER_CONSTANT, cv::Scalar::all(0));
    cv::cvtColor(paddedImage, paddedImage, cv::COLOR_BGR2RGB);

    return paddedImage;
}

void release_camera(ma::Camera*& camera) noexcept {
    
    camera->stopStream();
    camera = nullptr; // 确保线程安全
}

void release_model(ma::Model*& model, ma::engine::EngineCVI*& engine) {
    if (model) ma::ModelFactory::remove(model);  // 先释放model
    if (engine) delete engine; 

    model = nullptr;
    engine = nullptr;
}


ma::Camera* initialize_camera() noexcept{

    ma::Device* device = ma::Device::getInstance();
    ma::Camera* camera = nullptr;

    for (auto& sensor : device->getSensors()) {
        if (sensor->getType() == ma::Sensor::Type::kCamera) {
            camera = static_cast<ma::Camera*>(sensor);
            break;
        }
    }
    if (!camera) {
        MA_LOGE(TAG, "No camera sensor found");
        return camera;
    }
    if (camera->init(0) != MA_OK) {  // 假设0是默认模式
        MA_LOGE(TAG, "Camera initialization failed");
        return camera;
    }

    ma::Camera::CtrlValue value;
    value.i32 = 0;
    if (camera->commandCtrl(ma::Camera::CtrlType::kChannel, ma::Camera::CtrlMode::kWrite, value) != MA_OK) {
        MA_LOGE(TAG, "Failed to set camera channel");
        return camera;
    }

    value.u16s[0] = 1920;
    value.u16s[1] = 1080;
    if (camera->commandCtrl(ma::Camera::CtrlType::kWindow, ma::Camera::CtrlMode::kWrite, value) != MA_OK) {
        MA_LOGE(TAG, "Failed to set camera resolution");
        return camera;
    }

    value.i32 = 5;
    camera->commandCtrl(ma::Camera::CtrlType::kFps, ma::Camera::CtrlMode::kWrite, value);

    value.i32 = 0;
    camera->commandCtrl(ma::Camera::CtrlType::kFps, ma::Camera::CtrlMode::kRead, value);
    
    MA_LOGI(MA_TAG, "The value of kFps is: %d",  value.i32);

    value.i32 = 1;
    if (camera->commandCtrl(ma::Camera::CtrlType::kChannel, ma::Camera::CtrlMode::kWrite, value) != MA_OK) {
        MA_LOGE(TAG, "Failed to set camera channel");
        return camera;
    }
    value.u16s[0] = 1920;
    value.u16s[1] = 1080;
    if (camera->commandCtrl(ma::Camera::CtrlType::kWindow, ma::Camera::CtrlMode::kWrite, value) != MA_OK) {
        MA_LOGE(TAG, "Failed to set camera resolution");
        return camera;
    }
    value.i32 = 5;
    camera->commandCtrl(ma::Camera::CtrlType::kFps, ma::Camera::CtrlMode::kWrite, value);

    value.i32 = 0;
    camera->commandCtrl(ma::Camera::CtrlType::kFps, ma::Camera::CtrlMode::kRead, value);
    
    MA_LOGI(MA_TAG, "The value of kFps is: %d",  value.i32);
    value.i32 = 2;
    if (camera->commandCtrl(ma::Camera::CtrlType::kChannel, ma::Camera::CtrlMode::kWrite, value) != MA_OK) {
        MA_LOGE(TAG, "Failed to set camera channel");
        return camera;
    }
    value.i32 = 5;
    camera->commandCtrl(ma::Camera::CtrlType::kFps, ma::Camera::CtrlMode::kWrite, value);

    value.i32 = 0;
    camera->commandCtrl(ma::Camera::CtrlType::kFps, ma::Camera::CtrlMode::kRead, value);
    
    MA_LOGI(MA_TAG, "The value of kFps is: %d",  value.i32);


    camera->startStream(ma::Camera::StreamMode::kRefreshOnReturn);

    return camera;

}
// 定义函数（放在 main 之前）
size_t getCurrentRSS() {
    long rss = 0L;
    FILE* fp = nullptr;
    if ((fp = fopen("/proc/self/statm", "r")) == nullptr)
        return 0; // 无法获取
    
    if (fscanf(fp, "%*s%ld", &rss) != 1) {
        fclose(fp);
        return 0;
    }
    fclose(fp);
    return rss * sysconf(_SC_PAGESIZE) / 1024; // 转换为 KB
}


ma::Model* initialize_model(const std::string& model_path) noexcept{
    ma::Model* model_null = nullptr;
    ma_err_t ret = MA_OK;
    using namespace ma;
    auto* engine = new ma::engine::EngineCVI();
    ret          = engine->init();
    if (ret != MA_OK) {
        MA_LOGE(TAG, "engine init failed");
        delete engine;
        return model_null;
    }
    ret = engine->load(model_path);

    MA_LOGI(TAG, "engine load model %s", model_path);
    if (ret != MA_OK) {
        MA_LOGE(TAG, "engine load model failed");
        delete engine;
        return model_null;
    }

    ma::Model* model = ma::ModelFactory::create(engine);

    if (model == nullptr) {
        MA_LOGE(TAG, "model not supported");
        ma::ModelFactory::remove(model);
        delete engine;
        return model_null;
    }

    MA_LOGI(TAG, "model type: %d", model->getType());

    return model;
}

const std::vector<std::string> ClassMapper::classes= {
        "person", "bicycle", "car", "motorcycle", "airplane", "bus", "train", "truck", "boat", "traffic light",
        "fire hydrant", "stop sign", "parking meter", "bench", "bird", "cat", "dog", "horse", "sheep", "cow",
        "elephant", "bear", "zebra", "giraffe", "backpack", "umbrella", "handbag", "tie", "suitcase", "frisbee",
        "skis", "snowboard", "sports ball", "kite", "baseball bat", "baseball glove", "skateboard", "surfboard",
        "tennis racket", "bottle", "wine glass", "cup", "fork", "knife", "spoon", "bowl", "banana", "apple",
        "sandwich", "orange", "broccoli", "carrot", "hot dog", "pizza", "donut", "cake", "chair", "couch",
        "potted plant", "bed", "dining table", "toilet", "tv", "laptop", "mouse", "remote", "keyboard", "cell phone",
        "microwave", "oven", "toaster", "sink", "refrigerator", "book", "clock", "vase", "scissors", "teddy bear",
        "hair drier", "toothbrush"
    };

std::string model_detector(ma::Model*& model,ma::Camera*& camera,int& i) {

    static char buf[8*1024*1024];
    uint32_t count = 0;

    std::string rest="";
    cv::Mat image_catch;
    cv::Mat image;
    
    ma_img_t jpe;
    ma_img_t jpeg;

    int times = 5;
    size_t memory_samples[9];
    memory_samples[0] = getCurrentRSS(); // 直接调用
    MA_LOGI(MA_TAG, "Memory usage: %d",  memory_samples[0],"KB");

    auto start_relea = std::chrono::steady_clock::now();
    for (int k = 0; k <= times; k++) {
        ma_err_t ret = camera->retrieveFrame(jpe, MA_PIXEL_FORMAT_JPEG);
        if (ret != MA_OK) {
            MA_LOGE(TAG, "retrieveFrame failed");
            k--;
            continue;
        }
        
        jpe.physical=false;
        camera->returnFrame(jpe);
        // if (jpe.data != nullptr) {
        //     free(jpe.data);  // 或 delete[] img.data
        jpe.data = nullptr;
        // }
        // memset(&jpe, 0, sizeof(jpe));

        std::this_thread::sleep_for(std::chrono::milliseconds(20));

        memory_samples[k+1] = getCurrentRSS(); // 直接调用
        MA_LOGI(MA_TAG, "Memory usage_during_: %d",  memory_samples[k+1],"KB");
    }


    auto duration_relea  =std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now()-start_relea).count();

    auto start_retrieve = std::chrono::steady_clock::now();
    camera->retrieveFrame(jpeg, MA_PIXEL_FORMAT_JPEG);
    MA_LOGI(MA_TAG, "jpeg size: %d", jpeg.size);
    auto duration_retrieve  =std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now()-start_retrieve).count();

    //     std::string filename = "image_catched_"+std::to_string(i)+".jpg";
    image_catch = cv::imdecode(cv::Mat(1, jpeg.size, CV_8UC1, jpeg.data),cv::IMREAD_COLOR);
    // // 存
    //     cv::imwrite(filename, image_catch);
    camera->returnFrame(jpeg);
    
    memory_samples[6] = getCurrentRSS(); // 直接调用
    MA_LOGI(MA_TAG, "Memory usage_after: %d",   memory_samples[6],"KB");
    auto start_preprocess = std::chrono::steady_clock::now();
    
    if (image_catch.empty()) {
        MA_LOGE(TAG, "read image failed");
        return "read image failed";
    }

    image = preprocessImage(image_catch, model);

    if (image.empty()) {  // 检查图像是否为空
        printf("preprocessed image is empty");
        return "preprocessed image is empty";
    }


    ma_img_t img;
    img.data   = (uint8_t*)image.data;
    img.size   = image.rows * image.cols * image.channels();
    img.width  = image.cols;
    img.height = image.rows;
    img.format = MA_PIXEL_FORMAT_RGB888;
    img.rotate = MA_PIXEL_ROTATE_0;

    auto duration_preprocess  =std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now()-start_preprocess).count();

    auto start_detector = std::chrono::steady_clock::now();

    memory_samples[7] = getCurrentRSS(); // 直接调用
    MA_LOGI(MA_TAG, "Memory usage_before_model: %d",  memory_samples[7],"KB");

    ma::model::Detector* detector = static_cast<ma::model::Detector*>(model);
    detector->run(&img);
    auto _results = detector->getResults();
    if (_results.empty()) {
        rest+="No objects detected\n";  // 检测结果为空时的输出
    } else {
        for (auto result : _results) {
            float x1 = (result.x - result.w / 2.0) * image.cols;
            float y1 = (result.y - result.h / 2.0) * image.rows;
            float x2 = (result.x + result.w / 2.0) * image.cols;
            float y2 = (result.y + result.h / 2.0) * image.rows;
            std::string class_name = ClassMapper::get_class(result.target);
            rest+="Score: " + std::to_string(result.score)+",Target: " + class_name+
                   "  Box: [" + std::to_string(x1) + ", " + std::to_string(y1) + ", " + std::to_string(x2) + ", " + std::to_string(y2) + "]"+"   Center:[" + std::to_string(result.x) + ", " + std::to_string(result.y) + "]   Size:[" + std::to_string(result.w) + ", " + std::to_string(result.h)+"]";
            cv::rectangle(image, cv::Point(x1, y1), cv::Point(x2, y2), ColorPalette::getColor(result.target), 3, 8, 0);
            cv::putText(image, class_name, cv::Point(x1, y1 - 10), cv::FONT_HERSHEY_SIMPLEX, 0.6, ColorPalette::getColor(result.target), 2, cv::LINE_AA);
        }
        cv::cvtColor(image, image, cv::COLOR_RGB2BGR);
        
    }
    std::string filename2 = "image_detected_"+std::to_string(i)+".jpg";
    cv::imwrite(filename2, image);

    memory_samples[8] = getCurrentRSS(); // 直接调用
    MA_LOGI(MA_TAG, "Memory usage_after_model: %d",  memory_samples[8],"KB");
    
    auto perf = model->getPerf();
    MA_LOGI(TAG, "pre: %ldms, infer: %ldms, post: %ldms", perf.preprocess, perf.inference, perf.postprocess);
    auto duration_detector  =std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now()-start_detector).count();
    rest+="Release_duration:"+std::to_string(duration_relea)+"Capture_duration:" + std::to_string(duration_retrieve)+"Image_preprocessing_duration:" + std::to_string(duration_preprocess) + "Detection_duration: " + std::to_string(duration_detector) + "\n";
    return rest;

}


