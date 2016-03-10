
// VideoProducerDlg.h : header file
//

#pragma once


// CVideoProducerDlg dialog
class CVideoProducerDlg : public CDialogEx
{
// Construction
public:
	CVideoProducerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_VIDEOPRODUCER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonQuit();
	CString m_strSrcFile;
	CString m_strDstFile;
	CString m_strTimeStart;
	CString m_strTimeDuration;
	afx_msg void OnBnClickedButtonCut();
private:
	bool CheckFormatTime(const CString &strTime);
	void DropFiles(HDROP hDropInfo);
public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
};
