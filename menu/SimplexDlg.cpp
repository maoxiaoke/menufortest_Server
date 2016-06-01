// SimplexDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SimplexDlg.h"
#include "afxdialogex.h"
#include "SimplexFunction.h"
#include "TransRevShare.h"
#include "SystemParameter.h"
#include "menuDlg.h"


// CSimplexDlg �Ի���

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


// CSimplexDlg ��Ϣ�������


void CSimplexDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������

	CPen pen; //���廭�ʶ���
	CBrush brush; //�����ˢ����
	pen.CreatePen(PS_DASHDOT, 1, RGB(0, 0, 255)); //������ʼ������
	brush.CreateStockObject(NULL_BRUSH); //��ʼ��ʵ�ĵĿջ�ˢ��û�б�����ɫ��
	dc.SelectObject(&brush); //����ˢѡ��dc
	dc.SelectObject(&pen);  //������ѡ��dc
	dc.SetBkMode(TRANSPARENT); //���ñ���ģʽΪ͸����Ҳ����ʹ��SetBkColor���ñ���ɫ
	dc.Rectangle(15, 10, 500, 470); //����һ��͸�����ı���

	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
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

	hThread = CreateThread(NULL,
		0,
		(LPTHREAD_START_ROUTINE)ThreadFuncS,
		this,
		0,
		&ThreadID); //����һ���߳�

	return 0; //��������з���ֵ�ĺ�����������Ҫreturn 0
}
int CSimplexDlg::SetLedOffS(int a)
{
	CBitmap bitmap;
	HBITMAP hBmp;
	bitmap.LoadBitmap(IDB_BITMAP_GREY);
	hBmp = (HBITMAP)bitmap.GetSafeHandle();
	m_led1.SetBitmap(hBmp);
	m_led2.SetBitmap(hBmp);
	m_led3.SetBitmap(hBmp);
	m_led4.SetBitmap(hBmp);
	m_led5.SetBitmap(hBmp);
	m_led6.SetBitmap(hBmp);
	m_led7.SetBitmap(hBmp);


	return 0;
}
void ThreadFuncS(LPVOID lpParam)
{
	CSimplexDlg *pDlg = (CSimplexDlg*)lpParam;
	while (StopFlagS == 0)
	{
		if (StopFlagS == 1)
		{
			pDlg->SetLedOffS(1);
			break;
		}
		while (1)
		{
			Sleep(1000);
			state_inactiveR = 1;
			CBitmap bitmap;
			HBITMAP hBmp;
			bitmap.LoadBitmap(IDB_BITMAP_RED);
			hBmp = (HBITMAP)bitmap.GetSafeHandle();
			pDlg->m_led1.SetBitmap(hBmp);
			if (state_inactiveR == 1) break;
		}
		if (StopFlagS == 1)
		{
			pDlg->SetLedOffS(1);
			break;
		}
		while (1)
		{
			Sleep(1000);
			state_waithailR = 1;
			CBitmap bitmap;
			HBITMAP hBmp;
			bitmap.LoadBitmap(IDB_BITMAP_RED);
			hBmp = (HBITMAP)bitmap.GetSafeHandle();
			pDlg->m_led2.SetBitmap(hBmp);
			if (state_waithailR == 1) break;
		}
		if (StopFlagS == 1)
		{
			pDlg->SetLedOffS(1);
			break;
		}

		while (1)
		{
			if (CarrierSend_R == 1)
			{
				CarrierSend_R = 0;
				break;
			}
			if (StopFlagS == 1)
			{
				pDlg->SetLedOffS(1);
				return;
			}
		}

		while (1)
		{
			Sleep(1000);
			state_acquisitionR = 1;
			CBitmap bitmap;
			HBITMAP hBmp;
			bitmap.LoadBitmap(IDB_BITMAP_RED);
			hBmp = (HBITMAP)bitmap.GetSafeHandle();
			pDlg->m_led3.SetBitmap(hBmp);
			if (state_acquisitionR == 1) break;
		}
		if (StopFlagS == 1)
		{
			pDlg->SetLedOffS(1);
			break;
		}
		while (1)
		{
			Sleep(1000);
			state_simplexronR = 1;
			CBitmap bitmap;
			HBITMAP hBmp;
			bitmap.LoadBitmap(IDB_BITMAP_RED);
			hBmp = (HBITMAP)bitmap.GetSafeHandle();
			pDlg->m_led4.SetBitmap(hBmp);
			if (state_simplexronR == 1) break;
		}
		if (StopFlagS == 1)
		{
			pDlg->SetLedOffS(1);
			break;
		}
		while (1)
		{
			if (RNMD_R == 1)
			{
				RNMD_R = 0;
				break;
			}
			if (StopFlagS == 1)
			{
				pDlg->SetLedOffS(1);
				return;
			}
		}
		while (1)
		{
			Sleep(1000);
			state_rnmdendR = 1;
			CBitmap bitmap;
			HBITMAP hBmp;
			bitmap.LoadBitmap(IDB_BITMAP_RED);
			hBmp = (HBITMAP)bitmap.GetSafeHandle();
			pDlg->m_led5.SetBitmap(hBmp);

			SystemTimeS();  //���û�ȡϵͳʱ�亯��
			CmenuDlg *ppDlg = (CmenuDlg*)AfxGetApp()->m_pMainWnd;
			ppDlg->m_Hist.SetSel(ppDlg->m_Hist.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
			ppDlg->m_Hist.ReplaceSel(_T("���ݽ��ճɹ�\r\n"));

			if (state_rnmdendR == 1) break;
		}
		if (StopFlagS == 1)
		{
			pDlg->SetLedOffS(1);
			break;
		}
		while (1)
		{
			Sleep(1000);
			state_simplexrendR = 1;
			CBitmap bitmap;
			HBITMAP hBmp;
			bitmap.LoadBitmap(IDB_BITMAP_RED);
			hBmp = (HBITMAP)bitmap.GetSafeHandle();
			pDlg->m_led6.SetBitmap(hBmp);
			if (state_simplexrendR == 1) break;
		}
		if (StopFlagS == 1)
		{
			pDlg->SetLedOffS(1);
			break;
		}
		while (1)
		{
			Sleep(1000);
			state_terminatingtailR = 1;
			CBitmap bitmap;
			HBITMAP hBmp;
			bitmap.LoadBitmap(IDB_BITMAP_RED);
			hBmp = (HBITMAP)bitmap.GetSafeHandle();
			pDlg->m_led7.SetBitmap(hBmp);
			if (state_terminatingtailR == 1) break;
		}
		Sleep(2000);
		pDlg->SetLedOffS(1); //��LED���ú�
		break;
	}
}
void SystemTimeS()
{
	CString strTime;
	CTime tm;
	tm = CTime::GetCurrentTime(); //��ȡϵͳ��ǰʱ��
	strTime = tm.Format("%Y.%m.%d %X"); //��ʽת��
	CmenuDlg *ppDlg = (CmenuDlg*)AfxGetApp()->m_pMainWnd;
	//AfxGetMainWnd��Ӧ�ó������̵߳��ã����������Ϲ��򷵻�Ӧ�ó���������ڡ�����ú�����Ӧ�ó���Ĵ��̵߳��ã��ú�������������õ����߳����ӵ�������
	//		CmenuDlg *ppDlg = (CmenuDlg*)AfxGetMainWnd();
	ppDlg->m_Hist.SetSel(ppDlg->m_Hist.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
	ppDlg->m_Hist.ReplaceSel(strTime + "\r\n");
	//	return strTime;
}
