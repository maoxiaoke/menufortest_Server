#pragma once
#include "resource.h"
#include "afxwin.h"
#include "stdafx.h"
#include "ParameterSet.h"
#include "StatusDisplayDlg.h"

void ThreadFuncS(LPVOID lpParam); //���������̺߳���

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

	int SetLedOff(int a);
	int StartRunSimplex(int a);
<<<<<<< HEAD

	void SystemTime(); //��ȡϵͳʱ��
	UINT oldTickCount, newTickCount;
	HBITMAP m_grey;  // ��Ӿ������
	HBITMAP m_red;
	CFont font;

=======
	UINT oldTickCount, newTickCount;
	HBITMAP m_grey;  // ��Ӿ������
	HBITMAP m_red;

	CFont font;

	void SystemTime(); //��ȡϵͳʱ��
>>>>>>> dev
//	void dangongsend();

	CParameterSet *psSDlg;
	CStatusDisplayDlg * d_sdSDlg;  //��˫��״̬�·���StatusDisplay�Ի���  d = duplex
//	void arqarray(int framecounter);
//	void arqsend(int framecounter);

protected:
	HANDLE hThread; //�߳̾��
	DWORD ThreadID; //�߳�ID

public:
	int state_inactiveR;
	int state_waithailR;
	int state_hailacquisitionR;
	int state_haildirectivesR;
	int state_hailtailR;
	int state_hailresponseR;
	int state_carrieronlyR;
	int state_acquisitionR;
	int state_simplexronR;
	int state_lnmdendR;
	int state_rnmdendR;
	int state_simplexrendR;
	int state_terminatingtailR;
<<<<<<< HEAD
=======

>>>>>>> dev
	int StopFlagS;
	virtual BOOL OnInitDialog();
};
