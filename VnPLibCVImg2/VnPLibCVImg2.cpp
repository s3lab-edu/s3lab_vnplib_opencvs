/*
- Các tác giả : Binh Nguyen - Bioz, ...
- Bản quyền thuộc về : IEEV.org.
- Thông tin thêm : CD-01042010;UD-01042010;
- Mô tả : Chương trình minh họa cho việc sử dụng OpenCV để xử lý hình 
*/
// VnPLibCVImg1.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "VnPLibCVImg2.h"
#include "VnPLibCVImg2Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CVnPLibCVImg1App

BEGIN_MESSAGE_MAP(CVnPLibCVImg1App, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CVnPLibCVImg1App construction

CVnPLibCVImg1App::CVnPLibCVImg1App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CVnPLibCVImg1App object

CVnPLibCVImg1App theApp;


// CVnPLibCVImg1App initialization

BOOL CVnPLibCVImg1App::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	CVnPLibCVImg2Dlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
