/***************************************************************************
�ࣺCMatchingImg
���ã�����Ӱ�����ϵ��������
Welcome to my Github and my CSDN blog , more information will be available about the project!
Github:https://github.com/Yiqingde
CSDN Blog:https://me.csdn.net/weixin_42348202
��ʷ��**����**         **����**            **ǩ��**
	  2019��10��11��        ����              �����
/**************************************************************************/
#pragma once
#include "zrxCFeatureVector.h"
class CMatchingImg
{
public:
	CMatchingImg();
	~CMatchingImg();
	int Div(const CString strLine, char split, CStringArray &strArray);//�ַ����ָ��
	void lastview(Mat match_LImg, Mat match_RImg, vector<Point3f> f, vector<Point3f> r);//�����ʾ
	void Get_coefficient(Mat Lmatchwindow, Mat match_RImg, int x, int y, float &cofficent);//�����ϵ��
	bool read(vector < Point3f> &f);//��ȡtxt��vector
	void vectorsort(vector < Point3f> &Temp_sort);//����
	void MatchingImg(Mat &match_LImg, Mat &match_RImg, Mat match_RGBLImg, Mat match_RGBRImg, float lowst_door, int dist_width, int halflengthsize);//������
};

