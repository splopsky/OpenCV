#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
#include <stdio.h>
#include <cmath>

using namespace cv;
using namespace std;

int main(int ac, char** av)
{
	Mat Lenna_gray = imread("Lenna_gray.png", IMREAD_GRAYSCALE);
	Mat result = imread("Lenna_gray.png", IMREAD_GRAYSCALE);
	Mat smask;
	Mat result2;


	// Lenna 이미지를 불러와 픽셀 값을 모두 0으로 설정, 여기다가 결과 저장
	const int mulValue = 0;

	CV_Assert(result.depth() == CV_8U);
	int nChannels0 = result.channels();
	int nRows0 = result.rows;
	int nCols0 = result.cols;

	if (result.isContinuous())
	{
		nCols0 *= nRows0;
		nRows0 = 1;
	}

	int i0, j0;
	uchar* p0;
	for (i0 = 0; i0 < nRows0; ++i0)
	{
		p0 = result.ptr<uchar>(i0);
		for (j0 = 0; j0 < nCols0; ++j0)
		{
			int value0 = p0[j0] * mulValue;
			p0[j0] = uchar(value0);
		}
	}

	//============================================================//

	CV_Assert(Lenna_gray.depth() == CV_8U);
	int nChannels = Lenna_gray.channels();
	int nRows = Lenna_gray.rows;
	int nCols = Lenna_gray.cols;

	//Mat output = Mat::zeros(nRows, nCols, CV_8U);

	if (Lenna_gray.isContinuous())
	{
		nCols *= nRows;
		nRows = 1;
	}

	int i, j;
	uchar* q;

	for (i = 0; i < nRows; ++i)
	{
		q = result.ptr<uchar>(i);

		for (j = 0; j < nCols; ++j)
		{
			int sum = 0;
			
			if ((i - 1) >= 0 && (j - 1) >= 0) {
				sum += Lenna_gray.ptr<uchar>(i - 1)[j - 1];
			}

			if ((i - 1) >= 0 && j >= 0) {
				sum += Lenna_gray.ptr<uchar>(i - 1)[j];
			}

			if (((i - 1) < nRows && (j + 1) < nCols) && ((i - 1) >= 0 && (j + 1) >= 0)) {
				sum += Lenna_gray.ptr<uchar>(i - 1)[j + 1];
			}

			if (i >= 0 && (j - 1) >= 0) {
				sum += Lenna_gray.ptr<uchar>(i)[j - 1];
			}
			
			if (Lenna_gray.ptr<uchar>(i)[j]) {
				sum += Lenna_gray.ptr<uchar>(i)[j];
			}
			
			if (i < nRows && (j + 1) < nCols ) {
				sum += Lenna_gray.ptr<uchar>(i)[j + 1];
			}

			if (((i + 1) < nRows && (j - 1) < nCols) && ((i + 1) >= 0 && (j - 1) >= 0)) {
				sum += Lenna_gray.ptr<uchar>(i + 1)[j - 1];
			}

			if ((i + 1) < nRows && j < nCols) {
				sum += Lenna_gray.ptr<uchar>(i + 1)[j];
			}

			if ((i + 1) < nRows && (j + 1) < nCols) {
				sum += Lenna_gray.ptr<uchar>(i + 1)[j + 1];
			}
			
			int value = sum / 3;
			//cout << (int)Lenna_gray.ptr<uchar>(i)[j] << " ";
			//cout << sum << " ";
			q[j] = value;

		}
	}

	smask = Lenna_gray - result;
	result2 = Lenna_gray + smask;

	imshow("blur_result", result);
	imshow("sharp_result", result2);
	imshow("original", Lenna_gray);
	imwrite("blur_result.png", result);

	waitKey(0);

	return 0;

}