#include <opencv2/opencv.hpp>
#include <iostream>
//2025/04/17　VirtualBox上でWebカメラが動いた！
int main() {
    // VideoCaptureの初期化（v4l2を明示的に使用）
    cv::VideoCapture cap(0, cv::CAP_V4L2);  // ここは video0。動かない場合は 1〜3 も試す。

    if (!cap.isOpened()) {
        std::cerr << "カメラを開けませんでした" << std::endl;
        return -1;
    }

    // 解像度とフォーマットの設定（必要に応じて）
    cap.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M','J','P','G'));  // MJPEG形式
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);

    cv::Mat frame;

    while (true) {
        cap >> frame;
        if (frame.empty()) {
            std::cerr << "フレームの取得に失敗しました" << std::endl;
            break;
        }

        cv::imshow("カメラ映像", frame);

        // ESCキーで終了（waitKeyは10ミリ秒待つ）
        if (cv::waitKey(10) == 27) break;
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}
