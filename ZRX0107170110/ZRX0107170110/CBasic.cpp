#include "stdafx.h"
#include "CBasic.h"


CBasic::CBasic()
{
	this->tag = 0;//鲁棒
}


CBasic::~CBasic()
{
}
/***************************************************************************
函数：OpenImg()
作用：实现按钮功能，打开图像并显示灰度图像，存储到 m_srcimg中； tag是标签、增加程序鲁棒性
参数：无
返回值：无
历史：**日期**         **理由**            **签名**
	  2019年9月20日        创建              张睿祥
/**************************************************************************/
void CBasic::OpenImg()
{
	CFileDialog FileDlg(TRUE, "*.jpg;*.bmp", "*.jpg;*.bmp", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "影像文件()");
	if (FileDlg.DoModal() != IDOK)
	{
		return;
	}
	CString strImgName = FileDlg.GetPathName();
	//打开影像	
	m_srcimg = imread(strImgName.GetBuffer(), IMREAD_GRAYSCALE);//IMREAD_GRAYSCALE  以灰度形式打开
	m_srcimgrgb = imread(strImgName.GetBuffer(), IMREAD_COLOR);//IMREAD_COLOR  以彩色形式打开
	//resize(m_srcimg, m_srcimg, Size(m_srcimg.cols * 800 / m_srcimg.rows, 800), 0, 0, INTER_CUBIC);//自适应调整图像大小
	//resize(m_srcimgrgb, m_srcimgrgb, Size(m_srcimgrgb.cols * 800 / m_srcimgrgb.rows, 800), 0, 0, INTER_CUBIC);//自适应调整图像大小
	imshow("原始图像", m_srcimgrgb); //显示
	tag = 1;
}


/***************************************************************************
函数：Button_binaryImg()
作用：实现按钮功能，显示二值图像
参数：无
返回值：无
历史：**日期**         **理由**            **签名**
	  2019年9月20日        创建              张睿祥
/**************************************************************************/
void CBasic::Button_binaryImg()
{
	if (tag == 0)
	{
		AfxMessageBox(_T("需首先打开影像才能进行操作！"));
		return;
	}
	//二值化操作
	Mat m_binary;
	function1.BinaryImage(m_srcimg, 100, m_binary);
	imshow("图像二值化结果", m_binary); //显示
	waitKey();
}


/***************************************************************************
函数：Button_GaussImg()
作用：实现按钮功能，包括显示自写与opencv的gauss图像，并显示运行时间
参数：无
返回值：无
历史：**日期**         **理由**            **签名**
	  2019年9月20日        创建              张睿祥
/**************************************************************************/
void CBasic::Button_GaussImg()
{
	if (tag == 0)
	{
		AfxMessageBox(_T("需首先打开影像才能进行操作！"));
		return;
	}
	Mat distImg;
	clock_t start, finish;
	double totaltime;
	clock_t start1, finish1;
	double totaltime1;
	start = clock();
	function1.Gaussianfilter(m_srcimg, 5, 1.0, distImg);
	//namedWindow("ss", 1);
	imshow("高斯滤波结果", distImg); //显示
	finish = clock();
	totaltime = (double)(finish - start) / CLOCKS_PER_SEC;

	waitKey(100); //等待操作，将窗口关闭\回车\ESC等操作会运行以下的程序
	//opencv自带高斯滤波
	Mat dstImage;
	start1 = clock();
	GaussianBlur(m_srcimg, dstImage, Size(5, 5), 0, 0);
	//显示效果图
	imshow("opencv自带高斯滤波效果图", dstImage);
	finish1 = clock();
	totaltime1 = (double)(finish1 - start1) / CLOCKS_PER_SEC;

	waitKey(3000);
	CString runtime;
	runtime.Format("%s%f%s\r\n%s%f%s",
		_T("自写Gauss滤波运行时间："),
		totaltime,
		_T("s"),
		_T("opencvGauss滤波运行时间："),
		totaltime1,
		_T("s")
	);
	AfxMessageBox(runtime);

}

/***************************************************************************
函数：Button_Help()
作用：实现按钮功能，help
参数：无
返回值：无
历史：**日期**         **理由**            **签名**
	  2019年9月20日        创建              张睿祥
/**************************************************************************/
void CBasic::Button_Help()
{
	CString help;
	help.Format("%s\r\n%s\r\n%s\r\n%s\r\n%s\r\n\r\n%s\r\n%s\r\n%s\r\n", 
		_T("感谢您使用本程序！提示："),
		_T("需首先打开影像才能进行操作！"),
		_T("自写代码，Gauss滤波、Moravec、核线影像相关系数法匹配、数字高程模型内插运行较慢，请耐心等待!"),
		_T("数字高程模型内插采取最小二乘内插来做，自适应实验数据 uav1m.txt uav3m.txt!，生成结果可分别被CloudCompare、Sufer软件打开，另将方便调试过程的txt输出！"),
		_T("示例数据、示例结果在该MFC工作路径下!"),
		_T("Welcome to my Github and my CSDN blog , more information will be available about the project!"),
		_T("Github : https://github.com/Yiqingde"),
		_T("CSDN Blog : https://me.csdn.net/weixin_42348202")
	);
	AfxMessageBox(help);
}

/***************************************************************************
函数：Button_Moravec()
作用：实现按钮功能，Moravec
参数：无
返回值：无
历史：**日期**         **理由**            **签名**
	  2019年9月26日        创建              张睿祥
/**************************************************************************/
void CBasic::Button_Moravec()
{
	if (tag == 0)
	{
		AfxMessageBox(_T("需首先打开影像才能进行操作！"));
		return;
	}
	Mat MoravecImg;
	clock_t start, finish;
	start = clock();
	vector<Point3f> f;
	function2.Moravec(m_srcimg, m_srcimgrgb,9,20,500,MoravecImg,f);//调用函数
	finish = clock();
	double totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
	CString runtime;
	runtime.Format(_T("%s%4f%s\n"),_T("************************* Morevec算子运行时间："), totaltime,_T("s *************************"));
	imshow("Moravec单独显示", MoravecImg); //显示
	waitKey();
	imshow("Moravec彩色显示", m_srcimgrgb); //显示
	function2.Reporttxt(runtime);//输出txt
	imwrite("Moravec彩色显示.jpg", m_srcimgrgb);
}

/***************************************************************************
函数：Button_Imagematching_readleft()
作用：读取左影像数据,给match_LImg赋值
参数：无     
返回值：无
历史：**日期**         **理由**            **签名**
	  2019年10月6日        创建              张睿祥
/**************************************************************************/
void CBasic::Button_Imagematching_readleft()//读取左影像数据
{
	CFileDialog FileDlg(TRUE, "*.jpg;*.bmp", "*.jpg;*.bmp", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "影像文件()");
	if (FileDlg.DoModal() != IDOK)
	{
		return;
	}
	CString strImgName = FileDlg.GetPathName();
	//打开影像	
	match_LImg = imread(strImgName.GetBuffer(), IMREAD_GRAYSCALE);//IMREAD_GRAYSCALE  以灰度形式打开
	//match_LImg_txt = imread(strImgName.GetBuffer(), IMREAD_GRAYSCALE);//IMREAD_GRAYSCALE  以灰度形式打开
	match_RGBLImg = imread(strImgName.GetBuffer(), IMREAD_COLOR);//IMREAD_COLOR  以彩色形式打开
	//match_RGBLImg_txt = imread(strImgName.GetBuffer(), IMREAD_COLOR);//IMREAD_COLOR  以彩色形式打开
}


/***************************************************************************
函数：Button_Imagematching_readright()
作用：读取右影像数据,给match_RImg赋值
参数：无
返回值：无
历史：**日期**         **理由**            **签名**
	  2019年10月6日        创建              张睿祥
/**************************************************************************/
void CBasic::Button_Imagematching_readright()//读取左影像数据
{
	CFileDialog FileDlg(TRUE, "*.jpg;*.bmp", "*.jpg;*.bmp", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "影像文件()");
	if (FileDlg.DoModal() != IDOK)
	{
		return;
	}
	CString strImgName = FileDlg.GetPathName();
	//打开影像	
	match_RImg = imread(strImgName.GetBuffer(), IMREAD_GRAYSCALE);//IMREAD_GRAYSCALE  以灰度形式打开
	match_RGBRImg = imread(strImgName.GetBuffer(), IMREAD_COLOR);//IMREAD_COLOR  以彩色形式打开
	
}


/***************************************************************************
函数：Button_Imagematching_makingNumber(int Moricsize, int Moravecsize2,int Moraveclowstdoor)
作用：制作训练数据
参数：int Moricsize moricsize参数
      int Moravecsize2 moricsize参数
	  int Moraveclowstdoor   moricsize参数
返回值：无
历史：**日期**         **理由**            **签名**
	  2019年10月6日        创建              张睿祥
/**************************************************************************/
void CBasic::Button_Imagematching_makingNumber(int Moricsize, int Moravecsize2,int Moraveclowstdoor)
{
	zrxCFeatureVector making_moravec_txt;
	Mat tempImg;
	vector<Point3f> txtf;
	clock_t start, finish;
	start = clock();
	if (match_LImg.empty()) { AfxMessageBox(_T("请检查是否读入左核线影像")); return; }
	if (match_RImg.empty()) { AfxMessageBox(_T("请检查是否读入右核线影像")); return; }
	Mat match_LImg_txt= match_LImg.clone();//进行mat的复制
	Mat match_RGBLImg_txt= match_RGBLImg.clone();//进行mat的复制
	making_moravec_txt.Moravec(match_LImg_txt, match_RGBLImg_txt, Moricsize, Moravecsize2, Moraveclowstdoor,tempImg,txtf);
	finish = clock();
	double totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
	CString runtime;
	runtime.Format(_T("%s%4f%s\n%s\n"), _T("************************* Morevec算子运行时间："), totaltime, _T("s *************************"),_T("*************************影像存储至工作路径  左核线影像Moravec彩色显示.jpg  中 *************************"));
	making_moravec_txt.Reporttxt(runtime);//输出txt
	imwrite("左核线影像Moravec彩色显示.jpg", match_RGBLImg_txt);
}

/***************************************************************************
函数：Button_Imagematching_makingNumber(int Moricsize, int Moravecsize2,int Moraveclowstdoor)
作用：制作Moravecd的txt
参数：int Moricsize 
	  int Moravecsize2
	  int Moraveclowstdoor 三参数
返回值：无
历史：**日期**         **理由**            **签名**
	  2019年10月6日        创建              张睿祥
/**************************************************************************/
void CBasic::Button_Imagematching_view(float lowst_door, int dist_width, int halflengthsize)
{
	CMatchingImg No1;
	No1.MatchingImg(match_LImg,match_RImg,match_RGBLImg, match_RGBRImg,lowst_door,dist_width,halflengthsize);
}

/***************************************************************************
函数：Button_DEM()
作用：DEM按钮
参数：无
返回值：无
历史：**日期**         **理由**            **签名**
	  2019年10月6日        创建              张睿祥
/**************************************************************************/
void CBasic::Button_DEM()
{
	CDem t;
	t.main();
}