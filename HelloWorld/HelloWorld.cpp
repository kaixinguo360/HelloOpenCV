#include<iostream>
#include<opencv2/opencv.hpp>

#include"ex5.h"

using namespace cv;

int main() {

	std::cout << "Hello,world!" << std::endl;

	// 读取图片
	Mat image = imread("../Data/Lenna.png", IMREAD_UNCHANGED);
	cv::cvtColor(image, image, cv::COLOR_BGR2GRAY, 1);
	cv::cvtColor(image, image, cv::COLOR_GRAY2BGR, 3);
	imshow("原始图像", image);

	// 获取高斯权重
	Mat weights = ex5::getGaussianWeights(5, 1);
	printf("\n高斯权重 = \n");
	ex5::printWeights(weights);

	// 高斯平滑图像
	Mat bulr = ex5::conv(image, weights);
	imshow("高斯平滑", bulr);

	// 高斯差分
	Mat bulr1 = ex5::gaussianBulr(image, 5, 0.2);
	Mat bulr2 = ex5::gaussianBulr(image, 5, 2);
	Mat d = bulr1 - bulr2;
	double min, max; // 归一化, 提升显示效果
	cv::minMaxLoc(d, &min, &max);
	d = (d / (max - min)) * 255;
	imshow("高斯差分", d);

	waitKey();
}

