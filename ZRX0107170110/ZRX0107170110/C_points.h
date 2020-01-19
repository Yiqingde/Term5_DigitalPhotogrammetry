#pragma once
/***************************************************************************
类：C_points
作用：存储格网点的元素
Welcome to my Github and my CSDN blog , more information will be available about the project!
Github:https://github.com/Yiqingde
CSDN Blog:https://me.csdn.net/weixin_42348202
历史：**日期**         **理由**            **签名**
	  2019年10月26日        创建              张睿祥
/**************************************************************************/
#include <opencv2/opencv.hpp>
#include <vector>
#include <opencv2/flann/miniflann.hpp>
using namespace cv;
using namespace std;
class C_points
{
public:
	C_points();
	~C_points();
	int row;//row指的是行号  x
	int col;//col指的是列号  y
	
	double zz;//高程
	int rgb_r;//颜色
	int rgb_g;
	int rgb_b;
	vector<Point3d> xyz;//高程
	vector<Point3i> rgb;//颜色
	int sizeee;//用来给X_six计数
	int sizee;//vector的大小
	Mat X_six;//存储最小二乘需要的数据
	void addxyz(vector<Point3d> &xyz, double x, double y, double z);//加xyz
	void addrgb(vector<Point3i> &rgb, int r, int g, int b);//加颜色
	void add_int(double r, double c, double x, double y, double z, int r2, int g, int b);//加初始值
};

