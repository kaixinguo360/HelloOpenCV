#include<opencv2/opencv.hpp>

using namespace cv;

namespace ex5
{
	Mat getGaussianWeights(int dim, float sigma);
	void printWeights(Mat weights);
	Mat conv(Mat img, Mat weights);
	Mat gaussianBulr(Mat img, int dim, float sigma);
}
