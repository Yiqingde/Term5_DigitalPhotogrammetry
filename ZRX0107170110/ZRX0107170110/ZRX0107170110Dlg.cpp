/***************************************************************************
类：ZRX0107170110Dlg
作用：按钮实现文件
历史：**日期**         **理由**            **签名**
	  2019年9月20日        创建              张睿祥
/**************************************************************************/

// ZRX0107170110Dlg.cpp: 实现文件
//

#include "stdafx.h"
#include "ZRX0107170110.h"
#include "ZRX0107170110Dlg.h"
#include "afxdialogex.h"
#include "Imagematching.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CZRX0107170110Dlg 对话框



CZRX0107170110Dlg::CZRX0107170110Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ZRX0107170110_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CZRX0107170110Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CZRX0107170110Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CZRX0107170110Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_read2, &CZRX0107170110Dlg::OnBnClickedread2)
	ON_BN_CLICKED(IDC_read3, &CZRX0107170110Dlg::OnBnClickedread3)
	ON_BN_CLICKED(IDC_read4, &CZRX0107170110Dlg::OnBnClickedread4)
	ON_BN_CLICKED(IDC_read5, &CZRX0107170110Dlg::OnBnClickedread5)
	ON_BN_CLICKED(IDC_read6, &CZRX0107170110Dlg::OnBnClickedread6)
	ON_BN_CLICKED(IDC_read7, &CZRX0107170110Dlg::OnBnClickedread7)
END_MESSAGE_MAP()


// CZRX0107170110Dlg 消息处理程序

BOOL CZRX0107170110Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CZRX0107170110Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CZRX0107170110Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CZRX0107170110Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CBasic t;//全局变量
/*************************************************
按钮：读取图像函数
*************************************************/
void CZRX0107170110Dlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
	t.OpenImg();
}


/*************************************************
按钮：进行二值化显示
*************************************************/
void CZRX0107170110Dlg::OnBnClickedread2()
{
	// TODO: 在此添加控件通知处理程序代码
	t.Button_binaryImg();
}


/*************************************************
按钮：进行自写gauss显示与opencv显示且比较时间
*************************************************/
void CZRX0107170110Dlg::OnBnClickedread3()
{
	// TODO: 在此添加控件通知处理程序代码
	t.Button_GaussImg();
}

/*************************************************
按钮：help
*************************************************/
void CZRX0107170110Dlg::OnBnClickedread4()
{
	// TODO: 在此添加控件通知处理程序代码
	t.Button_Help();
}

/*************************************************
按钮：Moravec按钮显示  
*************************************************/
void CZRX0107170110Dlg::OnBnClickedread5()
{
	// TODO: 在此添加控件通知处理程序代码
	t.Button_Moravec();
}

/*************************************************
按钮：相关系数法按钮窗口打开
*************************************************/
void CZRX0107170110Dlg::OnBnClickedread6()
{
	// TODO: 在此添加控件通知处理程序代码
	Imagematching a;
	a.DoModal();
}


void CZRX0107170110Dlg::OnBnClickedread7()
{
	// TODO: 在此添加控件通知处理程序代码
	CBasic tt;
	tt.Button_DEM();
}
