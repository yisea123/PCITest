#pragma once


// CViewboard 视图

class CViewboard : public CView
{
	DECLARE_DYNCREATE(CViewboard)

public://protected:
	CViewboard();           // 动态创建所使用的受保护的构造函数
	virtual ~CViewboard();

public:
	virtual void OnDraw(CDC* pDC);      // 重写以绘制该视图
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
};


