#pragma once
/***************************************************************************
类：CBasic
作用：封装图像操作函数，仅储存按钮操作功能 调用相应其他图片处理类来完成图片操作
Welcome to my Github and my CSDN blog , more information will be available about the project!
Github:https://github.com/Yiqingde
CSDN Blog:https://me.csdn.net/weixin_42348202
历史：**日期**         **理由**            **签名**
	  2019年9月26日        创建              张睿祥
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
	Mat m_srcimg;//原始灰度图像
	Mat m_srcimgrgb;//RGB颜色的图像
	bool tag;//鲁棒性
	zrxCImgPro function1;//创建zrxCImgPro图像处理操作对象
	zrxCFeatureVector function2;//创建zrxCFeatureVector图像处理操作对象

	//Mat match_LImg_txt;//供制作左核线影像txt使用，是灰色的
	//Mat match_RGBLImg_txt;//供制作左核线影像txt使用，是彩色的
	Mat match_LImg;//存储左影像核线图像
	Mat match_RImg;//存储右影像核线图像
	Mat match_RGBLImg;//
	Mat match_RGBRImg;//
public://********************************存储按钮功能函数
	void OpenImg();//实现按钮功能，打开图像
	void Button_binaryImg();//实现按钮功能，显示二值图像
	void Button_GaussImg();//实现按钮功能，包括显示自写与opencv的gauss图像，并显示运行时间
	void Button_Help(); //实现按钮功能，help
	void Button_Moravec();//Moravec按钮
	void Button_Imagematching_readleft();//读取左影像数据
	void Button_Imagematching_readright();//读取右影像数据
	void Button_Imagematching_makingNumber(int Moricsize, int Moravecsize2, int Moraveclowstdoor);//制作左片Moravec数据
	void Button_Imagematching_view(float lowst_door, int dist_width, int halflengthsize);

	void Button_DEM();
};

