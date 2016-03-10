
// VideoProducerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VideoProducer.h"
#include "VideoProducerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
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

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CVideoProducerDlg dialog




CVideoProducerDlg::CVideoProducerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CVideoProducerDlg::IDD, pParent)
	, m_strSrcFile(_T(""))
	, m_strDstFile(_T(""))
	, m_strTimeStart(_T("00:11:44"))
	, m_strTimeDuration(_T("00:24:14"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVideoProducerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SRC_FILE, m_strSrcFile);
	DDX_Text(pDX, IDC_EDIT_DST_FILE, m_strDstFile);
	DDX_Text(pDX, IDC_EDIT_TIME_START, m_strTimeStart);
	DDV_MaxChars(pDX, m_strTimeStart, 8);
	DDX_Text(pDX, IDC_EDIT_TIME_DURATION, m_strTimeDuration);
	DDV_MaxChars(pDX, m_strTimeDuration, 8);
}

BEGIN_MESSAGE_MAP(CVideoProducerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_QUIT, &CVideoProducerDlg::OnBnClickedButtonQuit)
	ON_BN_CLICKED(IDC_BUTTON_CUT, &CVideoProducerDlg::OnBnClickedButtonCut)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// CVideoProducerDlg message handlers

BOOL CVideoProducerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CVideoProducerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CVideoProducerDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CVideoProducerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CVideoProducerDlg::OnBnClickedButtonQuit()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}


void CVideoProducerDlg::OnBnClickedButtonCut()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	m_strSrcFile.Trim();
	m_strDstFile.Trim();
	m_strTimeStart.Trim();
	m_strTimeDuration.Trim();

	CString strTimeDuration;
	int nTimeSeconds(0);
	do{
		if(!CheckFormatTime(m_strTimeStart))
		{
			break;
		}

		if(CheckFormatTime(m_strTimeDuration))
		{
			if(m_strTimeDuration <= m_strTimeStart)
			{
				break;
			}
			else
			{
				nTimeSeconds = (StrToInt(m_strTimeDuration.Left(2)) * 60 * 60 + StrToInt(m_strTimeDuration.Mid(3, 2)) * 60 + StrToInt(m_strTimeDuration.Right(2)))
					- (StrToInt(m_strTimeStart.Left(2)) * 60 * 60 + StrToInt(m_strTimeStart.Mid(3, 2)) * 60 + StrToInt(m_strTimeStart.Right(2)));
			}
		}
		else
		{
			nTimeSeconds = StrToInt(m_strTimeDuration);
		}

	}while(false);

	if(nTimeSeconds > 0)
	{
		strTimeDuration.Format(_T("%02d:%d:%02d"),  nTimeSeconds / 60 / 60, (nTimeSeconds / 60) % 60, nTimeSeconds % 60);
		CString strCMD;
		strCMD.Format(_T("D:\\study\\tool\\ffmpeg\\bin\\ffmpeg.exe -ss %s -t %s -i \"%s\"  -vcodec copy -acodec copy \"%s\""),
			m_strTimeStart, strTimeDuration, m_strSrcFile, m_strDstFile);

		USES_CONVERSION;   
		CStringA cmd = W2A(strCMD);

		WinExec(cmd, SW_NORMAL);
	}
	else
	{
		MessageBox(_T("检查时间格式"), _T("格式错误"), MB_OK);
	}
	
}

bool CVideoProducerDlg::CheckFormatTime(const CString &strTime)
{
	bool bRet(false);

	do
	{
		if(strTime.GetLength() != 8)
		{
			break;
		}

		int i(0);
		for(; i < 8; ++i)
		{
			if(i == 2 || i == 5)
			{
				if( strTime.GetAt(i) != L':')
				{
					break;
				}
			}
			else
			{
				if( strTime.GetAt(i) < L'0' || strTime.GetAt(i) > L'9')
				{
					break;
				}
			}
		}

		if(i < 8)
		{
			break;
		}

		CString strNum = strTime.Mid(3, 2);

		int nNum1 = StrToInt(strNum);
		strNum = strTime.Mid(6, 2);
		int nNum2 = StrToInt(strNum);

		if(nNum1 >= 60 || nNum2 >= 60)
		{
			break;
		}

		if(StrToInt(strTime.Left(2)) >= 24)
		{
			break;
		}

		bRet = true;

	}while(false);

	return bRet;
}

void CVideoProducerDlg::DropFiles(HDROP hDropInfo)
{
	int DropCount=DragQueryFile(hDropInfo, -1, NULL, 0);//取得被拖动文件的数目
	if(DropCount > 0)
	{
		WCHAR wczFullName[MAX_PATH];  
		DragQueryFile(hDropInfo, 0, wczFullName, MAX_PATH);//获得拖曳的第i个文件的文件名
		CString strTemp, strExt;
		strTemp = wczFullName;
		m_strSrcFile = strTemp;
		m_strDstFile = m_strSrcFile + _T("_01");
		strExt = PathFindExtension(wczFullName);
		if(strExt.GetLength() > 0)
		{
			m_strDstFile = strTemp.Left(strTemp.GetLength() - strExt.GetLength());
			m_strDstFile += _T("_01");
			m_strDstFile += strExt;
		}
		UpdateData(FALSE);
	}
}

void CVideoProducerDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	DropFiles(hDropInfo);
	CDialogEx::OnDropFiles(hDropInfo);
}
