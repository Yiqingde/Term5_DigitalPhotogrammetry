#pragma once
/***************************************************************************
�ࣺzrxCFeatureVector
���ã�Moraavec������ ��Ӻ���:Moravec()
Welcome to my Github and my CSDN blog , more information will be available about the project!
Github:https://github.com/Yiqingde
CSDN Blog:https://me.csdn.net/weixin_42348202
��ʷ��**����**         **����**            **ǩ��**
	  2019��9��26��        ����              �����
/**************************************************************************/
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
using namespace cv;
using namespace std;
class zrxCFeatureVector
{
private:
	CString strOut;//�洢���txt������
	void find(float a[], int m, float &max, float &min);//�����Сֵ
	float Moravec_core(Mat m_srcimg, int Moravecsize, int i, int j);//Moravec_core��������
	void Moravec_core2(Mat &m_srcimgrgb,int Moravecsize2, Mat &Morvec, vector<Point3f> &f);//Moravec_core2�ֲ����ƺ���
public:
	zrxCFeatureVector();
	~zrxCFeatureVector();
	void Reporttxt(CString temp);//�����txt����
	void Moravec(Mat m_srcimg, Mat &m_srcimgrgb, int Moravecsize, int Moravecsize2,int Moraveclowstdoor, Mat &Morvec, vector<Point3f> &f);//Moravec��Ҫ�����������������������
};

