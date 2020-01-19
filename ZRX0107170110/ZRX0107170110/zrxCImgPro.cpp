#include "stdafx.h"
#include "zrxCImgPro.h"


zrxCImgPro::zrxCImgPro()
{
}


zrxCImgPro::~zrxCImgPro()
{
}

/***************************************************************************
������BinaryImage(Mat Ori, const int binaryT, Mat &binary)                                                        
���ã���ԭʼ�Ҷ�ͼ��ת��Ϊ������ͼ��                          
������Mat Ori ԭʼͼ��
      const int binaryT  ��ֵ
	  Mat &binary  ������ͼ��
����ֵ����                                                                          
��ʷ��**����**         **����**            **ǩ��**                     
      2019��9��20��        ����              �����                                                                                                                                                   
/**************************************************************************/
void zrxCImgPro::BinaryImage(Mat Ori, const int binaryT, Mat &binary)
{
	//Ӱ���ʼ��
	binary.create(Ori.rows, Ori.cols, Ori.type());
	//ѭ������
	for (int i = 0; i < Ori.rows; i++)
	{
		for (int j = 0; j < Ori.cols; j++)
		{
			int tmp = Ori.at<uchar>(i, j);
			(tmp > binaryT) ? binary.at<uchar>(i, j) = 255 : binary.at<uchar>(i, j) = 0;
		}
	}
}

/***************************************************************************
������CreateGauss(const int nwiddowsize, const float sigma, Mat &Gauss)
���ã���˹�����
������const int nwiddowsize ����˴��ڿ�Ȼ򳤶�
	  const float sigma  ����sigma
	  Mat &Gauss  ��СΪnwiddowsize*nwiddowsize�ľ����
����ֵ����
��ʷ��**����**         **����**            **ǩ��**
	  2019��9��20��        ����              �����
/**************************************************************************/
void zrxCImgPro::CreateGauss(const int nwiddowsize, const float sigma, Mat &Gauss)
{
	Gauss.create(nwiddowsize, nwiddowsize, CV_32FC1);
	int center = (nwiddowsize + 1) / 2;
	const float PI = 4 * tan(1.0);
	float sum = 0;//����Ȩ��
	//��Mat����
	for (int i = 0; i < nwiddowsize; i++)
	{
		for (int j = 0; j < nwiddowsize; j++)
		{
			float radius = ((i + 1 - center)*(i + 1 - center) + (j + 1 - center)*(j + 1 - center));
			float temp1 = (1 / (2 * PI *sigma*sigma))* exp(-(radius / (2 * sigma*sigma)));
			Gauss.at<float>(i, j) = temp1;
			sum += Gauss.at<float>(i, j);
		}
	}
	for (int i = 0; i < nwiddowsize; i++)
	{
		for (int j = 0; j < nwiddowsize; j++)
		{
			Gauss.at<float>(i, j) = Gauss.at<float>(i, j) / (sum + 1e-6);
		}
	}
}


/***************************************************************************
������Gaussianfilter(const Mat srcImg, const int nwiddowsize, const float sigma, Mat &dstImg)
���ã���˹�˲����� ��Ҫ�������Ϻ�������˹�˲�����˺���
������const Mat srcImg ԭʼ�Ҷ�ͼ��
	  const int nwiddowsize ����˴��ڿ�Ȼ򳤶�
	  const float sigma ����sigma
	  Mat &dstImg ���ؾ���������ͼ��
����ֵ����
��ʷ��**����**         **����**            **ǩ��**
	  2019��9��20��        ����              �����
/**************************************************************************/
void zrxCImgPro::Gaussianfilter(const Mat srcImg, const int nwiddowsize, const float sigma, Mat &dstImg)
{
	double t = srcImg.rows;
	dstImg.create(srcImg.rows, srcImg.cols, CV_32FC1);
	Mat Gauss;
	CreateGauss(nwiddowsize, sigma, Gauss);
	for (int i = 2; i < srcImg.rows - 3; i++)
	{
		for (int j = 2; j < srcImg.cols - 3; j++)
		{
			Mat temp1;
			temp1.create(nwiddowsize, nwiddowsize, CV_32FC1);
			temp1 = srcImg(Range(i - 2, i + 3), Range(j - 2, j + 3));
			Mat temp2;
			temp1.convertTo(temp2, CV_32FC1);
			dstImg.at<float>(i, j) = temp2.dot(Gauss);
		}
	}
	dstImg.convertTo(dstImg, CV_8UC1);
}





