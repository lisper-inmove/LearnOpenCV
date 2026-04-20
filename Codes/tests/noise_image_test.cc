#include "pch.h"
#include "tester.h"
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/core/base.hpp>
#include <opencv2/core/fast_math.hpp>
#include <opencv2/core/hal/interface.h>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/matx.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

namespace cvtest::tester {
TEST_F(Tester, NoiseImageTest) {
  /**
   * 生成椒盐噪声图片
   * */
  cv::RNG rng(12345);
  cv::Mat image = cv::imread(filepath_, cv::IMREAD_COLOR);
  int h = image.rows;
  int w = image.cols;
  int nums = 10000;
  cv::Mat noiseImg = image.clone();
  for (int i = 0; i < nums; i++) {
    int x = rng.uniform(0, w);
    int y = rng.uniform(0, h);
    if (i % 2 == 0) {
      noiseImg.at<cv::Vec3b>(y, x) = cv::Vec3b(255, 255, 255);
    } else {
      noiseImg.at<cv::Vec3b>(y, x) = cv::Vec3b(0, 0, 0);
    }
  }
  cv::imshow("Source", image);
  cv::imshow("Noise Image", noiseImg);
  cv::waitKey(0);
  cv::destroyAllWindows();
  cv::imwrite(jyNoisePath_, noiseImg);
}

TEST_F(Tester, GaussianNoiseImageTest) {
  /**
   * 生成高斯噪声图片
   * */
  cv::RNG rng(12345);
  cv::Mat image = cv::imread(filepath_, cv::IMREAD_COLOR);
  cv::Mat noiseImg = cv::Mat::zeros(image.size(), image.type());
  cv::randn(noiseImg, (15, 15, 15), (30, 30, 30));
  cv::Mat dst;
  cv::add(image, noiseImg, dst);
  cv::imshow("Source", image);
  cv::imshow("Gaussian Noise Image", dst);
  cv::waitKey(0);
  cv::destroyAllWindows();
  cv::imwrite(gsNoisePath_, dst);
}

} // namespace cvtest::tester
