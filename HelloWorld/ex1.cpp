#include<opencv2/opencv.hpp>

using namespace cv;

namespace ex1
{
	// 灰度化
	Mat gray(Mat img)
	{
		// 新建单通道图像
		Mat gray(img.rows, img.cols, CV_8UC1);

		// 调用OpenCV灰度化函数
		//cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY, 1);

		// 手动灰度化
		for (int i = 0; i < img.rows; i++) {
			for (int j = 0; j < img.cols; j++) {
				Vec3b point = img.at<Vec3b>(i, j);

				// 加权平均法, 红/黄/蓝 = 0.30/0.59/0.11
				gray.at<uchar>(i, j) = (uchar) (point[0] * 0.30 + point[1] * 0.59 + point[2] * 0.11);
			}
		}

		return gray;
	}

	// 二值化
	void threshold(Mat img, uchar threshold)
	{
		// 调用OpenCV二值化函数
		//cv::threshold(img, img, threshold, 255, cv::THRESH_BINARY);

		// 手动二值化
		for (int i = 0; i < img.rows; i++) {
			for (int j = 0; j < img.cols; j++) {
				uchar point = img.at<uchar>(i, j);

				// 与阈值比较
				img.at<uchar>(i, j) = point < threshold ? 0 : 255;
			}
		}
	}
}