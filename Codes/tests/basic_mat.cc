#include "tester.h"
#include "pch.h"

namespace cvtest::tester
{
    TEST_F(Tester, BasicMat)
    {
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

    TEST_F(Tester, IteratorMat)
    {
        // Mat的遍历
        cv::Mat mat = cv::Mat::ones(5, 5, CV_8UC3);
        EXPECT_EQ(mat.rows, 5);
        EXPECT_EQ(mat.cols, 5);
        EXPECT_EQ(mat.type(), CV_8UC3);

        for (int row = 0; row < mat.rows; row++)
        {

            for (int col = 0; col < mat.cols; col++)
            {
                cv::Vec3b pv = mat.at<cv::Vec3b>(row, col);
                EXPECT_EQ(pv[0], 1);
                EXPECT_EQ(pv[1], 0);
            }
        }
    }
}
