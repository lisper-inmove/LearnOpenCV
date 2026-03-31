#pragma once

#include <gtest/gtest.h>

namespace cvtest::tester
{
    class Tester : public ::testing::Test
    {
    public:
        void SetUp() override;
        void TearDown() override;

    protected:
        std::string filepath_ = "/home/inmove/nvme1/Learn/LearnOpenCV/Codes/assets/bee.png";
        std::string savedFilepath_ = "/home/inmove/nvme1/Learn/LearnOpenCV/Codes/assets/bee2.png";
        std::string videoPath_ = "/home/inmove/nvme1/Learn/book-opencv4-practice/book_images/green_light.mp4";
    };
}