/*
- Các tác giả : Binh Nguyen - Bioz, ...
- Bản quyền thuộc về : IEEV.org.
- Thông tin thêm : CD-01042010;UD-01042010;
- Mô tả : Chương trình minh họa cho việc sử dụng OpenCV để xử lý hình 
*/
// VnPLibCVImg1Dlg.h : header file
//
#pragma once
//#include "afxwin.h"
#include "imgproc.hpp"
#include "highgui\highgui.hpp"
#include "highgui\highgui_c.h"

#include <stdio.h>
#include <iostream>
using namespace cv;
using namespace std;

// CVnPLibCVImg1Dlg dialog
class CVnPLibCVImg1Dlg : public CDialog
{
// Construction
public:
	CVnPLibCVImg1Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_VNPLIBCVIMG1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
private:
	CString sRootPath;
	int iProcessStep;	

	void LoadFileListToListBox(int iIListBoxId, CString iSRootPath, CString iSFileExt);
	CString GetFileNameFromListBox(int iIListBoxId);
	void ShowImageOnIFace(Mat pIImgDisp, Mat pIImgSour,  int iIROIXPad, int iIROIYPad,
									  int iIROIWidth, int iIROIHeight, const char* cPCView);
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedImageBrowserBtn();
	afx_msg void OnLbnSelchangeListSourceImage();	
	afx_msg void OnClose();
	CStatic mSourceAnchor;
	int mDisplayWindowSize;
	TCHAR mSDirectory[MAX_PATH] = "";
};
