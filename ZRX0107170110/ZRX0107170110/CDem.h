#pragma once
#include "C_points.h"
/***************************************************************************
�ࣺCDem
���ã���װ��С����DEM�������������������水ť�������ܣ�����txt
Welcome to my Github and my CSDN blog , more information will be available about the project!
Github:https://github.com/Yiqingde
CSDN Blog:https://me.csdn.net/weixin_42348202
��ʷ��**����**         **����**            **ǩ��**
	  2019��10��26��        ����              �����
/**************************************************************************/
class CDem
{
	C_points *p;//���ݶ���һά����
	int allpoints;//���е�
	//����������
	int nx;//�к�
	int ny;//�к�
	
	double width;//�ֱ���1 ��3
	double dists;//����
	//�������������������������Сֵ
	double xlo;
	double xhi;
	double ylo;
	double yhi;
	double zlo;
	double zhi;
public:
	CDem();
	~CDem();
	int Div(const CString strLine, char split, CStringArray &strArray);//�ַ����ָ��
	void findpoints(int x, int y, int size, C_points *d);//Ѱ��
	void convertxy2id(double x, double y, int &tempr, int &tempc, int &id);//ת��ID
	int convertcr2id(int tempr, int tempc);//ת��ID
	void convertid2rc(int id, int&rr, int &cc);//ת��ID
	double dist(double x, double y, double x2, double y2);//�������
	double truedist2(double x, double y, double x2, double y2);//�������
	double workout(int rr, int cc, Mat X_six);//��С���˾���
	bool readDem();//��ȡdem����
	void search();//��������
	void out();//���1
	void out2();//���2
	void out3();//���3
	void getcolor1(Mat &f);//������ɫ����������
	void returncolor(double &a, double &b, double &c, double zz, double min, double max, Mat color);//�õ���ɫ
	void BeatifulDem();//��������Dem������ȥ������
	void main();//������
};

