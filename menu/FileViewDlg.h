#pragma once


// CFileViewDlg 对话框

class CFileViewDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFileViewDlg)

public:
	CFileViewDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFileViewDlg();

// 对话框数据
	enum { IDD = IDD_FILEHANDLE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
