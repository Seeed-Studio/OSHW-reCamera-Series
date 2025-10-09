#ifndef MODEL_DETECTOR_H
#define MODEL_DETECTOR_H
// 头文件内容
#endif

#include <opencv2/opencv.hpp>
#include <sscma.h>
#include <numeric>
struct ClassMapper {
    static const std::vector<std::string> classes;
    static std::string get_class(int index);
};
class ColorPalette {
public:
    static std::vector<cv::Scalar> getPalette();
    static cv::Scalar getColor(int index);

private:
    static const std::vector<cv::Scalar> palette;
};

// 图像预处理函数声明
cv::Mat preprocessImage(cv::Mat& image, ma::Model* model);

void release_camera(ma::Camera*& camera) noexcept;
void release_model(ma::Model*& model, ma::engine::EngineCVI*& engine);
size_t getCurrentRSS();
// 初始化函数
ma::Camera* initialize_camera() noexcept;
ma::Model* initialize_model(const std::string& model_path) noexcept;

// 目标检测主函数
hv::Json model_detector(ma::Model*& model,ma::Camera*& camera,int& i);