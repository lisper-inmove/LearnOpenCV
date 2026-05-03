#pragma once
#include <filesystem>

#include "pch.h"
#include <gtest/gtest.h>
#include <opencv2/core/types.hpp>

namespace cvtest::tester {
class Tester : public ::testing::Test {
public:
  void SetUp() override;
  void TearDown() override;
  int sharpenValue(cv::Mat &image);
  void drawHistogram1D(const cv::Mat &hist, const std::string &histName,
                       int histSize);
  void drawColorHistogram3Channel(const cv::Mat &src);
  void drawDetailedHistogram(const cv::Mat &gray);
  int calculateLaplacianSum(const cv::Mat &src);

protected:
  cv::Scalar green_{0, 255, 0};
  cv::Scalar blue_{255, 0, 0};
  cv::Scalar red_{0, 0, 255};
  std::string assets_ = "/home/inmove/nvme1/Learn/LearnOpenCV/Codes/assets/";
  std::string filepath_ = std::filesystem::path(assets_) / "bee.png";
  std::string aPath_ = std::filesystem::path(assets_) / "A_image.png";
  std::string abcPath_ = std::filesystem::path(assets_) / "ABC_image.png";
  std::string coinsPath_ = std::filesystem::path(assets_) / "coins.jpg";
  std::string rectContourPath_ =
      std::filesystem::path(assets_) / "rect_contour.png";
  std::string sudokuPath_ = std::filesystem::path(assets_) / "sudoku.png";
  std::string cxPath_ = std::filesystem::path(assets_) / "xt.png";
  std::string grape_ = std::filesystem::path(assets_) / "grape.png";
  std::string grapeTpl_ = std::filesystem::path(assets_) / "grape_tpl.png";
  std::string stuffPath_ = std::filesystem::path(assets_) / "stuff.jpg";
  std::string contoursPath_ = std::filesystem::path(assets_) / "contours.png";
  std::string convexPath_ = std::filesystem::path(assets_) / "convex.png";
  std::string ricePath_ = std::filesystem::path(assets_) / "rice.png";
  std::string savedFilepath_ = std::filesystem::path(assets_) / "bee2.png";
  std::string videoPath_ = std::filesystem::path(assets_) / "green_light.mp4";
  std::string jyNoisePath_ = std::filesystem::path(assets_) / "jy_noise.png";
  std::string gsNoisePath_ = std::filesystem::path(assets_) / "gs.png";
};
} // namespace cvtest::tester
