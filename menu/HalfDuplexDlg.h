#pragma once
#include "afxwin.h"
#include "ParameterSet.h"
#include "StatusDisplayDlg.h"


// CHalfDuplexDlg 对话框
void ThreadFuncH(LPVOID lpParam); //类外声明线程函数
void SystemTimeH(); //获取系统时间

class CHalfDuplexDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHalfDuplexDlg)

public:
	CHalfDuplexDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CHalfDuplexDlg();

	// 对话框数据
	enum { IDD = IDD_HALFDUPLEX_DIALOG };

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
	CStatic m_led8;
	CStatic m_led9;
	CStatic m_led10;
	CStatic m_led11;
	CStatic m_led12;
	//	CStatic led13;
	CStatic m_led14;
	CStatic m_led15;
	CStatic m_led16;
	CStatic m_led17;
	virtual BOOL OnInitDialog();
	CStatic m_led13;
	afx_msg void OnBnClickedOk();
	int SetLedOffH(int a);
	int StartRunHalfDuplex(int a);
	void banshuanggongsend();

	CParameterSet *psHDlg;
	CStatusDisplayDlg * d_sdHDlg;  //半双工状态下访问StatusDisplay对话框  d = duplex
	void arqarray(int framecounter);
	void arqsend(int framecounter);

protected:
	HANDLE hThread; //线程句柄
	DWORD ThreadID; //线程ID
};
