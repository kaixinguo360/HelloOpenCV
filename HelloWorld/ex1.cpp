#include<opencv2/opencv.hpp>

using namespace cv;

namespace ex1
{
	// �ҶȻ�
	Mat gray(Mat img)
	{
		// �½���ͨ��ͼ��
		Mat gray(img.rows, img.cols, CV_8UC1);

		// ����OpenCV�ҶȻ�����
		//cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY, 1);

		// �ֶ��ҶȻ�
		for (int i = 0; i < img.rows; i++) {
			for (int j = 0; j < img.cols; j++) {
				Vec3b point = img.at<Vec3b>(i, j);

				// ��Ȩƽ����, ��/��/�� = 0.30/0.59/0.11
				gray.at<uchar>(i, j) = (uchar) (point[0] * 0.30 + point[1] * 0.59 + point[2] * 0.11);
			}
		}

		return gray;
	}

	// ��ֵ��
	void threshold(Mat img, uchar threshold)
	{
		// ����OpenCV��ֵ������
		//cv::threshold(img, img, threshold, 255, cv::THRESH_BINARY);

		// �ֶ���ֵ��
		for (int i = 0; i < img.rows; i++) {
			for (int j = 0; j < img.cols; j++) {
				uchar point = img.at<uchar>(i, j);

				// ����ֵ�Ƚ�
				img.at<uchar>(i, j) = point < threshold ? 0 : 255;
			}
		}
	}
}