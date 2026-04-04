#include "pch.h"
#include "tester.h"
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/core/base.hpp>
#include <opencv2/core/fast_math.hpp>
#include <opencv2/core/hal/interface.h>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

namespace cvtest::tester {
TEST_F(Tester, MarginDetectTest) {
  /**
   * 边缘检测
   * 标准的边缘检测，包括以下几步
   * 1. 将图像转成灰度图
   * 2. 通过高斯卷积实现降噪
   * 3. 计算图像梯度的大小与角度
   * 4. 非最大信号压制
   * 5. 双阈值边缘连接
   *
   * void cv::Canny(
   *  InputArray image,
   *  OutputArray edges,
   *  double threshold1,
   *  double threshold2,
   *  int apertureSize = 3,
   *  bool L2gradient = false
   * )
   * */
  cv::Mat image = cv::imread(filepath_, cv::IMREAD_COLOR);
  cv::Mat edge;
  cv::Canny(image, edge, 150, 300, 3, false);
  cv::imshow("Source", image);
  cv::imshow("Edge", edge);
  cv::waitKey(0);
  cv::destroyAllWindows();
}
} // namespace cvtest::tester
