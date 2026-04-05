#pragma once
#include <filesystem>

#include "pch.h"
#include <gtest/gtest.h>

namespace cvtest::tester {
class Tester : public ::testing::Test {
public:
  void SetUp() override;
  void TearDown() override;
  int sharpenValue(cv::Mat &image);

protected:
  std::string assets_ = "/home/inmove/nvme1/Learn/LearnOpenCV/Codes/assets/";
  std::string filepath_ = std::filesystem::path(assets_) / "bee.png";
  std::string cxPath_ = std::filesystem::path(assets_) / "xt.png";
  std::string stuffPath_ = std::filesystem::path(assets_) / "stuff.jpg";
  std::string contoursPath_ = std::filesystem::path(assets_) / "contours.png";
  std::string ricePath_ = std::filesystem::path(assets_) / "rice.png";
  std::string savedFilepath_ = std::filesystem::path(assets_) / "bee2.png";
  std::string videoPath_ = std::filesystem::path(assets_) / "green_light.mp4";
  std::string jyNoisePath_ = std::filesystem::path(assets_) / "jy_noise.png";
  std::string gsNoisePath_ = std::filesystem::path(assets_) / "gs.png";
};
} // namespace cvtest::tester
