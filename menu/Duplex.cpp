// Duplex.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "menu.h"
#include "Duplex.h"
#include "afxdialogex.h"
//#include "DuplexFunction.h"
#include "menuDlg.h"
#include "TransRevShare.h"
#include "SystemParameter.h"
#include "encode.h"
#include "Framing.h"



// CDuplex �Ի���

IMPLEMENT_DYNAMIC(CDuplex, CDialogEx)

CDuplex::CDuplex(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDuplex::IDD, pParent)
{

}

CDuplex::~CDuplex()
{
}

void CDuplex::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LED1_STATIC, m_led1);
	DDX_Control(pDX, IDC_LED2_STATIC, m_led2);
	DDX_Control(pDX, IDC_LED3_STATIC, m_led3);
	DDX_Control(pDX, IDC_LED6_STATIC, m_led6);
	DDX_Control(pDX, IDC_LED5_STATIC, m_led5);
	DDX_Control(pDX, IDC_LED7_STATIC, m_led7);
	DDX_Control(pDX, IDC_LED8_STATIC, m_led8);
	DDX_Control(pDX, IDC_LED9_STATIC, m_led9);
	DDX_Control(pDX, IDC_LED10_STATIC, m_led10);
	DDX_Control(pDX, IDC_LED11_STATIC, m_led11);
	DDX_Control(pDX, IDC_LED12_STATIC, m_led12);
	DDX_Control(pDX, IDC_LED13_STATIC, m_led13);
	DDX_Control(pDX, IDC_LED14_STATIC, m_led14);
	DDX_Control(pDX, IDC_LED4_STATIC, m_led4);
	//  DDX_Control(pDX, IDC_RECORDTEST_EDIT, m_histrecord);
	//  DDX_Control(pDX, IDC_VIEWFORTEST_EDIT, m_Text);
}


BEGIN_MESSAGE_MAP(CDuplex, CDialogEx)
//	ON_BN_CLICKED(IDOK, &CDuplex::OnBnClickedOk)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDuplex ��Ϣ�������

/*========================================*/
/*                                          ����˫��ģʽ                                            */
/*=======================================*/
int CDuplex::StartRunDuplex(int a)
{
	state_inactive = 0;
	state_waithail = 0;
	state_starthail = 0;
	state_hailacquisition = 0;
	state_haildirectives = 0;
	state_hailtail = 0;
	state_hailresponse = 0;
	state_carrieronly = 0;
	state_acquisition = 0;
	state_duplexon = 0;
	state_rnmdend = 0;
	state_lnmdend = 0;
	state_duplexend = 0;
	state_terminatingtail = 0;
	//LedFlag = 0;
	StopFlag = 0;

	SetLedOff(1);
	Sleep(1000);
	state_inactive = 1;   //��ʼ״̬
	m_led1.SetBitmap(m_red);

	hThread = CreateThread(NULL,
												0,
												(LPTHREAD_START_ROUTINE)ThreadFunc,
												this,
												0,
												&ThreadID); //����һ���߳�
												

	//CWinThread * m_pThread;
	//m_pThread = AfxBeginThread(ThreadFunc, this);
	//if (NULL == m_pThread)
	//{
	//	TRACE("�����µ��̳߳���\n");
	//	return 0;
	//}
//	AfxBeginThread(ThreadFunc, NULL);
	return 0; //��������з���ֵ�ĺ�����������Ҫreturn 0
}

void ThreadFunc(LPVOID lpParam)
{
	CDuplex *pDlg = (CDuplex *)lpParam;
	CmenuDlg *ppDlg = (CmenuDlg*)AfxGetApp()->m_pMainWnd;

	pDlg->DuplexState = 2;	//get in State-2 at the first start

	while (1)
	{
		switch (pDlg->DuplexState)
		{
		case 2:
			pDlg->state_waithail = 1;
			pDlg->SystemTime();

			ppDlg->m_Hist.SetSel(ppDlg->m_Hist.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
			ppDlg->m_Hist.ReplaceSel(_T("�ȴ�������Ӧ\r\n"));
			pDlg->m_led2.SetBitmap(pDlg->m_red);

			pDlg->oldTickCount = GetTickCount();
			while (1)
			{
				pDlg->newTickCount = GetTickCount();
				if (Start_Hail_R)
				{
					Start_Hail_R = 0;
					pDlg->DuplexState = 41;

					break;
				}
				if ((pDlg->newTickCount - pDlg->oldTickCount) >= 60000)
				{
					break;
				}
			}

			//���ͷ���
			HallCommond = 1;
			Hailresponse_T = 1;
			
			CommondGroup = SPDU_framing();
			encodecommond(CommondGroup);
			((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->SendMessagepro(P_Data_CC, Len_DataInProcess);
			
			HallCommond = 0;
			Hailresponse_T = 0;

			Sleep(200);
			break;
		case 41:
			pDlg->state_carrieronly = 1;
			pDlg->SystemTime();

			ppDlg->m_Hist.SetSel(ppDlg->m_Hist.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
			ppDlg->m_Hist.ReplaceSel(_T("�ز�ͬ��\r\n"));
			pDlg->m_led8.SetBitmap(pDlg->m_red);
			Sleep(1000);

			pDlg->DuplexState = 42;
			break;
		case 42:
			pDlg->state_acquisition = 1;
			pDlg->SystemTime();

			ppDlg->m_Hist.SetSel(ppDlg->m_Hist.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
			ppDlg->m_Hist.ReplaceSel(_T("���Ϳ�������\r\n"));
			pDlg->m_led9.SetBitmap(pDlg->m_red);
			Sleep(400);

			pDlg->DuplexState = 40;
			break;
		case 40:
			pDlg->state_duplexon = 1;
			pDlg->SystemTime();

			ppDlg->m_Hist.SetSel(ppDlg->m_Hist.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
			ppDlg->m_Hist.ReplaceSel(_T("˫�����ݴ���\r\n"));
			pDlg->m_led10.SetBitmap(pDlg->m_red);

			pDlg->shuanggongsend();

			pDlg->state_lnmdend = 1;
			pDlg->SystemTime();
			ppDlg->m_Hist.SetSel(ppDlg->m_Hist.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
			ppDlg->m_Hist.ReplaceSel(_T("���ط������\r\n"));
			pDlg->m_led11.SetBitmap(pDlg->m_red);

			SetControlParameters = 1;
			RNMD_T = 1;
			CommondGroup = SPDU_framing();
			encodecommond(CommondGroup);
			//������������Զ�̷������ָ��
			((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->SendMessagepro(P_Data_CC, Len_DataInProcess);
			SetControlParameters = 0;
			RNMD_T = 0;

			//�ж��Ƿ���յ�Զ�������ݷ���ָ��
			pDlg->oldTickCount = GetTickCount();
			while (1)
			{
				pDlg->newTickCount = GetTickCount();
				if (RNMD_R)
				{
					pDlg->SystemTime();
					ppDlg->m_Hist.SetSel(ppDlg->m_Hist.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
					ppDlg->m_Hist.ReplaceSel(_T("�յ�Զ��RNMD\r\n"));
					RNMD_R = 0;
					break;
				}
				if ((pDlg->newTickCount - pDlg->oldTickCount) >= 120000)
				{
					break;
				}
			}

			pDlg->state_rnmdend = 1;
			pDlg->SystemTime();
			ppDlg->m_Hist.SetSel(ppDlg->m_Hist.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
			ppDlg->m_Hist.ReplaceSel(_T("Զ�̷������\r\n"));
			pDlg->m_led12.SetBitmap(pDlg->m_red);

			pDlg->state_duplexend = 1;
			pDlg->SystemTime();
			ppDlg->m_Hist.SetSel(ppDlg->m_Hist.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
			ppDlg->m_Hist.ReplaceSel(_T("���ݷ������\r\n"));
			pDlg->m_led13.SetBitmap(pDlg->m_red);

			pDlg->DuplexState = 45;
			break;
		case 45:
			pDlg->state_terminatingtail = 1;
			pDlg->SystemTime();
			ppDlg->m_Hist.SetSel(ppDlg->m_Hist.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
			ppDlg->m_Hist.ReplaceSel(_T("����β����\r\n"));
			pDlg->m_led14.SetBitmap(pDlg->m_red);
			Sleep(50);
			break;
			
		default:
			break;
		}
		if (pDlg->state_terminatingtail == 1)
		{
			pDlg->SetLedOff(1);
			break;
		}
	}
}

int CDuplex::SetLedOff(int a)
{
	//	state_inactive = 0;
	m_led1.SetBitmap(m_grey);
	m_led2.SetBitmap(m_grey);
	m_led3.SetBitmap(m_grey);
	m_led4.SetBitmap(m_grey);
	m_led5.SetBitmap(m_grey);
	m_led6.SetBitmap(m_grey);
	m_led7.SetBitmap(m_grey);
	m_led8.SetBitmap(m_grey);
	m_led9.SetBitmap(m_grey);
	m_led10.SetBitmap(m_grey);
	m_led11.SetBitmap(m_grey);
	m_led12.SetBitmap(m_grey);
	m_led13.SetBitmap(m_grey);
	m_led14.SetBitmap(m_grey);
	return 0;
}

void CDuplex::shuanggongsend()
{	
	int *temp, *temp2;
	int *buffer;
	int h = 0;
	int n;
	int allnumber = 0;			//����֡����
//	char *temp;
	num_frame = 0; //֡���к�
	Error = 0;
	Num_Data = SendA.FrameLength * 8;
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
	char *strFilePath = new char[dBufSize+1]; //new���������Ķѵ�һ��ռ䣬������Ӧ�������ͷţ�������������ڴ�й©
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
	err = fopen_s(&fp,strFilePath, "r+"); //��ȫ��ʽ���ļ����ɹ��򿪷���0��δ�ɹ��򿪷���1
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
	d_sdDlg->m_HistSendData.SetSel(d_sdDlg->m_HistSendData.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
	d_sdDlg->m_HistSendData.ReplaceSel(strDisplay); //�滻��ǰ�ı�
		//	d_sdDlg->GetDlgItem(IDC_SENDDATA_EDIT)->SetWindowText(strDisplay);
	d_sdDlg->SetDlgItemInt(IDC_SEND_EDIT, (allnumber + 1)*Num_Data); //���������ܱ�������ʾ
	d_sdDlg->SetDlgItemInt(IDC_CURRENTSENDNUM_EDIT, num_frame);//��ʾ��֡��
	fclose(fp);//C���Ա���µĹر��ļ�
	free(temp); //�ͷ�ָ��ָ����ڴ�
	temp = NULL;//ָ���ڴ��ָ����Ϊ�գ���ֹ������治С��ʹ������

	while (1)
	{
		if (commondstate == 0)					 //�жϴ�ʱû��ָ���
		{
			messagestate = 1;						//��ʱ��������
			encode(buffer);

//			Sleep(5000);
			((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->SendMessagepro(P_Data_CC, Len_DataInProcess);
			arqarray(num_frame);					//�����ݴ������飬�Է���arq
			break;
		}	
	}
	messagestate = 0;
		/******���õ���˸��ʾ���ڷ�������*****/
	state_lnmdend = 1;
	CBitmap bitmap[2];
	HBITMAP hBmp[2];
	bitmap[0].LoadBitmap(IDB_BITMAP_RED);
	hBmp[0] = (HBITMAP)bitmap[0].GetSafeHandle();
	m_led11.SetBitmap(hBmp[0]);
	Sleep(1000);
	state_lnmdend = 0;
	bitmap[1].LoadBitmap(IDB_BITMAP_GREY);
	hBmp[1] = (HBITMAP)bitmap[1].GetSafeHandle();
	m_led11.SetBitmap(hBmp[1]);
		/*************************************/
	num_frame++;
	allnumber++;
	Sleep(4000);

	while (1)
	{
		if (arqreceiveflag == 1)
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
					((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->SendMessagepro(P_Data_CC, Len_DataInProcess);
					break;
				}
			}
			messagestate = 0;
			d_sdDlg->SetDlgItemInt(IDC_CURRENTSENDNUM_EDIT, ResendNumber_R);//��ʾ��֡��
			/******���õ���˸��ʾ���ڷ�������*****/
			state_lnmdend = 1;
			CBitmap bitmap[2];
			HBITMAP hBmp[2];
			bitmap[0].LoadBitmap(IDB_BITMAP_RED);
			hBmp[0] = (HBITMAP)bitmap[0].GetSafeHandle();
			m_led11.SetBitmap(hBmp[0]);
			Sleep(1000);
			state_lnmdend = 0;
			bitmap[1].LoadBitmap(IDB_BITMAP_GREY);
			hBmp[1] = (HBITMAP)bitmap[1].GetSafeHandle();
			m_led11.SetBitmap(hBmp[1]);
			/*************************************/
			allnumber++;
			h = ResendNumber_R + 1;
			num_frame = ResendNumber_R + 1;
			Sleep(4000);
		}

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
		d_sdDlg->m_HistSendData.SetSel(d_sdDlg->m_HistSendData.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
		d_sdDlg->m_HistSendData.ReplaceSel(strDisplay); //�滻��ǰ�ı�
		//	d_sdDlg->GetDlgItem(IDC_SENDDATA_EDIT)->SetWindowText(strDisplay);
		d_sdDlg->SetDlgItemInt(IDC_SEND_EDIT, (allnumber + 1)*Num_Data); //���������ܱ�������ʾ
		d_sdDlg->SetDlgItemInt(IDC_CURRENTSENDNUM_EDIT, num_frame);//��ʾ��֡��

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
		state_lnmdend = 1;
		CBitmap bitmap[2];
		HBITMAP hBmp[2];
		bitmap[0].LoadBitmap(IDB_BITMAP_RED);
		hBmp[0] = (HBITMAP)bitmap[0].GetSafeHandle();
		m_led11.SetBitmap(hBmp[0]);
		Sleep(1000);
		state_lnmdend = 0;
		bitmap[1].LoadBitmap(IDB_BITMAP_GREY);
		hBmp[1] = (HBITMAP)bitmap[1].GetSafeHandle();
		m_led11.SetBitmap(hBmp[1]);
		/*************************************/
		num_frame++;
		allnumber++;
		Sleep(4000);
	}
		
	
	/*
	while (1)
	{
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
		d_sdDlg->m_HistSendData.SetSel(d_sdDlg->m_HistSendData.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
		d_sdDlg->m_HistSendData.ReplaceSel(strDisplay); //�滻��ǰ�ı�
		//	d_sdDlg->GetDlgItem(IDC_SENDDATA_EDIT)->SetWindowText(strDisplay);
		d_sdDlg->SetDlgItemInt(IDC_SEND_EDIT, h*Num_Data); //���������ܱ�������ʾ
		d_sdDlg->SetDlgItemInt(IDC_CURRENTSENDNUM_EDIT, num_frame);//��ʾ��֡��
		fclose(fp);//C���Ա���µĹر��ļ�
		free(temp); //�ͷ�ָ��ָ����ڴ�
		temp = NULL;//ָ���ڴ��ָ����Ϊ�գ���ֹ������治С��ʹ������

		while (1)
		{
			if (commondstate == 0)					 //�жϴ�ʱû��ָ���
			{
				messagestate = 1;						//��ʱ��������
				encode(buffer);

				Sleep(4000);
				((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->SendMessage(P_Data_CC, Len_DataInProcess);
			}
			break;
		}
		messagestate = 0;
		num_frame++;
		if (n == h)
		{
			break;
		}
	}*/
/*	CFile file(SendA.gSendDataPath, CFile::modeRead | CFile::typeBinary);
	char *pBuf;
	int dwFileLen; //
	dwFileLen = file.GetLength();
	pBuf = new char[dwFileLen + 1];
	pBuf[dwFileLen] = 0;
	file.Read(pBuf, dwFileLen);
	
	if (dwFileLen%Num_Data)						
	{	
		n = dwFileLen / Num_Data + 1;				//��������
	}
	else
	{
		n = dwFileLen / Num_Data;					//������
	}

	temp = new char[n*Num_Data + 1];
	temp[n*Num_Data] = 0;
	for (int i = 0; i < n*Num_Data; i++)
	{
		if (i < dwFileLen)
			temp[i] = pBuf[i];
		else
			temp[i] = 0;
	}

	CString strDisplay;

	
	for (int i = 0; i < n*Num_Data; i++) //size_tֻ��Ϊ����߿���ֲ��
	{
		strDisplay += temp[i];
	} Char������תCString����
	//��Ҫ���͵������͵�CStatusDisply�Ի������еķ������ݱ༭��
	d_sdDlg->GetDlgItem(IDC_SENDDATA_EDIT)->SetWindowText(strDisplay); 
	d_sdDlg->SetDlgItemInt(IDC_SEND_EDIT, dwFileLen); //���������ܱ�������ʾ
	d_sdDlg->SetDlgItemInt(IDC_CURRENTSENDNUM_EDIT, num_frame);//��ʾ��֡��
//	MessageBox(strDisplay); //������Գ���
	file.Close();
//	delete[] pBuf;

	
	*/
		
}

// ��ͼ
void CDuplex::OnPaint()
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
	dc.Rectangle(15, 20, 500, 430); //����һ��͸�����ı���
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
}



/*==================================*/
//
// FunctionName : systemtime
// Description      :  ��ȡϵͳʱ�䲢��ʾ
//
/*=================================*/
void CDuplex::SystemTime()
{
	CString strTime;
	CTime tm;
	tm = CTime::GetCurrentTime(); //��ȡϵͳ��ǰʱ��
	strTime = tm.Format("%Y.%m.%d %X"); //��ʽת��
		CmenuDlg *ppDlg = (CmenuDlg*)AfxGetApp()->m_pMainWnd;
	//AfxGetMainWnd��Ӧ�ó������̵߳��ã����������Ϲ��򷵻�Ӧ�ó���������ڡ�����ú�����Ӧ�ó���Ĵ��̵߳��ã��ú�������������õ����߳����ӵ�������
//		CmenuDlg *ppDlg = (CmenuDlg*)AfxGetMainWnd();
		ppDlg->m_Hist.SetSel(ppDlg->m_Hist.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
		ppDlg->m_Hist.ReplaceSel(strTime + "\r\n" );
//	return strTime;
}

void CDuplex::arqarray(int framecounter)
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

void CDuplex::arqsend(int framecounter)
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


BOOL CDuplex::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	/********************************��������******************************************/
	font.CreatePointFont(110, _T("΢���ź�")); //����������ʽ������110����11������
	GetDlgItem(IDC_DUPLEXPROCEDURES_STATIC)->SetFont(&font); //�����崫�ݸ���̬��

	m_grey = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_GREY));
	m_red = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_RED));
	//AfxGetInstanceHandle():This function allows you to retrieve (ȡ��) the instance handle of the current application.
	//MAKEINTRESOURCE macro (��):Converts an integer value to a resource type compatible with the resource-management functions. This macro is used in place of a string containing the name of the resource.

	/*********��ʼled��Ϊ��ɫ**********/
	m_led1.SetBitmap(m_grey);
	m_led2.SetBitmap(m_grey);
	m_led3.SetBitmap(m_grey);
	m_led4.SetBitmap(m_grey);
	m_led5.SetBitmap(m_grey);
	m_led6.SetBitmap(m_grey);
	m_led7.SetBitmap(m_grey);
	m_led8.SetBitmap(m_grey);
	m_led9.SetBitmap(m_grey);
	m_led10.SetBitmap(m_grey);
	m_led11.SetBitmap(m_grey);
	m_led12.SetBitmap(m_grey);
	m_led13.SetBitmap(m_grey);
	m_led14.SetBitmap(m_grey);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
