/*
- Các tác giả : Binh Nguyen - Bioz, ...
- Bản quyền thuộc về : IEEV.org.
- Thông tin thêm : CD-01042010;UD-01042010;
- Mô tả : Chương trình minh họa cho việc sử dụng OpenCV để xử lý hình 
*/
// VnPLibCVImg1.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include "VnSLibCPlusUtils.h"


// CVnPLibCVImg1App:
// See VnPLibCVImg1.cpp for the implementation of this class
//

class CVnPLibCVImg1App : public CWinAppEx
{
public:
	CVnPLibCVImg1App();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CVnPLibCVImg1App theApp;