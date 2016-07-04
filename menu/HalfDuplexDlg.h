#pragma once
#include "afxwin.h"
#include "ParameterSet.h"
#include "StatusDisplayDlg.h"


// CHalfDuplexDlg 对话框
void ThreadFuncH(LPVOID lpParam); //类外声明线程函数

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
//	afx_msg void OnBnClickedOk();
	int SetLedOff(int a);
	int StartRunHalfDuplex(int a);
	void banshuanggongsend();
	void SystemTime(); //获取系统时间

	HBITMAP m_grey;  // 添加句柄变量
	HBITMAP m_red;

	CParameterSet *psHDlg;
	CStatusDisplayDlg * d_sdHDlg;  //半双工状态下访问StatusDisplay对话框  d = duplex
	void arqarray(int framecounter);
	void arqsend(int framecounter);

protected:
	HANDLE hThread; //线程句柄
	DWORD ThreadID; //线程ID

public:
	int state_inactiveH; //初始状态
	int state_waithailH;  //等待握手
	int state_starthailH; //开始载波同步
	int state_hailacquisitionH; // 开始符号同步
	int state_haildirectivesH; //发送握手指令
	int state_hailtailH;  //发送握手指令
	int state_hailresponseH;  //等待握手响应
	int state_carrieronlyH; //信道载波维持
	int state_acquisitionH;  //发送捕获序列
	int state_receiveDataH;  //接收数据
	int state_waitfirstframeH; //等待第一帧
	int state_waitcarrierH; // 等待载波
	int state_tailswitchH; //尾序列转换
	int state_tokenexchangeH; //状态转换
	int state_senddataH; //发送数据
	int state_responseendH; //终止应答
	int state_tailquitH; //结束尾序列

	int StopFlagH;

	int HalfDuplexState;			//当前全双工状态
	UINT oldTickCount, newTickCount;
};
