#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "resource.h"
//#include "ParameterSet.h"


// CStatusDisplayDlg �Ի���

class CStatusDisplayDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CStatusDisplayDlg)

public:
	CStatusDisplayDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CStatusDisplayDlg();

// �Ի�������
	enum { IDD = IDD_STATUSDISPLAY_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();

	CFont font;
//	CEdit m_ReceiveDataEdit;
//	CString m_ReceivedataEdit;
//	CEdit m_ReceiveDataEdit;

//	CParameterSet m_paraset;
//	afx_msg void OnBnClickedShowtextButton();
//	CEdit m_HistRceciveData;
	CEdit m_HistReceiveData;
	CEdit m_HistSendData;
	CEdit m_ResendFrameNumEdit;
	CEdit m_MissingFrameNumEdit;
};
