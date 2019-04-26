#include<opencv2/opencv.hpp>
#include<math.h>

#include"ex3.h"

using namespace cv;

namespace ex4
{
	// 计算中心点
	void getCenter(Mat mark, int m, int &avgX, int &avgY) {
		int sumX = 0, sumY = 0, count = 0;
		for (int y = 0; y < mark.rows; y++) {
			for (int x = 0; x < mark.cols; x++) {
				if (mark.at<uchar>(y, x) == m) {
					sumX += x;
					sumY += y;
					count++;
				}
			}
		}
		avgX = sumX / count;
		avgY = sumY / count;
	}


	// 计算主轴角度与长度
	void getAngle(Mat mark, int m, int avgX, int avgY, double &betterAngle, double &maxLength) {


		// 计算矩
		double u11 = 0, u20 = 0, u02 = 0;
		int maxX = 0, maxY = 0;
		for (int y = 0; y < mark.rows; y++) {
			for (int x = 0; x < mark.cols; x++) {
				if (mark.at<uchar>(y, x) == m) {
					maxX = x > maxX ? x : maxX;
					maxY = y > maxY ? y : maxY;
					int dx = x - avgX;
					int dy = y - avgY;
					u11 += dx * dy;
					u20 += dx * dx;
					u02 += dy * dy;
				}
			}
		}
		maxX -= avgX;
		maxY -= avgY;

		// 计算角度
		double a = atan((2 * u11) / (u20 - u02)) / 2;

		// 选择较长的轴向角度
		// 方式1: 画从中心向外侧延伸的射线, 比较在图形外接矩形内部的长度
		// 方式2: 画从中心向外侧延伸的射线, 比较在图形内部的长度 (当外接矩形为近似正方形时, 增加准确度的替代方法)
		bool isSquare = abs(maxX - maxY) < 3; // 判断应采用哪种方式
		maxLength = 0;
		for (int i = 0; i < 2; i++, a += 3.1415926 / 2) {
			for (int l = 0; l < max(mark.rows, mark.cols); l++) {
				int x = l * cos(a);
				int y = l * sin(a);
				bool inRange;
				if (isSquare) {
					inRange = mark.at<uchar>(avgY + y, avgX + x) == m; // 使用方式2判断是否还在图形内
				} else {
					inRange = (abs(x) < maxX) && (abs(y) < maxY); // 使用方式1判断是否还在图形内
				}
				if (inRange) {
					if (l > maxLength) {
						maxLength = l;
						betterAngle = a;
					}
				} else {
					if (!isSquare || maxLength != 0) {  // 解决方式2的空心图形问题
						break;
					}
				}
			}
		}
	}

	Mat getAxis(Mat img, uchar space)
	{
		// 分割原始图像
		Mat axis = ex3::segment(img, space);

		// 获取标号图像
		int count;
		Mat mark = ex3::getMark(img, space, count);

		// 遍历标号
		for (int m = 1; m < count + 1; m++) {

			// 获取中心点
			int avgX, avgY;
			getCenter(mark, m, avgX, avgY);

			// 画出中心点
			circle(axis, Point(avgX, avgY), 3, 0);

			// 获取主轴角度与长度
			double angle, length;
			getAngle(mark, m, avgX, avgY, angle, length);

			// 画出主轴
			int dx = length * cos(angle), dy = length * sin(angle);
			line(axis, Point(avgX + dx, avgY + dy), Point(avgX - dx, avgY - dy), Scalar(0, 0, 255, 0));
		}

		return axis;
	}
}