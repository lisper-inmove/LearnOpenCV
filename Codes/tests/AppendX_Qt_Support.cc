#include "pch.h"
#include "tester.h"
#include "gtest/gtest.h"
#include <array>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

/**
 * 第四章: 卷积操作
 * */

namespace cvtest::tester {
TEST_F(Tester, QtSupportTest) {
  cv::Mat image = cv::imread(filepath_);
  cv::namedWindow("Image", cv::WINDOW_GUI_EXPANDED);
  std::cout << "OpenCV build information:\n"
            << cv::getBuildInformation() << "\n";
  cv::imshow("Image", image);
  cv::displayStatusBar("Image", "Ready", 1000);
  cv::waitKey(0);
  cv::destroyAllWindows();
}

} // namespace cvtest::tester
