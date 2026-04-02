#include "tester.h"
#include "pch.h"

namespace cvtest::tester
{
    TEST_F(Tester, OpenImage)
    {
        cv::Mat image = cv::imread(filepath_, cv::IMREAD_COLOR);
        cv::namedWindow("OpenCV Window", cv::WINDOW_AUTOSIZE);
        cv::imshow("OpenCV Window", image);
        cv::waitKey(0);
        cv::destroyAllWindows();
        // imwrite(const string& filename, InputArray img, const std::vector<int>& params = {})
        // 第三个参数是保存图片的参数
        //  如果是PNG格式，需要添加参数cv::IMWRITE_PNG_COMPRESSION=9
        //  如果是JPG格式，需要添加参数cv::IMWRITE_JPEG_QUALITY=90
        std::vector<int> opts;
        opts.push_back(cv::IMWRITE_PNG_COMPRESSION);
        opts.push_back(9);
        cv::imwrite(savedFilepath_, image);
    }

    TEST_F(Tester, OpenVideo)
    {
        cv::VideoCapture cap(videoPath_);
        cv::Mat frame;
        cv::namedWindow("OpenCV Window", cv::WINDOW_AUTOSIZE);

        // 获取视频帧率
        double fps = cap.get(cv::CAP_PROP_FPS);
        int delay = static_cast<int>(1000.0 / fps); // 计算每帧延迟时间(ms)

        // 获取视频信息
        double totalFrames = cap.get(cv::CAP_PROP_FRAME_COUNT);
        double width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
        double height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);

        std::cerr << "Video Info:" << std::endl;
        std::cerr << "  FPS: " << fps << std::endl;
        std::cerr << "  Total Frames: " << totalFrames << std::endl;
        std::cerr << "  Resolution: " << width << "x" << height << std::endl;
        std::cerr << "  Press 'q' or 'ESC' to quit" << std::endl;

        while (true)
        {
            bool ret = cap.read(frame);
            if (!ret)
            {
                break;
            }
            cv::imshow("OpenCV Window", frame);
            cv::waitKey(1);
            char key = static_cast<char>(cv::waitKey(delay));
            if (key == 'q' || key == 27) // 27 = ESC
            {
                break;
            }
        }
        cap.release(); // 释放视频资源
        cv::destroyAllWindows();
    }
}
