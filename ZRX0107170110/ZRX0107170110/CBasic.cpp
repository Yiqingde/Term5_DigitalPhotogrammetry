#include "stdafx.h"
#include "CBasic.h"


CBasic::CBasic()
{
	this->tag = 0;//³��
}


CBasic::~CBasic()
{
}
/***************************************************************************
������OpenImg()
���ã�ʵ�ְ�ť���ܣ���ͼ����ʾ�Ҷ�ͼ�񣬴洢�� m_srcimg�У� tag�Ǳ�ǩ�����ӳ���³����
��������
����ֵ����
��ʷ��**����**         **����**            **ǩ��**
	  2019��9��20��        ����              �����
/**************************************************************************/
void CBasic::OpenImg()
{
	CFileDialog FileDlg(TRUE, "*.jpg;*.bmp", "*.jpg;*.bmp", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "Ӱ���ļ�()");
	if (FileDlg.DoModal() != IDOK)
	{
		return;
	}
	CString strImgName = FileDlg.GetPathName();
	//��Ӱ��	
	m_srcimg = imread(strImgName.GetBuffer(), IMREAD_GRAYSCALE);//IMREAD_GRAYSCALE  �ԻҶ���ʽ��
	m_srcimgrgb = imread(strImgName.GetBuffer(), IMREAD_COLOR);//IMREAD_COLOR  �Բ�ɫ��ʽ��
	//resize(m_srcimg, m_srcimg, Size(m_srcimg.cols * 800 / m_srcimg.rows, 800), 0, 0, INTER_CUBIC);//����Ӧ����ͼ���С
	//resize(m_srcimgrgb, m_srcimgrgb, Size(m_srcimgrgb.cols * 800 / m_srcimgrgb.rows, 800), 0, 0, INTER_CUBIC);//����Ӧ����ͼ���С
	imshow("ԭʼͼ��", m_srcimgrgb); //��ʾ
	tag = 1;
}


/***************************************************************************
������Button_binaryImg()
���ã�ʵ�ְ�ť���ܣ���ʾ��ֵͼ��
��������
����ֵ����
��ʷ��**����**         **����**            **ǩ��**
	  2019��9��20��        ����              �����
/**************************************************************************/
void CBasic::Button_binaryImg()
{
	if (tag == 0)
	{
		AfxMessageBox(_T("�����ȴ�Ӱ����ܽ��в�����"));
		return;
	}
	//��ֵ������
	Mat m_binary;
	function1.BinaryImage(m_srcimg, 100, m_binary);
	imshow("ͼ���ֵ�����", m_binary); //��ʾ
	waitKey();
}


/***************************************************************************
������Button_GaussImg()
���ã�ʵ�ְ�ť���ܣ�������ʾ��д��opencv��gaussͼ�񣬲���ʾ����ʱ��
��������
����ֵ����
��ʷ��**����**         **����**            **ǩ��**
	  2019��9��20��        ����              �����
/**************************************************************************/
void CBasic::Button_GaussImg()
{
	if (tag == 0)
	{
		AfxMessageBox(_T("�����ȴ�Ӱ����ܽ��в�����"));
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
	imshow("��˹�˲����", distImg); //��ʾ
	finish = clock();
	totaltime = (double)(finish - start) / CLOCKS_PER_SEC;

	waitKey(100); //�ȴ������������ڹر�\�س�\ESC�Ȳ������������µĳ���
	//opencv�Դ���˹�˲�
	Mat dstImage;
	start1 = clock();
	GaussianBlur(m_srcimg, dstImage, Size(5, 5), 0, 0);
	//��ʾЧ��ͼ
	imshow("opencv�Դ���˹�˲�Ч��ͼ", dstImage);
	finish1 = clock();
	totaltime1 = (double)(finish1 - start1) / CLOCKS_PER_SEC;

	waitKey(3000);
	CString runtime;
	runtime.Format("%s%f%s\r\n%s%f%s",
		_T("��дGauss�˲�����ʱ�䣺"),
		totaltime,
		_T("s"),
		_T("opencvGauss�˲�����ʱ�䣺"),
		totaltime1,
		_T("s")
	);
	AfxMessageBox(runtime);

}

/***************************************************************************
������Button_Help()
���ã�ʵ�ְ�ť���ܣ�help
��������
����ֵ����
��ʷ��**����**         **����**            **ǩ��**
	  2019��9��20��        ����              �����
/**************************************************************************/
void CBasic::Button_Help()
{
	CString help;
	help.Format("%s\r\n%s\r\n%s\r\n%s\r\n%s\r\n\r\n%s\r\n%s\r\n%s\r\n", 
		_T("��л��ʹ�ñ�������ʾ��"),
		_T("�����ȴ�Ӱ����ܽ��в�����"),
		_T("��д���룬Gauss�˲���Moravec������Ӱ�����ϵ����ƥ�䡢���ָ߳�ģ���ڲ����н����������ĵȴ�!"),
		_T("���ָ߳�ģ���ڲ��ȡ��С�����ڲ�����������Ӧʵ������ uav1m.txt uav3m.txt!�����ɽ���ɷֱ�CloudCompare��Sufer����򿪣���������Թ��̵�txt�����"),
		_T("ʾ�����ݡ�ʾ������ڸ�MFC����·����!"),
		_T("Welcome to my Github and my CSDN blog , more information will be available about the project!"),
		_T("Github : https://github.com/Yiqingde"),
		_T("CSDN Blog : https://me.csdn.net/weixin_42348202")
	);
	AfxMessageBox(help);
}

/***************************************************************************
������Button_Moravec()
���ã�ʵ�ְ�ť���ܣ�Moravec
��������
����ֵ����
��ʷ��**����**         **����**            **ǩ��**
	  2019��9��26��        ����              �����
/**************************************************************************/
void CBasic::Button_Moravec()
{
	if (tag == 0)
	{
		AfxMessageBox(_T("�����ȴ�Ӱ����ܽ��в�����"));
		return;
	}
	Mat MoravecImg;
	clock_t start, finish;
	start = clock();
	vector<Point3f> f;
	function2.Moravec(m_srcimg, m_srcimgrgb,9,20,500,MoravecImg,f);//���ú���
	finish = clock();
	double totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
	CString runtime;
	runtime.Format(_T("%s%4f%s\n"),_T("************************* Morevec��������ʱ�䣺"), totaltime,_T("s *************************"));
	imshow("Moravec������ʾ", MoravecImg); //��ʾ
	waitKey();
	imshow("Moravec��ɫ��ʾ", m_srcimgrgb); //��ʾ
	function2.Reporttxt(runtime);//���txt
	imwrite("Moravec��ɫ��ʾ.jpg", m_srcimgrgb);
}

/***************************************************************************
������Button_Imagematching_readleft()
���ã���ȡ��Ӱ������,��match_LImg��ֵ
��������     
����ֵ����
��ʷ��**����**         **����**            **ǩ��**
	  2019��10��6��        ����              �����
/**************************************************************************/
void CBasic::Button_Imagematching_readleft()//��ȡ��Ӱ������
{
	CFileDialog FileDlg(TRUE, "*.jpg;*.bmp", "*.jpg;*.bmp", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "Ӱ���ļ�()");
	if (FileDlg.DoModal() != IDOK)
	{
		return;
	}
	CString strImgName = FileDlg.GetPathName();
	//��Ӱ��	
	match_LImg = imread(strImgName.GetBuffer(), IMREAD_GRAYSCALE);//IMREAD_GRAYSCALE  �ԻҶ���ʽ��
	//match_LImg_txt = imread(strImgName.GetBuffer(), IMREAD_GRAYSCALE);//IMREAD_GRAYSCALE  �ԻҶ���ʽ��
	match_RGBLImg = imread(strImgName.GetBuffer(), IMREAD_COLOR);//IMREAD_COLOR  �Բ�ɫ��ʽ��
	//match_RGBLImg_txt = imread(strImgName.GetBuffer(), IMREAD_COLOR);//IMREAD_COLOR  �Բ�ɫ��ʽ��
}


/***************************************************************************
������Button_Imagematching_readright()
���ã���ȡ��Ӱ������,��match_RImg��ֵ
��������
����ֵ����
��ʷ��**����**         **����**            **ǩ��**
	  2019��10��6��        ����              �����
/**************************************************************************/
void CBasic::Button_Imagematching_readright()//��ȡ��Ӱ������
{
	CFileDialog FileDlg(TRUE, "*.jpg;*.bmp", "*.jpg;*.bmp", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "Ӱ���ļ�()");
	if (FileDlg.DoModal() != IDOK)
	{
		return;
	}
	CString strImgName = FileDlg.GetPathName();
	//��Ӱ��	
	match_RImg = imread(strImgName.GetBuffer(), IMREAD_GRAYSCALE);//IMREAD_GRAYSCALE  �ԻҶ���ʽ��
	match_RGBRImg = imread(strImgName.GetBuffer(), IMREAD_COLOR);//IMREAD_COLOR  �Բ�ɫ��ʽ��
	
}


/***************************************************************************
������Button_Imagematching_makingNumber(int Moricsize, int Moravecsize2,int Moraveclowstdoor)
���ã�����ѵ������
������int Moricsize moricsize����
      int Moravecsize2 moricsize����
	  int Moraveclowstdoor   moricsize����
����ֵ����
��ʷ��**����**         **����**            **ǩ��**
	  2019��10��6��        ����              �����
/**************************************************************************/
void CBasic::Button_Imagematching_makingNumber(int Moricsize, int Moravecsize2,int Moraveclowstdoor)
{
	zrxCFeatureVector making_moravec_txt;
	Mat tempImg;
	vector<Point3f> txtf;
	clock_t start, finish;
	start = clock();
	if (match_LImg.empty()) { AfxMessageBox(_T("�����Ƿ���������Ӱ��")); return; }
	if (match_RImg.empty()) { AfxMessageBox(_T("�����Ƿ�����Һ���Ӱ��")); return; }
	Mat match_LImg_txt= match_LImg.clone();//����mat�ĸ���
	Mat match_RGBLImg_txt= match_RGBLImg.clone();//����mat�ĸ���
	making_moravec_txt.Moravec(match_LImg_txt, match_RGBLImg_txt, Moricsize, Moravecsize2, Moraveclowstdoor,tempImg,txtf);
	finish = clock();
	double totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
	CString runtime;
	runtime.Format(_T("%s%4f%s\n%s\n"), _T("************************* Morevec��������ʱ�䣺"), totaltime, _T("s *************************"),_T("*************************Ӱ��洢������·��  �����Ӱ��Moravec��ɫ��ʾ.jpg  �� *************************"));
	making_moravec_txt.Reporttxt(runtime);//���txt
	imwrite("�����Ӱ��Moravec��ɫ��ʾ.jpg", match_RGBLImg_txt);
}

/***************************************************************************
������Button_Imagematching_makingNumber(int Moricsize, int Moravecsize2,int Moraveclowstdoor)
���ã�����Moravecd��txt
������int Moricsize 
	  int Moravecsize2
	  int Moraveclowstdoor ������
����ֵ����
��ʷ��**����**         **����**            **ǩ��**
	  2019��10��6��        ����              �����
/**************************************************************************/
void CBasic::Button_Imagematching_view(float lowst_door, int dist_width, int halflengthsize)
{
	CMatchingImg No1;
	No1.MatchingImg(match_LImg,match_RImg,match_RGBLImg, match_RGBRImg,lowst_door,dist_width,halflengthsize);
}

/***************************************************************************
������Button_DEM()
���ã�DEM��ť
��������
����ֵ����
��ʷ��**����**         **����**            **ǩ��**
	  2019��10��6��        ����              �����
/**************************************************************************/
void CBasic::Button_DEM()
{
	CDem t;
	t.main();
}