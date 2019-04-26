#include<opencv2/opencv.hpp>
#include<math.h>

#include"ex3.h"

using namespace cv;

namespace ex4
{
	// �������ĵ�
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


	// ��������Ƕ��볤��
	void getAngle(Mat mark, int m, int avgX, int avgY, double &betterAngle, double &maxLength) {


		// �����
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

		// ����Ƕ�
		double a = atan((2 * u11) / (u20 - u02)) / 2;

		// ѡ��ϳ�������Ƕ�
		// ��ʽ1: ����������������������, �Ƚ���ͼ����Ӿ����ڲ��ĳ���
		// ��ʽ2: ����������������������, �Ƚ���ͼ���ڲ��ĳ��� (����Ӿ���Ϊ����������ʱ, ����׼ȷ�ȵ��������)
		bool isSquare = abs(maxX - maxY) < 3; // �ж�Ӧ�������ַ�ʽ
		maxLength = 0;
		for (int i = 0; i < 2; i++, a += 3.1415926 / 2) {
			for (int l = 0; l < max(mark.rows, mark.cols); l++) {
				int x = l * cos(a);
				int y = l * sin(a);
				bool inRange;
				if (isSquare) {
					inRange = mark.at<uchar>(avgY + y, avgX + x) == m; // ʹ�÷�ʽ2�ж��Ƿ���ͼ����
				} else {
					inRange = (abs(x) < maxX) && (abs(y) < maxY); // ʹ�÷�ʽ1�ж��Ƿ���ͼ����
				}
				if (inRange) {
					if (l > maxLength) {
						maxLength = l;
						betterAngle = a;
					}
				} else {
					if (!isSquare || maxLength != 0) {  // �����ʽ2�Ŀ���ͼ������
						break;
					}
				}
			}
		}
	}

	Mat getAxis(Mat img, uchar space)
	{
		// �ָ�ԭʼͼ��
		Mat axis = ex3::segment(img, space);

		// ��ȡ���ͼ��
		int count;
		Mat mark = ex3::getMark(img, space, count);

		// �������
		for (int m = 1; m < count + 1; m++) {

			// ��ȡ���ĵ�
			int avgX, avgY;
			getCenter(mark, m, avgX, avgY);

			// �������ĵ�
			circle(axis, Point(avgX, avgY), 3, 0);

			// ��ȡ����Ƕ��볤��
			double angle, length;
			getAngle(mark, m, avgX, avgY, angle, length);

			// ��������
			int dx = length * cos(angle), dy = length * sin(angle);
			line(axis, Point(avgX + dx, avgY + dy), Point(avgX - dx, avgY - dy), Scalar(0, 0, 255, 0));
		}

		return axis;
	}
}