#pragma once


// CFileViewDlg �Ի���

class CFileViewDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFileViewDlg)

public:
	CFileViewDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFileViewDlg();

// �Ի�������
	enum { IDD = IDD_FILEHANDLE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
