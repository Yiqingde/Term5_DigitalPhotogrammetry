#pragma once
// Imagematching 对话框

class Imagematching : public CDialogEx
{
	DECLARE_DYNAMIC(Imagematching)
	CBrush m_brushBg;
public:
	Imagematching(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Imagematching();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Correlationmatching };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedreadleft();
	afx_msg void OnBnClickedreadright();
	afx_msg void OnBnClickedview();
	afx_msg void OnBnClickedview2();
	int Moravecsize1;
	int Moravecsize2;
	int Moraveclowstdoor;
	int dist_width;
	float lowst_door;
	int halflengthsize; 
	
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedButton1();
};
