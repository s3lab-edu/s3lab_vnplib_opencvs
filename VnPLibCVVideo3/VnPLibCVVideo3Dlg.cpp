/*
- Các tác giả : Binh Nguyen - Bioz, ...
- Bản quyền thuộc về : IEEV.org.
- Thông tin thêm : CD-01042010;UD-01042010;
- Mô tả : Chương trình minh họa cho việc sử dụng OpenCV để xử lý video 
*/
// VnPLibCVVideo3Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "VnPLibCVVideo3.h"
#include "VnPLibCVVideo3Dlg.h"

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


// CVnPLibCVVideo3Dlg dialog

CVnPLibCVVideo3Dlg::CVnPLibCVVideo3Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVnPLibCVVideo3Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVnPLibCVVideo3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SOURCE_IMAGE_ANCHOR, mSourceAnchor);
}

BEGIN_MESSAGE_MAP(CVnPLibCVVideo3Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(ID_IMAGE_BROWSER_BTN, &CVnPLibCVVideo3Dlg::OnBnClickedImageBrowserBtn)
	ON_LBN_SELCHANGE(IDC_LIST_SOURCE_IMAGE, &CVnPLibCVVideo3Dlg::OnLbnSelchangeListSourceImage)	
	ON_WM_CLOSE()	
	ON_BN_CLICKED(ID_CANCEL_PROCESS_BTN, &CVnPLibCVVideo3Dlg::OnBnClickedCancelProcessBtn)	
	ON_BN_CLICKED(ID_CAM_BROWSER_BTN, &CVnPLibCVVideo3Dlg::OnBnClickedCamBrowserBtn)
END_MESSAGE_MAP()


// CVnPLibCVVideo3Dlg message handlers

BOOL CVnPLibCVVideo3Dlg::OnInitDialog()
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
	iCameraType = 1;
	iIsProcess = 0;

	return TRUE;
}

void CVnPLibCVVideo3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CVnPLibCVVideo3Dlg::OnPaint()
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
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CVnPLibCVVideo3Dlg::OnQueryDragIcon()
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

void CVnPLibCVVideo3Dlg::OnBnClickedImageBrowserBtn()
{
	// TODO: Add your control notification handler code here
	if(iIsProcess > 0)
	{
		return;
	}

	BROWSEINFO   bi; 
	ZeroMemory(&bi,   sizeof(bi)); 
	TCHAR   szDisplayName[MAX_PATH]; 
	szDisplayName[0]    =   ' ';  

	bi.hwndOwner        =   NULL; 
	bi.pidlRoot         =   NULL; 
	bi.pszDisplayName   =   szDisplayName; 
	bi.lpszTitle        =   _T("Please select a folder that stored video files :"); 
	bi.ulFlags          = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
	bi.lParam           = (LPARAM)mSDirectory;
	bi.iImage           =   0;	
	bi.lpfn = BrowseCallBackProc;

	LPITEMIDLIST   pidl   =   SHBrowseForFolder(&bi);
	TCHAR   szPathName[MAX_PATH]; 
	if   (NULL   !=   pidl)
	{
		iCameraType = 1;

		BOOL bRet = SHGetPathFromIDList(pidl,szPathName);
		if(FALSE == bRet)
		{
			return;
		}

		sRootPath = (CString)szPathName + (CString)"\\";
		LoadFileListToListBox(IDC_LIST_SOURCE_IMAGE, sRootPath, (CString)"*.avi,*.mp4,*.mov,*.mpeg");
	}
}

void CVnPLibCVVideo3Dlg::LoadFileListToListBox(int iIListBoxId, CString iSRootPath, CString iSFileExt)
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

CString CVnPLibCVVideo3Dlg::GetFileNameFromListBox(int iIListBoxId, int* oPICamId )
{
	CListBox * pLbxFiles;
	pLbxFiles = (CListBox *)GetDlgItem(iIListBoxId);
	CString sResult = "";

	(*oPICamId) = pLbxFiles->GetCurSel();
	pLbxFiles->GetText((*oPICamId), sResult);
	return sResult;
}

void CVnPLibCVVideo3Dlg::ShowImageOnIFace(Mat pIImgDisp, Mat pIImgSour, int iIROIXPad, int iIROIYPad,
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

void CVnPLibCVVideo3Dlg::OnLbnSelchangeListSourceImage()
{	
	if(iIsProcess > 0)
	{
		return;
	}	
	CString sPath;
	CString sText;
	int iSelIndex = 0;

	// Tinh thoi gian thuc thi
	double dStartTime;
	double dStopTime;
	double dTime;
	// ~Tinh thoi gian thuc thi
	
	// Khai bao du lieu cho human detection
	cv::HOGDescriptor oHogSVM;
    oHogSVM.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
	// ~Khai bao du lieu cho human detection
	
	// Du lieu hinh
	VideoCapture pOViSour;

	Mat pIDispOrig = Mat::zeros(mDisplayWindowSize, mDisplayWindowSize, CV_8UC3);
	Mat pIDispGrey = Mat::zeros(mDisplayWindowSize, mDisplayWindowSize, CV_8UC1);

	Mat pISourOrig;
	Mat pISourGrey;
	// ~Du lieu hinh

	// Thong tin hinh
	int iWidth;
	int iHeight;
	int iSize;
	// ~Thong tin hinh

	// Thong tin de scale hinh cho hien thi
	int iMaxSize;
	int iDispWidth, iDispHeigh, iDispWPad, iDispHPad;
	float fScale;
	// ~Thong tin de scale hinh cho hien thi

	int iCountFrm; 

	if(iSelIndex < 0)
	{
		MessageBox("Please select the cascade data", "Warning");
		goto ESCAPE;
	}
	
	switch(iCameraType){
		case 0:
			sPath = GetFileNameFromListBox(IDC_LIST_SOURCE_IMAGE, &iSelIndex);
			pOViSour.open(iSelIndex);
			break;
		case 1:
			sPath = sRootPath + GetFileNameFromListBox(IDC_LIST_SOURCE_IMAGE, &iSelIndex);
			pOViSour.open(sPath.GetBuffer(0));
			break;		
		default: 
			break;
	}

	if( pOViSour.isOpened() == false)
	{		
		MessageBox("Can not capture video from source", "Error");
		return;
	}

	bool bSuccess = pOViSour.read(pISourOrig);

	if (!bSuccess)
	{
		return;
	}

	CButton* pBtnCancel = (CButton *)GetDlgItem(ID_CANCEL_PROCESS_BTN);
	pBtnCancel->EnableWindow(true);	
	CStatic* pLblInfor = (CStatic *)GetDlgItem(IDC_STATIC_INFOR);
	
	iWidth = pISourOrig.size().width; 
	iHeight = pISourOrig.size().height;
	iSize = iWidth * iHeight;			

	// Tinh toan thong tin de scale hinh chuan bi hien thi
	iMaxSize = (iWidth > iHeight)? iWidth : iHeight;  
	fScale = (float) ( (float)iMaxSize / (float)mDisplayWindowSize );

	if(fScale == 0)
	{ 
		fScale = 1;
	}

	iDispWidth = (int)( (float)iWidth / fScale );
	iDispHeigh = (int)( (float)iHeight / fScale );
	iDispWPad = (mDisplayWindowSize - iDispWidth) / 2;
	iDispHPad = (mDisplayWindowSize - iDispHeigh) / 2;
	// ~Tinh toan thong tin de scale hinh chuan bi hien thi

	ShowImageOnIFace(pIDispOrig, pISourOrig,  iDispWPad, iDispHPad, iDispWidth, iDispHeigh, "SOURVIEW");	

	iCountFrm = 1;
	iIsProcess = 1;	

	dStartTime = (double)clock();
	while(iIsProcess == 1)
	{		
		bool bSuccess = pOViSour.read(pISourOrig);

		if (!bSuccess)
		{
			break;
		}

		iCountFrm++;

		if(iCountFrm == 480)
		{
			cv::imwrite("e:/video2_480.jpg", pISourOrig);
		}

		if(iCountFrm == 700)
		{
			cv::imwrite("e:/video2_700.jpg", pISourOrig);
		}

		// Xu ly chinh		
		cv::cvtColor(pISourOrig, pISourGrey, cv::COLOR_BGR2GRAY);
		std::vector<cv::Rect> aOHumanFound, aOFilteredHumanFound;
        oHogSVM.detectMultiScale(pISourGrey, aOHumanFound, 0, cv::Size(8,8), cv::Size(32,32), 1.05, 2, false);
		// ~Xu ly chinh
		
		dStopTime = (double)clock();
		dTime = dStopTime - dStartTime;

		// hien thi		
		size_t i, j;

        for (i = 0; i < aOHumanFound.size(); i++)
        {
            cv::Rect oRect = aOHumanFound[i];

            for (j = 0; j < aOHumanFound.size(); j++)
			{
                if ( (j != i) && ((oRect & aOHumanFound[j]) == oRect) )
				{
                    break;
				}
			}
            if (j == aOHumanFound.size())
			{
                aOFilteredHumanFound.push_back(oRect);
			}
        }

        for (i = 0; i < aOFilteredHumanFound.size(); i++)
        {
			cv::Rect oRect = aOFilteredHumanFound[i];
			oRect.x += cvRound(oRect.width * 0.1);
			oRect.width = cvRound(oRect.width * 0.8);
			oRect.y += cvRound(oRect.height * 0.07);
			oRect.height = cvRound(oRect.height * 0.8);
			rectangle(pISourOrig, oRect.tl(), oRect.br(), cv::Scalar(0,255,0), 2);
		}		

		sText.Format("Frame %d - FPS: %lf", iCountFrm, iCountFrm/(dTime / CLOCKS_PER_SEC));
		pLblInfor->SetWindowTextA(sText);		
		ShowImageOnIFace(pIDispOrig, pISourOrig, iDispWPad, iDispHPad, iDispWidth, iDispHeigh, "SOURVIEW");
		ShowImageOnIFace(pIDispGrey, pISourGrey, iDispWPad, iDispHPad, iDispWidth, iDispHeigh, "DESTVIEW");
		// ~hien thi
					
		cvWaitKey(5);		
	}
	
	// Thiet lap lai giao dien dieu khien
	iIsProcess = 0;
	pBtnCancel->EnableWindow(false);	
	// ~Thiet lap lai giao dien dieu khien

	// Giai phong bo nho	
	pOViSour.release();

	pIDispOrig.release();
	pISourGrey.release();
	pISourOrig.release();
	pIDispGrey.release();
	// ~Giai phong bo nho

ESCAPE:
	return;
}

void CVnPLibCVVideo3Dlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	iIsProcess = 0;
	cvWaitKey(100);
	destroyWindow("SOURVIEW");
	destroyWindow("DESTVIEW");
	CDialog::OnClose();
}

void CVnPLibCVVideo3Dlg::OnBnClickedCancelProcessBtn()
{
	// TODO: Add your control notification handler code here
	iIsProcess = 0;
	cvWaitKey(100);
}

void CVnPLibCVVideo3Dlg::OnBnClickedCamBrowserBtn()
{
	// TODO: Add your control notification handler code here
	if(iIsProcess > 0)
	{
		return;
	}

	int iCount=0;
	CListBox * pList;
	pList = (CListBox *)GetDlgItem(IDC_LIST_SOURCE_IMAGE);
	pList->ResetContent();
	VideoCapture vdoSour;
	CString sCamItem;	

	iCameraType = 0;
	AfxGetApp()->DoWaitCursor(1);
	while (iCount < 10)
	{				
		vdoSour.open(iCount);
		if (vdoSour.isOpened() == false)
		{
			break;
		}
		sCamItem.Format("Camera [ %d ]", iCount + 1);
		pList->AddString(sCamItem);
		iCount++;
		vdoSour.release();
	}	
	
	AfxGetApp()->DoWaitCursor(-1);

	if(iCount <= 0)
	{
		pList->AddString((CString)"No device found");
	}		
}
