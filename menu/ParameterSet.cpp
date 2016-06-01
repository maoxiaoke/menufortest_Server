// ParameterSet.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "menu.h"
#include "ParameterSet.h"
#include "afxdialogex.h"
#include "menuDlg.h"
//#include "StatusDisplayDlg.h"


// CParameterSet �Ի���

IMPLEMENT_DYNAMIC(CParameterSet, CDialogEx)

CParameterSet::CParameterSet(CWnd* pParent /*=NULL*/)
	: CDialogEx(CParameterSet::IDD, pParent)
	, m_FrameSpinedit(0)
//	, sdDlg(NULL)
{

}

CParameterSet::~CParameterSet()
{
}

void CParameterSet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);


	DDX_Control(pDX, IDC_PROTOCOLMODE_COMBO, m_ProtocolMode);
	DDX_Control(pDX, IDC_ATUOARQ_COMBO, m_AutoArq);
	DDX_Control(pDX, IDC_FRAMELEN_SPIN, m_FrameLenSpin);
	DDX_Text(pDX, IDC_FRAMESPIN_EDIT, m_FrameSpinedit);
	DDX_Control(pDX, IDC_MODULATION_COMBO, m_ModulationCombo);
	DDX_Control(pDX, IDC_CHANNELSTATUS_COMBO, m_ChannelStatusCombo);
	DDX_Control(pDX, IDC_CCCODE_COMBO, m_CcCodeCombo);
	//  DDX_Control(pDX, IDC_GROUPBOX1, m_GroupBox1); //GroupBox�ؼ�����
	DDX_Control(pDX, IDC_CCCODE_COMBO2, m_CcCodeCombo2);
	DDX_Control(pDX, IDC_MODULATION_COMBO2, m_ModulationCombo2);
	DDX_Control(pDX, IDC_SENDSOUCER_EDIT, m_SendSoucerEdit);
}


BEGIN_MESSAGE_MAP(CParameterSet, CDialogEx)
//	ON_WM_INITMENU()
//	ON_CBN_SELCHANGE(IDC_COMBO1, &CParameterSet::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_SENDSOUCER_BUTTON, &CParameterSet::OnBnClickedSendsoucerButton)
	ON_EN_CHANGE(IDC_FRAMESPIN_EDIT, &CParameterSet::OnEnChangeFramespinEdit)
	ON_BN_CLICKED(IDC_RECEIVESAVE_BUTTON, &CParameterSet::OnBnClickedReceivesaveButton)
	ON_BN_CLICKED(IDC_RECEIVESOUCER_BUTTON, &CParameterSet::OnBnClickedReceivesoucerButton)
	ON_WM_PAINT()
	ON_CBN_SELCHANGE(IDC_PROTOCOLMODE_COMBO, &CParameterSet::OnCbnSelchangeProtocolmodeCombo)
//	ON_COMMAND(ID_LoadConfig, &CParameterSet::OnLoadconfig)
//ON_COMMAND(ID_LoadConfig, &CParameterSet::OnLoadconfig)
//ON_BN_CLICKED(IDC_LOADCONFIG_BUTTON, &CParameterSet::OnBnClickedLoadconfigButton)
//ON_BN_CLICKED(IDC_SAVECONFIG_BUTTON, &CParameterSet::OnBnClickedSaveconfigButton)
END_MESSAGE_MAP()


// CParameterSet ��Ϣ�������


//void CParameterSet::OnInitMenu(CMenu* pMenu)
//{
//	CDialogEx::OnInitMenu(pMenu);
//
//	return ;
//
//
//	// TODO:  �ڴ˴������Ϣ����������
//}


//BOOL CParameterSet::OnInitDialog()
//{
//	CDialogEx::OnInitDialog();
//	m_ParaSet.AddString(_T("ȫ˫��ģʽA<-->B"));
//	m_ParaSet.AddString(_T("��˫��ģʽ"));
//
//	m_ParaSet.SetCurSel(0);
//	SetDlgItemText(IDC_PROTOCOLMODE_COMBO, _T("ȫ˫��ģʽA<-->B"));
//	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
//
//	return TRUE;  // return TRUE unless you set the focus to a control
//	// �쳣:  OCX ����ҳӦ���� FALSE
//}


//BOOL CParameterSet::OnInitDialog()
//{
//	CDialogEx::OnInitDialog();
//
//	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
//	m_ProtocolMode.AddString(_T("ȫ˫��ģʽA<-->B"));
//	m_ProtocolMode.AddString(_T("��˫��ģʽ"));
//
//	m_ProtocolMode.SetCurSel(0);
//	SetDlgItemText(IDC_PROTOCOLMODE_COMBO, _T("ȫ˫��ģʽA<-->B"));
//	return TRUE;  // return TRUE unless you set the focus to a control
//	// �쳣:  OCX ����ҳӦ���� FALSE
//}


//void CParameterSet::OnCbnSelchangeCombo1()
//{
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//	//m_ProtocolMode.GetCurSel();
//	CmenuDlg *pDlg = (CmenuDlg*)AfxGetMainWnd();
//	//pDlg->ModeChange(i);
//}


void CParameterSet::OnBnClickedSendsoucerButton() //�����������Դ�ļ�
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//*******************���ļ�*********************
	
	//���ù�����
	TCHAR szFilter[] = _T("����Դ�ļ�(*.dat)|*.dat|�����ļ�(*.*)|*.*||");
	//������ļ��Ի���
	CFileDialog fileDlg(TRUE, _T("dat"), NULL, 0, szFilter, this);
	CString strFilePath;

	//��ʾ�ļ��򿪶Ի���
	if (IDOK == fileDlg.DoModal())
	{
		//�������ˡ��򿪡���ť����ѡ����ļ�·����ʾ���༭����
		strFilePath = fileDlg.GetPathName();
		SetDlgItemText(IDC_SENDSOUCER_EDIT, strFilePath);

		/*==================================*/
		//�����ô��루code for test��
		//������δ����Ŀ����: �Ѽ��ص������ļ�������������StatusDisplayDlg�Ի����еı༭������ʾ����
		/*=================================*/
	
		/*
		CFile file(strFilePath, CFile::modeRead | CFile::typeBinary);
		char *pBuf;
		DWORD dwFileLen;
		dwFileLen = file.GetLength();
		pBuf = new char[dwFileLen + 1];
		pBuf[dwFileLen] = 0;
		file.Read(pBuf, dwFileLen);
	
		CString strDisplay;
		for (int i = 0; (size_t)i < dwFileLen; i++) //size_tֻ��Ϊ����߿���ֲ��
		{
			strDisplay += pBuf[i];
			
		}	
		sdDlg->GetDlgItem(IDC_RECEIVEDATA_EDIT)->SetWindowText(strDisplay);

		file.Close();
		delete[]pBuf;
		*/


	//	SendDlgItemMessage(, strDisplay, 0, 0);
	//	MessageBox(strDisplay);
	//	CWnd *pDlg = FindWindow(NULL, _T("IDD_STATUSDISPLAY_DIALOG"));	
	//	pDlg->GetDlgItem(IDC_RECEIVEDATA_EDIT)->SetWindowText(strDisplay);
	//	pDlg->SetDlgItemText(IDC_RECEIVEDATA_EDIT, strDisplay);
	//	GetParent()->GetParent()->SetDlgItemText(IDC_OPENFILE_EDIT, strDisplay);
	//	HWND hWnd;
	//	hWnd = ::FindWindow(NULL, _T("IDD_STATUSDISPLAY_DIALOG"));
	//	sddlg.m_ReceiveDataEdit.SetDlgItemText(IDC_RECEIVEDATA_EDIT, _T("Type in text") );
	//	GetParent()->GetParent()->SetDlgItemText(IDC_OPENFILE_EDIT, strDisplay);
		

	}







}


void CParameterSet::OnEnChangeFramespinEdit() //���ڱ༭��ؼ�����������ת��ťһ��仯
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	m_FrameSpinedit = GetDlgItemInt(IDC_FRAMESPIN_EDIT);

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CParameterSet::OnBnClickedReceivesaveButton() //���ջ�����Դ�ļ�
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	// ���ù�����   
	TCHAR szFilter[] = _T("����Դ�ļ�(*.dat)|*.dat|�ı��ļ�(*.txt)|*.txt|�����ļ�(*.*)|*.*||");
	// ���챣���ļ��Ի���   
	CFileDialog fileDlg(FALSE, _T("dat"), _T("my"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	CString strFilePath;

	// ��ʾ�����ļ��Ի���   
	if (IDOK == fileDlg.DoModal())
	{
		// ���������ļ��Ի����ϵġ����桱��ť����ѡ����ļ�·����ʾ���༭����   
		strFilePath = fileDlg.GetPathName();

		SetDlgItemText(IDC_RECEIVESAVE_EDIT, strFilePath);
	}
}


void CParameterSet::OnBnClickedReceivesoucerButton() //���ջ�������Դ�ļ�
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//���ù�����
	TCHAR szFilter[] = _T("����Դ�ļ�(*.dat)|*.dat|�����ļ�(*.*)|*.*||"); //��������������⣬�򲻿�txt�ļ�
	//������ļ��Ի���
	CFileDialog fileDlg(TRUE, _T("dat"), NULL, 0, szFilter, this);
	CString strFilePath;

	//��ʾ�ļ��򿪶Ի���
	if (IDOK == fileDlg.DoModal())
	{
		//�������ˡ��򿪡���ť����ѡ����ļ�·����ʾ���༭����
		strFilePath = fileDlg.GetPathName();
		SetDlgItemText(IDC_RECEIVESOUCER_EDIT, strFilePath);
	}
}


void CParameterSet::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()

	CPen pen[4]; //���廭�ʶ���
	CBrush brush[3]; //�����ˢ����
	pen[0].CreatePen(PS_DASHDOT, 1, RGB(0, 0, 255)); //������ʼ������
	brush[0].CreateStockObject(NULL_BRUSH); //��ʼ��ʵ�ĵĿջ�ˢ��û�б�����ɫ��
	dc.SelectObject(&brush[0]); //����ˢѡ��dc
	dc.SelectObject(&pen[0]);  //������ѡ��dc
	dc.SetBkMode(TRANSPARENT); //���ñ���ģʽΪ͸����Ҳ����ʹ��SetBkColor���ñ���ɫ
	dc.Rectangle(15, 30, 500, 100); //����һ��͸�����ı���
	//pen[0].DeleteObject(); //�ͷ�dc
	//brush[0].DeleteObject();  //ע�͵����ΪʲôҲ���ԣ��ѵ�������ͷ���

	pen[1].CreatePen(PS_DASHDOT, 1, RGB(0, 0, 255)); //������ʼ������
	brush[1].CreateStockObject(NULL_BRUSH); //��ʼ��ʵ�ĵĿջ�ˢ��û�б�����ɫ��
	dc.SelectObject(&brush[1]); //
	dc.SelectObject(&pen[1]);  //����ˢѡ��dc
	//	dc.SetBkMode(TRANSPARENT);
	dc.SetBkMode(TRANSPARENT); //���ñ���ģʽΪ͸����Ҳ����ʹ��SetBkColor���ñ���ɫ
	//DrawRect(&dc);
	dc.Rectangle(15, 120, 500, 270); //����һ��͸�����ı���

	//pen[1].DeleteObject();
	//brush[1].DeleteObject();
	pen[2].CreatePen(PS_DASHDOT, 1, RGB(0, 0, 255)); //������ʼ������
	brush[2].CreateStockObject(NULL_BRUSH); //��ʼ��ʵ�ĵĿջ�ˢ��û�б�����ɫ��
	dc.SelectObject(&brush[2]); //
	dc.SelectObject(&pen[2]);  //����ˢѡ��dc
	//	dc.SetBkMode(TRANSPARENT);
	dc.SetBkMode(TRANSPARENT); //���ñ���ģʽΪ͸����Ҳ����ʹ��SetBkColor���ñ���ɫ
	//DrawRect(&dc);
	dc.Rectangle(15, 290, 500, 430); //����һ��͸�����ı���

	//pen[2].DeleteObject();
	//brush[2].DeleteObject();

	pen[3].CreatePen(PS_DASHDOT, 1, RGB(0, 0, 255)); //������ʼ������
	dc.SelectObject(&pen[3]);  //����ˢѡ��dc
	dc.MoveTo(240, 190); //��ֱ��
	dc.LineTo(240, 250); //��ֱ��
	//	pen[3].DeleteObject();

}


BOOL CParameterSet::OnInitDialog()
{
	CDialogEx::OnInitDialog();
// TODO:  �ڴ���Ӷ���ĳ�ʼ��
//	CParameterSet *ps_Dlg;
//	ps_Dlg = this;
	/********************************��������******************************************/
	font.CreatePointFont(120, _T("΢���ź�")); //����������ʽ������120����12������
	GetDlgItem(IDC_SYSTEMPARAMETER_STATIC)->SetFont(&font); //�����崫�ݸ���̬��
	GetDlgItem(IDC_SENDER_STATIC)->SetFont(&font); //�����崫�ݸ���̬��
	GetDlgItem(IDC_RECEIVER_STATIC)->SetFont(&font); //�����崫�ݸ���̬��

	

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CParameterSet::OnCbnSelchangeProtocolmodeCombo() //���ģʽѡ����Ͽ�->Э�鹲������ʽ
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int i = m_ProtocolMode.GetCurSel();
	CmenuDlg *pDlg = (CmenuDlg*)AfxGetMainWnd();//��ø����ڵ�ָ��
	pDlg->ModeChange(i);
}


//void CParameterSet::OnLoadconfig(CString strFilePath)  //���������ļ�
//{
//	// TODO:  �ڴ���������������
//}


//void CParameterSet::OnLoadconfig()
//{
//	// TODO:  �ڴ���������������
//	
//		//*******************���ļ�*********************
//		//���ù�����
//		TCHAR szFilter[] = _T("�ı��ļ�(*.ini)|*.ini|�����ļ�(*.*)|*.*||"); 
//		//������ļ��Ի���
//		CFileDialog fileDlg(TRUE, _T("ini"), NULL, 0, szFilter, this);
//		CString strFilePath;
//	
//		//��ʾ�ļ��򿪶Ի���
//	if (IDOK == fileDlg.DoModal())
//		{
//		//�������ˡ��򿪡���ť����ѡ����ļ�·����ʾ���༭����
//		strFilePath = fileDlg.GetPathName();
//		SetDlgItemText(IDC_OPENFILE_EDIT, strFilePath);
//		//m_parameterset.OnLoadconfig();
//		}
//}


//void CParameterSet::OnBnClickedLoadconfigButton()
//{
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//}

/*************************��ȡ������Ϣ******************************************************/
//�����ļ���ʽ����
/*
[�����ļ�����]
type = "Config"

[ϵͳ����]
EquipMode = 0
ProtocolMode = 0
ARQ = 1

[�����A����]
FrameLength = 200
ModulationMethod = 0
CC = 0
ChannelStatus = 0
SendDataPathA = "c:\\Users\\Administrator\\Desktop\\09Last_InstrCommunicationVer\\SendData.dat"

[���ջ�A����]
FrameLength = 0
ModulationMethod = 0
CC = 0
ReceiveDataPathA = "c:\\Users\\Administrator\\Desktop\\09Last_InstrCommunicationVer\\ReceiveData.dat"
RemoteDataPathA = "c:\\Users\\Administrator\\Desktop\\09Last_InstrCommunicationVer\\SendData.dat"

[�����B����]
FrameLength = 200
ModulationMethod = 0
CC = 0
ChannelStatus = 0
SendDataPathB = "c:\\Users\\Administrator\\Desktop\\InstrCommunicationVer\\SendData.dat"

[���ջ�B����]
FrameLength = 0
ModulationMethod = 0
CC = 0
ReceiveDataPathB = "c:\\Users\\Administrator\\Desktop\\InstrCommunicationVer\\ReceiveData.dat"
RemoteDataPathB = "c:\\Users\\Administrator\\Desktop\\InstrCommunicationVer\\SendData.dat"

//GetPrivateProfileString����
DWORD WINAPI GetPrivateProfileString(
_In_  LPCTSTR lpAppName,
_In_  LPCTSTR lpKeyName,
_In_  LPCTSTR lpDefault,
_Out_ LPTSTR  lpReturnedString,
_In_  DWORD   nSize,
_In_  LPCTSTR lpFileName
);
lpAppName������
lpKeyName������
lpDefault��Ĭ��ֵ
lpReturnedString��Ŀ�Ļ�����
nSize��Ŀ�Ļ������Ĵ�С
lpFileName��Ҫ��ȡ�������ļ����ļ�·��

//GetPrivateProfileInt����  ȡ��һ���ض������ļ��ļ���ֵ������ֵ��
UINT WINAPI GetPrivateProfileInt(
_In_ LPCTSTR lpAppName,
_In_ LPCTSTR lpKeyName,
_In_ INT     nDefault,
_In_ LPCTSTR lpFileName
);
lpAppName������
lpKeyName������
nDefault�����û���ҵ������ļ���Ĭ�Ϸ���ֵ
lpFileName�������ļ����ļ�·��


*/

void CParameterSet::ConFigure(CString strFilePath)
{
	//Э�鹤����ʽ
	int ProtocolMode;
	ProtocolMode = (int)GetPrivateProfileInt(_T("ϵͳ����"), _T("ProtocolMode"), 0, strFilePath);
	m_ProtocolMode.SetCurSel(ProtocolMode);
	OnCbnSelchangeProtocolmodeCombo(); //�����ļ��������غ���ú�������Э�������

	//ARQ
	int arq = (int)GetPrivateProfileInt(_T("ϵͳ����"), _T("ARQ"), 0, strFilePath);
	m_AutoArq.SetCurSel(arq);

	//���������  as A�ķ����
	//֡����
	int as_framelen = (int)GetPrivateProfileInt(_T("�����A����"), _T("FrameLength"), 0, strFilePath);
	CString len;
	len.Format(_T("%d"), as_framelen);
	SetDlgItemText(IDC_FRAMESPIN_EDIT, len);

	//���Ʒ�ʽ
	int as_Moudulation;
	as_Moudulation = (int)GetPrivateProfileInt(_T("�����A����"), _T("ModulationMethod"), 0, strFilePath);
	m_ModulationCombo.SetCurSel(as_Moudulation);
	//((CComboBox*)GetDlgItem(IDC_MODULATION_COMBO))->SetCurSel(a_Moudulation);   //����ͨ������CComboBox ���������ò���

	//CC
	int as_CC = (int)GetPrivateProfileInt(_T("�����A����"), _T("CC"), 0, strFilePath);
	m_CcCodeCombo.SetCurSel(as_CC);

	//�ŵ�״̬
	int as_ChannelStatus = (int)GetPrivateProfileInt(_T("�����A����"), _T("ChannelStatus"), 0, strFilePath);
	m_ChannelStatusCombo.SetCurSel(as_ChannelStatus);

	//���������Դ�ļ�
	CString as_SendDataPath;
	GetPrivateProfileString(_T("�����A����"), _T("SendDataPathA"), _T(""), as_SendDataPath.GetBuffer(100), 100, strFilePath);
	as_SendDataPath.ReleaseBuffer();//�ͷ�
	SetDlgItemText(IDC_SENDSOUCER_EDIT, as_SendDataPath);


	//���ջ�A����  ar A�Ľ��ջ�
	//���Ʒ�ʽ
	int ar_Moudulation;
	ar_Moudulation = (int)GetPrivateProfileInt(_T("���ջ�A����"), _T("ModulationMethod"), 0, strFilePath);
	m_ModulationCombo2.SetCurSel(ar_Moudulation);

	//CC
	int ar_CC = (int)GetPrivateProfileInt(_T("���ջ�A����"), _T("CC"), 0, strFilePath);
	m_CcCodeCombo.SetCurSel(ar_CC);

	//���ջ������ļ�
	CString ar_SendDataPath1;
	GetPrivateProfileString(_T("���ջ�A����"), _T("ReceiveDataPathA"), _T(""), ar_SendDataPath1.GetBuffer(100), 100, strFilePath);
	ar_SendDataPath1.ReleaseBuffer();//�ͷ�
	SetDlgItemText(IDC_RECEIVESAVE_EDIT, ar_SendDataPath1);

	//���ջ�����Դ�ļ�
	CString ar_SendDataPath2;
	GetPrivateProfileString(_T("���ջ�A����"), _T("RemoteDataPathA"), _T(""), ar_SendDataPath2.GetBuffer(100), 100, strFilePath);
	ar_SendDataPath2.ReleaseBuffer();//�ͷ�
	SetDlgItemText(IDC_RECEIVESOUCER_EDIT, ar_SendDataPath2);

	MessageBox(_T("�������óɹ���"));
}
void CParameterSet::ConFigSave(CString strFilePath) //���������ļ�
{
	//�����ļ�����
	WritePrivateProfileString(_T("�����ļ�����"), _T("type"), _T("Config"), strFilePath);

	//ϵͳ����
	WritePrivateProfileString(_T("ϵͳ����"), _T("EquipMode"), _T("0"), strFilePath);

	int pm = m_ProtocolMode.GetCurSel();
	//int pm = ((CComboBox*)GetDlgItem(IDC_PROTOCOLMODE_COMBO))->GetCurSel();
	CString ProtocolMode;
	ProtocolMode.Format(_T("%d"), pm);
	WritePrivateProfileString(_T("ϵͳ����"), _T("ProtocolMode"), ProtocolMode, strFilePath);

	int ar = m_AutoArq.GetCurSel();
	CString arq;
	arq.Format(_T("%d"), ar);
	WritePrivateProfileString(_T("ϵͳ����"), _T("ARQ"), arq, strFilePath);

	//���������
	CString as_framelen;
	GetDlgItemText(IDC_FRAMESPIN_EDIT,as_framelen);
	WritePrivateProfileString(_T("�����A����"), _T("FrameLength"), as_framelen, strFilePath);

	int as_m = m_ModulationCombo.GetCurSel();
	CString as_modulation;
	as_modulation.Format(_T("%d"), as_m);
	WritePrivateProfileString(_T("�����A����"), _T("ModulationMethod"), as_modulation, strFilePath);

	int as_c = m_CcCodeCombo.GetCurSel();
	CString as_CC;
	as_CC.Format(_T("%d"), as_c);
	WritePrivateProfileString(_T("�����A����"), _T("CC"), as_CC, strFilePath);

	int as_cs = m_ChannelStatusCombo.GetCurSel();
	CString as_ChannelStatus;
	as_ChannelStatus.Format(_T("%d"), as_cs);
	WritePrivateProfileString(_T("�����A����"), _T("ChannelStatus"), as_ChannelStatus, strFilePath);

	CString as_DataPath;
	GetDlgItemText(IDC_SENDSOUCER_EDIT, as_DataPath);
	WritePrivateProfileString(_T("�����A����"), _T("SendDataPathA"), as_DataPath, strFilePath);

	//���ջ�����
	int ar_m = m_ModulationCombo2.GetCurSel();
	CString ar_modulation;
	ar_modulation.Format(_T("%d"), ar_m);
	WritePrivateProfileString(_T("���ջ�A����"), _T("ModulationMethod"), ar_modulation, strFilePath);
	
	int ar_c = m_CcCodeCombo2.GetCurSel();
	CString ar_CC;
	ar_CC.Format(_T("%d"), ar_c);
	WritePrivateProfileString(_T("���ջ�A����"), _T("CC"), ar_CC, strFilePath);

	CString ar_ReceiveData;
	GetDlgItemText(IDC_RECEIVESAVE_EDIT, ar_ReceiveData);
	WritePrivateProfileString(_T("���ջ�A����"), _T("ReceiveDataPathA"), ar_ReceiveData, strFilePath);

	CString ar_RemoteData;
	GetDlgItemText(IDC_RECEIVESOUCER_EDIT, ar_RemoteData);
	WritePrivateProfileString(_T("���ջ�A����"), _T("RemoteDataPathA"), ar_RemoteData, strFilePath);

	MessageBox(_T("��������ɹ�"));
}

//void CParameterSet::OnBnClickedSaveconfigButton()
//{
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//}
