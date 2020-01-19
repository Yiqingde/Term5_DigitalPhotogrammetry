/***************************************************************************
类：CMatchingImg
作用：核线影像相关系数计算类
Welcome to my Github and my CSDN blog , more information will be available about the project!
Github:https://github.com/Yiqingde
CSDN Blog:https://me.csdn.net/weixin_42348202
历史：**日期**         **理由**            **签名**
	  2019年10月11日        创建              张睿祥
/**************************************************************************/
#pragma once
#include "zrxCFeatureVector.h"
class CMatchingImg
{
public:
	CMatchingImg();
	~CMatchingImg();
	int Div(const CString strLine, char split, CStringArray &strArray);//字符串分割函数
	void lastview(Mat match_LImg, Mat match_RImg, vector<Point3f> f, vector<Point3f> r);//最后显示
	void Get_coefficient(Mat Lmatchwindow, Mat match_RImg, int x, int y, float &cofficent);//求相关系数
	bool read(vector < Point3f> &f);//读取txt到vector
	void vectorsort(vector < Point3f> &Temp_sort);//排序
	void MatchingImg(Mat &match_LImg, Mat &match_RImg, Mat match_RGBLImg, Mat match_RGBRImg, float lowst_door, int dist_width, int halflengthsize);//主函数
};

