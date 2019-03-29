#include<iostream>
#include<opencv2/opencv.hpp>

#include"ex1.h"
#include"ex2.h"

using namespace cv;

int main() {

	std::cout << "Hello,world!" << std::endl;

	// 读取图片
	Mat image = imread("../Data/Test.bmp", IMREAD_UNCHANGED);
	imshow("Origin", image);

	// 灰度化
	Mat gray = ex1::gray(image);
	imshow("Gray", gray);

	// 二值化
	Mat bin = gray.clone();
	ex1::threshold(bin, 85);
	imshow("Binarization", bin);

	// 获取边界
	Mat line = ex2::line(bin);
	imshow("Line", line);

	waitKey();
}