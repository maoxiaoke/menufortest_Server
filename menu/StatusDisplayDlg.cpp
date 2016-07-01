// StatusDisplayDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "menu.h"
#include "StatusDisplayDlg.h"
#include "afxdialogex.h"
#include "ParameterSet.h"


// CStatusDisplayDlg 对话框

IMPLEMENT_DYNAMIC(CStatusDisplayDlg, CDialogEx)

CStatusDisplayDlg::CStatusDisplayDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CStatusDisplayDlg::IDD, pParent)
//	, m_ReceivedataEdit(_T(""))
{

}

CStatusDisplayDlg::~CStatusDisplayDlg()
{
}

void CStatusDisplayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_RECEIVEDATA_EDIT, m_ReceiveDataEdit);
	//  DDX_Text(pDX, IDC_RECEIVEDATA_EDIT, m_ReceivedataEdit);
	//  DDX_Control(pDX, IDC_RECEIVEDATA_EDIT, m_ReceiveDataEdit);
	//  DDX_Control(pDX, IDC_RECEIVEDATA_EDIT, m_HistRceciveData);
	DDX_Control(pDX, IDC_RECEIVEDATA_EDIT, m_HistReceiveData);
	DDX_Control(pDX, IDC_SENDDATA_EDIT, m_HistSendData);
	DDX_Control(pDX, IDC_RESEND_FRAME_NUM_EDIT, m_ResendFrameNumEdit);
	DDX_Control(pDX, IDC_MISSING_FRAME_NUM_EDIT, m_MissingFrameNumEdit);
}


BEGIN_MESSAGE_MAP(CStatusDisplayDlg, CDialogEx)
	ON_WM_PAINT()
//	ON_BN_CLICKED(IDC_SHOWTEXT_BUTTON, &CStatusDisplayDlg::OnBnClickedShowtextButton)
END_MESSAGE_MAP()


// CStatusDisplayDlg 消息处理程序


void CStatusDisplayDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()

	CPen pen[3]; //定义画笔对象
	CBrush brush[2]; //定义笔刷对象
	pen[0].CreatePen(PS_DASHDOT, 1, RGB(0, 0, 255)); //创建初始化画笔
	brush[0].CreateStockObject(NULL_BRUSH); //初始化实心的空画刷（没有背景颜色）
	dc.SelectObject(&brush[0]); //将画刷选入dc
	dc.SelectObject(&pen[0]);  //将画笔选入dc
	dc.SetBkMode(TRANSPARENT); //设置背景模式为透明，也可以使用SetBkColor设置背景色
	dc.Rectangle(15, 20, 500, 310); //创建一个透明的文本框
	//pen[0].DeleteObject(); //释放dc
	//brush[0].DeleteObject();  //注释掉这个为什么也可以？难道用完就释放了

	pen[1].CreatePen(PS_DASHDOT, 1, RGB(0, 0, 255)); //创建初始化画笔
	dc.SelectObject(&pen[1]);  //将画刷选入dc
	dc.MoveTo(15, 165); //画直线
	dc.LineTo(500, 165); //画直线
	//	pen[1].DeleteObject();

	pen[2].CreatePen(PS_DASHDOT, 1, RGB(0, 0, 255)); //创建初始化画笔
	brush[1].CreateStockObject(NULL_BRUSH); //初始化实心的空画刷（没有背景颜色）
	dc.SelectObject(&brush[1]); //将画刷选入dc
	dc.SelectObject(&pen[2]);  //将画笔选入dc
	dc.SetBkMode(TRANSPARENT); //设置背景模式为透明，也可以使用SetBkColor设置背景色
	dc.Rectangle(15, 318, 500, 430); //创建一个透明的文本框
	//pen[2].DeleteObject(); //释放dc
	//brush[1].DeleteObject();  //注释掉这个为什么也可以？难道用完就释放了

	
}


BOOL CStatusDisplayDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	/********************************设置字体******************************************/
	font.CreatePointFont(120, _T("微软雅黑")); //创建字体样式，传递120请求12点字体
	GetDlgItem(IDC_SENDDATA_STATIC)->SetFont(&font); //将字体传递给静态框
	GetDlgItem(IDC_RECEIVEDATA_STATIC)->SetFont(&font); //将字体传递给静态框

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


//void CStatusDisplayDlg::OnBnClickedShowtextButton()
//{
//	// TODO:  在此添加控件通知处理程序代码
///*	CString strFilePath;
//	m_paraset.m_SendSoucerEdit.GetWindowText(strFilePath);
//	CFile file(strFilePath, CFile::modeRead | CFile::typeBinary);
//	char *pBuf;
//	DWORD dwFileLen;
//	dwFileLen = file.GetLength();
//	pBuf = new char[dwFileLen + 1];
//	pBuf[dwFileLen] = 0;
//	file.Read(pBuf, dwFileLen);
//
//	CString strDisplay;
//	for (int i = 0; (size_t)i < dwFileLen; i++) //size_t只是为了提高可移植性
//	{
//		strDisplay += pBuf[i];
//
//	}
//	SetDlgItemText(IDC_RECEIVEDATA_EDIT, strDisplay);
//	file.Close();
//	delete[]pBuf;
//	*/
//}
