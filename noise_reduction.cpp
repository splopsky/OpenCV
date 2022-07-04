#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;


int main(int ac, char** av)
{
	double weight = 0.1;

	Mat img[10];
	Mat result;

	img[0] = imread(samples::findFile("lenna0.png"));
	img[1] = imread(samples::findFile("lenna1.png"));
	img[2] = imread(samples::findFile("lenna2.png"));
	img[3] = imread(samples::findFile("lenna3.png"));
	img[4] = imread(samples::findFile("lenna4.png"));
	img[5] = imread(samples::findFile("lenna5.png"));
	img[6] = imread(samples::findFile("lenna6.png"));
	img[7] = imread(samples::findFile("lenna7.png"));
	img[8] = imread(samples::findFile("lenna8.png"));
	img[9] = imread(samples::findFile("lenna9.png"));

	result = imread(samples::findFile("lenna0.png"));


	// Lenna 이미지를 하나 불러와 픽셀 값을 모두 0으로 설정
	const int mulValue = 0;

	CV_Assert(result.depth() == CV_8U);
	int nChannels = result.channels();
	int nRows = result.rows;
	int nCols = result.cols * nChannels;

	if (result.isContinuous())
	{
		nCols *= nRows;
		nRows = 1;
	}

	int i, j;
	uchar* p;
	for (i = 0; i < nRows; ++i)
	{
		p = result.ptr<uchar>(i);
		for (j = 0; j < nCols; ++j)
		{
			int value = p[j] * mulValue;
			p[j] = uchar(value);
		}
	}

	// 픽셀 값이 모두 0으로 초기화된 Lenna이미지에 10장의 주어진 노이즈 이미지를 동일한 weight 값을 주어 더함. 
	// = 10장의 image를 average

	for (int i = 0; i < 10; i++) {

		result += weight * img[i];
	}

	imshow("result", result);
	imwrite("result.png", result);

	waitKey(0);

	return 0;
}