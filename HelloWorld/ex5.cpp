#include<opencv2/opencv.hpp>

using namespace cv;

namespace ex5
{
	// ��ȡָ����С�ĸ�˹Ȩ�ؾ���
	Mat getGaussianWeights(int dim, float sigma)
	{
		// ����Ȩ�ؾ���
		int radius = (dim - 1) / 2;
		Mat weights(dim, dim, CV_32FC1);
		// ����Ȩ��
		float s2 = 2.0 * sigma * sigma;
		for (int x = (-radius); x <= radius; x++) {
			for (int y = (-radius); y <= radius; y++) {
				weights.at<float>(x + radius, y + radius) = exp(-(x * x + y * y) / s2);
			}
		}
		// ��һ��
		Scalar all = sum(weights);
		weights = weights / all[0];
		return weights;
	}

	// ��ӡȨ�ؾ���
	void printWeights(Mat weights) {
		for (int row = 0; row < weights.rows; row++) {
			printf("\n\t");
			for (int col = 0; col < weights.cols; col++) {
				printf("%f, ", weights.at<float>(col, row));
			}
		}
	}

	// ��ȡ���ص� (���Ǳ߽�)
	Vec3b getPixel(Mat img, int col, int row)
	{
		col = col < 0 ? 0 : col;
		col = col > img.cols - 1 ? img.cols - 1 : col;
		row = row < 0 ? 0 : row;
		row = row > img.rows - 1 ? img.rows - 1 : row;
		return img.at<Vec3b>(row, col);
	}

	// ���㲢�޸�ָ�����ص�
	void calculate(Mat img, int col, int row, Mat weights)
	{
		int colRadius = (weights.cols - 1) / 2;
		int rowRadius = (weights.rows - 1) / 2;
		Vec3b sum;
		for (int x = (-colRadius); x <= colRadius; x++) {
			for (int y = (-rowRadius); y <= rowRadius; y++) {
				sum += getPixel(img, col + x, row + y) * weights.at<float>(rowRadius + y, colRadius + x);
			}
		}
		img.at<Vec3b>(row, col) = sum;
	}

	// ͨ�������������˲�
	Mat conv(Mat img, Mat weights)
	{
		Mat result = img.clone();
		for (int row = 0; row < img.rows; row++) {
			for (int col = 0; col < img.cols; col++) {
				calculate(result, col, row, weights);
			}
		}
		return result;
	}

	// ��˹ģ��
	Mat gaussianBulr(Mat img, int dim, float sigma) {
		Mat weights = ex5::getGaussianWeights(dim, sigma);
		return conv(img, weights);
	}
}