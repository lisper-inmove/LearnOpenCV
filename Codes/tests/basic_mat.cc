#include "pch.h"
#include "tester.h"
#include <opencv2/core.hpp>

namespace cvtest::tester {
TEST_F(Tester, BasicMat) {
  // 创建Mat
  cv::Mat mat = cv::Mat::zeros(100, 100, CV_8UC3);
  EXPECT_EQ(mat.rows, 100);
  EXPECT_EQ(mat.cols, 100);
  EXPECT_EQ(mat.type(), CV_8UC3);

  // Mat的复制
  cv::Mat m;
  mat.copyTo(m);
  // Mat的克隆
  cv::Mat m2 = mat.clone();
  // Mat的ROI
  cv::Rect roi(0, 0, 20, 20);
  cv::Mat roiMat = mat(roi);
  EXPECT_EQ(roiMat.rows, 20);
  EXPECT_EQ(roiMat.cols, 20);
  EXPECT_EQ(roiMat.type(), CV_8UC3);
}

TEST_F(Tester, IteratorMat) {
  uchar table[256];
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

  {
    /**
     * void cv::mat::convertTo(OutputArray m, int rtype, double alpha = 1,
     * double beta = 0) const;
     * rtype: 数据类型
     * alpha 和 beta: 缩放 和 加和
     * 转换类型之后: m = saturate<rType>(src(x, y) * alpha + beta)
     * */

    /**
     * int cv::Mat::channels() const;
     * 返回图像通道
     * */

    /**
     * void cv::cvtColor(
     *    InputArray src,
     *    OutputArray dst,
     *    int code, // 转换格式 // COLOR_BGR2GRAY COLOR_GRAY2BGR 等
     *    int dstCn = 0
     * );
     * */

    /**
     * 通道分离
     * void cv::split(const Mat& src, Mat* mvbegin)
     * 通道合并
     * void cv::merge(InputArrayOfArrays mv, OutputArray dst);
     * 调整通道顺序
     * void cv::mixChannels(
     *     const Mat* src, // 输入数组
     *     size_t nsrcs,   // 输入图像数目
     *     Mat* dst,
     *     size_t ndsts,    // 输出数目
     *     const int* fromTo, // 索引对
     *     size_t npairs  // 索引对数目
     * )
     * */
  }
}
} // namespace cvtest::tester
