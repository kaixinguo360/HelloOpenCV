#include<iostream>
#include<opencv2/opencv.hpp>

int main() {

	std::cout << "Hello,world!" << std::endl;

	// 读取图片
	cv::Mat image = cv::imread("../Data/Test.bmp", cv::IMREAD_UNCHANGED);
	cv::imshow("Origin", image);

	// 灰度化
	cv::Mat gray = image.clone();
	
	// 调用OpenCV灰度化函数
	//cv::cvtColor(gray, gray, cv::COLOR_BGR2GRAY, 1);

	// 手动灰度化
	for (int i = 0; i < gray.rows; i++) {
		for (int j = 0; j < gray.rows; j++) {
			cv::Vec3b point = gray.at<cv::Vec3b>(i, j);

			// 加权平均法, 红/黄/蓝 = 0.30/0.59/0.11
			point[0] = point[1] = point[2]
				= point[0] * 0.30 + point[1] * 0.59 + point[2] * 0.11;
			gray.at<cv::Vec3b>(i, j) = point;
		}
	}
	cv::imshow("Gray", gray);
	
	// 二值化
	cv::Mat bin = gray.clone();

	// 调用OpenCV二值化函数
	//cv::threshold(bin, bin, 85, 255, cv::THRESH_BINARY);

	// 手动二值化
	for (int i = 0; i < bin.rows; i++) {
		for (int j = 0; j < bin.rows; j++) {
			cv::Vec3b point = bin.at<cv::Vec3b>(i, j);

			// 加权平均法, 红/黄/蓝 = 0.30/0.59/0.11
			point[0] = point[1] = point[2]
				= point[0] < 85 ? 0 : 255;
			bin.at<cv::Vec3b>(i, j) = point;
		}
	}
	cv::imshow("Binarization", bin);

	cv::waitKey();
}