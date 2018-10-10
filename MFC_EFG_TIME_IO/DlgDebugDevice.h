#pragma once


// CDlgDebugDevice 对话框

class CDlgDebugDevice : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgDebugDevice)

public:
	CDlgDebugDevice(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgDebugDevice();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DEVICE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
private:
  CBrush m_brush;
public:
  afx_msg void OnBnClickedBtnMeasure();
  afx_msg void OnBnClickedXTip();
  virtual BOOL OnInitDialog();
  afx_msg void OnBnClickedXrayGate();
  afx_msg void OnTimer(UINT_PTR nIDEvent);
  afx_msg void OnBnClickedBtnRealtime();
  afx_msg void OnCbnSelchangeMotorSel();
  afx_msg void OnBnClickedMotorEn();
  afx_msg void OnEnChangeMotorMax();
  afx_msg void OnEnChangeMotorMin();
  afx_msg void OnEnChangeMotorFlexible();
  afx_msg void OnEnChangeEditOut3();
  afx_msg void OnEnChangeEditOut6();
  afx_msg BOOL OnEraseBkgnd(CDC* pDC);
  afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
