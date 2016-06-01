#pragma once
#include "resource.h"
#include "afxwin.h"
#include "stdafx.h"
#include "ParameterSet.h"
#include "StatusDisplayDlg.h"

void ThreadFuncS(LPVOID lpParam); //类外声明线程函数
void SystemTimeS(); //获取系统时间

// CSimplexDlg 对话框

class CSimplexDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSimplexDlg)

public:
	CSimplexDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSimplexDlg();

// 对话框数据
	enum { IDD = IDD_SIMPLEX_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
	CStatusDisplayDlg * d_sdSDlg;  //半双工状态下访问StatusDisplay对话框  d = duplex
//	void arqarray(int framecounter);
//	void arqsend(int framecounter);

protected:
	HANDLE hThread; //线程句柄
	DWORD ThreadID; //线程ID
};
