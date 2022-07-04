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

	Mat Lenna_gray;
	Mat Moon;
	
	int l_his[256] = { };
	int m_his[256] = { };

	Lenna_gray = imread(samples::findFile("Lenna_gray.png"));
	Moon = imread(samples::findFile("Moon.png"));


//==========================================================//

	CV_Assert(Lenna_gray.depth() == CV_8U);
	int nChannels = Lenna_gray.channels();
	int nRows = Lenna_gray.rows;
	int nCols = Lenna_gray.cols * nChannels;


	if (Lenna_gray.isContinuous())
	{
		nCols *= nRows;
		nRows = 1;
	}

	int i, j;
	uchar* p;
	for (i = 0; i < nRows; ++i)
	{
		p = Lenna_gray.ptr<uchar>(i);
		for (j = 0; j < nCols; ++j)
		{
			int value = p[j];
			l_his[value]++;			
		
		}
	}


	int sum = 0;
	for (int i = 0; i < 256; i++) {
		sum += l_his[i];
	}

	float cum_his[256] = { };
	cum_his[0] = (float)l_his[0] / (float)sum * 255;
	for (int j = 1; j < 256; j++)
	{
		cum_his[j] = cum_his[j - 1] + ((float)l_his[j] / (float)sum) * 255;
	}
	
	/*
	for (int i = 0; i < 256; i++) {

		cout << cum_his[i] << " ";

	}
	*/

	for (i = 0; i < nRows; ++i)
	{
		p = Lenna_gray.ptr<uchar>(i);
		for (j = 0; j < nCols; ++j)
		{
			int value = p[j];
			if (value == 255) {
				p[j] = 255;
			}
			else {
				p[j] = uchar(round(cum_his[value]));
			}

		}
	}


	//========================================//

	CV_Assert(Moon.depth() == CV_8U);
	int nChannels2 = Moon.channels();
	int nRows2 = Moon.rows;
	int nCols2 = Moon.cols * nChannels2;


	if (Moon.isContinuous())
	{
		nCols2 *= nRows2;
		nRows2 = 1;
	}
	uchar* q;
	for (i = 0; i < nRows2; ++i)
	{
		q = Moon.ptr<uchar>(i);
		for (j = 0; j < nCols2; ++j)
		{
			int value = q[j];
			m_his[value]++;

		}
	}


	int sum2 = 0;
	for (int i = 0; i < 256; i++) {
		sum2 += m_his[i];
	}

	float cum_his2[256] = { };
	cum_his2[0] = (float)m_his[0] / (float)sum2 * 255;
	for (int j = 1; j < 256; j++)
	{
		cum_his2[j] = cum_his2[j - 1] + ((float)m_his[j] / (float)sum2) * 255;
	}

	/*
	for (int i = 0; i < 256; i++) {

		cout << cum_his2[i] << " ";

	}
	*/

	for (i = 0; i < nRows2; ++i)
	{
		q = Moon.ptr<uchar>(i);
		for (j = 0; j < nCols2; ++j)
		{
			int value = q[j];
			if (value == 255) {
				q[j] = 255;
			}
			else {
				q[j] = uchar(round(cum_his2[value]));
			}

		}
	}
	//====================================================//
	imshow("Lenna_eq", Lenna_gray);
	imwrite("Lenna_eq.png", Lenna_gray);
	imshow("Moon_eq", Moon);
	imwrite("Moon_eq.png", Moon);
	

	//===================================================//

	for (i = 0; i < nRows; ++i)
	{
		p = Lenna_gray.ptr<uchar>(i);
		for (j = 0; j < nCols; ++j)
		{
			int value = p[j];
			for (int k = 0; k < 256; k++) {

			if (value == uchar(round(cum_his2[k]))) {
				p[j] = k;
			}
			}

		}
	}


	imshow("Lenna_mtc", Lenna_gray);
	imwrite("Lenna_mtc.png", Lenna_gray);


	//=====================================================//

	waitKey(0);

	return 0;
}