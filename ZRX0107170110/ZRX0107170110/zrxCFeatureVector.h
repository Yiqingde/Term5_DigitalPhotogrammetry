#pragma once
/***************************************************************************
类：zrxCFeatureVector
作用：Moraavec算子类 外接函数:Moravec()
Welcome to my Github and my CSDN blog , more information will be available about the project!
Github:https://github.com/Yiqingde
CSDN Blog:https://me.csdn.net/weixin_42348202
历史：**日期**         **理由**            **签名**
	  2019年9月26日        创建              张睿祥
/**************************************************************************/
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
using namespace cv;
using namespace std;
class zrxCFeatureVector
{
private:
	CString strOut;//存储输出txt中内容
	void find(float a[], int m, float &max, float &min);//最大最小值
	float Moravec_core(Mat m_srcimg, int Moravecsize, int i, int j);//Moravec_core滑动窗口
	void Moravec_core2(Mat &m_srcimgrgb,int Moravecsize2, Mat &Morvec, vector<Point3f> &f);//Moravec_core2局部抑制函数
public:
	zrxCFeatureVector();
	~zrxCFeatureVector();
	void Reporttxt(CString temp);//输出至txt函数
	void Moravec(Mat m_srcimg, Mat &m_srcimgrgb, int Moravecsize, int Moravecsize2,int Moraveclowstdoor, Mat &Morvec, vector<Point3f> &f);//Moravec主要函数，调用上面的两个函数
};

