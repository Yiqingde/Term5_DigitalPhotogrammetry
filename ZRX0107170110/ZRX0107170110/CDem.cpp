#include "stdafx.h"
#include "CDem.h"

typedef struct tagDIRECTION
{
	int x_offset;
	int y_offset;
}DIRECTION;

DIRECTION direction_8[] = { {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1} };
//DIRECTION direction_4[] = { {0, -1},{0, 1} ,{-1, 0}, {1, 0}};
CDem::CDem()
{
	this->xlo = 9999999;
	this->ylo = 9999999;
	this->zlo = 9999999;
	this->xhi = 0;
	this->yhi = 0;
	this->zhi = 0;
	width = 3;
	dists = 10;
}


CDem::~CDem()
{
	if (p != NULL)
	{
		delete[] p;
	}
}

/***************************************************************************
������getcolor1(Mat &f)
���ã���ɫ����
������Mat &f ��ɫ���� ������0-1
����ֵ����
��ʷ��**����**         **����**            **ǩ��**
	  2019��10��27��        ����              �����
/**************************************************************************/
void CDem::getcolor1(Mat &f)
{
	f.create(64, 3, CV_64FC1);
	double temp_1 = 0.5625;
	for (int i = 0; i < 8 ;i++)
	{
		f.at<double>(i, 0) = 0;
		f.at<double>(i, 1) = 0;
		f.at<double>(i, 2) = temp_1;
		temp_1 += 0.0625;
	}
	temp_1 = 0.0625;
	for (int i = 8; i < 24; i++)
	{
		f.at<double>(i, 0) = 0;
		f.at<double>(i, 1) = temp_1;
		f.at<double>(i, 2) = 1;
		temp_1 += 0.0625;
	}
	temp_1 = 0.0625;
	for (int i = 24;  i < 40;i++)
	{
		f.at<double>(i, 0) = temp_1;
		f.at<double>(i, 1) = 1;
		f.at<double>(i, 2) = 1-temp_1;
		temp_1 += 0.0625;
	}
	temp_1 = 0.9375;
	for (int i = 40; i < 55; i++)
	{
		f.at<double>(i, 0) = 1;
		f.at<double>(i, 1) = temp_1;
		f.at<double>(i, 2) = 0;
		temp_1 -= 0.0625;
	}
	temp_1 = 1;
	for (int i = 55; i < 64;i++)
	{
		f.at<double>(i, 0) = temp_1;
		f.at<double>(i, 1) = 0;
		f.at<double>(i, 2) = 0;
		temp_1 -= 0.0625;
	}
}

/***************************************************************************
������returncolor(double &a, double &b, double &c, double zz, double min, double max,Mat color)
���ã�����ɫ������rgb��ɫ���������ֵ��Сֵ
������double &a  ����rgb��a
      double &b  ����rgb��b
	  double &c  ����rgb��c
	  double zz  ���ݸ�ֵ��ɫ
	  double min ��Сֵ
	  double max ���ֵ
	  Mat color ��ɫ����
����ֵ����
��ʷ��**����**         **����**            **ǩ��**
	  2019��10��27��        ����              �����
/**************************************************************************/
void CDem::returncolor(double &a, double &b, double &c, double zz, double min, double max,Mat color)
{
	int t = (zz - min) * 64 / (max - min);
	t = t < 0 ? 0 : t;
	t = t > 64 ? 64 : t;
	a = color.at<double>(t, 0);
	b = color.at<double>(t, 1);
	c = color.at<double>(t, 2);
}


//***********************************
//�ַ��ָ��
//***********************************
int CDem::Div(const CString strLine, char split, CStringArray &strArray)
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
������convertcr2id(int tempr, int tempc)
���ã������к��кŷ��� id
������int tempr
      int tempc
����ֵ��int һά�����id��
��ʷ��**����**         **����**            **ǩ��**
	  2019��10��27��        ����              �����
/**************************************************************************/
int CDem::convertcr2id(int tempr, int tempc)
{
	int id = (tempr - 1)*ny + tempc - 1;
	return id;
}

/***************************************************************************
������convertid2rc(int id, int&rr, int &cc)
���ã�����id �������к�
������int id  id��
	  int &rr  ���к�
	  int &cc  ���к�
����ֵ����
��ʷ��**����**         **����**            **ǩ��**
	  2019��10��27��        ����              �����
/**************************************************************************/
void CDem::convertid2rc(int id, int &rr, int &cc)
{
	double temp = double(id + 1) - 0.05;
	rr = (int(temp) / ny) + 1;
	cc = id + 1 - (rr - 1) *ny;
}

/***************************************************************************
������convertxy2id(double x, double y, int &tempr, int &tempc, int &id)
���ã�����xy   ���� �������кż�id ��������ʱʹ��
������double x xֵ
	  double y yֵ
	  int &tempr  �к�
	  int &tempc  �к�
	  int &id  id
����ֵ����
��ʷ��**����**         **����**            **ǩ��**
	  2019��10��27��        ����              �����
/**************************************************************************/
void CDem::convertxy2id(double x, double y, int &tempr, int &tempc, int &id)
{
	tempr = int((x - xlo-0.001) / width) + 1;
	tempc = int((y - ylo-0.001) / width) + 1;
	id=convertcr2id(tempr, tempc);
}


/***************************************************************************
������dist(double x, double y, double x2, double y2)
���ã���ȡ����
������double x ��xyzֵ
	  double y ��xyzֵ
	  double x2 ����������к�
	  double y2 ����������к�
����ֵ����
��ʷ��**����**         **����**            **ǩ��**
	  2019��10��27��        ����              �����
/**************************************************************************/
double CDem::dist(double x, double y, double x2, double y2)
{
	x2= (x2 - 1)*width + xlo;
	y2= (y2 - 1)*width + ylo;
	double distance = sqrt((x - x2)*(x - x2) + (y - y2)*(y - y2));
	return distance;
}

/***************************************************************************
������dist(double x, double y, double x2, double y2)
���ã���ȡ�����ƽ��
������double x ��xyzֵ
	  double y ��xyzֵ
	  double x2 ��xyzֵ
	  double y2 ��xyzֵ
����ֵ����
��ʷ��**����**         **����**            **ǩ��**
	  2019��10��27��        ����              �����
/**************************************************************************/
double CDem::truedist2(double x, double y, double x2, double y2)
{
	double distance = (x - x2)*(x - x2) + (y - y2)*(y - y2);
	return distance;
}


/***************************************************************************
������readDem()
���ã���ȡDem���� ����p��
��������
����ֵ��bool ��1 ��0
��ʷ��**����**         **����**            **ǩ��**
	  2019��10��27��        ����              �����
/**************************************************************************/
bool CDem::readDem()//��ȡdem����
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
	allpoints = _ttoi(strLine);
	
	vector<Point3d> int_points_xyz;
	vector<Point3i> int_points_rgb;
	for (int i = 0; i < allpoints; i++)
	{
		bEOF = sf.ReadString(strLine);
		if (bEOF == 0) { AfxMessageBox(_T("���ݲ��淶")); return 0; }
		int n = Div(strLine, ' ', array);
		if (n < 3) { AfxMessageBox(_T("����ȱʧ")); return 0; }
		C_points temp;
		temp.addxyz(int_points_xyz, _tstof(array[0]), _tstof(array[1]), _tstof(array[2]));
		temp.addrgb(int_points_rgb, _ttoi(array[3]), _ttoi(array[4]), _ttoi(array[5]));
		xlo = (xlo < _tstof(array[0])) ? xlo : _tstof(array[0]);
		xhi = (xhi > _tstof(array[0])) ? xhi : _tstof(array[0]);
		ylo = (ylo < _tstof(array[1])) ? ylo : _tstof(array[1]);
		yhi = (yhi > _tstof(array[1])) ? yhi : _tstof(array[1]);
		zlo = (zlo < _tstof(array[2])) ? zlo : _tstof(array[2]);
		zhi = (zhi > _tstof(array[2])) ? zhi : _tstof(array[2]);
	}
	//�����к��еĳ�ʼ��
	if (allpoints > 100000) { width = 1; }
	const int r = (xhi - xlo ) / width+1;//���� ��x����
	const int c = (yhi - ylo ) / width+1;//����
	nx = r;
	ny = c;
	p = new C_points[r*c];//�����һά���� 

	for (int i = 0; i < allpoints; i++)
	{
		int tempr, tempc,  idd = 0;
		convertxy2id(int_points_xyz.at(i).x, int_points_xyz.at(i).y, tempr, tempc, idd);
		p[idd].add_int(tempr, tempc, int_points_xyz.at(i).x, int_points_xyz.at(i).y, int_points_xyz.at(i).z, int_points_rgb.at(i).x, int_points_rgb.at(i).y, int_points_rgb.at(i).z);
	}
	for (int i = 0; i < r*c; i++)
	{
		int temp_r, temp_c;
		convertid2rc(i, temp_r, temp_c);
		p[i].row = temp_r;
		p[i].col = temp_c;
	}
	return 1;
}


/***************************************************************************
������findpoints(int x, int y, int size, C_points *d)
���ã�Ѱ�ҵ�λ������d�����Ա��mat����
������int x �����к�
	  int y �����к�
	  int size ���ڴ�С
	   C_points *d ������
����ֵ����
��ʷ��**����**         **����**            **ǩ��**
	  2019��10��27��        ����              �����
/**************************************************************************/
void  CDem::findpoints(int x, int y, int size, C_points *d)
{

	int halfsize = size / 2;
	for (int i = -halfsize; i < size; i++)
	{
		for (int j =-halfsize; j < size; j++)
		{
			//���ڳ���������
			if (convertcr2id(x + i, y + j) > 0 && convertcr2id(x + i, y + j) < nx*ny&&(x+i)>0&& (x + i) <=nx&& (y + i) > 0 && (y + i) <= ny)
			{
				//�жϸõ��Ƿ���Ԫ��
				if (d[convertcr2id(x + i, y + j)].sizee != 0)
				{
					for (int ii = 0; ii < d[convertcr2id(x + i, y + j)].sizee; ii++)
					{
						//����Ӧ���󴰿�
						double temp = dist(d[convertcr2id(x + i, y + j)].xyz.at(ii).x, d[convertcr2id(x + i, y + j)].xyz.at(ii).y,x,y);
						if (temp < size*5)
						{
							d[convertcr2id(x, y)].X_six.at<double>(d[convertcr2id(x, y)].sizeee, 0) = d[convertcr2id(x + i, y + j)].xyz.at(ii).x;
							d[convertcr2id(x, y)].X_six.at<double>(d[convertcr2id(x, y)].sizeee, 1) = d[convertcr2id(x + i, y + j)].xyz.at(ii).y;
							d[convertcr2id(x, y)].X_six.at<double>(d[convertcr2id(x, y)].sizeee, 2) = d[convertcr2id(x + i, y + j)].xyz.at(ii).z;
							d[convertcr2id(x, y)].X_six.at<double>(d[convertcr2id(x, y)].sizeee, 3) = 1;
							d[convertcr2id(x, y)].rgb_r = d[convertcr2id(x + i, y + j)].rgb.at(ii).x;
							d[convertcr2id(x, y)].rgb_g = d[convertcr2id(x + i, y + j)].rgb.at(ii).y;
							d[convertcr2id(x, y)].rgb_b = d[convertcr2id(x + i, y + j)].rgb.at(ii).z;
							d[convertcr2id(x, y)].sizeee++;
						}
						if (d[convertcr2id(x, y)].sizeee == 6) { return; }
					}
				}
			}
		}
	}
}


/***************************************************************************
������workout(int rr, int cc, Mat X_six)
���ã���С�����㷨
������int rr �к�
	  int cc �к�
	  Mat X_six ����
����ֵ����
��ʷ��**����**         **����**            **ǩ��**
	  2019��10��27��        ����              �����
/**************************************************************************/
double CDem::workout(int rr, int cc, Mat X_six)
{
	Mat X_six_clone;//��������
	X_six_clone = X_six.clone();	
	if (p[convertcr2id(rr, cc)].sizeee ==6)
	{
		//�ֲ����Ļ�
		double x_center = 0;
		double y_center = 0;
		for (int i = 0; i < X_six_clone.rows; i++)
		{
			x_center += X_six_clone.at<double>(i, 0);
			y_center += X_six_clone.at<double>(i, 1);
		}
		x_center = x_center / X_six_clone.rows;
		y_center = y_center / X_six_clone.rows;
		for (int i = 0; i < X_six_clone.rows; i++)
		{
			X_six_clone.at<double>(i, 0) = X_six_clone.at<double>(i, 0) - x_center;
			X_six_clone.at<double>(i, 1) = X_six_clone.at<double>(i, 1) - y_center;
		}
		Mat M=Mat::zeros(X_six_clone.rows,6, X_six_clone.type());
		Mat Z=Mat::zeros(X_six_clone.rows,1, X_six_clone.type());
		Mat P=Mat::zeros(X_six_clone.rows,6, X_six_clone.type());
		for (int i = 0; i < M.rows; i++)
		{
			M.at<double>(i, 0) = X_six_clone.at<double>(i, 0)*X_six_clone.at<double>(i, 0);
			M.at<double>(i, 1) = X_six_clone.at<double>(i, 0)*X_six_clone.at<double>(i, 1);
			M.at<double>(i, 2) = X_six_clone.at<double>(i, 1)*X_six_clone.at<double>(i, 1);
			M.at<double>(i, 3) = X_six_clone.at<double>(i, 0);
			M.at<double>(i, 4) = X_six_clone.at<double>(i, 1);
			M.at<double>(i, 5) = 1;
			Z.at<double>(i, 0) = X_six_clone.at<double>(i, 2);
			P.at<double>(i, i) = 1/truedist2(X_six_clone.at<double>(i, 0), X_six_clone.at<double>(i, 1), x_center, y_center);
		}
		Mat X = (M.t()*M).inv()*M.t()*Z;//��С���˽���
		double f = X.at<double>(5, 0);
		//�������Դ���Ľ��м�Ȩ�㷨
		if (f < zlo || f > zhi)
		{
			double sum = 0;
			double f = 0;
			for (int j = 0; j < p[convertcr2id(rr, cc)].sizeee; j++)
			{
				sum += X_six.at<double>(j, 3);
			}
			for (int j = 0; j < p[convertcr2id(rr, cc)].sizeee; j++)
			{
				f += X_six.at<double>(j, 3)*X_six.at<double>(j, 2);
			}
			return f / sum;
		}
		//�˲�
		return f;
	}
}

/***************************************************************************
������search()
���ã���������
������
����ֵ����
��ʷ��**����**         **����**            **ǩ��**
	  2019��10��27��        ����              �����
/**************************************************************************/
void CDem::search()
{
	for (int i = 0; i < nx*ny; i++)
	{
		int rr = 0;
		int cc = 0;
		convertid2rc(i, rr, cc);//��id���к���
		int ddsize = 4;//��ʵ����4*4
		while (1)
		{
			findpoints(rr, cc,ddsize, p);
			ddsize += 4;//�Ҳ���6���㣬������������4
			if (p[i].sizeee == 6) { break; }//�ҵ�����
		}
		p[i].zz = workout(rr, cc, p[i].X_six);//����
	}
}

/***************************************************************************
������out()
���ã����Dem.grd.txt
������
����ֵ����
��ʷ��**����**         **����**            **ǩ��**
	  2019��10��27��        ����              �����
/**************************************************************************/
void CDem::out()
{
	//�����txt��
	CStdioFile SF;
	CString strLine;
	CString strOut;
	setlocale(LC_ALL, "");
	if (!SF.Open(_T("Dem.grd"), CFile::modeCreate | CFile::modeWrite)) return;
	strLine.Format(_T("%s\n%d %d\n%f %f\n%f %f\n%f %f\n"),
		"DSAA",
		nx, ny,
		xlo, xhi,
		ylo, yhi,
		zlo, zhi
	);
	strOut += strLine;

	for (int j = 1; j <= ny; j++)
	{
		for (int i = 1; i <= nx; i++)
		{
			strLine.Format(_T("%.4f "), p[convertcr2id(i, j)].zz);
			strOut += strLine;
		}
	}
	SF.WriteString(strOut);
	SF.Close();
	AfxMessageBox(_T("�ɹ�!����������Dem.grd ��DemDataforCloudCompare_2color.txt��DemPecessForDebug.txt���У���MFC����·����"));
}

/***************************************************************************
������out2()
���ã����DemDataforCloudCompare_2color.txt,����DemDataforCloudCompare_2color
��������ɫ��һ�ֽ��䣬һ����ʵ
������
����ֵ����
��ʷ��**����**         **����**            **ǩ��**
	  2019��10��27��        ����              �����
/**************************************************************************/
void CDem::out2()
{
	CStdioFile SF;
	CString strLine;
	CString strOut;
	setlocale(LC_ALL, "");
	if (!SF.Open(_T("DemDataforCloudCompare_2color.txt"), CFile::modeCreate | CFile::modeWrite)) return;
	Mat colormap;
	getcolor1(colormap);
	for (int i = 0; i < (nx*ny); i++)
	{
		int cc = 0; int rr = 0;
		convertid2rc(i, rr, cc);
		int i2 = convertcr2id(rr, cc);
		double x_center = (rr - 1)*width + xlo;
		double y_center = (cc - 1)*width + ylo;
		double a;
		double b;
		double c;
		returncolor(a, b, c, p[i].zz,zlo,zhi,colormap);
		strOut += strLine;
		strLine.Format(_T("%.8f %.8f %.8f %f %f %f %d %d %d\n"),
			x_center, y_center, p[i].zz,a,b,c, p[i].rgb_r, p[i].rgb_g, p[i].rgb_b
		);
		strOut += strLine;
		
	}
	SF.WriteString(strOut);
	SF.Close();
}


/***************************************************************************
������out3()
���ã����DemPecessForDebug.txt
������
����ֵ����
��ʷ��**����**         **����**            **ǩ��**
	  2019��10��27��        ����              �����
/**************************************************************************/
void CDem::out3()
{
	CStdioFile SF;
	CString strLine;
	CString strOut;
	setlocale(LC_ALL, "");
	if (!SF.Open(_T("DemPecessForDebug.txt"), CFile::modeCreate | CFile::modeWrite)) return;

	for (int i = 0; i < (nx*ny); i++)
	{

		int cc = 0; int rr = 0;
		convertid2rc(i, rr, cc);
		int i2 = convertcr2id(rr, cc);
		double x_center = (rr - 1)*width + xlo;
		double y_center = (cc - 1)*width + ylo;

		strOut += strLine;
		strLine.Format(_T("%.8f %.8f %.8f \n"),
			x_center, y_center, p[i].zz
		);
		strOut += strLine;
		for (int j = 0; j < p[i].sizeee; j++)
		{
			int rr = 0;
			int cc = 0;
			int iddd = 0;
			convertxy2id(p[i].X_six.at<double>(j, 0), p[i].X_six.at<double>(j, 1), rr, cc, iddd);
			double sd = p[i].X_six.at<double>(j, 2);
			strLine.Format(_T("%.8f %.8f %.8f %d %d %d \n"),
				p[i].X_six.at<double>(j, 0), p[i].X_six.at<double>(j, 1), p[i].X_six.at<double>(j, 2), rr, cc, iddd
			);
			strOut += strLine;
		}
		strLine.Format(_T("\n"));
	}
	strOut += strLine;

	SF.WriteString(strOut);
	SF.Close();
}

/***************************************************************************
������BeatifulDem()
���ã�����
������
����ֵ����
��ʷ��**����**         **����**            **ǩ��**
	  2019��10��27��        ����              �����
/**************************************************************************/
void CDem::BeatifulDem()
{
	for (int i = 1; i <= nx; i++)
	{
		for (int j = 1; j <= ny; j++)
		{
			int tag = 5;
			if (convertcr2id(i + tag, j) > 0 && convertcr2id(i - tag, j) > 0 && convertcr2id(i, j + tag) > 0 && convertcr2id(i, j - tag) > 0)
			{
				if (convertcr2id(i + tag, j) < nx*ny && convertcr2id(i - tag, j) < nx*ny  && convertcr2id(i, j + tag) < nx*ny  && convertcr2id(i, j - tag) < nx*ny)
				{
					double temp1 = fabs(p[convertcr2id(i, j)].zz - p[convertcr2id(i + tag, j)].zz);
					double temp2 = fabs(p[convertcr2id(i, j)].zz - p[convertcr2id(i - tag, j)].zz);
					double temp3 = fabs(p[convertcr2id(i, j)].zz - p[convertcr2id(i, j + tag)].zz);
					double temp4 = fabs(p[convertcr2id(i, j)].zz - p[convertcr2id(i, j - tag)].zz);
					double Dist = 5;
					double ff =  p[convertcr2id(i + tag, j)].zz+ p[convertcr2id(i - tag, j)].zz+ p[convertcr2id(i, j + tag)].zz+ p[convertcr2id(i, j - tag)].zz;
					if (temp1 > Dist&&temp2 > Dist&&temp3 > Dist&&temp4 > Dist)
					{
						p[convertcr2id(i, j)].zz = ff/4;
					}
				}
			}
		}
	}
	for (int i = 1; i <= nx; i++)
	{
		for (int j = 1; j <= ny; j++)
		{
			int tag = 5;
			if (i <= tag || i > nx - tag || j <= tag || j > ny - tag)
			{
				int t = (i - tag) > 0 ? (i - tag) : (i + tag);
				int t2 = (j - tag) > 0 ? (j - tag) : (j + tag);
				p[convertcr2id(i, j)].zz = p[convertcr2id(t, t2)].zz;

			}
		}
	}
}
/***************************************************************************
������main()
���ã�������
������
����ֵ����
��ʷ��**����**         **����**            **ǩ��**
	  2019��10��27��        ����              �����
/**************************************************************************/
void CDem::main()
{
	bool tagger=readDem();//��ȡ����
	if (tagger == 0) { return; }
	search();//����
	BeatifulDem();//����
	out2();//���
	out3();//���
	out();//���
}