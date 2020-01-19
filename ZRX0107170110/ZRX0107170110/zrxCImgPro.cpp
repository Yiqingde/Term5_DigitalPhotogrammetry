#include "stdafx.h"
#include "zrxCImgPro.h"


zrxCImgPro::zrxCImgPro()
{
}


zrxCImgPro::~zrxCImgPro()
{
}

/***************************************************************************
函数：BinaryImage(Mat Ori, const int binaryT, Mat &binary)                                                        
作用：将原始灰度图像转化为二进制图像                          
参数：Mat Ori 原始图像
      const int binaryT  阈值
	  Mat &binary  二进制图像
返回值：无                                                                          
历史：**日期**         **理由**            **签名**                     
      2019年9月20日        创建              张睿祥                                                                                                                                                   
/**************************************************************************/
void zrxCImgPro::BinaryImage(Mat Ori, const int binaryT, Mat &binary)
{
	//影像初始化
	binary.create(Ori.rows, Ori.cols, Ori.type());
	//循环带走
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
函数：CreateGauss(const int nwiddowsize, const float sigma, Mat &Gauss)
作用：高斯卷积核
参数：const int nwiddowsize 卷积核窗口宽度或长度
	  const float sigma  就是sigma
	  Mat &Gauss  大小为nwiddowsize*nwiddowsize的卷积阵
返回值：无
历史：**日期**         **理由**            **签名**
	  2019年9月20日        创建              张睿祥
/**************************************************************************/
void zrxCImgPro::CreateGauss(const int nwiddowsize, const float sigma, Mat &Gauss)
{
	Gauss.create(nwiddowsize, nwiddowsize, CV_32FC1);
	int center = (nwiddowsize + 1) / 2;
	const float PI = 4 * tan(1.0);
	float sum = 0;//计算权阵
	//给Mat复制
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
函数：Gaussianfilter(const Mat srcImg, const int nwiddowsize, const float sigma, Mat &dstImg)
作用：高斯滤波函数 需要调用以上函数：高斯滤波卷积核函数
参数：const Mat srcImg 原始灰度图像
	  const int nwiddowsize 卷积核窗口宽度或长度
	  const float sigma 就是sigma
	  Mat &dstImg 返回经经卷积后的图像
返回值：无
历史：**日期**         **理由**            **签名**
	  2019年9月20日        创建              张睿祥
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





