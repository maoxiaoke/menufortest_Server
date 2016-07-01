#pragma once
#include "afxwin.h"
#include "ParameterSet.h"

//UINT ThreadFunc(LPVOID lpParam);
void ThreadFunc(LPVOID lpParam); //类外声明线程函数


// CDuplex 对话框

class CDuplex : public CDialogEx
{
	DECLARE_DYNAMIC(CDuplex)

public:
	CDuplex(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDuplex();

// 对话框数据
	enum { IDD = IDD_DUPLEX_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
//	afx_msg void OnBnClickedOk();
	int SetLedOff(int a);
	CStatic m_led4;
	afx_msg void OnPaint();

	int StartRunDuplex(int a);
	void shuanggongsend();
	void SystemTime(); //获取系统时间

	HBITMAP m_grey;  // 添加句柄变量
	HBITMAP m_red;
	CFont font;


protected:
	HANDLE hThread; //线程句柄
	DWORD ThreadID; //线程ID

public:
//	CEdit m_histrecord;
	CParameterSet *psDlg;
	CStatusDisplayDlg * d_sdDlg;  //双工状态下访问StatusDisplay对话框  d = duplex
	void arqarray(int framecounter);
	void arqsend(int framecounter);
//	CEdit m_Text;
	int state_inactive;  //初始等待
	int state_waithail;    //等待握手
	int state_starthail;   //开始载波同步
	int state_hailacquisition;   //开始符号同步
	int state_haildirectives;     //发送握手指令
	int state_hailtail;                //发送握手尾序列
	int state_hailresponse;   //等待握手响应
	int state_carrieronly;       //信道载波维持
	int state_acquisition;     //发送捕获序列
	int state_duplexon;          //双向数据传递
	int state_rnmdend;         //远程发送成功
	int state_lnmdend;           //本地发送成功
	int state_duplexend;       //双向数据传递完成
	int state_terminatingtail;   //尾序列
	int StopFlag;  //强制停止的标志变量 ?

	int lnmdsign;						//本地发送完成标志
	int rnmdsign;					//远程发送完成标志

	int DuplexState;			//当前全双工状态
	virtual BOOL OnInitDialog();
	UINT oldTickCount, newTickCount;
};
