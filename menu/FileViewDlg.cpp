// FileViewDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "menu.h"
#include "FileViewDlg.h"
#include "afxdialogex.h"


// CFileViewDlg �Ի���

IMPLEMENT_DYNAMIC(CFileViewDlg, CDialogEx)

CFileViewDlg::CFileViewDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFileViewDlg::IDD, pParent)
{

}

CFileViewDlg::~CFileViewDlg()
{
}

void CFileViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFileViewDlg, CDialogEx)
END_MESSAGE_MAP()


// CFileViewDlg ��Ϣ�������
