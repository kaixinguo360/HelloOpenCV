#include<opencv2/opencv.hpp>

#define MAX_MARK 1000

using namespace cv;

namespace ex3
{
	// 合并标号
	void merge(Mat mark, int from, int to) {
		int count = 0;
		for (int i = 0; i < mark.rows; i++) {
			for (int j = 0; j < mark.cols; j++) {
				if (mark.at<uchar>(i, j) == from) {
					mark.at<uchar>(i, j) = to;
					count++;
				}
			}
		}
		// printf("共处理 %d 个点, ", count);
	}

	Mat getMark(Mat img, uchar space) {

		// 新建单通道图像
		Mat mark(img.rows, img.cols, CV_8UC1);

		int maxMark = 1;
		// 单独扫描第一行
		for (int i = 1; i < img.rows; i++) {
			if (img.at<uchar>(i, 0) != space) {
				uchar left = mark.at<uchar>(i, 0);
				if (left == 0) {
					mark.at<uchar>(i, 0) = maxMark;
					maxMark++;
				}
			}
			else {
				mark.at<uchar>(i, 0) = 0;
			}
		}
		// 单独扫描第一列
		for (int j = 1; j < img.cols; j++) {
			if (img.at<uchar>(0, j) != space) {
				uchar left = mark.at<uchar>(0, j);
				if (left == 0) {
					mark.at<uchar>(0, j) = maxMark;
					maxMark++;
				}
			}
			else {
				mark.at<uchar>(0, j) = 0;
			}
		}
		// 行扫描
		for (int j = 1; j < img.cols; j++) {
			for (int i = 1; i < img.rows; i++) {
				if (img.at<uchar>(i, j) != space) {
					uchar up = mark.at<uchar>(i, j - 1);
					uchar left = mark.at<uchar>(i - 1, j);
					if (up != 0) {
						mark.at<uchar>(i, j) = up;
						if (left != 0 && left != up) {
							int z = 1;
							while (i - z >= 0 && mark.at<uchar>(i - z, j) != 0) {
								mark.at<uchar>(i - z, j) = up;
								z++;
							}
						}
					}
					else if (left != 0) {
						mark.at<uchar>(i, j) = left;
					}
					else {
						mark.at<uchar>(i, j) = maxMark;
						maxMark++;
					}
				}
				else {
					mark.at<uchar>(i, j) = 0;
				}
			}
		}

		// 标记存在的标号
		bool marks[MAX_MARK];
		for (int i = 0; i < MAX_MARK; i++) {
			marks[i] = false;
		}

		// 解决相邻标号问题
		for (int j = 0; j < img.cols; j++) {
			for (int i = 0; i < img.rows; i++) {
				uchar m = mark.at<uchar>(i, j);
				if (m != 0) {
					marks[m] = true;
					uchar round[4];
					round[0] = mark.at<uchar>(i - 1, j);
					round[1] = mark.at<uchar>(i + 1, j);
					round[2] = mark.at<uchar>(i, j - 1);
					round[3] = mark.at<uchar>(i, j + 1);
					for (int i = 0; i < 4; i++) {
						if (round[i] != 0 && round[i] != m) {
							int from = round[i] > m ? m : round[i];
							int to = round[i] > m ? round[i] : m;
							merge(mark, from, to);
							marks[from] = false;
							// printf("合并标号: %d -> %d\n", from, to);
						}
					}
				}
			}
		}

		// 最小化标号
		int minMark = 1;
		for (int i = 0; i < MAX_MARK; i++) {
			if (marks[i]) {
				if (i == minMark) {
					minMark++;
				}
				else if (i > minMark) {
					merge(mark, i, minMark);
					// printf("合并标号: %d -> %d\n", i, minMark);
					minMark++;
				}
			}
		}

		return mark;
	}

	// 分割
	Mat segment(Mat img, uchar space)
	{
		// 获取标号图像
		Mat mark = getMark(img, space);

		// 预设MAX_MARK种颜色
		uchar colors[MAX_MARK];
		for (int i = 1; i < MAX_MARK; i++) {
			colors[i] = (rand() + 255) % 255;
		}

		// 新建三通道图像
		Mat color(img.rows, img.cols, CV_8UC3);
		for (int i = 0; i < img.rows; i++) {
			for (int j = 0; j < img.cols; j++) {
				uchar m = mark.at<uchar>(i, j);
				if (m != 0) {
					color.at<Vec3b>(i, j)[0] = colors[m];
					color.at<Vec3b>(i, j)[1] = colors[m + 1];
					color.at<Vec3b>(i, j)[2] = colors[m + 2];
				}
				else {
					color.at<Vec3b>(i, j)[0] = 255;
					color.at<Vec3b>(i, j)[1] = 255;
					color.at<Vec3b>(i, j)[2] = 255;
				}
			}
		}

		return color;
	}
}