/***************************************************************************
�ࣺzrxCImgPro 
���ã���װͼ�������������ť��������Ҳ�洢������ ʹ����opencv4.1.1
Welcome to my Github and my CSDN blog , more information will be available about the project!
Github:https://github.com/Yiqingde
CSDN Blog:https://me.csdn.net/weixin_42348202
��ʷ��**����**         **����**            **ǩ��**
	  2019��9��20��        ����              �����
/**************************************************************************/
#pragma once
#include <opencv2/opencv.hpp>
using namespace cv;
class zrxCImgPro
{
	void CreateGauss(const int nwiddowsize, const float sigma, Mat &Gauss);//��˹�����
public:
	zrxCImgPro();
	~zrxCImgPro();
	void BinaryImage(Mat Ori, const int binaryT, Mat &binary);//��ԭʼ�Ҷ�ͼ��ת��Ϊ������ͼ��       
	void Gaussianfilter(const Mat srcImg, const int nwiddowsize, const float sigma, Mat &dstImg);//��˹�˲����� ��Ҫ�������Ϻ�������˹�˲�����˺���
};

