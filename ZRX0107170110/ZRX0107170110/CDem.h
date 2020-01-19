#pragma once
#include "C_points.h"
/***************************************************************************
类：CDem
作用：封装最小二乘DEM制作操作函数，仅储存按钮操作功能，调用txt
Welcome to my Github and my CSDN blog , more information will be available about the project!
Github:https://github.com/Yiqingde
CSDN Blog:https://me.csdn.net/weixin_42348202
历史：**日期**         **理由**            **签名**
	  2019年10月26日        创建              张睿祥
/**************************************************************************/
class CDem
{
	C_points *p;//数据对象，一维数组
	int allpoints;//所有点
	//定义行列数
	int nx;//行号
	int ny;//列号
	
	double width;//分辨率1 或3
	double dists;//距离
	//定义六个变量用来储存最大最小值
	double xlo;
	double xhi;
	double ylo;
	double yhi;
	double zlo;
	double zhi;
public:
	CDem();
	~CDem();
	int Div(const CString strLine, char split, CStringArray &strArray);//字符串分割函数
	void findpoints(int x, int y, int size, C_points *d);//寻点
	void convertxy2id(double x, double y, int &tempr, int &tempc, int &id);//转换ID
	int convertcr2id(int tempr, int tempc);//转换ID
	void convertid2rc(int id, int&rr, int &cc);//转换ID
	double dist(double x, double y, double x2, double y2);//计算距离
	double truedist2(double x, double y, double x2, double y2);//计算距离
	double workout(int rr, int cc, Mat X_six);//最小二乘矩阵
	bool readDem();//读取dem数据
	void search();//搜索函数
	void out();//输出1
	void out2();//输出2
	void out3();//输出3
	void getcolor1(Mat &f);//渐变颜色函数，矩阵
	void returncolor(double &a, double &b, double &c, double zz, double min, double max, Mat color);//得到颜色
	void BeatifulDem();//进行最后的Dem美化，去除噪声
	void main();//主函数
};

