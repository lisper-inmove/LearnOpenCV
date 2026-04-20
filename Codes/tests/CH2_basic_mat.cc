#include "pch.h"
#include "tester.h"
#include <array>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/core/hal/interface.h>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

/**
 * 第二章: Mat对象操作
 * */

namespace cvtest::tester {
TEST_F(Tester, BasicMat) {
  // 创建Mat
  cv::Mat mat = cv::Mat::ones(5, 5, CV_8UC3);
  std::cout << mat << "\n";

  // Mat的复制
  cv::Mat m;
  mat.copyTo(m);
  // Mat的克隆
  cv::Mat m2 = mat.clone();
  // // Mat的ROI
  cv::Rect roi(0, 0, 3, 3);
  cv::Mat roiMat = mat(roi);
}

TEST_F(Tester, IteratorMat) {
  std::array<uchar, 256> table;
  for (int i = 0; i < 256; i++) {
    table[i] = (uchar)(16 * (i / 16));
  }

  // Mat的遍历
  cv::Mat mat = cv::Mat::ones(5, 5, CV_8UC3);
  EXPECT_EQ(mat.rows, 5);
  EXPECT_EQ(mat.cols, 5);
  EXPECT_EQ(mat.type(), CV_8UC3);

  for (int row = 0; row < mat.rows; row++) {

    for (int col = 0; col < mat.cols; col++) {
      cv::Vec3b pv = mat.at<cv::Vec3b>(row, col);
      EXPECT_EQ(pv[0], 1);
      EXPECT_EQ(pv[1], 0);
    }
  }

  {
    cv::MatIterator_<uchar> it, end;
    for (it = mat.begin<uchar>(), end = mat.end<uchar>(); it != end; ++it) {
      *it = table[*it];
    }
  }

  {
    cv::MatIterator_<cv::Vec3b> it, end;
    for (it = mat.begin<cv::Vec3b>(), end = mat.end<cv::Vec3b>(); it != end;
         ++it) {
      (*it)[0] = table[(*it)[0]];
      (*it)[1] = table[(*it)[1]];
      (*it)[2] = table[(*it)[2]];
    }
  }

  // 加减乘除
  {
    /**
     * 加
     * void cv::add(InputArray src1, InputArray src2, OutputArray dst,
     * InputArray mask = noArray(), int dtype = -1)
     *
     * 加
     * subtract
     *
     * 乘
     * void cv::multiply(InputArray src1, InputArray src2, OutputArray dst,
     * double scale = 1, int dtype = -1)
     *
     * 除
     * */
    cv::Mat mat2 = mat.clone();
    cv::Mat mat3;
    cv::add(mat, mat2, mat3);
    cv::subtract(mat, mat2, mat3);
    cv::multiply(mat, mat2, mat3);
    cv::divide(mat, mat2, mat3);
    cv::bitwise_not(mat, mat3);
    cv::bitwise_and(mat, mat2, mat3);
  }

  {
    cv::Mat mat2 = mat.clone();
    mat2.setTo(cv::Scalar(0.9, 0.9, 0.9));
  }
}

TEST_F(Tester, BitOperateTest) {

  // 位运算
  /**
   * void cv::bitwise_not(InputArray src, OutputArray dst, Inputarray mask =
   * noArray())
   *
   * 位与，位或，位异或 参数相同: bitwise_or, bitwise_xor
   * void cv::bitwise_and(InputArray src1, InputArray src2, OutputArray dst,
   * InputArray mask = noArray())
   * */
  cv::Mat mat1 = cv::Mat::zeros(3, 3, CV_8UC3);
  mat1.setTo(cv::Scalar(2, 2, 2));
  cv::Mat mat2 = cv::Mat::zeros(3, 3, CV_8UC3);
  mat2.setTo(cv::Scalar(0.9, 0.9, 0.9));
  cv::Mat mat3;
  cv::bitwise_and(mat1, mat2, mat3);
  std::cout << mat3 << "\n";
}

TEST_F(Tester, ImageTypeAndChannelTest) {
  /**
   * 图像类型与通道
   * void cv::Mat::convertTo(
   *  OutputArray m, // 输出图像
   *  int rtype,  // 要转换到的类型
   *  double alpha = 1, // 缩放
   *  double beta = 0; // 加合
   * ) const
   *
   * int cv::Mat::channels() const; 返回图像通道
   * */
  cv::Mat f1 = cv::Mat::zeros(3, 3, CV_32FC3);
  f1.setTo(cv::Scalar(0.9, 2.3, 0.27));
  std::cout << f1 << "\n";
  cv::Mat f2;
  f1.convertTo(f2, CV_8U); // 小数部分4舍5入
  std::cout << f2 << "\n";
  std::cout << "channels: " << f1.channels() << "\n";
}

TEST_F(Tester, CVTColorTest) {
  /**
   * void cv::cvtColor {
   *  InputArray src,
   *  OutputArray dst,
   *  int cod,  // 颜色空间转换代码
   *  int dstCn = 0, // 目标图像的通道数
   * }
   *
   * COLOR_BGR2GRAY    // BGR → 灰度
   * COLOR_RGB2GRAY    // RGB → 灰度
   * COLOR_BGR2RGB     // BGR → RGB
   * COLOR_BGR2HSV     // BGR → HSV
   * COLOR_RGB2HSV     // RGB → HSV
   * COLOR_BGR2HLS     // BGR → HLS
   * COLOR_BGR2Lab     // BGR → CIE Lab
   * COLOR_BGR2Luv     // BGR → CIE Luv
   * COLOR_BGR2YUV     // BGR → YUV
   * COLOR_BGR2YCrCb   // BGR → YCrCb
   * COLOR_HSV2BGR     // HSV → BGR
   * COLOR_HSV2RGB     // HSV → RGB
   * COLOR_HLS2BGR     // HLS → BGR
   * COLOR_BayerBG2BGR // Bayer 模式转 BGR
   * COLOR_BGR2XYZ     // BGR → XYZ
   * COLOR_BGR2LAB     // BGR → CIELAB
   * COLOR_BGR2LUV     // BGR → CIELUV
   *
   * dstCn: 0，从src到code自动推导。大于0，指定通道数。通常不需要手动设置
   * */
}

TEST_F(Tester, ChannelOperateTest) {
  /**
   * 通道分离
   * void cv::split(
   *  const Mat &src,  // 输入图像
   *  Mat* mvbegin // 输出的通道Mat数组,用std::vector<Mat>
   * )
   * 通道合并
   * void cv::merge(
   *  InputArrayOfArrays mv, // 输入的多个单通道数据
   *  OutputArray dst // 输出
   * )
   * 通道混合
   * void cv::mixChannels(
   *  const Mat* src,     // 输入图像数组
   *  size_t nsrcs,       // 输入图像数目
   *  Mat* dst,
   *  size_t ndsts,       // 输出数目
   *  const int *fromTo,  // 通道映射规则数
   *  size_t npairs       // 通道映射规则数量
   * )
   * void cv::mixChannels(
   *  InputArrayOfArrays src,
   *  InputOutputArrayOfArrays dst,
   *  const std::vector<int>& fromTo  // 通道映射规则
   * )
   * */
  cv::Mat image = cv::imread(filepath_);
  std::array<cv::Mat, 3> bgr_;
  cv::split(image, bgr_);
  std::cout << bgr_[0].size << "\n"
            << bgr_[1].size << "\n"
            << bgr_[2].size << "\n";

  cv::Mat mat1;
  cv::merge(bgr_, mat1);

  cv::imshow("bgr1", bgr_[0]);
  cv::imshow("bgr2", bgr_[1]);
  cv::imshow("bgr3", bgr_[2]);
  cv::imshow("merged", mat1);
  cv::waitKey();
  cv::destroyAllWindows();
}

TEST_F(Tester, ChannelOperateMixTest) {
  cv::Mat image = cv::imread(filepath_);
  std::vector<cv::Mat> srcVec = {image};
  std::vector<cv::Mat> dstVec(3);
  for (int i = 0; i < 3; i++) {
    dstVec[i] = cv::Mat(image.size(), CV_8UC1);
  }

  // 4个为一组
  // 0: src[0], 0: src[0][0]: 第一个用于选择一个src,第二个用于选择一个通道
  // 0: dst[0], 0: dst[0][0]
  std::vector<int> fromTo = {0, 0, 0, 0, 0, 1, 1, 0, 0, 2, 2, 0};
  cv::mixChannels(srcVec, dstVec, fromTo);

  cv::imshow("bgr1", dstVec[0]);
  cv::imshow("bgr2", dstVec[1]);
  cv::imshow("bgr3", dstVec[2]);
  cv::waitKey();
  cv::destroyAllWindows();
}
} // namespace cvtest::tester
