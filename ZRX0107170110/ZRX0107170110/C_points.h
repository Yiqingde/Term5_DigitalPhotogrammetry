#pragma once
/***************************************************************************
�ࣺC_points
���ã��洢�������Ԫ��
Welcome to my Github and my CSDN blog , more information will be available about the project!
Github:https://github.com/Yiqingde
CSDN Blog:https://me.csdn.net/weixin_42348202
��ʷ��**����**         **����**            **ǩ��**
	  2019��10��26��        ����              �����
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
	int row;//rowָ�����к�  x
	int col;//colָ�����к�  y
	
	double zz;//�߳�
	int rgb_r;//��ɫ
	int rgb_g;
	int rgb_b;
	vector<Point3d> xyz;//�߳�
	vector<Point3i> rgb;//��ɫ
	int sizeee;//������X_six����
	int sizee;//vector�Ĵ�С
	Mat X_six;//�洢��С������Ҫ������
	void addxyz(vector<Point3d> &xyz, double x, double y, double z);//��xyz
	void addrgb(vector<Point3i> &rgb, int r, int g, int b);//����ɫ
	void add_int(double r, double c, double x, double y, double z, int r2, int g, int b);//�ӳ�ʼֵ
};

