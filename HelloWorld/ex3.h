#include<opencv2/opencv.hpp>

using namespace cv;

namespace ex3
{
	Mat getMark(Mat img, uchar space, int &count);
	Mat segment(Mat img, uchar space);
}
