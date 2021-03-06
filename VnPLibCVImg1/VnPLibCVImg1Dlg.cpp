/*
- Các tác giả : Binh Nguyen - Bioz, ...
- Bản quyền thuộc về : IEEV.org.
- Thông tin thêm : CD-01042010;UD-01042010;
- Mô tả : Chương trình minh họa cho việc sử dụng OpenCV để xử lý hình 
*/
// VnPLibCVImg1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "VnPLibCVImg1.h"
#include "VnPLibCVImg1Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CVnPLibCVImg1Dlg dialog

CVnPLibCVImg1Dlg::CVnPLibCVImg1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVnPLibCVImg1Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVnPLibCVImg1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SOURCE_IMAGE_ANCHOR, mSourceAnchor);
}

BEGIN_MESSAGE_MAP(CVnPLibCVImg1Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(ID_IMAGE_BROWSER_BTN, &CVnPLibCVImg1Dlg::OnBnClickedImageBrowserBtn)
	ON_LBN_SELCHANGE(IDC_LIST_SOURCE_IMAGE, &CVnPLibCVImg1Dlg::OnLbnSelchangeListSourceImage)	
	ON_WM_CLOSE()	
END_MESSAGE_MAP()


// CVnPLibCVImg1Dlg message handlers

BOOL CVnPLibCVImg1Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	// hien thi anh nguon
	namedWindow("SOURVIEW", 1);
	// hien thi anh ket qua
	namedWindow("DESTVIEW", 1);

	// attach open cv window view vao panel window
	HWND hWnd = (HWND) cvGetWindowHandle("SOURVIEW");
	HWND hParent = ::GetParent(hWnd);
	::SetParent(hWnd, GetDlgItem(IDC_SOURCE_IMAGE_ANCHOR)->m_hWnd);
	::ShowWindow(hParent, SW_HIDE);	

	// attach open cv window view vao panel window
	hWnd = (HWND) cvGetWindowHandle("DESTVIEW");
	hParent = ::GetParent(hWnd);
	::SetParent(hWnd, GetDlgItem(IDC_DEST_IMAGE_ANCHOR)->m_hWnd);
	::ShowWindow(hParent, SW_HIDE);	

	CRect oSizeofPanel;
	mSourceAnchor.GetWindowRect(&oSizeofPanel);
	mDisplayWindowSize = oSizeofPanel.right - oSizeofPanel.left;

	Mat pTmpBg = Mat::zeros(mDisplayWindowSize, mDisplayWindowSize, CV_8UC1);
	imshow("SOURVIEW", pTmpBg);
	imshow("DESTVIEW", pTmpBg);
	pTmpBg.release();

	::GetCurrentDirectory(sizeof(mSDirectory) - 1, mSDirectory);
	sRootPath = "";		

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CVnPLibCVImg1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CVnPLibCVImg1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}else{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CVnPLibCVImg1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int CALLBACK BrowseCallBackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	switch (uMsg)
	{
	case BFFM_INITIALIZED:
		::SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lpData);
		break;
	}
	return 0;
}

void CVnPLibCVImg1Dlg::OnBnClickedImageBrowserBtn()
{
	// TODO: Add your control notification handler code here
	BROWSEINFO   bi; 
	ZeroMemory(&bi,   sizeof(bi)); 
	TCHAR   szDisplayName[MAX_PATH]; 
	szDisplayName[0]    =   ' ';  

	bi.hwndOwner        =   NULL; 
	bi.pidlRoot         =   NULL; 
	bi.pszDisplayName   =   szDisplayName; 
	bi.lpszTitle        =   _T("Please select a folder that stored image files :"); 
	bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
	bi.lParam = (LPARAM)mSDirectory;
	bi.iImage = 0;
	bi.lpfn = BrowseCallBackProc;

	LPITEMIDLIST   pidl   =   SHBrowseForFolder(&bi);
	TCHAR   szPathName[MAX_PATH]; 
	if   (NULL   !=   pidl)
	{
		BOOL bRet = SHGetPathFromIDList(pidl,szPathName);
		if(FALSE == bRet)
		{
			return;
		}

		sRootPath = (CString)szPathName + (CString)"\\";		
		LoadFileListToListBox(IDC_LIST_SOURCE_IMAGE, sRootPath, (CString)"*.jpg,*.png");
	}
}

void CVnPLibCVImg1Dlg::LoadFileListToListBox(int iIListBoxId, CString iSRootPath, CString iSFileExt)
{
	CListBox * pList;
	pList = (CListBox *)GetDlgItem(iIListBoxId);
	
	pList->ResetContent();
	
	CFileFind oFileFinder;
	BOOL bFinding;
	int iCount=0;

	int	iCurPos=0;
	CString sToken;
	sToken = iSFileExt.Tokenize(_T(","), iCurPos);

	while(sToken != _T(""))
	{
		bFinding = oFileFinder.FindFile (iSRootPath + sToken);		
			
		while (bFinding)
		{
			bFinding = oFileFinder.FindNextFile();
			pList->AddString(oFileFinder.GetFileName());
			iCount++;
		}
		
		sToken = iSFileExt.Tokenize(_T(","), iCurPos); 
	}

	if(iCount <= 0)
	{
		pList->AddString((CString)"No files found");
	}
	
	oFileFinder.Close ();
}

CString CVnPLibCVImg1Dlg::GetFileNameFromListBox(int iIListBoxId)
{
	CListBox * pLbxFiles;
	pLbxFiles = (CListBox *)GetDlgItem(iIListBoxId);
	CString sResult = "";

	int iSelIndex = pLbxFiles->GetCurSel();
	pLbxFiles->GetText(iSelIndex, sResult);
	return sResult;
}
void CVnPLibCVImg1Dlg::ShowImageOnIFace(Mat pIImgDisp, Mat pIImgSour,  int iIROIXPad, int iIROIYPad,
									  int iIROIWidth, int iIROIHeight, const char* cPCView)
{
	//Tao vung ROI
	Rect roi(iIROIXPad, iIROIYPad, iIROIWidth, iIROIHeight);

	//Anh xa mot ma tran anh vao ROI
	Mat pIImgDispROI = pIImgDisp(roi);
	
	// scale anh nguon vao vung ROI
	cv::resize(pIImgSour, pIImgDispROI, cv::Size(iIROIWidth, iIROIHeight), 0, 0);

	// Hien thi anh
	imshow(cPCView, pIImgDisp);	

	pIImgDispROI.release();
}

void CVnPLibCVImg1Dlg::OnLbnSelchangeListSourceImage()
{
	// TODO: Add your control notification handler code		

	// Chuan bi du lieu anh	

	CString sPath = sRootPath + GetFileNameFromListBox(IDC_LIST_SOURCE_IMAGE);	
	Mat pIDispOrig = Mat::zeros(mDisplayWindowSize, mDisplayWindowSize, CV_8UC3);
	Mat pIDispGrey = Mat::zeros(mDisplayWindowSize, mDisplayWindowSize, CV_8UC1);

	// doc anh vao ma tran anh nguon
	Mat pISourOrig= cv::imread(sPath.GetBuffer(0), 1);
	// khoi tao ma tran anh de hien thi bang mau den
	pIDispOrig = cv::Scalar(0);
	
	int iWidth = pISourOrig.size().width;
	int iHeight = pISourOrig.size().height;
	int iSize = iWidth * iHeight;

	// khoi tao ma tran anh den trang, ket qua convert tu anh nguon
	Mat pISourGrey = Mat::zeros( iWidth, iHeight, CV_8UC1);
	// khoi tao ma tran anh de hien thi ket qua bang mau den
	pIDispGrey = cv::Scalar(0);

	// ~Chuan bi du lieu anh
	
	// Du lieu tinh scale anh de hien thi
	int iMaxSize = (iWidth > iHeight)? iWidth : iHeight;  
	float fScale = (float) ( (float)iMaxSize / (float)mDisplayWindowSize );

	if(fScale == 0)
	{
		fScale = 1;
	}

	int iDispWidth = (int)( (float)iWidth / fScale );
	int iDispHeigh = (int)( (float)iHeight / fScale );
	int iDispWPad = (mDisplayWindowSize - iDispWidth) / 2;
	int iDispHPad = (mDisplayWindowSize - iDispHeigh) / 2;
	// ~Du lieu tinh scale anh de hien thi
		
	// Xu ly chinh chuyen anh mau sang anh den trang
	cv::cvtColor( pISourOrig, pISourGrey, cv::COLOR_BGR2GRAY);			
	// ~Xu ly chinh

	// Hien thi
	ShowImageOnIFace(pIDispOrig, pISourOrig,  iDispWPad, iDispHPad, iDispWidth, iDispHeigh, "SOURVIEW");
	ShowImageOnIFace(pIDispGrey, pISourGrey,  iDispWPad, iDispHPad, iDispWidth, iDispHeigh, "DESTVIEW");
	// ~Hien thi

	// Giai phong bo nho
	pIDispOrig.release();
	pIDispGrey.release();
	pISourOrig.release();	
	pISourGrey.release();		
	// ~Giai phong bo nho
}


void CVnPLibCVImg1Dlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnClose();
	destroyWindow("SOURVIEW");
	destroyWindow("DESTVIEW");
}
