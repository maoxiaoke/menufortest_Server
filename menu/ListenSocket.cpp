// ListenSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "ListenSocket.h"
#include "menuDlg.h"
#include "TransRevShare.h"


// CListenSocket

CListenSocket::CListenSocket()
{
}

CListenSocket::~CListenSocket()
{
}


// CListenSocket 成员函数


void CListenSocket::OnAccept(int nErrorCode)
{
	// TODO:  在此添加专用代码和/或调用基类
	Accept(((CmenuDlg *)(AfxGetApp()->m_pMainWnd))->m_ServerSocket);//接受连接请求
	((CmenuDlg  *)(AfxGetApp()->m_pMainWnd))->m_ServerSocket.AsyncSelect(FD_READ | FD_CLOSE);

	ConnectOkFlag = 1;

	CString str;
	str = ((CmenuDlg  *)(AfxGetApp()->m_pMainWnd))->SystemTime();
	((CmenuDlg  *)(AfxGetApp()->m_pMainWnd))->m_Hist.SetSel(((CmenuDlg  *)(AfxGetApp()->m_pMainWnd))->m_Hist.GetWindowTextLength(), -1); //获取当前编辑框字符
	((CmenuDlg  *)(AfxGetApp()->m_pMainWnd))->m_Hist.ReplaceSel(str + "\r\n" + _T("接收了一个客户端的连接请求\r\n")); //替换当前文本

	//控件禁用

	CAsyncSocket::OnAccept(nErrorCode);
}
