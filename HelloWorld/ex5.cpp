#include<opencv2/opencv.hpp>

using namespace cv;

namespace ex5
{
	// 获取指定大小的高斯权重矩阵
	Mat getGaussianWeights(int dim, float sigma)
	{
		// 创建权重矩阵
		int radius = (dim - 1) / 2;
		Mat weights(dim, dim, CV_32FC1);
		// 计算权重
		float s2 = 2.0 * sigma * sigma;
		for (int x = (-radius); x <= radius; x++) {
			for (int y = (-radius); y <= radius; y++) {
				weights.at<float>(x + radius, y + radius) = exp(-(x * x + y * y) / s2);
			}
		}
		// 归一化
		Scalar all = sum(weights);
		weights = weights / all[0];
		return weights;
	}

	// 打印权重矩阵
	void printWeights(Mat weights) {
		for (int row = 0; row < weights.rows; row++) {
			printf("\n\t");
			for (int col = 0; col < weights.cols; col++) {
				printf("%f, ", weights.at<float>(col, row));
			}
		}
	}

	// 获取像素点 (考虑边界)
	Vec3b getPixel(Mat img, int col, int row)
	{
		col = col < 0 ? 0 : col;
		col = col > img.cols - 1 ? img.cols - 1 : col;
		row = row < 0 ? 0 : row;
		row = row > img.rows - 1 ? img.rows - 1 : row;
		return img.at<Vec3b>(row, col);
	}

	// 计算并修改指定像素点
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

	// 通过卷积运算进行滤波
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

	// 高斯模糊
	Mat gaussianBulr(Mat img, int dim, float sigma) {
		Mat weights = ex5::getGaussianWeights(dim, sigma);
		return conv(img, weights);
	}
}