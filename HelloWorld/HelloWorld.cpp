#include<iostream>
#include<opencv2/opencv.hpp>

int main() {

	std::cout << "Hello,world!" << std::endl;

	// ��ȡͼƬ
	cv::Mat image = cv::imread("../Data/Test.bmp", cv::IMREAD_UNCHANGED);
	cv::imshow("Origin", image);

	// �ҶȻ�
	cv::Mat gray = image.clone();
	
	// ����OpenCV�ҶȻ�����
	//cv::cvtColor(gray, gray, cv::COLOR_BGR2GRAY, 1);

	// �ֶ��ҶȻ�
	for (int i = 0; i < gray.rows; i++) {
		for (int j = 0; j < gray.rows; j++) {
			cv::Vec3b point = gray.at<cv::Vec3b>(i, j);

			// ��Ȩƽ����, ��/��/�� = 0.30/0.59/0.11
			point[0] = point[1] = point[2]
				= point[0] * 0.30 + point[1] * 0.59 + point[2] * 0.11;
			gray.at<cv::Vec3b>(i, j) = point;
		}
	}
	cv::imshow("Gray", gray);
	
	// ��ֵ��
	cv::Mat bin = gray.clone();

	// ����OpenCV��ֵ������
	//cv::threshold(bin, bin, 85, 255, cv::THRESH_BINARY);

	// �ֶ���ֵ��
	for (int i = 0; i < bin.rows; i++) {
		for (int j = 0; j < bin.rows; j++) {
			cv::Vec3b point = bin.at<cv::Vec3b>(i, j);

			// ��Ȩƽ����, ��/��/�� = 0.30/0.59/0.11
			point[0] = point[1] = point[2]
				= point[0] < 85 ? 0 : 255;
			bin.at<cv::Vec3b>(i, j) = point;
		}
	}
	cv::imshow("Binarization", bin);

	cv::waitKey();
}