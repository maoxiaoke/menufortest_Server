// HalfDuplexDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "menu.h"
#include "HalfDuplexDlg.h"
#include "afxdialogex.h"
#include "HalfDuplexFunction.h"
#include "menuDlg.h"
#include "TransRevShare.h"
#include "SystemParameter.h"
#include "encode.h"
#include "Framing.h"


// CHalfDuplexDlg �Ի���

IMPLEMENT_DYNAMIC(CHalfDuplexDlg, CDialogEx)

CHalfDuplexDlg::CHalfDuplexDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CHalfDuplexDlg::IDD, pParent)
{

}

CHalfDuplexDlg::~CHalfDuplexDlg()
{
}

void CHalfDuplexDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LED1_STATIC, m_led1);
	DDX_Control(pDX, IDC_LED2_STATIC, m_led2);
	DDX_Control(pDX, IDC_LED3_STATIC, m_led3);
	DDX_Control(pDX, IDC_LED4_STATIC, m_led4);
	DDX_Control(pDX, IDC_LED5_STATIC, m_led5);
	DDX_Control(pDX, IDC_LED6_STATIC, m_led6);
	DDX_Control(pDX, IDC_LED7_STATIC, m_led7);
	DDX_Control(pDX, IDC_LED8_STATIC, m_led8);
	DDX_Control(pDX, IDC_LED9_STATIC, m_led9);
	DDX_Control(pDX, IDC_LED10_STATIC, m_led10);
	DDX_Control(pDX, IDC_LED11_STATIC, m_led11);
	DDX_Control(pDX, IDC_LED12_STATIC, m_led12);
	//  DDX_Control(pDX, IDC_LED13_STATIC, led13);
	DDX_Control(pDX, IDC_LED14_STATIC, m_led14);
	DDX_Control(pDX, IDC_LED15_STATIC, m_led15);
	DDX_Control(pDX, IDC_LED16_STATIC, m_led16);
	DDX_Control(pDX, IDC_LED17_STATIC, m_led17);
	DDX_Control(pDX, IDC_LED13_STATIC, m_led13);
}


BEGIN_MESSAGE_MAP(CHalfDuplexDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDOK, &CHalfDuplexDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CHalfDuplexDlg ��Ϣ�������


void CHalfDuplexDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()

	CPen pen; //���廭�ʶ���
	CBrush brush; //�����ˢ����
	pen.CreatePen(PS_DASHDOT, 1, RGB(0, 0, 255)); //������ʼ������
	brush.CreateStockObject(NULL_BRUSH); //��ʼ��ʵ�ĵĿջ�ˢ��û�б�����ɫ��
	dc.SelectObject(&brush); //����ˢѡ��dc
	dc.SelectObject(&pen);  //������ѡ��dc
	dc.SetBkMode(TRANSPARENT); //���ñ���ģʽΪ͸����Ҳ����ʹ��SetBkColor���ñ���ɫ
	dc.Rectangle(15, 20, 500, 430); //����һ��͸�����ı���
}


BOOL CHalfDuplexDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��


	//


	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


/*========================================*/
/*                                          ������˫��ģʽ                                            */
/*=======================================*/
int CHalfDuplexDlg::StartRunHalfDuplex(int a)
{
	state_inactiveH = 0; //��ʼ״̬
	state_waithailH = 0;  //�ȴ�����
	state_starthailH = 0; //��ʼ�ز�ͬ��
	state_hailacquisitionH = 0; // ��ʼ����ͬ��
	state_haildirectivesH = 0; //��������ָ��
	state_hailtailH = 0;  //��������ָ��
	state_hailresponseH = 0;  //�ȴ�������Ӧ
	state_carrieronlyH = 0; //�ŵ��ز�ά��
	state_acquisitionH = 0;  //���Ͳ�������
	state_receiveDataH = 0;  //��������
	state_waitfirstframeH = 0; //�ȴ���һ֡
	state_waitcarrierH = 0; // �ȴ��ز�
	state_tailswitchH = 0; //β����ת��
	state_tokenexchangeH = 0; //״̬ת��
	state_senddataH = 0; //��������
	state_responseendH = 0;
	state_tailquitH = 0; //����β����

	StopFlagH = 0;

	hThread = CreateThread(NULL,
		0,
		(LPTHREAD_START_ROUTINE)ThreadFuncH,
		this,
		0,
		&ThreadID); //����һ���߳�

	return 0; //��������з���ֵ�ĺ�����������Ҫreturn 0
}

void CHalfDuplexDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������


	hThread = CreateThread(NULL,
		0,
		(LPTHREAD_START_ROUTINE)ThreadFuncH,
		this,
		0,
		&ThreadID);
	/*
	state_inactiveH = 0; //��ʼ״̬
	state_waithailH = 0;  //�ȴ�����
	state_starthailH = 0; //��ʼ�ز�ͬ��
	state_hailacquisitionH = 0; // ��ʼ����ͬ��
	state_haildirectivesH = 0; //��������ָ��
	state_hailtailH = 0;  //��������ָ��
	state_hailresponseH = 0;  //�ȴ�������Ӧ
	state_carrieronlyH = 0; //�ŵ��ز�ά��
	state_acquisitionH = 0;  //���Ͳ�������
	state_receiveDataH = 0;  //��������
	state_waitfirstframeH = 0; //�ȴ���һ֡
	state_waitcarrierH = 0; // �ȴ��ز�
	state_tailswitchH = 0; //β����ת��
	state_tokenexchangeH = 0; //״̬ת��
	state_senddataH = 0; //��������
	state_responseendH = 0;
	state_tailquitH = 0; //����β����

	StopFlagH = 0;

	// SetLedOffH(1);
	//	Sleep(1000);
	while (StopFlagH == 0)
	{
	if (StopFlagH == 1)
	{
	SetLedOffH(1);
	break;
	}
	while (1)
	{
	Sleep(1000);
	state_inactiveH = 1;
	CBitmap bitmap;
	HBITMAP hBmp;
	bitmap.LoadBitmap(IDB_BITMAP_RED);
	hBmp = (HBITMAP)bitmap.GetSafeHandle();
	m_led1.SetBitmap(hBmp);
	if (state_inactiveH == 1) break;
	}
	if (StopFlagH == 1)
	{
	SetLedOffH(1);
	break;
	}
	while (1)
	{
	Sleep(1000);
	state_waithailH = 1;
	CBitmap bitmap;
	HBITMAP hBmp;
	bitmap.LoadBitmap(IDB_BITMAP_RED);
	hBmp = (HBITMAP)bitmap.GetSafeHandle();
	m_led2.SetBitmap(hBmp);
	if (state_waithailH == 1) break;
	}
	if (StopFlagH == 1)
	{
	SetLedOffH(1);
	break;
	}
	while (1)
	{
	Sleep(1000);
	state_starthailH = 1;
	CBitmap bitmap;
	HBITMAP hBmp;
	bitmap.LoadBitmap(IDB_BITMAP_RED);
	hBmp = (HBITMAP)bitmap.GetSafeHandle();
	m_led14.SetBitmap(hBmp);
	if (state_starthailH == 1) break;
	}
	if (StopFlagH == 1)
	{
	SetLedOffH(1);
	break;
	}
	while (1)
	{
	Sleep(1000);
	state_hailacquisitionH = 1;
	CBitmap bitmap;
	HBITMAP hBmp;
	bitmap.LoadBitmap(IDB_BITMAP_RED);
	hBmp = (HBITMAP)bitmap.GetSafeHandle();
	m_led15.SetBitmap(hBmp);
	if (state_hailacquisitionH == 1) break;
	}
	if (StopFlagH == 1)
	{
	SetLedOffH(1);
	break;
	}
	while (1)
	{
	Sleep(1000);
	state_haildirectivesH = 1;
	CBitmap bitmap;
	HBITMAP hBmp;
	bitmap.LoadBitmap(IDB_BITMAP_RED);
	hBmp = (HBITMAP)bitmap.GetSafeHandle();
	m_led16.SetBitmap(hBmp);
	if (state_haildirectivesH == 1) break;
	}
	if (StopFlagH == 1)
	{
	SetLedOffH(1);
	break;
	}
	while (1)
	{
	Sleep(1000);
	state_hailtailH = 1;
	CBitmap bitmap;
	HBITMAP hBmp;
	bitmap.LoadBitmap(IDB_BITMAP_RED);
	hBmp = (HBITMAP)bitmap.GetSafeHandle();
	m_led17.SetBitmap(hBmp);
	if (state_hailtailH == 1) break;
	}
	if (StopFlagH == 1)
	{
	SetLedOffH(1);
	break;
	}
	while (1)
	{
	Sleep(1000);
	state_hailresponseH = 1;
	CBitmap bitmap;
	HBITMAP hBmp;
	bitmap.LoadBitmap(IDB_BITMAP_RED);
	hBmp = (HBITMAP)bitmap.GetSafeHandle();
	m_led3.SetBitmap(hBmp);
	if (state_hailresponseH == 1) break;
	}
	if (StopFlagH == 1)
	{
	SetLedOffH(1);
	break;
	}
	while (1)
	{
	Sleep(1000);
	state_receiveDataH = 1;
	CBitmap bitmap;
	HBITMAP hBmp;
	bitmap.LoadBitmap(IDB_BITMAP_RED);
	hBmp = (HBITMAP)bitmap.GetSafeHandle();
	m_led6.SetBitmap(hBmp);
	if (state_receiveDataH == 1) break;
	}
	if (StopFlagH == 1)
	{
	SetLedOffH(1);
	break;
	}
	while (1)
	{
	Sleep(1000);
	state_waitcarrierH = 1;
	CBitmap bitmap;
	HBITMAP hBmp;
	bitmap.LoadBitmap(IDB_BITMAP_RED);
	hBmp = (HBITMAP)bitmap.GetSafeHandle();
	m_led7.SetBitmap(hBmp);
	if (state_waitcarrierH == 1) break;
	}
	if (StopFlagH == 1)
	{
	SetLedOffH(1);
	break;
	}
	while (1)
	{
	Sleep(1000);
	state_acquisitionH = 1;
	CBitmap bitmap;
	HBITMAP hBmp;
	bitmap.LoadBitmap(IDB_BITMAP_RED);
	hBmp = (HBITMAP)bitmap.GetSafeHandle();
	m_led8.SetBitmap(hBmp);
	if (state_acquisitionH == 1) break;
	}

	if (StopFlagH == 1)
	{
	SetLedOffH(1);
	break;
	}
	while (1)
	{
	Sleep(1000);
	state_senddataH = 1;
	CBitmap bitmap;
	HBITMAP hBmp;
	bitmap.LoadBitmap(IDB_BITMAP_RED);
	hBmp = (HBITMAP)bitmap.GetSafeHandle();
	m_led9.SetBitmap(hBmp);
	if (state_senddataH == 1) break;
	}
	if (StopFlagH == 1)
	{
	SetLedOffH(1);
	break;
	}
	while (1)
	{
	Sleep(1000);
	state_responseendH = 1;
	CBitmap bitmap;
	HBITMAP hBmp;
	bitmap.LoadBitmap(IDB_BITMAP_RED);
	hBmp = (HBITMAP)bitmap.GetSafeHandle();
	m_led10.SetBitmap(hBmp);
	if (state_responseendH == 1) break;
	}
	if (StopFlagH == 1)
	{
	SetLedOffH(1);
	break;
	}
	while (1)
	{
	Sleep(1000);
	state_tailquitH = 1;
	CBitmap bitmap;
	HBITMAP hBmp;
	bitmap.LoadBitmap(IDB_BITMAP_RED);
	hBmp = (HBITMAP)bitmap.GetSafeHandle();
	m_led11.SetBitmap(hBmp);
	if (state_tailquitH == 1) break;
	}
	break;
	}
	*/
	//	CDialogEx::OnOK();
}

int CHalfDuplexDlg::SetLedOffH(int a)
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
	m_led8.SetBitmap(hBmp);
	m_led9.SetBitmap(hBmp);
	m_led10.SetBitmap(hBmp);
	m_led11.SetBitmap(hBmp);
	m_led12.SetBitmap(hBmp);
	m_led13.SetBitmap(hBmp);
	m_led14.SetBitmap(hBmp);
	m_led15.SetBitmap(hBmp);
	m_led16.SetBitmap(hBmp);
	m_led17.SetBitmap(hBmp);
	return 0;
}

void ThreadFuncH(LPVOID lpParam)
{
	CHalfDuplexDlg *pDlg = (CHalfDuplexDlg*)lpParam;

	while (StopFlagH == 0)
	{
		if (StopFlagH == 1)
		{
			pDlg->SetLedOffH(1);
			break;
		}
		while (1)
		{
			Sleep(1000);
			state_inactiveH = 1;
			CBitmap bitmap;
			HBITMAP hBmp;
			bitmap.LoadBitmap(IDB_BITMAP_RED);
			hBmp = (HBITMAP)bitmap.GetSafeHandle();
			pDlg->m_led1.SetBitmap(hBmp);
			if (state_inactiveH == 1) break;
		}
		if (StopFlagH == 1)
		{
			pDlg->SetLedOffH(1);
			break;
		}
		while (1)
		{
			Sleep(1000);
			state_waithailH = 1;
			CBitmap bitmap;
			HBITMAP hBmp;
			bitmap.LoadBitmap(IDB_BITMAP_RED);
			hBmp = (HBITMAP)bitmap.GetSafeHandle();
			pDlg->m_led2.SetBitmap(hBmp);

			SystemTimeH();  //���û�ȡϵͳʱ�亯��

			CmenuDlg *ppDlg = (CmenuDlg*)AfxGetApp()->m_pMainWnd;
			ppDlg->m_Hist.SetSel(ppDlg->m_Hist.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
			ppDlg->m_Hist.ReplaceSel(_T("�ȴ�����\r\n"));

			if (state_waithailH == 1) break;
		}
		if (StopFlagH == 1)
		{
			pDlg->SetLedOffH(1);
			break;
		}

		while (1)
		{
			if (Start_Hail_R == 1)
			{
				Start_Hail_R = 0;
				break;
			}
			if (StopFlagH == 1)
			{
				pDlg->SetLedOffH(1);
				return;
			}
		}

		while (1)
		{
			Sleep(1000);
			state_carrieronlyH = 1;
			CBitmap bitmap;
			HBITMAP hBmp;
			bitmap.LoadBitmap(IDB_BITMAP_RED);
			hBmp = (HBITMAP)bitmap.GetSafeHandle();
			pDlg->m_led7.SetBitmap(hBmp);

			HallCommond = 1;
			CarrierSend_T = 1;
			CommondGroup = SPDU_framing();
			encodecommond(CommondGroup);
			((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->SendMessagepro(P_Data_CC, Len_DataInProcess);
			HallCommond = 0;
			CarrierSend_T = 0;

			if (state_carrieronlyH == 1) break;
		}
		if (StopFlagH == 1)
		{
			pDlg->SetLedOffH(1);
			break;
		}
		while (1)
		{
			Sleep(1000);
			state_acquisitionH = 1;
			CBitmap bitmap;
			HBITMAP hBmp;
			bitmap.LoadBitmap(IDB_BITMAP_RED);
			hBmp = (HBITMAP)bitmap.GetSafeHandle();
			pDlg->m_led8.SetBitmap(hBmp);
			if (state_acquisitionH == 1) break;
		}
		if (StopFlagH == 1)
		{
			pDlg->SetLedOffH(1);
			break;
		}
		while (1)
		{
			Sleep(1000);
			SystemTimeH();  //���û�ȡϵͳʱ�亯��
			CmenuDlg *ppDlg = (CmenuDlg*)AfxGetApp()->m_pMainWnd;
			ppDlg->m_Hist.SetSel(ppDlg->m_Hist.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
			ppDlg->m_Hist.ReplaceSel(_T("��������\r\n"));
			pDlg->banshuanggongsend();

			state_senddataH = 1;
			CBitmap bitmap;
			HBITMAP hBmp;
			bitmap.LoadBitmap(IDB_BITMAP_RED);
			hBmp = (HBITMAP)bitmap.GetSafeHandle();
			pDlg->m_led9.SetBitmap(hBmp);



		
			if (state_senddataH == 1) break;
		}
		if (StopFlagH == 1)
		{
			pDlg->SetLedOffH(1);
			break;
		}
		while (1)
		{
			Sleep(1000);
			state_tokenexchangeH = 1;
			CBitmap bitmap;
			HBITMAP hBmp;
			bitmap.LoadBitmap(IDB_BITMAP_RED);
			hBmp = (HBITMAP)bitmap.GetSafeHandle();
			pDlg->m_led12.SetBitmap(hBmp);
			if (state_tokenexchangeH == 1) break;
		}
		if (StopFlagH == 1)
		{
			pDlg->SetLedOffH(1);
			break;
		}
		while (1)
		{
			Sleep(1000);
			state_tailswitchH = 1;
			CBitmap bitmap;
			HBITMAP hBmp;
			bitmap.LoadBitmap(IDB_BITMAP_RED);
			hBmp = (HBITMAP)bitmap.GetSafeHandle();
			pDlg->m_led13.SetBitmap(hBmp);
			if (state_tailswitchH == 1) break;
		}
		if (StopFlagH == 1)
		{
			pDlg->SetLedOffH(1);
			break;
		}
		while (1)
		{
			Sleep(1000);
			state_waitcarrierH = 1;
			CBitmap bitmap;
			HBITMAP hBmp;
			bitmap.LoadBitmap(IDB_BITMAP_RED);
			hBmp = (HBITMAP)bitmap.GetSafeHandle();
			pDlg->m_led4.SetBitmap(hBmp);

			HallCommond = 1;
			WaitCarrier_T = 1;
			CommondGroup = SPDU_framing();
			encodecommond(CommondGroup);
			((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->SendMessagepro(P_Data_CC, Len_DataInProcess);
			HallCommond = 0;
			WaitCarrier_T = 0;

			if (state_waitcarrierH == 1) break;
		}
		while (1)
		{
			if (CarrierSend_R == 1)
			{
				CarrierSend_R = 0;
				break;
			}
			if (StopFlagH == 1)
			{
				pDlg->SetLedOffH(1);
				return;
			}
		}
		while (1)
		{
			Sleep(1000);
			state_waitfirstframeH = 1;
			CBitmap bitmap;
			HBITMAP hBmp;
			bitmap.LoadBitmap(IDB_BITMAP_RED);
			hBmp = (HBITMAP)bitmap.GetSafeHandle();
			pDlg->m_led5.SetBitmap(hBmp);
			if (state_waitfirstframeH == 1) break;
		}
		if (StopFlagH == 1)
		{
			pDlg->SetLedOffH(1);
			break;
		}
		while (1)
		{
			Sleep(1000);
			state_receiveDataH = 1;
			CBitmap bitmap;
			HBITMAP hBmp;
			bitmap.LoadBitmap(IDB_BITMAP_RED);
			hBmp = (HBITMAP)bitmap.GetSafeHandle();
			pDlg->m_led6.SetBitmap(hBmp);

			SystemTimeH();  //���û�ȡϵͳʱ�亯��
			CmenuDlg *ppDlg = (CmenuDlg*)AfxGetApp()->m_pMainWnd;
			ppDlg->m_Hist.SetSel(ppDlg->m_Hist.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
			ppDlg->m_Hist.ReplaceSel(_T("��������\r\n"));

			if (state_receiveDataH == 1) break;
		}
		while (1)
		{
			if (ResponseSend_R == 1)
			{
				ResponseSend_R = 0;
				break;
			}
			if (StopFlagH == 1)
			{
				pDlg->SetLedOffH(1);
				return;
			}
		}
	
		Sleep(2000);
		pDlg->SetLedOffH(1); //��LED���ú�
		break;
	}
}
void CHalfDuplexDlg::banshuanggongsend()
{
	int *temp, *temp2;
	int *buffer; //����
	int h = 0;							//������Ч֡�Ĵ���
	int n;
	int allnumber = 0;			//����֡����
	//	char *temp;
	num_frame = 0; //֡���к�
	Error = 0;
	Num_Data = SendA.FrameLength * 8;			//��bit����FrameLength���ֽ�
	/*********ͨ��������ȥ��ÿؼ�ֵ���������д��룩
	CString strFilePath;
	psDlg->GetDlgItemText(IDC_SENDSOUCER_EDIT, strFilePath);
	CFile file(strFilePath, CFile::modeRead | CFile::typeBinary);
	*/
	// ����κ��壺��ȡԶ�̷����ļ�
	/****************����WideCharToMultiByte���ϵͳ������CStringת��char*��************************/
	//��ȡת�������Ŀ�껺���С
	DWORD dBufSize_R = WideCharToMultiByte(CP_OEMCP, 0, ReceiveA.gRemoteDataPath, -1, NULL, 0, NULL, FALSE);
	//����Ŀ�껺��
	char *strFilePath_R = new char[dBufSize_R + 1]; //new���������Ķѵ�һ��ռ䣬������Ӧ�������ͷţ�������������ڴ�й©
	memset(strFilePath_R, 0, dBufSize_R);
	//ת����WideCharToMultiByte����������гɹ�������cchMultiByte��Ϊ�㣬����ֵ���� lpMultiByteStrָ��Ļ�������д����ֽ�����
	int nRet_R = WideCharToMultiByte(CP_OEMCP, 0, ReceiveA.gRemoteDataPath, -1, strFilePath_R, dBufSize_R, NULL, FALSE);
	/******���Դ���
	if (nRet_R <= 0)
	{
	MessageBox(_T("ת��ʧ��\n"));
	}
	else
	{
	MessageBox(_T("ת���ɹ�\n"));
	}
	*/
	FILE *fp_R;
	errno_t err_R;
	err_R = fopen_s(&fp_R, strFilePath_R, "r+"); //��ȫ��ʽ���ļ����ɹ��򿪷���0��δ�ɹ��򿪷���1
	/********���Դ���
	if (err_R == 0)
	{
	MessageBox(_T("The file  was opened!"));
	}
	else
	{
	MessageBox(_T("The file  was not opened"));
	}
	*/
	//fopen()������fseek��ftell������ļ��ĳ���
	fseek(fp_R, 0, SEEK_END);		//��λ�ļ�ָ�뵽�ļ�ĩβ	�ɹ�����0�����ɹ�����-1
	fileSize1 = ftell(fp_R);			//���ԣ�����Դ�ļ�1111.dat   filesize = 72
	fseek(fp_R, 0, SEEK_SET);	//�ٶ�λ�ļ�ָ�뵽�ļ�ͷ
	delete[]strFilePath_R; //�ͷţ����ɺ�ϰ��
	strFilePath_R = NULL;

	SourceFile = (int*)malloc(fileSize1*sizeof(int));//C���������ڴ�ռ亯��
	for (int i = 0; i < fileSize1; i++)
	{
		fscanf_s(fp_R, "%1u", &SourceFile[i]);		//%u����ʽ�ַ�����%1u��Ҫ����������Ҷ���һλ
	}

	fclose(fp_R);//C���Ա���µĹر��ļ�

	// ����κ��壺��ȡ���ط����ļ�
	/****************����WideCharToMultiByte���ϵͳ������CStringת��char*��************************/
	//��ȡת�������Ŀ�껺���С
	DWORD dBufSize = WideCharToMultiByte(CP_OEMCP, 0, SendA.gSendDataPath, -1, NULL, 0, NULL, FALSE); //���ԣ�����Դ�ļ�1111.dat   dBufSize = 77
	//����Ŀ�껺��
	char *strFilePath = new char[dBufSize + 1]; //new���������Ķѵ�һ��ռ䣬������Ӧ�������ͷţ�������������ڴ�й©
	memset(strFilePath, 0, dBufSize);
	//ת����WideCharToMultiByte����������гɹ�������cchMultiByte��Ϊ�㣬����ֵ���� lpMultiByteStrָ��Ļ�������д����ֽ�����
	int nRet = WideCharToMultiByte(CP_OEMCP, 0, SendA.gSendDataPath, -1, strFilePath, dBufSize, NULL, FALSE);

	/*���Դ��� *****
	if (nRet <= 0)
	{
	MessageBox(_T("ת��ʧ��\n"));
	}
	else
	{
	MessageBox(_T("ת���ɹ�\n"));
	}
	*/
	FILE *fp;
	errno_t err;
	err = fopen_s(&fp, strFilePath, "r+"); //��ȫ��ʽ���ļ����ɹ��򿪷���0��δ�ɹ��򿪷���1
	/**********����
	if (err == 0)
	{
	MessageBox(_T("The file  was opened!"));
	}
	else
	{
	MessageBox(_T("The file  was not opened"));
	}*/
	//fopen()������fseek��ftell������ļ��ĳ���
	int filesize;
	fseek(fp, 0, SEEK_END);		//��λ�ļ�ָ�뵽�ļ�ĩβ	�ɹ�����0�����ɹ�����-1
	filesize = ftell(fp);			//���ԣ�����Դ�ļ�1111.dat   filesize = 72
	fseek(fp, 0, SEEK_SET);	//�ٶ�λ�ļ�ָ�뵽�ļ�ͷ
	delete[]strFilePath; //�ͷţ����ɺ�ϰ��
	strFilePath = NULL;

	temp = (int*)malloc(filesize*sizeof(int));//C���������ڴ�ռ亯��
	for (int i = 0; i < filesize; i++)
	{
		fscanf_s(fp, "%1u", &temp[i]);		//%u����ʽ�ַ�����%1u��Ҫ����������Ҷ���һλ
	}
	//�ж�Ҫ���͵Ĵ���n
	if (filesize % Num_Data)
	{
		n = filesize / Num_Data + 1;
	}
	else
	{
		n = filesize / Num_Data;
	}

	//��ɱ�׼֡�����㲹0
	temp2 = (int*)malloc(Num_Data*n*sizeof(int));
	for (int i = 0; i < Num_Data*n; i++)
	{
		if (i < filesize)
			temp2[i] = temp[i];
		else
			temp2[i] = 0;
	}
	while (1)
	{
		buffer = (int *)malloc(Num_Data*sizeof(int));
		for (int i = 0; i < Num_Data; i++)
		{
			buffer[i] = temp2[i + Num_Data*h];
		}
		h++;
		break;
	}

	CString	*str;
	str = new CString[Num_Data*n + 1];
	CString strDisplay;
	for (int i = 0; i < Num_Data; i++) //Ϊ�˴�int������תCString���������������
	{
		str[i].Format(_T("%d"), buffer[i]);
		strDisplay += str[i];	//����CString��������+=������
	} //���ݱ��浽strDisplay���������

	//��Ҫ���͵������͵�CStatusDisply�Ի������еķ������ݱ༭��
	d_sdHDlg->m_HistSendData.SetSel(d_sdHDlg->m_HistSendData.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
	d_sdHDlg->m_HistSendData.ReplaceSel(strDisplay); //�滻��ǰ�ı�
	//	d_sdDlg->GetDlgItem(IDC_SENDDATA_EDIT)->SetWindowText(strDisplay);
	d_sdHDlg->SetDlgItemInt(IDC_SEND_EDIT, (allnumber + 1)*Num_Data); //���������ܱ�������ʾ
	d_sdHDlg->SetDlgItemInt(IDC_CURRENTSENDNUM_EDIT, num_frame);//��ʾ��֡��


	while (1)
	{
		if (commondstate == 0)					 //�жϴ�ʱû��ָ���
		{
			messagestate = 1;						//��ʱ��������
			encode(buffer);


			((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->SendMessagepro(P_Data_CC, Len_DataInProcess);
			arqarray(num_frame);					//�����ݴ������飬�Է���arq
			break;
		}

	}
	messagestate = 0;
	/******���õ���˸��ʾ���ڷ�������*****/
	state_senddataH = 1;
	CBitmap bitmap[2];
	HBITMAP hBmp[2];
	bitmap[0].LoadBitmap(IDB_BITMAP_RED);
	hBmp[0] = (HBITMAP)bitmap[0].GetSafeHandle();
	m_led9.SetBitmap(hBmp[0]);
	Sleep(1000);
	state_senddataH = 0;
	bitmap[1].LoadBitmap(IDB_BITMAP_GREY);
	hBmp[1] = (HBITMAP)bitmap[1].GetSafeHandle();
	m_led9.SetBitmap(hBmp[1]);
	/*************************************/
	num_frame++;
	allnumber++;
	Sleep(4000);

	while (1)
	{
		/*		if (arqreceiveflag == 1)
		{
		arqreceiveflag = 0;
		d_sdDlg->SetDlgItemInt(IDC_SEND_EDIT, (allnumber + 1)*Num_Data); //���������ܱ�������ʾ
		CString frame_resend;
		frame_resend.Format(_T("%d"), ResendNumber_R);
		d_sdDlg->m_ResendFrameNumEdit.SetSel(d_sdDlg->m_ResendFrameNumEdit.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
		d_sdDlg->m_ResendFrameNumEdit.ReplaceSel(frame_resend); //�滻��ǰ�ı�
		d_sdDlg->m_ResendFrameNumEdit.SetSel(d_sdDlg->m_ResendFrameNumEdit.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
		d_sdDlg->m_ResendFrameNumEdit.ReplaceSel(_T(",")); //�滻��ǰ�ı�
		while (1)
		{
		if (commondstate == 0)
		{
		messagestate = 1;
		arqsend(ResendNumber_R);					//�ӻ����ȡ�ش�֡
		Len_DataInProcess = Num_Data + 24 + 40 + 32;
		Sleep(1000);
		((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->SendMessage(P_Data_CC, Len_DataInProcess);
		break;
		}

		}
		messagestate = 0;
		d_sdDlg->SetDlgItemInt(IDC_CURRENTSENDNUM_EDIT, ResendNumber_R);//��ʾ��֡��

		state_senddataH = 1;
		CBitmap bitmap[2];
		HBITMAP hBmp[2];
		bitmap[0].LoadBitmap(IDB_BITMAP_RED);
		hBmp[0] = (HBITMAP)bitmap[0].GetSafeHandle();
		m_led11.SetBitmap(hBmp[0]);
		Sleep(1000);
		state_senddataH = 0;
		bitmap[1].LoadBitmap(IDB_BITMAP_GREY);
		hBmp[1] = (HBITMAP)bitmap[1].GetSafeHandle();
		m_led11.SetBitmap(hBmp[1]);

		allnumber++;
		h = ResendNumber_R + 1;
		num_frame = ResendNumber_R + 1;
		Sleep(4000);
		}*/

		if (n == h)
		{
			break;
		}
		Sleep(1000);
		while (1)
		{
			for (int i = 0; i < Num_Data; i++)
			{
				buffer[i] = temp2[i + Num_Data*h];
			}
			h++;
			break;
		}
		CString	*str;
		str = new CString[Num_Data*n + 1];
		CString strDisplay;
		for (int i = 0; i < Num_Data; i++) //Ϊ�˴�int������תCString���������������
		{
			str[i].Format(_T("%d"), buffer[i]);
			strDisplay += str[i];	//����CString��������+=������
		} //���ݱ��浽strDisplay���������

		//��Ҫ���͵������͵�CStatusDisply�Ի������еķ������ݱ༭��
		d_sdHDlg->m_HistSendData.SetSel(d_sdHDlg->m_HistSendData.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
		d_sdHDlg->m_HistSendData.ReplaceSel(strDisplay); //�滻��ǰ�ı�
		//	d_sdDlg->GetDlgItem(IDC_SENDDATA_EDIT)->SetWindowText(strDisplay);
		d_sdHDlg->SetDlgItemInt(IDC_SEND_EDIT, (allnumber + 1)*Num_Data); //���������ܱ�������ʾ
		d_sdHDlg->SetDlgItemInt(IDC_CURRENTSENDNUM_EDIT, num_frame);//��ʾ��֡��

		while (1)
		{
			if (commondstate == 0)					 //�жϴ�ʱû��ָ���
			{
				messagestate = 1;						//��ʱ��������
				encode(buffer);

				//				Sleep(4000);
				((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->SendMessagepro(P_Data_CC, Len_DataInProcess);
				arqarray(num_frame);					//�����ݴ������飬�Է���arq
				break;
			}

		}
		messagestate = 0;
		/******���õ���˸��ʾ���ڷ�������*****/
		state_senddataH = 1;
		CBitmap bitmap[2];
		HBITMAP hBmp[2];
		bitmap[0].LoadBitmap(IDB_BITMAP_RED);
		hBmp[0] = (HBITMAP)bitmap[0].GetSafeHandle();
		m_led9.SetBitmap(hBmp[0]);
		Sleep(1000);
		state_senddataH = 0;
		bitmap[1].LoadBitmap(IDB_BITMAP_GREY);
		hBmp[1] = (HBITMAP)bitmap[1].GetSafeHandle();
		m_led9.SetBitmap(hBmp[1]);
		/*************************************/
		num_frame++;
		allnumber++;
		Sleep(4000);
	}

	fclose(fp);//C���Ա���µĹر��ļ�
	free(temp); //�ͷ�ָ��ָ����ڴ�
	temp = NULL;//ָ���ڴ��ָ����Ϊ�գ���ֹ������治С��ʹ������

}

/*==================================*/
//
// FunctionName : systemtime
// Description      :  ��ȡϵͳʱ�䲢��ʾ
//
/*=================================*/
void SystemTimeH()
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

void CHalfDuplexDlg::arqarray(int framecounter)
{
	int length = Num_Data + 24 + 40 + 32;

	switch (framecounter % 10)
	{
	case 0:
		for (int i = 0; i<length; i++)
		{
			*(Arq_data + i) = *(P_Data_CC + i);
		}
		break;
	case 1:
		for (int i = 0; i<length; i++)
		{
			*(Arq_data + length + i) = *(P_Data_CC + i);
		}
		break;
	case 2:
		for (int i = 0; i<length; i++)
		{
			*(Arq_data + 2 * length + i) = *(P_Data_CC + i);
		}
		break;
	case 3:
		for (int i = 0; i<length; i++)
		{
			*(Arq_data + 3 * length + i) = *(P_Data_CC + i);
		}
		break;
	case 4:
		for (int i = 0; i<length; i++)
		{
			*(Arq_data + 4 * length + i) = *(P_Data_CC + i);
		}
		break;
	case 5:
		for (int i = 0; i<length; i++)
		{
			*(Arq_data + 5 * length + i) = *(P_Data_CC + i);
		}
		break;
	case 6:
		for (int i = 0; i<length; i++)
		{
			*(Arq_data + 6 * length + i) = *(P_Data_CC + i);
		}
		break;
	case 7:
		for (int i = 0; i<length; i++)
		{
			*(Arq_data + 7 * length + i) = *(P_Data_CC + i);
		}
		break;
	case 8:
		for (int i = 0; i<length; i++)
		{
			*(Arq_data + 8 * length + i) = *(P_Data_CC + i);
		}
		break;
	case 9:
		for (int i = 0; i<length; i++)
		{
			*(Arq_data + 9 * length + i) = *(P_Data_CC + i);
		}
		break;
	}

}

void CHalfDuplexDlg::arqsend(int framecounter)
{
	int length = Num_Data + 24 + 40 + 32;
	P_Data_CC = (int *)malloc(length*sizeof(int));
	switch (framecounter % 10)
	{
	case 0:
		for (int i = 0; i<length; i++)
		{
			P_Data_CC[i] = Arq_data[i];
		}
		break;
	case 1:
		for (int i = 0; i<length; i++)
		{
			P_Data_CC[i] = Arq_data[length + i];
		}
		break;
	case 2:
		for (int i = 0; i<length; i++)
		{
			P_Data_CC[i] = Arq_data[2 * length + i];
		}
		break;
	case 3:
		for (int i = 0; i<length; i++)
		{
			P_Data_CC[i] = Arq_data[3 * length + i];
		}
		break;
	case 4:
		for (int i = 0; i<length; i++)
		{
			P_Data_CC[i] = Arq_data[4 * length + i];
		}
		break;
	case 5:
		for (int i = 0; i<length; i++)
		{
			P_Data_CC[i] = Arq_data[5 * length + i];
		}
		break;
	case 6:
		for (int i = 0; i<length; i++)
		{
			P_Data_CC[i] = Arq_data[6 * length + i];
		}
		break;
	case 7:
		for (int i = 0; i<length; i++)
		{
			P_Data_CC[i] = Arq_data[7 * length + i];
		}
		break;
	case 8:
		for (int i = 0; i<length; i++)
		{
			P_Data_CC[i] = Arq_data[8 * length + i];
		}
		break;
	case 9:
		for (int i = 0; i<length; i++)
		{
			P_Data_CC[i] = Arq_data[9 * length + i];
		}
		break;

	}
}
