#pragma once


// CViewboard ��ͼ

class CBoardView : public CView
{
	DECLARE_DYNCREATE(CBoardView)

public://protected:
	CBoardView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CBoardView();
  CDC *m_dc;
  CBitmap *m_bm, *m_oldbm;
public:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
protected:
	DECLARE_MESSAGE_MAP()


public:
  void DrawLaserSin();
  void DrawLaserCircle();
  void DrawXRayOneShot();
  void DrawPoint(POINT point);
  void DrawCircle(POINT point, LONG r);
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

