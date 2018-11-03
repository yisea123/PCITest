// CPicture.h: interface for the CPicture class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PICTURE_H__081D008A_5029_4C56_B80C_37793E323DF6__INCLUDED_)
#define AFX_PICTURE_H__081D008A_5029_4C56_B80C_37793E323DF6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//////////////////////////////////////////////////////////////////////////
#include <stdio.h>

//------------------------------------------

typedef enum
{
	OFM_WRITE        = 0,
	OFM_READ         = 1
}FILE_OPENMODE;

#define HIMETRIC_INCH 2540

//=-----------------------------
class CFileProcess
{
private :
	FILE  *m_File;

public:
	CFileProcess();
   ~CFileProcess();
    BOOL	Open        (char * FileName , FILE_OPENMODE Open_Mode);
	BOOL	Write       (VOID * zBuffer, DWORD cSize);
    BOOL	Read        (VOID * zBuffer, DWORD cSize);
	LONG    GetSize     (VOID);
	VOID    Close       (VOID);
};

//-------------------------------------------------------------


//-----------------------------------------
class CPicture  
{
public:
	CPicture();
	virtual ~CPicture();
	
private:
	IPicture *m_pic;
	HGLOBAL  hGlobal;
	LPPICTURE m_pPict;

public:

	HBITMAP LoadPicture(char * FileName);
	HBITMAP LoadPicture(char * FileName, HDC hdc);
	HBITMAP LoadPicture(char *FileName, HDC hdc, long cx, long cy);
	VOID    FreePicture( VOID );
    HDC     _GetDC     ( VOID );
	HBITMAP _GetHandle ( VOID );
	DWORD   _GetWidth  ( VOID );
	DWORD   _GetHeight ( VOID );
	BOOL    DrawPicture(HDC hdc,long x,long y,long cx,long cy);
	BOOL SaveNewImage(HBITMAP hbitmap, LPCTSTR filename, int nColor);
	BOOL SaveBmp(HBITMAP hBitmap, const char *FileName);
	bool SaveBitmapToFile(CBitmap* bitmap, LPCWSTR lpFileName);

	void Render(CDC* pDC, LPRECT pDrawRect/*目标矩形，单位是逻辑坐标单位*/, LPRECT 
	
		
		
		pSrcRect=NULL/*来源矩形，单位是0.01毫米,如果为空，则拉伸整个图像到目标矩形*/,LPCRECT prcWBounds=NULL/*图元文件专用，绑定矩形*/);//在给定的DC上画图，


};

#endif // !defined(AFX_PICTURE_H__081D008A_5029_4C56_B80C_37793E323DF6__INCLUDED_)
