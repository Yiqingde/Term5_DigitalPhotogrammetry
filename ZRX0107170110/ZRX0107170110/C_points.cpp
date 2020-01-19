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
������addxyz(vector<Point3d> &xyz, double x, double y, double z)
���ã�xyzд��vector
������vector<Point3d> &xyz ����vector����
      double x xֵ
	  double y yֵ
	  double z zֵ
����ֵ����
��ʷ��**����**         **����**            **ǩ��**
	  2019��10��27��        ����              �����
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
������addrgb(vector<Point3i> &rgb, int r, int g, int b)
���ã�rgbд��vector
������vector<Point3i> &rgb ����vector����
	  int r
	  int g
	  int b
����ֵ����
��ʷ��**����**         **����**            **ǩ��**
	  2019��10��27��        ����              �����
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
������add_int(double r, double c, double x, double y, double z, int r2, int g, int b)
���ã�д���ۺϺ���
������double r �к�
	  double c �к�
	  double x xֵ
	  double y yֵ
	  int r2 rgb��r2
	  int g  rgb��b
	  int b  rgb��b
����ֵ����
��ʷ��**����**         **����**            **ǩ��**
	  2019��10��27��        ����              �����
/**************************************************************************/
void C_points::add_int(double r, double c, double x, double y, double z, int r2, int g, int b)
{
	row = r;
	col = c;
	addxyz(xyz, x, y, z);
	addrgb(rgb, r2, g, b);
}