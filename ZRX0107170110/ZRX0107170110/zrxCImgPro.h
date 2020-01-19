/***************************************************************************
类：zrxCImgPro 
作用：封装图像操作函数，按钮操作功能也存储在其内 使用了opencv4.1.1
Welcome to my Github and my CSDN blog , more information will be available about the project!
Github:https://github.com/Yiqingde
CSDN Blog:https://me.csdn.net/weixin_42348202
历史：**日期**         **理由**            **签名**
	  2019年9月20日        创建              张睿祥
/**************************************************************************/
#pragma once
#include <opencv2/opencv.hpp>
using namespace cv;
class zrxCImgPro
{
	void CreateGauss(const int nwiddowsize, const float sigma, Mat &Gauss);//高斯卷积核
public:
	zrxCImgPro();
	~zrxCImgPro();
	void BinaryImage(Mat Ori, const int binaryT, Mat &binary);//将原始灰度图像转化为二进制图像       
	void Gaussianfilter(const Mat srcImg, const int nwiddowsize, const float sigma, Mat &dstImg);//高斯滤波函数 需要调用以上函数：高斯滤波卷积核函数
};

