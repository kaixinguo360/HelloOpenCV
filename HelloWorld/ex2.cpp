#include<opencv2/opencv.hpp>

using namespace cv;

namespace ex2
{
	// ��ȡ�߽�
	Mat line(Mat img)
	{
		// �½���ͨ��ͼ��
		Mat line(img.rows, img.cols, CV_8UC1);

		// ���һ��/�е�����
		int lastCol = img.cols - 1;
		int lastRow = img.rows - 1;

		// ��ɨ�� (Ϊ��ֹԽ��, �ų����һ��)
		for (int i = 0; i < img.rows; i++) {
			for (int j = 0; j < img.cols - 1; j++) {
				line.at<uchar>(i, j) = (img.at<uchar>(i, j) != img.at<uchar>(i, j + 1)) ?
					0 : 255;
			}
		}
		// ����ɨ�����һ��
		for (int i = 0; i < img.rows; i++) {
			line.at<uchar>(i, lastCol) = (img.at<uchar>(i, lastCol) == 0) ?
				0 : 255;
		}

		// ��ɨ�� (Ϊ��ֹԽ��, �ų����һ��)
		for (int i = 0; i < img.rows; i++) {
			for (int j = 0; j < img.cols; j++) {
				line.at<uchar>(j, i) = (img.at<uchar>(j, i) != img.at<uchar>(j + 1, i)) ?
					0 : line.at<uchar>(j, i);
			}
		}
		// ����ɨ�����һ��
		for (int j = 0; j < img.cols; j++) {
			line.at<uchar>(lastRow, j) = (img.at<uchar>(lastRow, j) == 0) ?
				0 : 255;
		}

		return line;
	}
}