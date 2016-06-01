// FileViewDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "menu.h"
#include "FileViewDlg.h"
#include "afxdialogex.h"


// CFileViewDlg 对话框

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


// CFileViewDlg 消息处理程序
