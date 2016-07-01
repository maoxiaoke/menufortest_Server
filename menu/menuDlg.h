
// menuDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "ParameterSet.h"
#include "Duplex.h"
#include "StatusDisplayDlg.h"
#include "HalfDuplexDlg.h"
#include "SimplexDlg.h"

#include "ListenSocket.h"
#include "ServerSocket.h"


#include "SystemParameter.h"
#include "afxwin.h"



// CmenuDlg 对话框
class CmenuDlg : public CDialogEx
{
// 构造
public:
	CmenuDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MENU_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnOpen();
	
	CTabCtrl m_tab;
	//CString strfilepath;  //定义的加载配置字符串变量，因为对该字符串进行操作

	//添加标签控件对话框的类成员变量
	CDuplex m_duplex;
	CParameterSet m_parameterset;
	CStatusDisplayDlg m_statusdisplydlg;
	CHalfDuplexDlg m_halfduplexdlg;
	CSimplexDlg m_simplexdlg;
	CListenSocket m_ListenSocket;							//监听socket类的成员变量
	CServerSocket m_ServerSocket;							//监听客户端的连接请求而定义的socket成员变量

	void ModeChange(int i); //响应协议单元“协议工作方式”下拉框的变化
	bool quanshuanggong;
	bool banshuanggong;
	bool dangong;
	bool halfduplexExistFlag; //判断半双工tab页面是否存在标志
	bool simplexExistFlag;
	bool comboFirstChange; //

	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnLoadconfig();
	afx_msg void OnSave();
//	afx_msg void OnParaset();
//	CComboBox m_lala;
//	afx_msg void OnBnClickedOk();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
//	CBitmap bitmap;
//	CBitmap *pMenuBitmap;
//	afx_msg void OnUserguider();
	afx_msg void OnUserguider();
	afx_msg void OnLoadconfig();
//	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSaveconfig();
	afx_msg void OnBootsystem(); //启动系统
	void OperatingRecord();
	CEdit m_Hist; //操作记录
	bool runandstopflag; //启动、终止系统标识
	CIPAddressCtrl ServerIP;
	int sPort;
	afx_msg void OnBnClickedStartmonitorButton();

	CString SystemTime();
	afx_msg void OnBnClickedEndmonitorButton();
	CEdit m_ServerPort;
	CButton m_ListenButton;
	CButton m_ListenEndButton;

	void SendMessagepro(int *P_SE, int fLen); //发送消息
	CString m_sWords;
//	afx_msg void OnBnClickedSendButton();
	afx_msg void OnSendmail();
	afx_msg void OnStatusdisplay();
	afx_msg void OnParaset();

	CFont font;
	afx_msg void OnLogout();
	afx_msg void OnBnClickedCleanupButton();
};
