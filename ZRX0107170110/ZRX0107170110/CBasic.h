#pragma once
/***************************************************************************
�ࣺCBasic
���ã���װͼ����������������水ť�������� ������Ӧ����ͼƬ�����������ͼƬ����
Welcome to my Github and my CSDN blog , more information will be available about the project!
Github:https://github.com/Yiqingde
CSDN Blog:https://me.csdn.net/weixin_42348202
��ʷ��**����**         **����**            **ǩ��**
	  2019��9��26��        ����              �����
/**************************************************************************/
#include "time.h"
#include "zrxCImgPro.h"
#include "CMatchingImg.h"
#include "CDem.h"
class CBasic
{
public:
	CBasic();
	~CBasic();
	Mat m_srcimg;//ԭʼ�Ҷ�ͼ��
	Mat m_srcimgrgb;//RGB��ɫ��ͼ��
	bool tag;//³����
	zrxCImgPro function1;//����zrxCImgProͼ�����������
	zrxCFeatureVector function2;//����zrxCFeatureVectorͼ�����������

	//Mat match_LImg_txt;//�����������Ӱ��txtʹ�ã��ǻ�ɫ��
	//Mat match_RGBLImg_txt;//�����������Ӱ��txtʹ�ã��ǲ�ɫ��
	Mat match_LImg;//�洢��Ӱ�����ͼ��
	Mat match_RImg;//�洢��Ӱ�����ͼ��
	Mat match_RGBLImg;//
	Mat match_RGBRImg;//
public://********************************�洢��ť���ܺ���
	void OpenImg();//ʵ�ְ�ť���ܣ���ͼ��
	void Button_binaryImg();//ʵ�ְ�ť���ܣ���ʾ��ֵͼ��
	void Button_GaussImg();//ʵ�ְ�ť���ܣ�������ʾ��д��opencv��gaussͼ�񣬲���ʾ����ʱ��
	void Button_Help(); //ʵ�ְ�ť���ܣ�help
	void Button_Moravec();//Moravec��ť
	void Button_Imagematching_readleft();//��ȡ��Ӱ������
	void Button_Imagematching_readright();//��ȡ��Ӱ������
	void Button_Imagematching_makingNumber(int Moricsize, int Moravecsize2, int Moraveclowstdoor);//������ƬMoravec����
	void Button_Imagematching_view(float lowst_door, int dist_width, int halflengthsize);

	void Button_DEM();
};

