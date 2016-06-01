#pragma once
#include "afxwin.h"
#include "ParameterSet.h"

void ThreadFunc(LPVOID lpParam); //���������̺߳���
void SystemTime(); //��ȡϵͳʱ��

// CDuplex �Ի���

class CDuplex : public CDialogEx
{
	DECLARE_DYNAMIC(CDuplex)

public:
	CDuplex(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDuplex();

// �Ի�������
	enum { IDD = IDD_DUPLEX_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_led1;
	CStatic m_led2;
	CStatic m_led3;
	CStatic m_led6;
	CStatic m_led5;
	CStatic m_led7;
	CStatic m_led8;
	CStatic m_led9;
	CStatic m_led10;
	CStatic m_led11;
	CStatic m_led12;
	CStatic m_led13;
	CStatic m_led14;
	afx_msg void OnBnClickedOk();
	int SetLedOff(int a);
	CStatic m_led4;
	afx_msg void OnPaint();

	int StartRunDuplex(int a);
	void shuanggongsend();

	

protected:
	HANDLE hThread; //�߳̾��
	DWORD ThreadID; //�߳�ID

public:
//	CEdit m_histrecord;
	CParameterSet *psDlg;
	CStatusDisplayDlg * d_sdDlg;  //˫��״̬�·���StatusDisplay�Ի���  d = duplex
	void arqarray(int framecounter);
	void arqsend(int framecounter);
//	CEdit m_Text;
};
