#include<opencv2/opencv.hpp>

using namespace cv;

namespace ex2
{
	// 获取边界
	Mat line(Mat img)
	{
		// 新建单通道图像
		Mat line(img.rows, img.cols, CV_8UC1);

		// 最后一列/行的索引
		int lastCol = img.cols - 1;
		int lastRow = img.rows - 1;

		// 行扫描 (为防止越界, 排除最后一列)
		for (int i = 0; i < img.rows; i++) {
			for (int j = 0; j < img.cols - 1; j++) {
				line.at<uchar>(i, j) = (img.at<uchar>(i, j) != img.at<uchar>(i, j + 1)) ?
					0 : 255;
			}
		}
		// 单独扫描最后一列
		for (int i = 0; i < img.rows; i++) {
			line.at<uchar>(i, lastCol) = (img.at<uchar>(i, lastCol) == 0) ?
				0 : 255;
		}

		// 列扫描 (为防止越界, 排除最后一行)
		for (int i = 0; i < img.rows; i++) {
			for (int j = 0; j < img.cols; j++) {
				line.at<uchar>(j, i) = (img.at<uchar>(j, i) != img.at<uchar>(j + 1, i)) ?
					0 : line.at<uchar>(j, i);
			}
		}
		// 单独扫描最后一行
		for (int j = 0; j < img.cols; j++) {
			line.at<uchar>(lastRow, j) = (img.at<uchar>(lastRow, j) == 0) ?
				0 : 255;
		}

		return line;
	}
}