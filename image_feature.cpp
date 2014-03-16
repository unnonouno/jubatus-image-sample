#include <sstream>

#include <jubatus/core/plugin.hpp>
#include <opencv2/opencv.hpp>

class image_feature : public jubatus::core::fv_converter::binary_feature {
 public:
  void add_feature(
      const std::string& key,
      const std::string& value,
      std::vector<std::pair<std::string, float> >& ret_fv) const {
    std::vector<unsigned char> buf(value.begin(), value.end());
    cv::Mat mat = cv::imdecode(cv::Mat(buf), CV_LOAD_IMAGE_COLOR);
    for (int y = 0; y < mat.rows; ++y) {
      for (int x = 0; x < mat.cols; ++x) {
        const cv::Vec3b& vec = mat.at<cv::Vec3b>(y, x);
        for (int c = 0; c < 3; ++c) {
          std::ostringstream oss;
          oss << key << '-' << x << '-' << y << '-' << c;
          float val = static_cast<float>(vec[c]) / 255.0;
          ret_fv.push_back(std::make_pair(oss.str(), val));
        }
      }
    }
  }
};

extern "C" {
jubatus::core::fv_converter::binary_feature* create(
    const std::map<std::string, std::string>& param) {
  return new image_feature();
}
}
