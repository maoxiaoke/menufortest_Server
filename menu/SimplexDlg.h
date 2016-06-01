#pragma once
#include "resource.h"
#include "afxwin.h"
#include "stdafx.h"
#include "ParameterSet.h"
#include "StatusDisplayDlg.h"

void ThreadFuncS(LPVOID lpParam); //���������̺߳���
void SystemTimeS(); //��ȡϵͳʱ��

// CSimplexDlg �Ի���

class CSimplexDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSimplexDlg)

public:
	CSimplexDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSimplexDlg();

// �Ի�������
	enum { IDD = IDD_SIMPLEX_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	CStatic m_led1;
	CStatic m_led2;
	CStatic m_led3;
	CStatic m_led4;
	CStatic m_led5;
	CStatic m_led6;
	CStatic m_led7;

	int SetLedOffS(int a);
	int StartRunSimplex(int a);
//	void dangongsend();

	CParameterSet *psSDlg;
	CStatusDisplayDlg * d_sdSDlg;  //��˫��״̬�·���StatusDisplay�Ի���  d = duplex
//	void arqarray(int framecounter);
//	void arqsend(int framecounter);

protected:
	HANDLE hThread; //�߳̾��
	DWORD ThreadID; //�߳�ID
};
