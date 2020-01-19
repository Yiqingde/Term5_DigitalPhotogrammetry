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
函数：getcolor1(Mat &f)
作用：颜色代码
参数：Mat &f 颜色矩阵 浮点数0-1
返回值：无
历史：**日期**         **理由**            **签名**
	  2019年10月27日        创建              张睿祥
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
函数：returncolor(double &a, double &b, double &c, double zz, double min, double max,Mat color)
作用：由颜色矩阵获得rgb颜色，根据最大值最小值
参数：double &a  返回rgb中a
      double &b  返回rgb中b
	  double &c  返回rgb中c
	  double zz  依据该值上色
	  double min 最小值
	  double max 最大值
	  Mat color 颜色矩阵
返回值：无
历史：**日期**         **理由**            **签名**
	  2019年10月27日        创建              张睿祥
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
//字符分割函数
//***********************************
int CDem::Div(const CString strLine, char split, CStringArray &strArray)
{
	strArray.RemoveAll();//自带清空属性
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
函数：convertcr2id(int tempr, int tempc)
作用：输入行号列号返回 id
参数：int tempr
      int tempc
返回值：int 一维数组得id号
历史：**日期**         **理由**            **签名**
	  2019年10月27日        创建              张睿祥
/**************************************************************************/
int CDem::convertcr2id(int tempr, int tempc)
{
	int id = (tempr - 1)*ny + tempc - 1;
	return id;
}

/***************************************************************************
函数：convertid2rc(int id, int&rr, int &cc)
作用：输入id 解求行列号
参数：int id  id号
	  int &rr  行列号
	  int &cc  行列号
返回值：无
历史：**日期**         **理由**            **签名**
	  2019年10月27日        创建              张睿祥
/**************************************************************************/
void CDem::convertid2rc(int id, int &rr, int &cc)
{
	double temp = double(id + 1) - 0.05;
	rr = (int(temp) / ny) + 1;
	cc = id + 1 - (rr - 1) *ny;
}

/***************************************************************************
函数：convertxy2id(double x, double y, int &tempr, int &tempc, int &id)
作用：输入xy   返回 解求行列号及id 塞入数组时使用
参数：double x x值
	  double y y值
	  int &tempr  行号
	  int &tempc  列号
	  int &id  id
返回值：无
历史：**日期**         **理由**            **签名**
	  2019年10月27日        创建              张睿祥
/**************************************************************************/
void CDem::convertxy2id(double x, double y, int &tempr, int &tempc, int &id)
{
	tempr = int((x - xlo-0.001) / width) + 1;
	tempc = int((y - ylo-0.001) / width) + 1;
	id=convertcr2id(tempr, tempc);
}


/***************************************************************************
函数：dist(double x, double y, double x2, double y2)
作用：求取距离
参数：double x 真xyz值
	  double y 真xyz值
	  double x2 格网点的行列号
	  double y2 格网点的行列号
返回值：无
历史：**日期**         **理由**            **签名**
	  2019年10月27日        创建              张睿祥
/**************************************************************************/
double CDem::dist(double x, double y, double x2, double y2)
{
	x2= (x2 - 1)*width + xlo;
	y2= (y2 - 1)*width + ylo;
	double distance = sqrt((x - x2)*(x - x2) + (y - y2)*(y - y2));
	return distance;
}

/***************************************************************************
函数：dist(double x, double y, double x2, double y2)
作用：求取距离的平方
参数：double x 真xyz值
	  double y 真xyz值
	  double x2 真xyz值
	  double y2 真xyz值
返回值：无
历史：**日期**         **理由**            **签名**
	  2019年10月27日        创建              张睿祥
/**************************************************************************/
double CDem::truedist2(double x, double y, double x2, double y2)
{
	double distance = (x - x2)*(x - x2) + (y - y2)*(y - y2);
	return distance;
}


/***************************************************************************
函数：readDem()
作用：读取Dem数据 存入p中
参数：无
返回值：bool 读1 非0
历史：**日期**         **理由**            **签名**
	  2019年10月27日        创建              张睿祥
/**************************************************************************/
bool CDem::readDem()//读取dem数据
{
	CFileDialog dlgFile(TRUE, _T("txt"), NULL,
		OFN_ALLOWMULTISELECT | OFN_EXPLORER,
		//_T("(文本文件)|*.txt"));
		_T(""));
	if (dlgFile.DoModal() == IDCANCEL) return 0;
	CString strName = dlgFile.GetPathName();//获取打开文件文件名（路径）
	setlocale(LC_ALL, "");
	CStdioFile sf;
	if (!sf.Open(strName, CFile::modeRead)) return 0;//打开strName文件路径中的内容
	CString strLine;
	CString strContent;//接受内容字符串
	CStringArray array;//供下文分割使用
	strContent.Empty();//strContent中内容清空

	//开始读数据 
	BOOL bEOF = sf.ReadString(strLine);//第一行
	if (bEOF == 0) { AfxMessageBox(_T("空数据")); return 0; }
	allpoints = _ttoi(strLine);
	
	vector<Point3d> int_points_xyz;
	vector<Point3i> int_points_rgb;
	for (int i = 0; i < allpoints; i++)
	{
		bEOF = sf.ReadString(strLine);
		if (bEOF == 0) { AfxMessageBox(_T("数据不规范")); return 0; }
		int n = Div(strLine, ' ', array);
		if (n < 3) { AfxMessageBox(_T("数据缺失")); return 0; }
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
	//进行行和列的初始化
	if (allpoints > 100000) { width = 1; }
	const int r = (xhi - xlo ) / width+1;//行数 是x决定
	const int c = (yhi - ylo ) / width+1;//列数
	nx = r;
	ny = c;
	p = new C_points[r*c];//定义的一维数组 

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
函数：findpoints(int x, int y, int size, C_points *d)
作用：寻找点位，存入d对象成员的mat矩阵
参数：int x 输入行号
	  int y 输入列号
	  int size 窗口大小
	   C_points *d 即对象
返回值：无
历史：**日期**         **理由**            **签名**
	  2019年10月27日        创建              张睿祥
/**************************************************************************/
void  CDem::findpoints(int x, int y, int size, C_points *d)
{

	int halfsize = size / 2;
	for (int i = -halfsize; i < size; i++)
	{
		for (int j =-halfsize; j < size; j++)
		{
			//窗口出界则跳过
			if (convertcr2id(x + i, y + j) > 0 && convertcr2id(x + i, y + j) < nx*ny&&(x+i)>0&& (x + i) <=nx&& (y + i) > 0 && (y + i) <= ny)
			{
				//判断该点是否有元素
				if (d[convertcr2id(x + i, y + j)].sizee != 0)
				{
					for (int ii = 0; ii < d[convertcr2id(x + i, y + j)].sizee; ii++)
					{
						//自适应增大窗口
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
函数：workout(int rr, int cc, Mat X_six)
作用：最小二乘算法
参数：int rr 行号
	  int cc 列号
	  Mat X_six 矩阵
返回值：无
历史：**日期**         **理由**            **签名**
	  2019年10月27日        创建              张睿祥
/**************************************************************************/
double CDem::workout(int rr, int cc, Mat X_six)
{
	Mat X_six_clone;//将矩阵复制
	X_six_clone = X_six.clone();	
	if (p[convertcr2id(rr, cc)].sizeee ==6)
	{
		//局部中心化
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
		Mat X = (M.t()*M).inv()*M.t()*Z;//最小二乘解求
		double f = X.at<double>(5, 0);
		//对于明显错误的进行加权算法
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
		//滤波
		return f;
	}
}

/***************************************************************************
函数：search()
作用：搜索解求
参数：
返回值：无
历史：**日期**         **理由**            **签名**
	  2019年10月27日        创建              张睿祥
/**************************************************************************/
void CDem::search()
{
	for (int i = 0; i < nx*ny; i++)
	{
		int rr = 0;
		int cc = 0;
		convertid2rc(i, rr, cc);//由id得行和列
		int ddsize = 4;//其实窗口4*4
		while (1)
		{
			findpoints(rr, cc,ddsize, p);
			ddsize += 4;//找不到6个点，窗口依次增加4
			if (p[i].sizeee == 6) { break; }//找到即撤
		}
		p[i].zz = workout(rr, cc, p[i].X_six);//解求
	}
}

/***************************************************************************
函数：out()
作用：输出Dem.grd.txt
参数：
返回值：无
历史：**日期**         **理由**            **签名**
	  2019年10月27日        创建              张睿祥
/**************************************************************************/
void CDem::out()
{
	//输出至txt中
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
	AfxMessageBox(_T("成功!已输入至“Dem.grd 、DemDataforCloudCompare_2color.txt、DemPecessForDebug.txt”中（在MFC工作路径）"));
}

/***************************************************************************
函数：out2()
作用：输出DemDataforCloudCompare_2color.txt,可用DemDataforCloudCompare_2color
打开两种颜色，一种渐变，一种真实
参数：
返回值：无
历史：**日期**         **理由**            **签名**
	  2019年10月27日        创建              张睿祥
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
函数：out3()
作用：输出DemPecessForDebug.txt
参数：
返回值：无
历史：**日期**         **理由**            **签名**
	  2019年10月27日        创建              张睿祥
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
函数：BeatifulDem()
作用：除噪
参数：
返回值：无
历史：**日期**         **理由**            **签名**
	  2019年10月27日        创建              张睿祥
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
函数：main()
作用：主函数
参数：
返回值：无
历史：**日期**         **理由**            **签名**
	  2019年10月27日        创建              张睿祥
/**************************************************************************/
void CDem::main()
{
	bool tagger=readDem();//读取数据
	if (tagger == 0) { return; }
	search();//搜索
	BeatifulDem();//除噪
	out2();//输出
	out3();//输出
	out();//输出
}