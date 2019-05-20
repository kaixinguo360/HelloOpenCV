#include<iostream>
#include<opencv2/opencv.hpp>

#include"ex5.h"

using namespace cv;

int main() {

	std::cout << "Hello,world!" << std::endl;

	// ��ȡͼƬ
	Mat image = imread("../Data/Lenna.png", IMREAD_UNCHANGED);
	cv::cvtColor(image, image, cv::COLOR_BGR2GRAY, 1);
	cv::cvtColor(image, image, cv::COLOR_GRAY2BGR, 3);
	imshow("ԭʼͼ��", image);

	// ��ȡ��˹Ȩ��
	Mat weights = ex5::getGaussianWeights(5, 1);
	printf("\n��˹Ȩ�� = \n");
	ex5::printWeights(weights);

	// ��˹ƽ��ͼ��
	Mat bulr = ex5::conv(image, weights);
	imshow("��˹ƽ��", bulr);

	// ��˹���
	Mat bulr1 = ex5::gaussianBulr(image, 5, 0.2);
	Mat bulr2 = ex5::gaussianBulr(image, 5, 2);
	Mat d = bulr1 - bulr2;
	double min, max; // ��һ��, ������ʾЧ��
	cv::minMaxLoc(d, &min, &max);
	d = (d / (max - min)) * 255;
	imshow("��˹���", d);

	waitKey();
}

