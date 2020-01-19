#include "stdafx.h"
#include "CMatchingImg.h"


CMatchingImg::CMatchingImg()
{
}


CMatchingImg::~CMatchingImg()
{
}
//***********************************
//�ַ��ָ��
//***********************************
int CMatchingImg::Div(const CString strLine, char split, CStringArray &strArray)
{
	strArray.RemoveAll();//�Դ��������
	CString temp = strLine;
	int tag = 0;
	while (1)
	{
		tag = temp.Find(split);
		if (tag >= 0)
		{
			strArray.Add(temp.Left(tag));
			temp = temp.Right(temp.GetLength() - tag - 1);
		}
		else { break; }
	}
	strArray.Add(temp);
	return strArray.GetSize();
}

/***************************************************************************
������read(vector < Point3i> &f)
���ã���ȡtxt�ļ���������vector��
��������
����ֵ����
��ʷ��**����**         **����**            **ǩ��**
	  2019��10��11��        ����              �����
/**************************************************************************/
bool CMatchingImg::read(vector < Point3f> &f)
{
	CFileDialog dlgFile(TRUE, _T("txt"), NULL,
		OFN_ALLOWMULTISELECT | OFN_EXPLORER,
		//_T("(�ı��ļ�)|*.txt"));
		_T(""));
	if (dlgFile.DoModal() == IDCANCEL) return 0;
	CString strName = dlgFile.GetPathName();//��ȡ���ļ��ļ�����·����
	setlocale(LC_ALL, "");
	CStdioFile sf;
	if (!sf.Open(strName, CFile::modeRead)) return 0;//��strName�ļ�·���е�����
	CString strLine;
	CString strContent;//���������ַ���
	CStringArray array;//�����ķָ�ʹ��
	strContent.Empty();//strContent���������
	//��ʼ������ 
	BOOL bEOF = sf.ReadString(strLine);//��һ��
	if (bEOF == 0) { AfxMessageBox(_T("������")); return 0; }
	//��ȡ���Ƶ�
	bEOF = sf.ReadString(strLine);//�ڶ��� 
	if (bEOF == 0) { AfxMessageBox(_T("���ݲ��淶")); return 0; }
	bEOF = sf.ReadString(strLine);//������ 
	if (bEOF == 0) { AfxMessageBox(_T("���ݲ��淶")); return 0; }
	int n = Div(strLine, ':', array);
	if (n < 2) { AfxMessageBox(_T("����ȱʧ")); return 0; }
	int i = _ttoi(array[1]);
	bEOF = sf.ReadString(strLine);//������ 
	if (bEOF == 0) { AfxMessageBox(_T("���ݲ��淶")); return 0; }
	while (i>0)
	{
		bEOF = sf.ReadString(strLine);
		if (bEOF == 0) { AfxMessageBox(_T("���ݲ��淶")); return 0; }
		int n = Div(strLine, ',', array);
		if (n < 3) { AfxMessageBox(_T("����ȱʧ")); return 0; }
		
		Point3f temp;
		temp.x = _ttoi(array[0]);
		temp.y = _ttoi(array[1]);
		temp.z = _ttoi(array[2]);
		f.push_back(temp);
		i--;
	}
	return 1;
}


/***************************************************************************
������Get_coefficient(Mat Lmatchwindow, Mat match_RImg,int x,int y,float &cofficent)
���ã��������ϵ��
����:Mat Lmatchwindow�Ѿ����������Ƭ����
     Mat match_RImg �Һ���Ӱ��
	 int x ����ֵx
	 int y ����ֵy
	 float &cofficent�������ؼ�����ĵ���ֵ
����ֵ����
��ʷ��**����**         **����**            **ǩ��**
	  2019��10��11��        ����              �����
/**************************************************************************/
void CMatchingImg::Get_coefficient(Mat Lmatchwindow, Mat match_RImg,int x,int y,float &cofficent)
{
	//��������������ȷ�����������ڵĴ�С
	Mat Rmatchwindow;
	Rmatchwindow.create(Lmatchwindow.rows, Lmatchwindow.cols, CV_32FC1);
	float aveRImg = 0;
	for (int m = 0; m < Lmatchwindow.rows; m++)
	{
		for (int n = 0; n < Lmatchwindow.cols; n++)
		{
			aveRImg += match_RImg.at<uchar>(x + m, y + n);
			Rmatchwindow.at<float>(m, n) = match_RImg.at<uchar>(x + m, y + n);
		}
	}
	aveRImg = aveRImg / (Lmatchwindow.rows*Lmatchwindow.cols);
	for (int m = 0; m < Lmatchwindow.rows; m++)
	{
		for (int n = 0; n < Lmatchwindow.cols; n++)
		{
			Rmatchwindow.at<float>(m, n) -= aveRImg;
		}
	}
	//��ʼ�������ϵ��
	float cofficent1=0;
	float cofficent2=0;
	float cofficent3=0;
	for (int m = 0; m < Lmatchwindow.rows; m++)
	{
		for (int n = 0; n < Lmatchwindow.cols; n++)
		{
			cofficent1 += Lmatchwindow.at<float>(m, n)*Rmatchwindow.at<float>(m, n);
			cofficent2 += Rmatchwindow.at<float>(m, n)*Rmatchwindow.at<float>(m, n);
			cofficent3 += Lmatchwindow.at<float>(m, n)*Lmatchwindow.at<float>(m, n);
		}
	}
	cofficent = cofficent1 / sqrt(cofficent2 * cofficent3);
}
/***************************************************************************
������vectorsort(vector < Point3f> &Temp_sort)
���ã��������ڶ�vector < Point3f> &Temp_sort��zԪ��ð������xyz��Ϊһ��������иı䣬��Ԫ��ֵ���
����:vector < Point3f> &Temp_sort ��Ҫ�����vector
����ֵ����
��ʷ��**����**         **����**            **ǩ��**
	  2019��10��11��        ����              �����
/**************************************************************************/

void CMatchingImg::vectorsort(vector < Point3f> &Temp_sort)
{
	for (int i = 0; i < Temp_sort.size() - 1; i++) {
		float tem = 0;
		float temx = 0;
		float temy = 0;
		// �ڲ�forѭ���������ڵ�����Ԫ�ؽ��бȽ�
		for (int j = i + 1; j < Temp_sort.size(); j++) {
			if (Temp_sort.at(i).z < Temp_sort.at(j).z) {
				tem = Temp_sort.at(j).z;
				Temp_sort.at(j).z = Temp_sort.at(i).z;
				Temp_sort.at(i).z = tem;

				temx = Temp_sort.at(j).x;
				Temp_sort.at(j).x = Temp_sort.at(i).x;
				Temp_sort.at(i).x = temx;

				temy = Temp_sort.at(j).y;
				Temp_sort.at(j).y = Temp_sort.at(i).y;
				Temp_sort.at(i).y = temy;
			}
		}
	}
}


/***************************************************************************
������lastview(Mat match_LImg, Mat match_RImg,vector<Point3i> f,vector<Point3f> r)
���ã����������ʾͼ�񲢽���д�빤��·����txt��
����:Mat match_LImg �����Ӱ��
	 Mat match_RImg �Һ���Ӱ��
	 vector<Point3i> f �洢����ɸѡ�����moravecԪ��
	 vector<Point3f> r �洢����Ƭ��Ѱ�ҵ�����ӦԪ�أ���vector<Point3i> f���Ӧ
����ֵ����
��ʷ��**����**         **����**            **ǩ��**
	  2019��10��11��        ����              �����
/**************************************************************************/
void CMatchingImg::lastview(Mat match_LImg, Mat match_RImg,vector<Point3f> f,vector<Point3f> r)
{
	Mat bothview;//���ͼ��
	bothview.create(2 * match_LImg.rows, match_LImg.cols, match_LImg.type());
	for (int i = 0; i < match_LImg.rows; i++)
	{
		for (int j = 0; j < match_LImg.cols; j++)
		{
			bothview.at<Vec3b>(i, j) = match_LImg.at<Vec3b>(i, j);
		}
	}
	for (int i = match_LImg.rows; i < 2 * match_LImg.rows; i++)
	{
		for (int j = 0; j < match_LImg.cols; j++)
		{
			bothview.at<Vec3b>(i, j) = match_RImg.at<Vec3b>(i - match_LImg.rows, j);
		}
	}//����Ӱ��϶�Ϊһ	

	for (int i = 0; i < r.size(); i++)
	{
		/*
		if (A % 3 == 0) { a++; }
		if (A % 3 == 1) { b+=a; }
		if (A % 3 == 2) { c+=b; }
		c = c > 255 ? 1 : c;
		b = b > 255 ? 1 : b;
		a = a > 255 ? 1 : a;
		A++;
		int temp = a;
		a = b;
		b = temp;*/
		
		int a = (rand() % 200);
		int b = (rand() % 200 + 99);
		int c = (rand() % 200) - 50;
		if (a > 100 || a < 0)
		{
			a = 255;
		}
		if (b > 255 || b < 0)
		{
			b = 88;
		}
		if (c > 255 || c < 0)
		{
			c = 188;
		}
		line(bothview, Point(f.at(i).y,f.at(i).x), Point(r.at(i).y, r.at(i).x + match_LImg.rows ), Scalar(a, b, c),2);
	}


	//�����txt��
	CStdioFile SF;
	CString strLine;
	CString strOut;
	setlocale(LC_ALL, "");
//if (!SF.Open(_T("���ϵ����5Ԫ��.txt"), CFile::modeCreate | CFile::modeWrite)) return;
	if (!SF.Open(_T("���ϵ����5Ԫ��.txt"), CFile::modeCreate | CFile::modeWrite)) return;
	strLine.Format(_T("%d\n"),r.size());
	strOut += strLine;
	for (int i = 0; i < r.size(); i++)
	{
		strLine.Format(_T("%.f %.f %.f %.f\n"),  f.at(i).y, f.at(i).x, r.at(i).y, r.at(i).x );
		strOut += strLine;
	}
	SF.WriteString(strOut);
	SF.Close();
	AfxMessageBox(_T("�ɹ�!�������������ϵ����5Ԫ��.txt���У���MFC����·����"));
	imshow("����ƬӰ�����ϵ������λչʾ", bothview);
	//waitKey();
	imwrite("����ƬӰ�����ϵ������λչʾ.jpg", bothview);
}

/***************************************************************************
������MatchingImg(Mat &match_LImg, Mat &match_RImg , Mat match_RGBLImg, Mat match_RGBRImg, float lowst_door, int dist_width,int halflengthsize)
���ã����ϵ�������������������Ϻ���
����:Mat match_LImg �����Ӱ��
	 Mat match_RImg �Һ���Ӱ��
	 Mat match_RGBLImg ��Ƭ��ɫӰ��
	 Mat match_RGBRImg ��Ƭ��ɫӰ��
	 float lowst_door ���ϵ������ֵ
	 int dist_width �涨һ����Ƭ����Ƭ����Ծ���
	 int halflengthsize �涨�Ը�����Ϊ���ĵ�x��������뾶
����ֵ����
��ʷ��**����**         **����**            **ǩ��**
	  2019��10��11��        ����              �����
/**************************************************************************/
void CMatchingImg::MatchingImg(Mat &match_LImg, Mat &match_RImg , Mat match_RGBLImg, Mat match_RGBRImg, float lowst_door, int dist_width,int halflengthsize)
{
	if (match_LImg.empty()) { AfxMessageBox(_T("�����Ƿ���������Ӱ��")); return; }
	if (match_RImg.empty()) { AfxMessageBox(_T("�����Ƿ�����Һ���Ӱ��")); return; }
	int matchsize=9;//���ϵ���������δ��ڵı߳�
	int half_matchsize = matchsize / 2;//�߳���һ��
	//����֮ǰ����������λ��Ϣ�洢ֵf��
	vector<Point3f> f;//������ȡ��Ƭmoravec���ӵ�����
	vector<Point3f> r;//����д��Ƭƥ�䵽������
	int r_i = 0;
	bool tag=read(f);//���ж�ȡ����
	//�����󴰿ڵ�С����
	Mat Lmatchwindow;
	Lmatchwindow.create(matchsize, matchsize, CV_32FC1);
	//����f���ݵ�Ԥ���� ɾ�������Ϲ淶������
	for (size_t i = 0; i < f.size(); i++)
	{
		//*************************�������β���
		//***********����yֵ����Ӱ��Χ�ڵĵ�f	�ҡ�2
		if (f.at(i).y < dist_width + halflengthsize + half_matchsize + 1)
		{
			f.erase(f.begin() + i);
			i--;
			continue;
		}
		//***********����xֵ����Ӱ��Χ�ڵĵ�
		if (f.at(i).x <half_matchsize +5|| f.at(i).x>match_LImg.rows-half_matchsize-10)
		{
			f.erase(f.begin() + i);
			i--;
			continue;
		}
	}

	for (size_t i = 0; i < f.size(); i++)
	{
		//***************************���󴰿ڽ��м��㣬������Ϻ�ֵ����Lmatchwindow��
		float aveLImg = 0; 
		for (int m =0; m <matchsize; m++)
		{
			for (int n = 0; n < matchsize; n++)
			{
				aveLImg += match_LImg.at<uchar>(f.at(i).x - half_matchsize + m, f.at(i).y - half_matchsize + n);
				Lmatchwindow.at<float>(m, n) = match_LImg.at<uchar>(f.at(i).x - half_matchsize + m, f.at(i).y - half_matchsize + n);
			}
		}
		aveLImg = aveLImg / (matchsize* matchsize);//��ȡ�󴰿�ƽ��ֵ
		//����ĳ��ֵ
		for (int m = 0; m < matchsize; m++)
		{
			for (int n = 0; n < matchsize; n++)
			{
				Lmatchwindow.at<float>(m, n) = Lmatchwindow.at<float>(m, n) - aveLImg;
			}
		}
		//***************************���Ҵ��ڽ��м���
		//����Ԥ���Ҵ��ڵ�λ��
		
		vector < Point3f> halflengthsize2;
		//ȥ���ܵ�������ĵ�
		for (int ii = -halflengthsize; ii<=halflengthsize; ii++)
		{
			Point3f temphalflengthsize;
			float coffee;
			Get_coefficient(Lmatchwindow, match_RImg, f.at(i).x- half_matchsize, f.at(i).y - dist_width- half_matchsize + ii, coffee);
			temphalflengthsize.x = f.at(i).x;
			temphalflengthsize.y = f.at(i).y - dist_width + ii;
			temphalflengthsize.z = coffee;
			halflengthsize2.push_back(temphalflengthsize);
		}
		vectorsort(halflengthsize2);
		//*************************���еڶ��β���
		//***********�������������ϵ����������ֵ��ֵ
		if (halflengthsize2.at(0).z > lowst_door&&halflengthsize2.at(0).z < 1)
		{
			Point3f tempr;
			tempr.x = halflengthsize2.at(0).x;
			tempr.y = halflengthsize2.at(0).y;
			tempr.z = halflengthsize2.at(0).z;
			r.push_back(tempr);
		}
		else
		{
			f.erase(f.begin() + i);
			i--;
			continue;
		}
	}
	lastview(match_RGBLImg, match_RGBRImg,f,r);
}