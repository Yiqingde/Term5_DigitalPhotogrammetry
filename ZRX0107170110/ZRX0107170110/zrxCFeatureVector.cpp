#include "stdafx.h"
#include "zrxCFeatureVector.h"


zrxCFeatureVector::zrxCFeatureVector()
{
}


zrxCFeatureVector::~zrxCFeatureVector()
{
}

/***************************************************************************
������Reporttxt()
���ã���������txt���õ������б���strOut
��������
����ֵ����
��ʷ��**����**         **����**            **ǩ��**
	  2019��9��26��        ����              �����
/**************************************************************************/
void zrxCFeatureVector::Reporttxt(CString runtime)

{
	if (strOut == _T("")) { AfxMessageBox(_T("������������!")); }
	else {
		CFileDialog dlg(false, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("Txt Files(*.txt)|*.txt|All Files(*.*)|*.*|"), AfxGetMainWnd());
		CString strPath;
		if (dlg.DoModal() == IDCANCEL) return;
		else
		{
			strPath = dlg.GetPathName();

			if (strPath.Find(_T(".txt")) < 0)
			{
				if (strPath.Find(_T(".dat")) < 0)
				{
					strPath += _T(".txt");//Ĭ�ϴ���Ϊtxtģʽ
				}
			}
		}
		TRY
		{
			CString cs;
			CStdioFile file(strPath, CFile::shareExclusive | CFile::modeWrite | CFile::modeCreate);
			setlocale(LC_CTYPE, ("chs")); //�����������
			file.WriteString(runtime);
			file.WriteString(strOut);
			file.Close();
			CString temp;
			temp.Format(_T("%s%s"),_T("��λ��Ϣ�ѵ�����"),strPath);
			AfxMessageBox(temp);
		}
			CATCH_ALL(e)
		{
			e->ReportError();
			return;
		}
		END_CATCH_ALL
	}
}

/***************************************************************************
������find()
���ã�Ѱ����������ֵ ��Сֵ
������float a[]  ����
      int m ����ǰm��Ԫ��
	  float &max ���ֵ
	  float &min ��Сֵ
����ֵ����
��ʷ��**����**         **����**            **ǩ��**
	  2019��9��26��        ����              �����
/**************************************************************************/
void zrxCFeatureVector::find(float a[], int m, float &max, float &min)
{
	min = a[0];
	max = a[0];
	for (int i = 0; i < m; i++)
	{
		if (a[i] > max)
		{
			max = a[i];
			continue;
		}
		else if (a[i] < min)
		{
			min = a[i];
			continue;
		}
	}
}


/***************************************************************************
������Moravec_core()
���ã��������� ��"*"״��Сֵ
������Mat m_srcimg ԭʼͼ��
	  int Moravecsize ���ڴ�С
	  int i_x ����(x,y)�е�x
	  int j_y ����(x,y)�е�y
����ֵ����Сֵ
��ʷ��**����**         **����**            **ǩ��**
	  2019��9��26��        ����              �����
/**************************************************************************/
float zrxCFeatureVector::Moravec_core(Mat m_srcimg, int Moravecsize, int i_x, int j_y)
{
	int halfsize = (Moravecsize) / 2;//����С������ڴ�С
	float temp4[4];//�����ĸ����������������"*"�͵�ƽ����
	//�����ʼ��
	for (int i = 0; i < 4; i++)
	{
		temp4[i] = 0;
	}
	//�ۼ�*��ƽ����
	for (int i = 0; i < Moravecsize; i++)
	{
		float l = m_srcimg.at<uchar>(i_x - halfsize + i, j_y);//    | x���� ������
		temp4[0] += pow(m_srcimg.at<uchar>(i_x - halfsize + i, j_y) - m_srcimg.at<uchar>(i_x - halfsize + i + 1, j_y), 2);//    | x���� ������
		temp4[1] += pow(m_srcimg.at<uchar>(i_x, j_y - halfsize + i) - m_srcimg.at<uchar>(i_x, j_y - halfsize + i + 1), 2);//    - y����
		temp4[2] += pow(m_srcimg.at<uchar>(i_x - halfsize + i, j_y - halfsize + i) - m_srcimg.at<uchar>(i_x - halfsize + i + 1, j_y - halfsize + i + 1), 2);//   \ ����
		temp4[3] += pow(m_srcimg.at<uchar>(i_x - halfsize + i, j_y + halfsize - i) - m_srcimg.at<uchar>(i_x - halfsize + i + 1, j_y + halfsize - i - 1), 2);//   / ����
	}
	float min, max;//������������ֵ ��Сֵ
	find(temp4, 4, max, min);//����Сֵ��ֵ
	return min;//���ؼ�Сֵ
}


/***************************************************************************
������Moravec_core2()
���ã��ֲ����� ����ʼ��ͼ
������Mat m_srcimgrgb ԭʼ��ɫͼ��
	  int Moravecsize2 �ֲ����ƴ��ڴ�С
	  Mat &Morvec ��֮ǰMoravec���ڲ����󲢾�����ֵ���ͼ��
	  vector<Point3i> &f �����洢չ��
����ֵ����
��ʷ��**����**         **����**            **ǩ��**
	  2019��9��26��        ����              �����
/**************************************************************************/
void zrxCFeatureVector::Moravec_core2( Mat &m_srcimgrgb,int Moravecsize2, Mat &Morvec, vector<Point3f> &f)
{
	int halfMoravecsize2 = Moravecsize2 / 2;//����С������ڴ�С  
	//�Ĳ�ѭ�����ã���Դ��ڳ��˱߿��ÿһ������ȷ������Ϊ���ģ�ֻҪ������һ��ֵ��С������ֵ ��������һ�����0 �����ų�С�ڼ���ֵ��ֵ
	for (int i = halfMoravecsize2; i < Morvec.rows - halfMoravecsize2 - 1; i++)
	{
		for (int j = halfMoravecsize2; j < Morvec.cols - halfMoravecsize2 - 1; j++)
		{
			float temp1 = Morvec.at<float>(i, j);
			for (int m = 0; m < Moravecsize2; m++)
			{

				for (int n = 0; n < Moravecsize2; n++)
				{
					float temp2 = ((i - halfMoravecsize2 + m >= 0) && (j - halfMoravecsize2 + n >= 0) && (i - halfMoravecsize2 + m < Morvec.rows) && (j - halfMoravecsize2 + n < Morvec.rows)) ? Morvec.at<float>(i - halfMoravecsize2 + m, j - halfMoravecsize2 + n) : 0;
					//float temp2 = Morvec.at<float>(i - halfMoravecsize2 + m, j - halfMoravecsize2 + n);
					if (temp1 < temp2)
					{
						Morvec.at<float>(i, j) = 0;
						n = Moravecsize2;
						m = Moravecsize2;
					}
				}
			}
		}
	}
	//��ʼ���д洢�� vector<Point3i> &f ��
	for (int i = halfMoravecsize2; i < Morvec.rows - halfMoravecsize2 - 1; i++)
	{
		for (int j = halfMoravecsize2; j < Morvec.cols - halfMoravecsize2 - 1; j++)
		{

			if (Morvec.at<float>(i, j)> 0)
			{
				Point3f temp;
				temp.x = i;
				temp.y = j;
				temp.z = Morvec.at<float>(i, j);
				float a = temp.x;
				float b = temp.y;
				float c = temp.z;
				f.push_back(temp);
			}
		}
	}
	
	//��ʼɾ��ͬ��һ����ֵһ�����ظ��㣬���ܳ��ָ��ʽ�С�����ϴ��ͼ������ĳЩ�����л���ںü�����ֵ��ȵļ���ֵ
	for (int i = 0; i < f.size() - 1; i++)
	{
		for (int j = i + 1; j < f.size(); j++)
		{
			if ((f.at(i).z == f.at(j).z))
			{
				if (abs(f.at(i).x - f.at(j).x) < Moravecsize2 || abs(f.at(i).y - f.at(j).y) < Moravecsize2)
				{
					f.erase(f.begin() + j);
					j=j-1;
				}
			}
		}
	}
	/*
	//*********************ð������
	for (int i = 0; i < f.size()-1; i++) {
		int tem = 0;
		// �ڲ�forѭ���������ڵ�����Ԫ�ؽ��бȽ�
		for (int j = i + 1; j < f.size(); j++) {
			if (f.at(i).z < f.at(j).z) {
				tem = f.at(j).z;
				f.at(j).z = f.at(i).z;
				f.at(i).z = tem;
			}
		}
	}
	*/
	/*********************����ע�͵�D���� ������Ϊ���޸���ʾ��ֵ �������50 ֻ��ʾǰ50�����ֵ,����ð��������ʹ�ã�����Ч����̫��
	*/
	CString temp;
	temp.Format(_T("%s%d\n%s\n"),_T("���еĵ����:"),f.size(),_T("X���꣬Y���꣬Morevec���ֵ"));
	strOut += temp;
	
	//*D int tag2 = (f.size() > 50) ? 50 : f.size();
	for (size_t i = 0; i < f.size(); i++)
	{
		circle(m_srcimgrgb, Point(int(f.at(i).y), int(f.at(i).x)), 5, Scalar(0, 0, 255),1.67);
		temp.Format(_T("%d,%d,%f\n"), int(f.at(i).x), int(f.at(i).y), f.at(i).z);
		strOut += temp;
	}
}


/***************************************************************************
������Moravec()
���ã�Moeavec������ �������Ϻ���
������Mat m_srcimg ԭʼͼ��
      Mat m_srcimgrgb ԭʼ��ɫͼ��
	  int Moravecsize  * �ʹ��ڴ�С
	  int Moravecsize2 �ֲ����ƴ��ڴ�С
	  Mat &Morvec ��֮ǰMoravec���ڲ����󲢾�����ֵ���ͼ��
����ֵ����
��ʷ��**����**         **����**            **ǩ��**
	  2019��9��26��        ����              �����
/**************************************************************************/
void zrxCFeatureVector::Moravec(Mat m_srcimg, Mat &m_srcimgrgb, int Moravecsize, int Moravecsize2, int Moraveclowstdoor,Mat &Morvec, vector<Point3f> &f)
{
	//Moravecsize = (Moravecsize % 2 == 1) ? Moravecsize : Moravecsize + 1;
	//****************************�洢�����Ϣ ��bug��
	GaussianBlur(m_srcimg, m_srcimg, Size(Moravecsize, Moravecsize), 0, 0);//ʹ��opencv�Դ���˹�˲�Ԥ����
	Morvec.create(m_srcimg.rows, m_srcimg.cols, CV_32FC1);//���ٿռ�
	//if (mean < 60) { mean = 300; }
	for (int i = Moravecsize; i < m_srcimg.rows - Moravecsize; i++)
	{
		for (int j = Moravecsize; j < m_srcimg.cols - Moravecsize; j++)
		{
			float min = Moravec_core(m_srcimg, Moravecsize, i, j);
			Morvec.at<float>(i, j) = min;
			if (Morvec.at<float>(i, j) < Moraveclowstdoor)
			{
				Morvec.at<float>(i, j) = 0;
			}
		}
	}
	//****************************�ֲ����Ʋ���ʾ
	Moravec_core2(m_srcimgrgb, Moravecsize2, Morvec, f);
	Morvec.convertTo(Morvec, CV_8UC1);
	//Morvec2.convertTo(Morvec2, CV_8UC1);
}