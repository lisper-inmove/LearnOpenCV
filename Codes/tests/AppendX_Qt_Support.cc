#include "pch.h"
#include "tester.h"
#include "gtest/gtest.h"
#include <array>
#include <iostream>
#include <opencv2/core/cuda.hpp>
#include <opencv2/cudaarithm.hpp>
#include <opencv2/cudafilters.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/cudawarping.hpp>
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

// 测试 CUDA 设备是否可用
TEST_F(Tester, CudaDeviceAvailableTest) {
  int cuda_devices = cv::cuda::getCudaEnabledDeviceCount();
  std::cout << "CUDA enabled devices count: " << cuda_devices << "\n";

  EXPECT_GT(cuda_devices, 0) << "No CUDA enabled devices found!";

  if (cuda_devices > 0) {
    cv::cuda::printCudaDeviceInfo(0);
    std::cout << "Device Name: " << cv::cuda::getDevice() << "\n";
  }
}

// 测试 CUDA 算术运算性能对比
TEST_F(Tester, CudaPerformanceTest) {
  // 创建大矩阵以获得明显的性能差异
  cv::Mat cpu_mat = cv::Mat::ones(19200, 10800, CV_32FC1);
  cv::Mat cpu_scalar = cv::Mat::ones(19200, 10800, CV_32FC1) * 2.0;
  cv::Mat cpu_result;

  cv::cuda::GpuMat gpu_mat, gpu_scalar, gpu_result;
  gpu_mat.upload(cpu_mat);
  gpu_scalar.upload(cpu_scalar);

  // CPU 运算计时
  double cpu_start = cv::getTickCount();
  cpu_result = cpu_mat + cpu_scalar;
  double cpu_time = (cv::getTickCount() - cpu_start) / cv::getTickFrequency();

  // GPU 运算计时
  double gpu_start = cv::getTickCount();
  cv::cuda::add(gpu_mat, gpu_scalar, gpu_result);
  auto obj = cv::cuda::Stream();
  // cv::cuda::Stream::waitForCompletion();
  obj.waitForCompletion();
  double gpu_time = (cv::getTickCount() - gpu_start) / cv::getTickFrequency();

  std::cout << "CPU time: " << cpu_time * 1000 << " ms" << "\n";
  std::cout << "GPU time: " << gpu_time * 1000 << " ms" << "\n";

  // 下载 GPU 结果进行验证
  cv::Mat gpu_result_cpu;
  gpu_result.download(gpu_result_cpu);

  // 验证结果一致性
  double norm = cv::norm(gpu_result_cpu, cpu_result, cv::NORM_INF);
  EXPECT_LE(norm, 1e-5);

  // 性能测试不强制要求通过，只是输出信息
  if (gpu_time < cpu_time) {
    std::cout << "GPU is faster than CPU (Speedup: " << cpu_time / gpu_time
              << "x)" << "\n";
  } else {
    std::cout << "GPU is slower than CPU for this operation" << "\n";
  }
}

} // namespace cvtest::tester
