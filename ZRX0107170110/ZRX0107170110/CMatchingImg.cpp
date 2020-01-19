#include "stdafx.h"
#include "CMatchingImg.h"


CMatchingImg::CMatchingImg()
{
}


CMatchingImg::~CMatchingImg()
{
}
//***********************************
//字符分割函数
//***********************************
int CMatchingImg::Div(const CString strLine, char split, CStringArray &strArray)
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
函数：read(vector < Point3i> &f)
作用：读取txt文件，储存至vector中
参数：无
返回值：无
历史：**日期**         **理由**            **签名**
	  2019年10月11日        创建              张睿祥
/**************************************************************************/
bool CMatchingImg::read(vector < Point3f> &f)
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
	//读取控制点
	bEOF = sf.ReadString(strLine);//第二行 
	if (bEOF == 0) { AfxMessageBox(_T("数据不规范")); return 0; }
	bEOF = sf.ReadString(strLine);//第三行 
	if (bEOF == 0) { AfxMessageBox(_T("数据不规范")); return 0; }
	int n = Div(strLine, ':', array);
	if (n < 2) { AfxMessageBox(_T("数据缺失")); return 0; }
	int i = _ttoi(array[1]);
	bEOF = sf.ReadString(strLine);//第四行 
	if (bEOF == 0) { AfxMessageBox(_T("数据不规范")); return 0; }
	while (i>0)
	{
		bEOF = sf.ReadString(strLine);
		if (bEOF == 0) { AfxMessageBox(_T("数据不规范")); return 0; }
		int n = Div(strLine, ',', array);
		if (n < 3) { AfxMessageBox(_T("数据缺失")); return 0; }
		
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
函数：Get_coefficient(Mat Lmatchwindow, Mat match_RImg,int x,int y,float &cofficent)
作用：计算相关系数
参数:Mat Lmatchwindow已经计算过的左片窗口
     Mat match_RImg 右核线影像
	 int x 坐标值x
	 int y 坐标值y
	 float &cofficent用来返回计算过的单个值
返回值：无
历史：**日期**         **理由**            **签名**
	  2019年10月11日        创建              张睿祥
/**************************************************************************/
void CMatchingImg::Get_coefficient(Mat Lmatchwindow, Mat match_RImg,int x,int y,float &cofficent)
{
	//根据左搜索窗口确定右搜索窗口的大小
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
	//开始计算相关系数
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
函数：vectorsort(vector < Point3f> &Temp_sort)
作用：仅适用于对vector < Point3f> &Temp_sort的z元素冒泡排序，xyz作为一个整体进行改变，首元素值最大
参数:vector < Point3f> &Temp_sort 需要排序的vector
返回值：无
历史：**日期**         **理由**            **签名**
	  2019年10月11日        创建              张睿祥
/**************************************************************************/

void CMatchingImg::vectorsort(vector < Point3f> &Temp_sort)
{
	for (int i = 0; i < Temp_sort.size() - 1; i++) {
		float tem = 0;
		float temx = 0;
		float temy = 0;
		// 内层for循环控制相邻的两个元素进行比较
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
函数：lastview(Mat match_LImg, Mat match_RImg,vector<Point3i> f,vector<Point3f> r)
作用：最后用来显示图像并进行写入工作路径的txt中
参数:Mat match_LImg 左核线影像
	 Mat match_RImg 右核线影像
	 vector<Point3i> f 存储经过筛选过后的moravec元素
	 vector<Point3f> r 存储在右片所寻找到的相应元素，与vector<Point3i> f相对应
返回值：无
历史：**日期**         **理由**            **签名**
	  2019年10月11日        创建              张睿祥
/**************************************************************************/
void CMatchingImg::lastview(Mat match_LImg, Mat match_RImg,vector<Point3f> f,vector<Point3f> r)
{
	Mat bothview;//输出图像
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
	}//左右影像合二为一	

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


	//输出至txt中
	CStdioFile SF;
	CString strLine;
	CString strOut;
	setlocale(LC_ALL, "");
//if (!SF.Open(_T("相关系数法5元素.txt"), CFile::modeCreate | CFile::modeWrite)) return;
	if (!SF.Open(_T("相关系数法5元素.txt"), CFile::modeCreate | CFile::modeWrite)) return;
	strLine.Format(_T("%d\n"),r.size());
	strOut += strLine;
	for (int i = 0; i < r.size(); i++)
	{
		strLine.Format(_T("%.f %.f %.f %.f\n"),  f.at(i).y, f.at(i).x, r.at(i).y, r.at(i).x );
		strOut += strLine;
	}
	SF.WriteString(strOut);
	SF.Close();
	AfxMessageBox(_T("成功!已输入至“相关系数法5元素.txt”中（在MFC工作路径）"));
	imshow("左右片影像相关系数法点位展示", bothview);
	//waitKey();
	imwrite("左右片影像相关系数法点位展示.jpg", bothview);
}

/***************************************************************************
函数：MatchingImg(Mat &match_LImg, Mat &match_RImg , Mat match_RGBLImg, Mat match_RGBRImg, float lowst_door, int dist_width,int halflengthsize)
作用：相关系数法主函数，调用其上函数
参数:Mat match_LImg 左核线影像
	 Mat match_RImg 右核线影像
	 Mat match_RGBLImg 左片彩色影像
	 Mat match_RGBRImg 右片彩色影像
	 float lowst_door 相关系数法阈值
	 int dist_width 规定一个左片与右片的相对距离
	 int halflengthsize 规定以该像素为中心的x轴的搜索半径
返回值：无
历史：**日期**         **理由**            **签名**
	  2019年10月11日        创建              张睿祥
/**************************************************************************/
void CMatchingImg::MatchingImg(Mat &match_LImg, Mat &match_RImg , Mat match_RGBLImg, Mat match_RGBRImg, float lowst_door, int dist_width,int halflengthsize)
{
	if (match_LImg.empty()) { AfxMessageBox(_T("请检查是否读入左核线影像")); return; }
	if (match_RImg.empty()) { AfxMessageBox(_T("请检查是否读入右核线影像")); return; }
	int matchsize=9;//相关系数的正方形窗口的边长
	int half_matchsize = matchsize / 2;//边长的一半
	//调用之前函数，将点位信息存储值f中
	vector<Point3f> f;//用来读取左片moravec算子的数据
	vector<Point3f> r;//用来写右片匹配到的数据
	int r_i = 0;
	bool tag=read(f);//运行读取函数
	//创建左窗口的小窗口
	Mat Lmatchwindow;
	Lmatchwindow.create(matchsize, matchsize, CV_32FC1);
	//进行f数据的预处理 删除不符合规范的数据
	for (size_t i = 0; i < f.size(); i++)
	{
		//*************************进行两次擦除
		//***********擦除y值不在影像范围内的点f	我·2
		if (f.at(i).y < dist_width + halflengthsize + half_matchsize + 1)
		{
			f.erase(f.begin() + i);
			i--;
			continue;
		}
		//***********擦除x值不在影像范围内的点
		if (f.at(i).x <half_matchsize +5|| f.at(i).x>match_LImg.rows-half_matchsize-10)
		{
			f.erase(f.begin() + i);
			i--;
			continue;
		}
	}

	for (size_t i = 0; i < f.size(); i++)
	{
		//***************************对左窗口进行计算，计算完毕后值存入Lmatchwindow中
		float aveLImg = 0; 
		for (int m =0; m <matchsize; m++)
		{
			for (int n = 0; n < matchsize; n++)
			{
				aveLImg += match_LImg.at<uchar>(f.at(i).x - half_matchsize + m, f.at(i).y - half_matchsize + n);
				Lmatchwindow.at<float>(m, n) = match_LImg.at<uchar>(f.at(i).x - half_matchsize + m, f.at(i).y - half_matchsize + n);
			}
		}
		aveLImg = aveLImg / (matchsize* matchsize);//求取左窗口平均值
		//均除某个值
		for (int m = 0; m < matchsize; m++)
		{
			for (int n = 0; n < matchsize; n++)
			{
				Lmatchwindow.at<float>(m, n) = Lmatchwindow.at<float>(m, n) - aveLImg;
			}
		}
		//***************************对右窗口进行计算
		//首先预估右窗口的位置
		
		vector < Point3f> halflengthsize2;
		//去除跑到窗口外的点
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
		//*************************进行第二次擦除
		//***********擦除不符合相关系数不符合阈值的值
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