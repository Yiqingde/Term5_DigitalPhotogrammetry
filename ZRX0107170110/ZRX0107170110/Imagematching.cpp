/***************************************************************************
类：Imagematching
作用：核线影像相关系数MFC界面按钮操作相关类
Welcome to my Github and my CSDN blog , more information will be available about the project!
Github:https://github.com/Yiqingde
CSDN Blog:https://me.csdn.net/weixin_42348202
历史：**日期**         **理由**            **签名**
	  2019年10月11日        创建              张睿祥
/**************************************************************************/
// Imagematching.cpp: 实现文件
//

#include "stdafx.h"
#include "ZRX0107170110.h"
#include "Imagematching.h"
#include "afxdialogex.h"
#include "CBasic.h"
#include "Resource.h"
// Imagematching 对话框

IMPLEMENT_DYNAMIC(Imagematching, CDialogEx)

Imagematching::Imagematching(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Correlationmatching, pParent)
	, Moravecsize1(5)
	, Moravecsize2(9)
	, Moraveclowstdoor(240)
	, dist_width(500)
	, lowst_door(0.9)
	, halflengthsize(30)
{
	m_brushBg.CreateSolidBrush(RGB(0, 0, 255));
}

Imagematching::~Imagematching()
{
	
}

void Imagematching::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Moravecsize1, Moravecsize1);
	DDX_Text(pDX, IDC_Moravecsize2, Moravecsize2);
	DDX_Text(pDX, IDC_Moraveclowestdoor, Moraveclowstdoor);
	DDX_Text(pDX, IDC_dist_width, dist_width);
	DDX_Text(pDX, IDC_lowst_door, lowst_door);
	DDX_Text(pDX, IDC_halflengthsize, halflengthsize);
}


BEGIN_MESSAGE_MAP(Imagematching, CDialogEx)
	ON_BN_CLICKED(ID_readleft, &Imagematching::OnBnClickedreadleft)
	ON_BN_CLICKED(ID_readright, &Imagematching::OnBnClickedreadright)
	ON_BN_CLICKED(ID_view, &Imagematching::OnBnClickedview)
	ON_BN_CLICKED(ID_view2, &Imagematching::OnBnClickedview2)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON1, &Imagematching::OnBnClickedButton1)
END_MESSAGE_MAP()


// Imagematching 消息处理程序

CBasic temp;
//读取左影像按钮
void Imagematching::OnBnClickedreadleft()
{
	// TODO: 在此添加控件通知处理程序代码
	temp.Button_Imagematching_readleft();
}

//读取右影像按钮
void Imagematching::OnBnClickedreadright()
{
	// TODO: 在此添加控件通知处理程序代码
	temp.Button_Imagematching_readright();
}

//读取txt
void Imagematching::OnBnClickedview()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	temp.Button_Imagematching_view(lowst_door, dist_width, halflengthsize);
	UpdateData(false);
}
//制作txt
void Imagematching::OnBnClickedview2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	temp.Button_Imagematching_makingNumber(Moravecsize1, Moravecsize2, Moraveclowstdoor);
	UpdateData(false);
}

//help
void Imagematching::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString help;
	help.Format(_T("%s\r\n%s\r\n%s\r\n\r\n%s"), _T("Moravec算子执行速度略慢请耐心等待"),
		_T("如果您有txt标准格式数据的话，您可直接跳过该步骤,进行直接读取txt"), _T("工作路径下有: 标准数据1.txt  标准数据2.txt 标准数据3.txt  可供直接读取"),_T("执行步骤：打开左影像-->打开右影像-->设置Moravec参数-->左侧Moravec算子输出到txt中-->设置核线影像参数-->读取输出的txt"));
	AfxMessageBox(help);
}

HBRUSH Imagematching::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (pWnd == this)
	{
		return m_brushBg;
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


BOOL Imagematching::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	CDialogEx::SetBackgroundColor(RGB(240,255,255));
	//CDialogEx::SetBackgroundColor(RGB(233, 100, 30));
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


