// ListenSocket.cpp : ʵ���ļ�
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


// CListenSocket ��Ա����


void CListenSocket::OnAccept(int nErrorCode)
{
	// TODO:  �ڴ����ר�ô����/����û���
	Accept(((CmenuDlg *)(AfxGetApp()->m_pMainWnd))->m_ServerSocket);//������������
	((CmenuDlg  *)(AfxGetApp()->m_pMainWnd))->m_ServerSocket.AsyncSelect(FD_READ | FD_CLOSE);

	ConnectOkFlag = 1;

	CString str;
	str = ((CmenuDlg  *)(AfxGetApp()->m_pMainWnd))->SystemTime();
	((CmenuDlg  *)(AfxGetApp()->m_pMainWnd))->m_Hist.SetSel(((CmenuDlg  *)(AfxGetApp()->m_pMainWnd))->m_Hist.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
	((CmenuDlg  *)(AfxGetApp()->m_pMainWnd))->m_Hist.ReplaceSel(str + "\r\n" + _T("������һ���ͻ��˵���������\r\n")); //�滻��ǰ�ı�

	//�ؼ�����

	CAsyncSocket::OnAccept(nErrorCode);
}
