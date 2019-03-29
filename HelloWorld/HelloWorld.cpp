#include<iostream>
#include<opencv2/opencv.hpp>

#include"ex1.h"

using namespace cv;

int main() {

	std::cout << "Hello,world!" << std::endl;

	// ��ȡͼƬ
	Mat image = imread("../Data/Test.bmp", IMREAD_UNCHANGED);
	imshow("Origin", image);

	// �ҶȻ�
	Mat gray = ex1::toGray(image);
	imshow("Gray", gray);

	// ��ֵ��
	Mat bin = gray.clone();
	ex1::threshold(bin, 85);
	imshow("Binarization", bin);

	waitKey();
}