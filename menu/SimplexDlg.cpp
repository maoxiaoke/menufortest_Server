// SimplexDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SimplexDlg.h"
#include "afxdialogex.h"
//#include "SimplexFunction.h"
#include "TransRevShare.h"
#include "SystemParameter.h"
#include "menuDlg.h"


// CSimplexDlg 对话框

IMPLEMENT_DYNAMIC(CSimplexDlg, CDialogEx)

CSimplexDlg::CSimplexDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSimplexDlg::IDD, pParent)
{

}

CSimplexDlg::~CSimplexDlg()
{
}

void CSimplexDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LED1_STATIC, m_led1);
	DDX_Control(pDX, IDC_LED2_STATIC, m_led2);
	DDX_Control(pDX, IDC_LED3_STATIC, m_led3);
	DDX_Control(pDX, IDC_LED4_STATIC, m_led4);
	DDX_Control(pDX, IDC_LED50_STATIC, m_led5);
	DDX_Control(pDX, IDC_LED60_STATIC, m_led6);
	DDX_Control(pDX, IDC_LED70_STATIC, m_led7);
}


BEGIN_MESSAGE_MAP(CSimplexDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CSimplexDlg 消息处理程序


void CSimplexDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码

	CPen pen; //定义画笔对象
	CBrush brush; //定义笔刷对象
	pen.CreatePen(PS_DASHDOT, 1, RGB(0, 0, 255)); //创建初始化画笔
	brush.CreateStockObject(NULL_BRUSH); //初始化实心的空画刷（没有背景颜色）
	dc.SelectObject(&brush); //将画刷选入dc
	dc.SelectObject(&pen);  //将画笔选入dc
	dc.SetBkMode(TRANSPARENT); //设置背景模式为透明，也可以使用SetBkColor设置背景色
	dc.Rectangle(15, 20, 500, 430); //创建一个透明的文本框

	// 不为绘图消息调用 CDialogEx::OnPaint()
}

int CSimplexDlg::StartRunSimplex(int a)
{
	state_inactiveR = 0;
	state_waithailR = 0;
	state_hailacquisitionR = 0;
	state_haildirectivesR = 0;
	state_hailtailR = 0;
	state_hailresponseR = 0;
	state_carrieronlyR = 0;
	state_acquisitionR = 0;
	state_simplexronR = 0;
	state_lnmdendR = 0;
	state_rnmdendR = 0;
	state_simplexrendR = 0;
	state_terminatingtailR = 0;

	int StopFlagS = 0;

	SetLedOff(1);
	Sleep(1000);
	state_inactiveR = 1;   //初始状态
	m_led1.SetBitmap(m_red);

	hThread = CreateThread(NULL,
		0,
		(LPTHREAD_START_ROUTINE)ThreadFuncS,
		this,
		0,
		&ThreadID); //开辟一个线程

	return 0; //定义的是有返回值的函数，所以需要return 0
}
int CSimplexDlg::SetLedOff(int a)
{

	m_led1.SetBitmap(m_grey);
	m_led2.SetBitmap(m_grey);
	m_led3.SetBitmap(m_grey);
	m_led4.SetBitmap(m_grey);
	m_led5.SetBitmap(m_grey);
	m_led6.SetBitmap(m_grey);
	m_led7.SetBitmap(m_grey);


	return 0;
}
void ThreadFuncS(LPVOID lpParam)
{
	CSimplexDlg *pDlg = (CSimplexDlg*)lpParam;
	CmenuDlg *ppDlg = (CmenuDlg*)AfxGetApp()->m_pMainWnd;

	while (1)
	{
		pDlg->state_waithailR = 1;
		pDlg->SystemTime();
		ppDlg->m_Hist.SetSel(ppDlg->m_Hist.GetWindowTextLength(), -1); //获取当前编辑框字符
		ppDlg->m_Hist.ReplaceSel(_T("Waiting for Hail.\r\n"));
		pDlg->m_led2.SetBitmap(pDlg->m_red);
		Sleep(1000);

		pDlg->oldTickCount = GetTickCount();
		while (1)
		{
			pDlg->newTickCount = GetTickCount();
			if (CarrierSend_R)
			{
				CarrierSend_R = 0;
				break;
			}
			if ((pDlg->newTickCount - pDlg->oldTickCount) >= 60000)
			{
				break;
			}
		}

		pDlg->state_acquisitionR = 1;
		pDlg->SystemTime();
		ppDlg->m_Hist.SetSel(ppDlg->m_Hist.GetWindowTextLength(), -1); //获取当前编辑框字符
		ppDlg->m_Hist.ReplaceSel(_T("Receiving Hail Acquisition.\r\n"));
		pDlg->m_led3.SetBitmap(pDlg->m_red);
		Sleep(500);

		pDlg->state_simplexronR = 1;
		pDlg->SystemTime();
		ppDlg->m_Hist.SetSel(ppDlg->m_Hist.GetWindowTextLength(), -1); //获取当前编辑框字符
		ppDlg->m_Hist.ReplaceSel(_T("Data Service Receive.\r\n"));
		pDlg->m_led4.SetBitmap(pDlg->m_red);
//		Sleep(1000);

		pDlg->oldTickCount = GetTickCount();
		while (1)
		{
			pDlg->newTickCount = GetTickCount();
			if (RNMD_R)
			{
				RNMD_R = 0;
				break;
			}
			if ((pDlg->newTickCount - pDlg->oldTickCount) >= 120000)
			{
				break;
			}
		}
		pDlg->state_rnmdendR = 1;
		pDlg->SystemTime();
		ppDlg->m_Hist.SetSel(ppDlg->m_Hist.GetWindowTextLength(), -1); //获取当前编辑框字符
		ppDlg->m_Hist.ReplaceSel(_T("Receive RNMD.\r\n"));
		pDlg->m_led5.SetBitmap(pDlg->m_red);

		pDlg->state_simplexrendR = 1;
		pDlg->SystemTime();
		ppDlg->m_Hist.SetSel(ppDlg->m_Hist.GetWindowTextLength(), -1); //获取当前编辑框字符
		ppDlg->m_Hist.ReplaceSel(_T("Data Service End.\r\n"));
		pDlg->m_led6.SetBitmap(pDlg->m_red);
		Sleep(2000);

		pDlg->state_terminatingtailR = 1;
		pDlg->SystemTime();
		ppDlg->m_Hist.SetSel(ppDlg->m_Hist.GetWindowTextLength(), -1); //获取当前编辑框字符
		ppDlg->m_Hist.ReplaceSel(_T("Terminating Tail.\r\n"));
		pDlg->m_led7.SetBitmap(pDlg->m_red);

		Sleep(2000);
		pDlg->SetLedOff(1);

		break;
	}
}

//void ThreadFuncS(LPVOID lpParam)
//{
//	CSimplexDlg *pDlg = (CSimplexDlg*)lpParam;
//	while (StopFlagS == 0)
//	{
//		if (StopFlagS == 1)
//		{
//			pDlg->SetLedOffS(1);
//			break;
//		}
//		while (1)
//		{
//			Sleep(1000);
//			state_inactiveR = 1;
//			CBitmap bitmap;
//			HBITMAP hBmp;
//			bitmap.LoadBitmap(IDB_BITMAP_RED);
//			hBmp = (HBITMAP)bitmap.GetSafeHandle();
//			pDlg->m_led1.SetBitmap(hBmp);
//			if (state_inactiveR == 1) break;
//		}
//		if (StopFlagS == 1)
//		{
//			pDlg->SetLedOffS(1);
//			break;
//		}
//		while (1)
//		{
//			Sleep(1000);
//			state_waithailR = 1;
//			CBitmap bitmap;
//			HBITMAP hBmp;
//			bitmap.LoadBitmap(IDB_BITMAP_RED);
//			hBmp = (HBITMAP)bitmap.GetSafeHandle();
//			pDlg->m_led2.SetBitmap(hBmp);
//			if (state_waithailR == 1) break;
//		}
//		if (StopFlagS == 1)
//		{
//			pDlg->SetLedOffS(1);
//			break;
//		}
//
//		while (1)
//		{
//			if (CarrierSend_R == 1)
//			{
//				CarrierSend_R = 0;
//				break;
//			}
//			if (StopFlagS == 1)
//			{
//				pDlg->SetLedOffS(1);
//				return;
//			}
//		}
//
//		while (1)
//		{
//			Sleep(1000);
//			state_acquisitionR = 1;
//			CBitmap bitmap;
//			HBITMAP hBmp;
//			bitmap.LoadBitmap(IDB_BITMAP_RED);
//			hBmp = (HBITMAP)bitmap.GetSafeHandle();
//			pDlg->m_led3.SetBitmap(hBmp);
//			if (state_acquisitionR == 1) break;
//		}
//		if (StopFlagS == 1)
//		{
//			pDlg->SetLedOffS(1);
//			break;
//		}
//		while (1)
//		{
//			Sleep(1000);
//			state_simplexronR = 1;
//			CBitmap bitmap;
//			HBITMAP hBmp;
//			bitmap.LoadBitmap(IDB_BITMAP_RED);
//			hBmp = (HBITMAP)bitmap.GetSafeHandle();
//			pDlg->m_led4.SetBitmap(hBmp);
//			if (state_simplexronR == 1) break;
//		}
//		if (StopFlagS == 1)
//		{
//			pDlg->SetLedOffS(1);
//			break;
//		}
//		while (1)
//		{
//			if (RNMD_R == 1)
//			{
//				RNMD_R = 0;
//				break;
//			}
//			if (StopFlagS == 1)
//			{
//				pDlg->SetLedOffS(1);
//				return;
//			}
//		}
//		while (1)
//		{
//			Sleep(1000);
//			state_rnmdendR = 1;
//			CBitmap bitmap;
//			HBITMAP hBmp;
//			bitmap.LoadBitmap(IDB_BITMAP_RED);
//			hBmp = (HBITMAP)bitmap.GetSafeHandle();
//			pDlg->m_led5.SetBitmap(hBmp);
//
//			SystemTimeS();  //调用获取系统时间函数
//			CmenuDlg *ppDlg = (CmenuDlg*)AfxGetApp()->m_pMainWnd;
//			ppDlg->m_Hist.SetSel(ppDlg->m_Hist.GetWindowTextLength(), -1); //获取当前编辑框字符
//			ppDlg->m_Hist.ReplaceSel(_T("数据接收成功\r\n"));
//
//			if (state_rnmdendR == 1) break;
//		}
//		if (StopFlagS == 1)
//		{
//			pDlg->SetLedOffS(1);
//			break;
//		}
//		while (1)
//		{
//			Sleep(1000);
//			state_simplexrendR = 1;
//			CBitmap bitmap;
//			HBITMAP hBmp;
//			bitmap.LoadBitmap(IDB_BITMAP_RED);
//			hBmp = (HBITMAP)bitmap.GetSafeHandle();
//			pDlg->m_led6.SetBitmap(hBmp);
//			if (state_simplexrendR == 1) break;
//		}
//		if (StopFlagS == 1)
//		{
//			pDlg->SetLedOffS(1);
//			break;
//		}
//		while (1)
//		{
//			Sleep(1000);
//			state_terminatingtailR = 1;
//			CBitmap bitmap;
//			HBITMAP hBmp;
//			bitmap.LoadBitmap(IDB_BITMAP_RED);
//			hBmp = (HBITMAP)bitmap.GetSafeHandle();
//			pDlg->m_led7.SetBitmap(hBmp);
//			if (state_terminatingtailR == 1) break;
//		}
//		Sleep(2000);
//		pDlg->SetLedOffS(1); //将LED灯置黑
//		break;
//	}
//}
void CSimplexDlg::SystemTime()
{
	CString strTime;
	CTime tm;
	tm = CTime::GetCurrentTime(); //获取系统当前时间
	strTime = tm.Format("%Y.%m.%d %X"); //格式转换
	CmenuDlg *ppDlg = (CmenuDlg*)AfxGetApp()->m_pMainWnd;
	//AfxGetMainWnd被应用程序主线程调用，它根据以上规则返回应用程序的主窗口。如果该函数被应用程序的次线程调用，该函数返回与引起该调用线程连接的主窗口
	//		CmenuDlg *ppDlg = (CmenuDlg*)AfxGetMainWnd();
	ppDlg->m_Hist.SetSel(ppDlg->m_Hist.GetWindowTextLength(), -1); //获取当前编辑框字符
	ppDlg->m_Hist.ReplaceSel(strTime + "\r\n");
	//	return strTime;
}


BOOL CSimplexDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	font.CreatePointFont(110, _T("微软雅黑")); //创建字体样式，传递110请求11点字体
	GetDlgItem(IDC_SIMPLEXPROCEDURES_STATIC)->SetFont(&font); //将字体传递给静态框

	m_grey = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_GREY));
	m_red = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_RED));
	//AfxGetInstanceHandle():This function allows you to retrieve (取回) the instance handle of the current application.
	//MAKEINTRESOURCE macro (宏):Converts an integer value to a resource type compatible with the resource-management functions. This macro is used in place of a string containing the name of the resource.
	/*********初始led灯为灰色**********/
	m_led1.SetBitmap(m_grey);
	m_led2.SetBitmap(m_grey);
	m_led3.SetBitmap(m_grey);
	m_led4.SetBitmap(m_grey);
	m_led5.SetBitmap(m_grey);
	m_led6.SetBitmap(m_grey);
	m_led7.SetBitmap(m_grey);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
