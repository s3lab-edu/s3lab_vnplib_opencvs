/*
- Các tác giả : Binh Nguyen - Bioz, ...
- Bản quyền thuộc về : IEEV.org.
- Thông tin thêm : CD-01042010;UD-01042010;
- Mô tả : Chương trình minh họa cho việc sử dụng OpenCV để xử lý hình 
*/
// VnPLibCVImg2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "VnPLibCVImg2.h"
#include "VnPLibCVImg2Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

RNG rng(12345);

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


// CVnPLibCVImg2Dlg dialog

CVnPLibCVImg2Dlg::CVnPLibCVImg2Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVnPLibCVImg2Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVnPLibCVImg2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_ALGORITHM, cmbAlgorithm);
	DDX_Control(pDX, IDC_STATIC_INFO, txtInfo);
	DDX_Control(pDX, IDC_SOURCE_IMAGE_ANCHOR, mSourceAnchor);
}

BEGIN_MESSAGE_MAP(CVnPLibCVImg2Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(ID_IMAGE_BROWSER_BTN, &CVnPLibCVImg2Dlg::OnBnClickedImageBrowserBtn)
	ON_LBN_SELCHANGE(IDC_LIST_SOURCE_IMAGE, &CVnPLibCVImg2Dlg::OnLbnSelchangeListSourceImage)	
	ON_WM_CLOSE()	
END_MESSAGE_MAP()


// CVnPLibCVImg2Dlg message handlers

BOOL CVnPLibCVImg2Dlg::OnInitDialog()
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
	HWND hWnd = (HWND)cvGetWindowHandle("SOURVIEW");
	HWND hParent = ::GetParent(hWnd);
	::SetParent(hWnd, GetDlgItem(IDC_SOURCE_IMAGE_ANCHOR)->m_hWnd);
	::ShowWindow(hParent, SW_HIDE);

	// attach open cv window view vao panel window
	hWnd = (HWND)cvGetWindowHandle("DESTVIEW");
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

	cmbAlgorithm.AddString("Corner Tomashi");
	cmbAlgorithm.AddString("Corner Harris");		
    cmbAlgorithm.AddString("Smoothing Median");
	cmbAlgorithm.AddString("Smoothing Gaussian");
	cmbAlgorithm.AddString("Laplacian Filter");
    cmbAlgorithm.AddString("2D Reflect Y");
	cmbAlgorithm.AddString("2D Reflect X");
	cmbAlgorithm.AddString("2D Reflect XY");
	cmbAlgorithm.SetCurSel(6);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CVnPLibCVImg2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CVnPLibCVImg2Dlg::OnPaint()
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
HCURSOR CVnPLibCVImg2Dlg::OnQueryDragIcon()
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

void CVnPLibCVImg2Dlg::OnBnClickedImageBrowserBtn()
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

void CVnPLibCVImg2Dlg::LoadFileListToListBox(int iIListBoxId, CString iSRootPath, CString iSFileExt)
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

CString CVnPLibCVImg2Dlg::GetFileNameFromListBox(int iIListBoxId)
{
	CListBox * pLbxFiles;
	pLbxFiles = (CListBox *)GetDlgItem(iIListBoxId);
	CString sResult = "";

	int iSelIndex = pLbxFiles->GetCurSel();
	pLbxFiles->GetText(iSelIndex, sResult);
	return sResult;
}

void CVnPLibCVImg2Dlg::ShowImageOnIFace(Mat pIImgDisp, Mat pIImgSour, int iIROIXPad, int iIROIYPad,
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

void VnSUti24Bit2DReflectionY(uint8_t* oPCImgDest, int iIWidth, int iIHeight, int iIChannel, uint8_t* iPUcImgSrc)
{
	int x, y, iStep, iBackStep;

	for (y = 0; y != iIHeight; y++) 
	{
		for (x = 0, iStep = 0, iBackStep = ((iIWidth - 1) * 3); x != iIWidth; x++, iStep += iIChannel, iBackStep -= iIChannel)
		{	
			for (int i = 0; i < iIChannel; i++) {
				*(oPCImgDest + y * iIWidth * iIChannel + iStep + i) = *(iPUcImgSrc + y * iIWidth * iIChannel + iBackStep + i);
			}
		}		
	}
}

void VnSUti24Bit2DReflectionX(uint8_t* oPCImgDest, int iIWidth, int iIHeight, int iIChannel, uint8_t* iPUcImgSrc)
{
	int x, y, iStep, iBackStep;

	for (y = 0, iBackStep = (iIHeight - 1); y < iIHeight; y++, iBackStep--) 
	{
		for (x = 0, iStep = 0; x < iIWidth; x++, iStep += iIChannel)
		{	
			for (int i = 0; i < iIChannel; i++) {
				*(oPCImgDest + y * iIWidth * iIChannel + iStep + i) = *(iPUcImgSrc + iBackStep * iIWidth * iIChannel + iStep + i);
			}
		}		
	}
}

void VnSUti24Bit2DReflectionXY(uint8_t* oPCImgDest, int iIWidth, int iIHeight, int iIChannel, uint8_t* iPUcImgSrc)
{
	int x, y, iStep, iXBackStep, iYBackStep;

	for (y = 0, iYBackStep = (iIHeight - 1); y != iIHeight; y++, iYBackStep--) 
	{
		for (x = 0, iStep = 0, iXBackStep = ((iIWidth - 1) * 3); x != iIWidth; x++, iStep += iIChannel, iXBackStep -= iIChannel)
		{
			for (int i = 0; i < iIChannel; i++) {
				*(oPCImgDest + y * iIWidth * iIChannel + iStep + i) = *(iPUcImgSrc + iYBackStep * iIWidth * iIChannel + iXBackStep + i);
			}
		}		
	}
}

void CVnPLibCVImg2Dlg::OnLbnSelchangeListSourceImage()
{
	// TODO: Add your control notification handler code		
	// Chuan bi du lieu anh	
	CString sInfo;
	CString sPath = sRootPath + GetFileNameFromListBox(IDC_LIST_SOURCE_IMAGE);	
	Mat pIDispOrig = Mat::zeros(mDisplayWindowSize, mDisplayWindowSize, CV_8UC3);
	Mat pIDispGrey = Mat::zeros(mDisplayWindowSize, mDisplayWindowSize, CV_8UC1);

	// doc anh vao ma tran anh nguon
	Mat pISourOrig = cv::imread(sPath.GetBuffer(0), 1);
	// khoi tao ma tran anh de hien thi bang mau den
	pIDispOrig = cv::Scalar(0);
	
	int iWidth = pISourOrig.size().width;
	int iHeight = pISourOrig.size().height;
	int iSize = iWidth * iHeight;

	// khoi tao ma tran anh den trang, ket qua convert tu anh nguon
	Mat pISourGrey;
	// khoi tao ma tran anh de hien thi ket qua bang mau den
	pIDispGrey = cv::Scalar(0);

	Mat pIDestOrig = Mat::zeros(iHeight, iWidth, CV_8UC3);

	int iCornerCount = 0;
	std::vector<cv::Point2f> pPCorners;
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
		
	// Xu ly chinh	
	int iType = -1;
	cv::cvtColor(pISourOrig, pISourGrey, cv::COLOR_BGR2GRAY);
	cv::Mat mask;

	switch(cmbAlgorithm.GetCurSel())
	{
		case 0:
			cv::goodFeaturesToTrack(pISourGrey, pPCorners, 10, 0.01, 20, mask, 3, false, 0.04);
			break;
		case 1:
			cv::goodFeaturesToTrack(pISourGrey, pPCorners, 10, 0.01, 20, mask, 3, true, 0.04);
			break;	
		case 2:
			ShowImageOnIFace(pIDispOrig, pISourOrig, iDispWPad, iDispHPad, iDispWidth, iDispHeigh, "SOURVIEW");
			for (int i = 3; i < 51; i = i + 2)
			{
				cv::medianBlur(pISourOrig, pIDestOrig, i);
				sInfo.Format("Kernel Size %d", i);
				txtInfo.SetWindowTextA(sInfo);
				ShowImageOnIFace(pIDispOrig, pIDestOrig, iDispWPad, iDispHPad, iDispWidth, iDispHeigh, "DESTVIEW");
				cvWaitKey(100);
			}
			break;
		case 3:
			ShowImageOnIFace(pIDispOrig, pISourOrig,  iDispWPad, iDispHPad, iDispWidth, iDispHeigh, "SOURVIEW");
			for ( int i = 3; i < 51; i = i + 2 )
			{ 								
				cv::GaussianBlur(pISourOrig, pIDestOrig, Size(i, i), 0, 0);
				sInfo.Format("Kernel Size %d", i);
				txtInfo.SetWindowTextA(sInfo);				
				ShowImageOnIFace(pIDispOrig, pIDestOrig,  iDispWPad, iDispHPad, iDispWidth, iDispHeigh, "DESTVIEW");
				cvWaitKey(100);
			}
			break;
		case 4:
			ShowImageOnIFace(pIDispOrig, pISourOrig,  iDispWPad, iDispHPad, iDispWidth, iDispHeigh, "SOURVIEW");
			for ( int i = 1; i < 11; i = i + 2 )
			{ 				
				cv::Laplacian(pISourOrig, pIDestOrig, CV_16S, i, 1, 0);
				sInfo.Format("Kernel Size %d", i);
				txtInfo.SetWindowTextA(sInfo);				
				ShowImageOnIFace(pIDispOrig, pIDestOrig,  iDispWPad, iDispHPad, iDispWidth, iDispHeigh, "DESTVIEW");
				cvWaitKey(1000);
			}
			break;
		case 5:
			VnSUti24Bit2DReflectionY((uint8_t*)pIDestOrig.data, pISourOrig.cols, pISourOrig.rows, pISourOrig.channels(), (uint8_t*)pISourOrig.data);
			break;
		case 6:
			VnSUti24Bit2DReflectionX((uint8_t*)pIDestOrig.data, pISourOrig.cols, pISourOrig.rows, pISourOrig.channels(), (uint8_t*)pISourOrig.data);
			break;
		case 7:
			VnSUti24Bit2DReflectionXY((uint8_t*)pIDestOrig.data, pISourOrig.cols, pISourOrig.rows, pISourOrig.channels(), (uint8_t*)pISourOrig.data);
			break;		
		default:
			VnSUti24Bit2DReflectionXY((uint8_t*)pIDestOrig.data, pISourOrig.cols, pISourOrig.rows, pISourOrig.channels(), (uint8_t*)pISourOrig.data);
			
			break;
	}			
	// ~Xu ly chinh

	// Hien thi	
	switch(cmbAlgorithm.GetCurSel())
	{
		case 0:						
		case 1:
			ShowImageOnIFace(pIDispGrey, pISourGrey,  iDispWPad, iDispHPad, iDispWidth, iDispHeigh, "SOURVIEW");
			for(int i=0 ; i < pPCorners.size(); i++)
			{
				cv::circle(pISourOrig, pPCorners[i], 4, cv::Scalar(rng.uniform(0, 255), rng.uniform(0, 256), rng.uniform(0, 256)), cv::FILLED);
			}
			ShowImageOnIFace(pIDispOrig, pISourOrig,  iDispWPad, iDispHPad, iDispWidth, iDispHeigh, "DESTVIEW");	
			break;	
		default:
			ShowImageOnIFace(pIDispGrey, pISourGrey,  iDispWPad, iDispHPad, iDispWidth, iDispHeigh, "SOURVIEW");
			ShowImageOnIFace(pIDispOrig, pIDestOrig,  iDispWPad, iDispHPad, iDispWidth, iDispHeigh, "DESTVIEW");	
			break;
	}			
	// ~Hien thi

	// Giai phong bo nho
	pIDispOrig.release();
	pIDispGrey.release();
	pISourOrig.release();
	pISourGrey.release();

	pIDestOrig.release();
	// ~Giai phong bo nho	

}

void CVnPLibCVImg2Dlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnClose();
	destroyWindow("SOURVIEW");
	destroyWindow("DESTVIEW");
}
