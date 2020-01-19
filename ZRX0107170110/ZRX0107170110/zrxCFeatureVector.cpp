#include "stdafx.h"
#include "zrxCFeatureVector.h"


zrxCFeatureVector::zrxCFeatureVector()
{
}


zrxCFeatureVector::~zrxCFeatureVector()
{
}

/***************************************************************************
函数：Reporttxt()
作用：输出结果至txt，用到该类中变量strOut
参数：无
返回值：无
历史：**日期**         **理由**            **签名**
	  2019年9月26日        创建              张睿祥
/**************************************************************************/
void zrxCFeatureVector::Reporttxt(CString runtime)

{
	if (strOut == _T("")) { AfxMessageBox(_T("请先输入数据!")); }
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
					strPath += _T(".txt");//默认储存为txt模式
				}
			}
		}
		TRY
		{
			CString cs;
			CStdioFile file(strPath, CFile::shareExclusive | CFile::modeWrite | CFile::modeCreate);
			setlocale(LC_CTYPE, ("chs")); //设置中文输出
			file.WriteString(runtime);
			file.WriteString(strOut);
			file.Close();
			CString temp;
			temp.Format(_T("%s%s"),_T("点位信息已导出至"),strPath);
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
函数：find()
作用：寻找数组的最大值 最小值
参数：float a[]  数组
      int m 数组前m个元素
	  float &max 最大值
	  float &min 最小值
返回值：无
历史：**日期**         **理由**            **签名**
	  2019年9月26日        创建              张睿祥
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
函数：Moravec_core()
作用：滑动窗口 求"*"状最小值
参数：Mat m_srcimg 原始图像
	  int Moravecsize 窗口大小
	  int i_x 像素(x,y)中的x
	  int j_y 像素(x,y)中的y
返回值：最小值
历史：**日期**         **理由**            **签名**
	  2019年9月26日        创建              张睿祥
/**************************************************************************/
float zrxCFeatureVector::Moravec_core(Mat m_srcimg, int Moravecsize, int i_x, int j_y)
{
	int halfsize = (Moravecsize) / 2;//定义小半个窗口大小
	float temp4[4];//创立四个方向的数组来进行"*"型的平方和
	//数组初始化
	for (int i = 0; i < 4; i++)
	{
		temp4[i] = 0;
	}
	//累加*求平方和
	for (int i = 0; i < Moravecsize; i++)
	{
		float l = m_srcimg.at<uchar>(i_x - halfsize + i, j_y);//    | x方向 即北南
		temp4[0] += pow(m_srcimg.at<uchar>(i_x - halfsize + i, j_y) - m_srcimg.at<uchar>(i_x - halfsize + i + 1, j_y), 2);//    | x方向 即北南
		temp4[1] += pow(m_srcimg.at<uchar>(i_x, j_y - halfsize + i) - m_srcimg.at<uchar>(i_x, j_y - halfsize + i + 1), 2);//    - y方向
		temp4[2] += pow(m_srcimg.at<uchar>(i_x - halfsize + i, j_y - halfsize + i) - m_srcimg.at<uchar>(i_x - halfsize + i + 1, j_y - halfsize + i + 1), 2);//   \ 方向
		temp4[3] += pow(m_srcimg.at<uchar>(i_x - halfsize + i, j_y + halfsize - i) - m_srcimg.at<uchar>(i_x - halfsize + i + 1, j_y + halfsize - i - 1), 2);//   / 方向
	}
	float min, max;//定义两个极大值 极小值
	find(temp4, 4, max, min);//给极小值赋值
	return min;//返回极小值
}


/***************************************************************************
函数：Moravec_core2()
作用：局部抑制 并开始画图
参数：Mat m_srcimgrgb 原始彩色图像
	  int Moravecsize2 局部抑制窗口大小
	  Mat &Morvec 经之前Moravec窗口操作后并经过阈值后的图像
	  vector<Point3i> &f 用来存储展点
返回值：无
历史：**日期**         **理由**            **签名**
	  2019年9月26日        创建              张睿祥
/**************************************************************************/
void zrxCFeatureVector::Moravec_core2( Mat &m_srcimgrgb,int Moravecsize2, Mat &Morvec, vector<Point3f> &f)
{
	int halfMoravecsize2 = Moravecsize2 / 2;//定义小半个窗口大小  
	//四层循环作用：针对窗口除了边框的每一个点来确保以它为中心，只要存在有一个值不小于它的值 即给它做一个标记0 用来排除小于极大值的值
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
	//开始进行存储至 vector<Point3i> &f 中
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
	
	//开始删除同意一窗口值一样的重复点，尽管出现概率较小，但较大的图像往往某些窗口中会存在好几个数值相等的极大值
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
	//*********************冒泡排序
	for (int i = 0; i < f.size()-1; i++) {
		int tem = 0;
		// 内层for循环控制相邻的两个元素进行比较
		for (int j = i + 1; j < f.size(); j++) {
			if (f.at(i).z < f.at(j).z) {
				tem = f.at(j).z;
				f.at(j).z = f.at(i).z;
				f.at(i).z = tem;
			}
		}
	}
	*/
	/*********************以下注释的D部分 本来是为了修改显示的值 如果大于50 只显示前50个最大值,须于冒泡排序结合使用，但是效果不太好
	*/
	CString temp;
	temp.Format(_T("%s%d\n%s\n"),_T("所有的点个数:"),f.size(),_T("X坐标，Y坐标，Morevec后的值"));
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
函数：Moravec()
作用：Moeavec主函数 调用以上函数
参数：Mat m_srcimg 原始图像
      Mat m_srcimgrgb 原始彩色图像
	  int Moravecsize  * 型窗口大小
	  int Moravecsize2 局部抑制窗口大小
	  Mat &Morvec 经之前Moravec窗口操作后并经过阈值后的图像
返回值：无
历史：**日期**         **理由**            **签名**
	  2019年9月26日        创建              张睿祥
/**************************************************************************/
void zrxCFeatureVector::Moravec(Mat m_srcimg, Mat &m_srcimgrgb, int Moravecsize, int Moravecsize2, int Moraveclowstdoor,Mat &Morvec, vector<Point3f> &f)
{
	//Moravecsize = (Moravecsize % 2 == 1) ? Moravecsize : Moravecsize + 1;
	//****************************存储点的信息 查bug用
	GaussianBlur(m_srcimg, m_srcimg, Size(Moravecsize, Moravecsize), 0, 0);//使用opencv自带高斯滤波预处理
	Morvec.create(m_srcimg.rows, m_srcimg.cols, CV_32FC1);//开辟空间
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
	//****************************局部抑制并显示
	Moravec_core2(m_srcimgrgb, Moravecsize2, Morvec, f);
	Morvec.convertTo(Morvec, CV_8UC1);
	//Morvec2.convertTo(Morvec2, CV_8UC1);
}