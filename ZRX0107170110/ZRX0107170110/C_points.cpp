#include "stdafx.h"
#include "C_points.h"

C_points::C_points()
{
	sizee=0;
	sizeee = 0;
	X_six.create(6, 4, CV_64FC1);
	rgb_r = 0;
	rgb_g = 0;
	rgb_b = 0;
}


C_points::~C_points()
{
}
/***************************************************************************
函数：addxyz(vector<Point3d> &xyz, double x, double y, double z)
作用：xyz写入vector
参数：vector<Point3d> &xyz 存入vector数组
      double x x值
	  double y y值
	  double z z值
返回值：无
历史：**日期**         **理由**            **签名**
	  2019年10月27日        创建              张睿祥
/**************************************************************************/
void C_points::addxyz(vector<Point3d> &xyz, double x, double y, double z)
{
	Point3d temp;
	temp.x = x;
	temp.y = y;
	temp.z = z;
	sizee++;
	xyz.push_back(temp);
}
/***************************************************************************
函数：addrgb(vector<Point3i> &rgb, int r, int g, int b)
作用：rgb写入vector
参数：vector<Point3i> &rgb 存入vector数组
	  int r
	  int g
	  int b
返回值：无
历史：**日期**         **理由**            **签名**
	  2019年10月27日        创建              张睿祥
/**************************************************************************/
void C_points::addrgb(vector<Point3i> &rgb, int r, int g, int b)
{
	Point3i temp;
	temp.x = r;
	temp.y = g;
	temp.z = b;
	rgb.push_back(temp);
}
/***************************************************************************
函数：add_int(double r, double c, double x, double y, double z, int r2, int g, int b)
作用：写入综合函数
参数：double r 行号
	  double c 列号
	  double x x值
	  double y y值
	  int r2 rgb的r2
	  int g  rgb的b
	  int b  rgb的b
返回值：无
历史：**日期**         **理由**            **签名**
	  2019年10月27日        创建              张睿祥
/**************************************************************************/
void C_points::add_int(double r, double c, double x, double y, double z, int r2, int g, int b)
{
	row = r;
	col = c;
	addxyz(xyz, x, y, z);
	addrgb(rgb, r2, g, b);
}