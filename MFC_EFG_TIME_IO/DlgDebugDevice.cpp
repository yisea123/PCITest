// DlgDebugDevice.cpp: 实现文件
//

#include "stdafx.h"
#include "MFC_EFG_TIME_IO.h"
#include "DlgDebugDevice.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "DlgDebug1.h"//访问父窗口


// CDlgDebugDevice 对话框

IMPLEMENT_DYNAMIC(CDlgDebugDevice, CDialogEx)

CDlgDebugDevice::CDlgDebugDevice(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DEVICE, pParent)
{

}

CDlgDebugDevice::~CDlgDebugDevice()
{
}

void CDlgDebugDevice::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgDebugDevice, CDialogEx)
  ON_BN_CLICKED(IDC_BTN_MEASURE, &CDlgDebugDevice::OnBnClickedBtnMeasure)
  ON_BN_CLICKED(IDC_X_TIP, &CDlgDebugDevice::OnBnClickedXTip)
  ON_BN_CLICKED(IDC_XRAY_GATE, &CDlgDebugDevice::OnBnClickedXrayGate)
  ON_WM_TIMER()
  ON_BN_CLICKED(IDC_BTN_REALTIME, &CDlgDebugDevice::OnBnClickedBtnRealtime)
  ON_CBN_SELCHANGE(IDC_MOTOR_SEL, &CDlgDebugDevice::OnCbnSelchangeMotorSel)
  ON_BN_CLICKED(IDC_MOTOR_EN, &CDlgDebugDevice::OnBnClickedMotorEn)
  ON_EN_CHANGE(IDC_MOTOR_MAX, &CDlgDebugDevice::OnEnChangeMotorMax)
  ON_EN_CHANGE(IDC_MOTOR_MIN, &CDlgDebugDevice::OnEnChangeMotorMin)
  ON_EN_CHANGE(IDC_MOTOR_FLEXIBLE, &CDlgDebugDevice::OnEnChangeMotorFlexible)
  ON_EN_CHANGE(IDC_EDIT_OUT3, &CDlgDebugDevice::OnEnChangeEditOut3)
  ON_EN_CHANGE(IDC_EDIT_OUT6, &CDlgDebugDevice::OnEnChangeEditOut6)
  ON_WM_ERASEBKGND()
  ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CDlgDebugDevice 消息处理程序


void CDlgDebugDevice::OnBnClickedBtnMeasure()
{
  // TODO: 在此添加控件通知处理程序代码
  GetMainFrame()->m_diIntCounterSnap.BindCard(0, NULL, GetMainFrame()->m_viewBoard);
 // GetMainFrame()->Switch(VIEW_BOARD);
  GetMainFrame()->m_diIntCounterSnap.TestS();
  GetMainFrame()->m_viewBoard->DrawToDC(GetDlgItem(IDC_PREVIEW)->GetDC());
}


void CDlgDebugDevice::OnBnClickedXTip()
{
  // TODO: 在此添加控件通知处理程序代码
  CButton* pChk = (CButton*)GetDlgItem(IDC_X_TIP);
  int nStat = pChk->GetCheck();
  if (nStat)
  {
    
  }
  else
  {
    
  }
}

BOOL CDlgDebugDevice::OnInitDialog()
{
  CDialogEx::OnInitDialog();

  // TODO:  在此添加额外的初始化
  //combobox必须放在tab控件之后
  ((CComboBox*)GetDlgItem(IDC_MOTOR_SEL))->AddString(_T("X"));
  ((CComboBox*)GetDlgItem(IDC_MOTOR_SEL))->AddString(_T("Y"));
  ((CComboBox*)GetDlgItem(IDC_MOTOR_SEL))->AddString(_T("U"));
  //((CComboBox*)GetDlgItem(IDC_MOTOR_SEL))->SetCurSel(0);

  CBitmap bmp, sbmp;
  bmp.LoadBitmap(IDB_BK3);   //IDB_BITMAP1是图片资源ID
  CRect rect;
  GetClientRect(&rect);
  ScaleBitmap(&bmp,sbmp,rect.Width(),rect.Height());
  m_brush.CreatePatternBrush(&sbmp);
  bmp.DeleteObject();
  
  return TRUE;  // return TRUE unless you set the focus to a control
                // 异常: OCX 属性页应返回 FALSE
}


void CDlgDebugDevice::OnBnClickedXrayGate()
{
  // TODO: 在此添加控件通知处理程序代码
  CButton* pChk = (CButton*)GetDlgItem(IDC_XRAY_GATE);
  int nStat = pChk->GetCheck();
  if (nStat)
  {
    GetMainFrame()->m_efgio.WriteDo(XRAY_CTRL_GATE, 1);
  }
  else
  {
    GetMainFrame()->m_efgio.WriteDo(XRAY_CTRL_GATE, 0);
  }
}


void CDlgDebugDevice::OnTimer(UINT_PTR nIDEvent)
{
  // TODO: 在此添加消息处理程序代码和/或调用默认值

  CDialogEx::OnTimer(nIDEvent);
}


void CDlgDebugDevice::OnBnClickedBtnRealtime()
{
  // TODO: 在此添加控件通知处理程序代码
  CString str;
  GetDlgItemText(IDC_BTN_REALTIME, str);
  if ("实时" == str) {
    SetTimer(0, 100, NULL);
    SetDlgItemText(IDC_BTN_REALTIME, _T("停止"));
  }
  else {
    KillTimer(0);
    SetDlgItemText(IDC_BTN_REALTIME, _T("实时"));
  }

}


void CDlgDebugDevice::OnCbnSelchangeMotorSel()
{
  // TODO: 在此添加控件通知处理程序代码
  CString str;
  float max_freq;
  float min_freq;
  float flexible;
  EFG_Param *param = &GetMainFrame()->m_efgio.m_efg_param;
  //GetDlgItemText(IDC_MOTOR_SEL, str);/这里应该改内存，保存ini单独保存ctrl+s
  int sel = ((CComboBox*)GetDlgItem(IDC_MOTOR_SEL))->GetCurSel();
  switch (sel) {
  case 0:
    max_freq = param->motor.x.max_freq;
    min_freq = param->motor.x.min_freq;
    flexible = param->motor.x.flexible;
    break;
  case 1:
    max_freq = param->motor.y.max_freq;
    min_freq = param->motor.y.min_freq;
    flexible = param->motor.y.flexible;
    break;
  case 2:
    max_freq = param->motor.u.max_freq;
    min_freq = param->motor.u.min_freq;
    flexible = param->motor.u.flexible;
    break;
  default:
    return;
  }
  //
  str.Format(_T("%.2f"), max_freq);
  SetDlgItemText(IDC_MOTOR_MAX, str);
  str.Format(_T("%.2f"), min_freq);
  SetDlgItemText(IDC_MOTOR_MIN, str);
  str.Format(_T("%.2f"), flexible);
  SetDlgItemText(IDC_MOTOR_FLEXIBLE, str);

  SetDlgItemInt(IDC_MOTOR_SRC, 0, 0);
  SetDlgItemInt(IDC_MOTOR_DST, 0, 0);
    

}


void CDlgDebugDevice::OnBnClickedMotorEn()
{
  // TODO: 在此添加控件通知处理程序代码
  CButton* pChk = (CButton*)GetDlgItem(IDC_MOTOR_EN);
  int nStat = pChk->GetCheck();
  if (nStat)
  {
   // GetMainFrame()->m_efgio.WriteDo(U_EN, 1);
  }
  else
  {
  //  GetMainFrame()->m_efgio.WriteDo(U_EN, 0);
  }
}


void CDlgDebugDevice::OnEnChangeMotorMax()
{
  // TODO:  如果该控件是 RICHEDIT 控件，它将不
  // 发送此通知，除非重写 CDialogEx::OnInitDialog()
  // 函数并调用 CRichEditCtrl().SetEventMask()，
  // 同时将 ENM_CHANGE 标志“或”运算到掩码中。

  // TODO:  在此添加控件通知处理程序代码
  CString str;
  EFG_Param *param = &GetMainFrame()->m_efgio.m_efg_param;
  GetDlgItemText(IDC_MOTOR_MAX, str);
  double val = _wtof(str);
  int sel = ((CComboBox*)GetDlgItem(IDC_MOTOR_SEL))->GetCurSel();
  switch (sel) {
  case 0:
    param->motor.x.max_freq = val;
    break;
  case 1:
    param->motor.y.max_freq = val;
    break;
  case 2:
    param->motor.u.max_freq = val;
    break;
  default:
    return;
  }
}


void CDlgDebugDevice::OnEnChangeMotorMin()
{
  // TODO:  如果该控件是 RICHEDIT 控件，它将不
  // 发送此通知，除非重写 CDialogEx::OnInitDialog()
  // 函数并调用 CRichEditCtrl().SetEventMask()，
  // 同时将 ENM_CHANGE 标志“或”运算到掩码中。

  // TODO:  在此添加控件通知处理程序代码
  CString str;
  EFG_Param *param = &GetMainFrame()->m_efgio.m_efg_param;
  GetDlgItemText(IDC_MOTOR_MIN, str);
  double val = _wtof(str);
  int sel = ((CComboBox*)GetDlgItem(IDC_MOTOR_SEL))->GetCurSel();
  switch (sel) {
  case 0:
    param->motor.x.min_freq = val;
    break;
  case 1:
    param->motor.y.min_freq = val;
    break;
  case 2:
    param->motor.u.min_freq = val;
    break;
  default:
    return;
  }
}


void CDlgDebugDevice::OnEnChangeMotorFlexible()
{
  // TODO:  如果该控件是 RICHEDIT 控件，它将不
  // 发送此通知，除非重写 CDialogEx::OnInitDialog()
  // 函数并调用 CRichEditCtrl().SetEventMask()，
  // 同时将 ENM_CHANGE 标志“或”运算到掩码中。

  // TODO:  在此添加控件通知处理程序代码
  CString str;
  EFG_Param *param = &GetMainFrame()->m_efgio.m_efg_param;
  GetDlgItemText(IDC_MOTOR_FLEXIBLE, str);
  double val = _wtof(str);
  int sel = ((CComboBox*)GetDlgItem(IDC_MOTOR_SEL))->GetCurSel();
  switch (sel) {
  case 0:
    param->motor.x.flexible = val;
    break;
  case 1:
    param->motor.y.flexible= val;
    break;
  case 2:
    param->motor.u.flexible = val;
    break;
  default:
    return;
  }
}


void CDlgDebugDevice::OnEnChangeEditOut3()
{
  // TODO:  如果该控件是 RICHEDIT 控件，它将不
  // 发送此通知，除非重写 CDialogEx::OnInitDialog()
  // 函数并调用 CRichEditCtrl().SetEventMask()，
  // 同时将 ENM_CHANGE 标志“或”运算到掩码中。

  // TODO:  在此添加控件通知处理程序代码
  CString str;
  EFG_Param *param = &GetMainFrame()->m_efgio.m_efg_param;
  GetDlgItemText(IDC_EDIT_OUT3, str);
  double val = _wtof(str);
  param->laser.out3 = val;
}


void CDlgDebugDevice::OnEnChangeEditOut6()
{
  // TODO:  如果该控件是 RICHEDIT 控件，它将不
  // 发送此通知，除非重写 CDialogEx::OnInitDialog()
  // 函数并调用 CRichEditCtrl().SetEventMask()，
  // 同时将 ENM_CHANGE 标志“或”运算到掩码中。

  // TODO:  在此添加控件通知处理程序代码
  CString str;
  EFG_Param *param = &GetMainFrame()->m_efgio.m_efg_param;
  GetDlgItemText(IDC_EDIT_OUT6, str);
  double val = _wtof(str);
  param->laser.out6 = val;
}


BOOL CDlgDebugDevice::OnEraseBkgnd(CDC* pDC)
{
  // TODO: 在此添加消息处理程序代码和/或调用默认值

  return CDialogEx::OnEraseBkgnd(pDC);
 
  //HBITMAP hBitmap = ::LoadBitmap(::GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BK2));
  ////获取位图尺寸
  //BITMAP bitmap;
  //GetObject(hBitmap, sizeof(BITMAP), &bitmap);

  ////获取对话框尺寸
  //CRect rect;
  //GetClientRect(&rect);

  ////创建DC
  //HDC m_hBkDC = ::CreateCompatibleDC(pDC->m_hDC);

  ////绘图并清理
  //if (hBitmap && m_hBkDC)
  //{
  //  ::SelectObject(m_hBkDC, hBitmap);
  //  ::StretchBlt(pDC->m_hDC, 0, 0, bitmap.bmWidth, bitmap.bmHeight, m_hBkDC, 0, 0, rect.Width(), rect.Height(), SRCCOPY);
  //  ::DeleteObject(hBitmap);
  //  ::DeleteDC(m_hBkDC);
  //}

  ////这个很重要
  //return TRUE;

  //gdi+的方式
  //Graphics graphics(pDC->m_hDC);

  //Image image(L"image.jpg");
  //TextureBrush tBrush(&image);
  //Pen texturedPen(&tBrush, 10);

  //graphics.DrawLine(&texturedPen, 25, 25, 325, 25);
  //tBrush.SetWrapMode(WrapModeTileFlipXY);
  //graphics.FillRectangle(&tBrush, 25, 100, 300, 200);
}


HBRUSH CDlgDebugDevice::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
  HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

  // TODO:  在此更改 DC 的任何特性
  if (pWnd == this) {
    return m_brush;
  }
  else if (nCtlColor == CTLCOLOR_STATIC|| nCtlColor == CTLCOLOR_BTN  /*|| nCtlColor == CTLCOLOR_MAX*/)
  {
    pDC->SetBkMode(TRANSPARENT);
    pDC->SetTextColor(RGB(0, 0, 0));
    return (HBRUSH)::GetStockObject(NULL_BRUSH);
  }
  // TODO:  如果默认的不是所需画笔，则返回另一个画笔
  return hbr;
}
