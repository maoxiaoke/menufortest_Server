
// menuDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "menu.h"
#include "menuDlg.h"
#include "afxdialogex.h"
#include "FileViewDlg.h" //Ϊ���ڲ˵����ļ������д��ļ�������� IDD_FILEHANDLE_DIALOG
#include "ParameterSet.h"
#include "shellapi.h" //�˵�->����->ʹ���ĵ� �����ⲿ����ʱ��Ҫ��ͷ�ļ�
#include "windows.h"
#include "TransRevShare.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnUserguider();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	//ON_COMMAND(ID_UserGuider, &CAboutDlg::OnUserguider)
END_MESSAGE_MAP()


// CmenuDlg �Ի���



CmenuDlg::CmenuDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CmenuDlg::IDD, pParent)
	, sPort(0)
//	, m_sWords(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmenuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tab);
	//  DDX_Control(pDX, IDC_COMBO1, m_lala);
	DDX_Control(pDX, IDC_HIST_EDIT, m_Hist);
	DDX_Control(pDX, IDC_IPADDRESS, ServerIP);
	DDX_Text(pDX, IDC_SPORT_EDIT, sPort);
	DDX_Control(pDX, IDC_SPORT_EDIT, m_ServerPort);
	DDX_Control(pDX, IDC_STARTMONITOR_BUTTON, m_ListenButton);
	DDX_Control(pDX, IDC_ENDMONITOR_BUTTON, m_ListenEndButton);
//	DDX_Text(pDX, IDC_OPENFILE_EDIT, m_sWords);
}

BEGIN_MESSAGE_MAP(CmenuDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_OPEN, &CmenuDlg::OnOpen)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CmenuDlg::OnTcnSelchangeTab1)
//	ON_COMMAND(ID_LoadConfig, &CmenuDlg::OnLoadconfig)
	ON_COMMAND(ID_SAVE, &CmenuDlg::OnSave)
//	ON_COMMAND(ID_ParaSet, &CmenuDlg::OnParaset)
//ON_BN_CLICKED(IDOK, &CmenuDlg::OnBnClickedOk)
ON_WM_CREATE()
//ON_COMMAND(ID_UserGuider, &CmenuDlg::OnUserguider)
ON_COMMAND(ID_UserGuider, &CmenuDlg::OnUserguider)
ON_COMMAND(ID_LoadConfig, &CmenuDlg::OnLoadconfig)
ON_COMMAND(ID_SAVECONFIG, &CmenuDlg::OnSaveconfig)
ON_COMMAND(ID_BOOTSYSTEM, &CmenuDlg::OnBootsystem)
ON_BN_CLICKED(IDC_STARTMONITOR_BUTTON, &CmenuDlg::OnBnClickedStartmonitorButton)
ON_BN_CLICKED(IDC_ENDMONITOR_BUTTON, &CmenuDlg::OnBnClickedEndmonitorButton)
//ON_BN_CLICKED(IDC_SEND_BUTTON, &CmenuDlg::OnBnClickedSendButton)
ON_COMMAND(ID_SendMail, &CmenuDlg::OnSendmail)
ON_COMMAND(ID_StatusDisplay, &CmenuDlg::OnStatusdisplay)
ON_COMMAND(ID_ParaSet, &CmenuDlg::OnParaset)
ON_COMMAND(ID_LOGOUT, &CmenuDlg::OnLogout)
ON_BN_CLICKED(IDC_CLEANUP_BUTTON, &CmenuDlg::OnBnClickedCleanupButton)
END_MESSAGE_MAP()


// CmenuDlg ��Ϣ�������

BOOL CmenuDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	//��ʼ��IP�ؼ�
	BYTE nFild[4] = { 10	, 28, 155, 20 };
	ServerIP.SetAddress(nFild[0], nFild[1], nFild[2], nFild[3]);
	//Ĭ�϶˿ں�
	SetDlgItemText(IDC_SPORT_EDIT, _T("1026"));//Ĭ�϶˿ں�
	//�ؼ�����
	m_ListenEndButton.EnableWindow(false);
	


    //���ز˵�
	CMenu m_menu;
	m_menu.LoadMenu(IDR_MENU1);
	SetMenu(&m_menu);

	/********************************��������******************************************/
	font[0].CreatePointFont(100, _T("΢���ź�")); //����������ʽ������100����10������
	GetDlgItem(IDC_RECODE_STATIC)->SetFont(&font[0]); //�����崫�ݸ���̬��
	GetDlgItem(IDC_IP_STATIC)->SetFont(&font[0]); //�����崫�ݸ���̬��
	GetDlgItem(IDC_PORT_STATIC)->SetFont(&font[0]); //�����崫�ݸ���̬��

	font[1].CreatePointFont(120, _T("΢���ź�")); //����������ʽ������120����12������
	GetDlgItem(IDC_NUAA_STATIC)->SetFont(&font[1]); //�����崫�ݸ���̬��


	//����ȼ�
	//HACCEL m_hAcc = LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_ACCELERATOR1));
	//INT_PTR nRes;   //���ڱ���DoModal�����ķ���ֵ

	//CParameterSet parameterset;   //����Ի�����CFileViewDlg��ʵ��������
	//nRes = m_parameterset.DoModal();  //�����Ի���
	//if (IDCANCEL == nRes)           //�ж϶Ի����Ƴ���ķ���ֵ�Ƿ�ΪIDCANCEL
	//{
	//	return ;
//	}



	//��ʼ����ǩ
	CRect tabRect; //��ǩ�ؼ��ͻ�����λ�úʹ�С
	m_tab.InsertItem(0, _T("��������"));    //�����һ����ǩ,m_tab�Ǳ�ǩ�ؼ������ı���
	m_tab.InsertItem(1, _T("Э����"));    //����ڶ�����ǩ
	m_tab.InsertItem(2, _T("��������")); //�����������ǩ

	//m_tab.SetCurSel(0);

	m_parameterset.Create(IDD_PARAMETER_DIALOG, &m_tab); //������һ����ǩ
	m_duplex.Create(IDD_DUPLEX_DIALOG, &m_tab);  //�����ڶ�����ǩ
	//m_halfduplexdlg.Create(IDD_HALFDUPLEX_DIALOG, &m_tab); //��˫�����Ա�ǩ
	m_statusdisplydlg.Create(IDD_STATUSDISPLAY_DIALOG, &m_tab);  //������������ǩ

//	m_parameterset.sdDlg = &m_statusdisplydlg; //�ӶԻ���֮��������ݵ�˵��
	m_duplex.psDlg = &m_parameterset;//�ӶԻ���֮��������ݵ�˵��
	m_duplex.d_sdDlg = &m_statusdisplydlg; 
	m_ServerSocket.ds_sdDlg = &m_statusdisplydlg;
	m_halfduplexdlg.psHDlg = &m_parameterset;
	m_halfduplexdlg.d_sdHDlg = &m_statusdisplydlg;

	

	m_tab.GetClientRect(&tabRect); //��ȡ��ǩ�ؼ��ͻ���Rect
	//����tabRect��ʹ�串�Ƿ�Χ�ʺϷ��ñ�ǩҳ
	tabRect.left += 1;
	tabRect.right -= 1;
	tabRect.top += 25;
	tabRect.bottom -= 1;

	//���ݵ����õ�tabRect���õ�һ���Ի�������Ϊ����
	m_parameterset.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
	//���úõڶ����Ի�������Ϊ����
	m_duplex.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	//m_halfduplexdlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	//���úõ������Ի�������Ϊ��ʾ
	m_statusdisplydlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);


	//IDD_PARAMETERSET_DIALOG���ؼ���ʼ����Ҳ����ֱ����ParameterSet.cpp��OnInitdialog()������ֱ�ӳ�ʼ��
	/*****************************��Ͽ��ʼ��**********************************************************************************************/
	
	//������������Э��ģʽ�� ��Ͽ�ؼ��ĳ�ʼ��
	m_parameterset.m_ProtocolMode.AddString(_T("ȫ˫��A<->B")); //����б��ȫ˫��A<->B�� ����ֱ��m_ProtocolMode.AddString(.....)
	m_parameterset.m_ProtocolMode.AddString(_T("��˫��"));
	m_parameterset.m_ProtocolMode.AddString(_T("����A<-->B"));
//	m_parameterset.m_ProtocolMode.AddString(_T("����B-->A"));

	m_parameterset.m_ProtocolMode.SetCurSel(0); //�б��Ĭ��ѡ���һ��

	//�������������Զ��ش��� ��Ͽ�ؼ���ʼ��
	m_parameterset.m_AutoArq.AddString(_T("��ARQ"));
	m_parameterset.m_AutoArq.AddString(_T("��ARQ"));
	m_parameterset.m_AutoArq.SetCurSel(0);

	//�����������е��Ʒ�ʽ�� ��Ͽ�ؼ���ʼ��
	m_parameterset.m_ModulationCombo.AddString(_T("BPSK"));
	m_parameterset.m_ModulationCombo.AddString(_T("QPSK"));
	m_parameterset.m_ModulationCombo.SetCurSel(0);
	//�������������ŵ�״���� ��Ͽ�ؼ���ʼ��
	m_parameterset.m_ChannelStatusCombo.AddString(_T("��"));
	m_parameterset.m_ChannelStatusCombo.AddString(_T("��"));
	m_parameterset.m_ChannelStatusCombo.SetCurSel(0);
	//�����������з����������룩 ��Ͽ�ؼ���ʼ��
	m_parameterset.m_CcCodeCombo.AddString(_T("��"));
	m_parameterset.m_CcCodeCombo.AddString(_T("��"));
	m_parameterset.m_CcCodeCombo.SetCurSel(0);
	//�����������н��ջ�������룩 ��Ͽ�ؼ���ʼ��
	m_parameterset.m_CcCodeCombo2.AddString(_T("��"));
	m_parameterset.m_CcCodeCombo2.AddString(_T("��"));
	m_parameterset.m_CcCodeCombo2.SetCurSel(0);
	//�����������н��ջ�������룩 ��Ͽ�ؼ���ʼ��
	m_parameterset.m_ModulationCombo2.AddString(_T("BPSK"));
	m_parameterset.m_ModulationCombo2.AddString(_T("QPSK"));
	m_parameterset.m_ModulationCombo2.SetCurSel(0);



	/******************************Spin�ؼ���ʼ��**********************************************************************************************/
	m_parameterset.m_FrameLenSpin.SetBuddy(GetDlgItem(IDC_FRAMESPIN_EDIT)); // ������ת��ť�ͱ༭��ؼ����� ��ת�ؼ��Զ�����tab��ǰһ��
	m_parameterset.m_FrameLenSpin.SetRange(0, 10000); // ���ÿռ䰴ť��Χ
	m_parameterset.m_FrameLenSpin.SetPos(200); //������ת��ť��ǰλ��

	/************************************�����ļ���ʼ��*****************************************************/
	m_parameterset.ConfigureLoadFlag = false;

	quanshuanggong = true;
	banshuanggong = false;
	dangong = false;
	halfduplexExistFlag = false;
	simplexExistFlag = false;
	comboFirstChange = true;



	
	
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CmenuDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CmenuDlg::OnPaint()
{
	

	/*if (IsIconic())
	{*/
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

//		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	//}
	//else
	//{
	//	CDialogEx::OnPaint();
	//}

	CPen pen[2]; //���廭�ʶ���
	CBrush brush[2]; //�����ˢ����
	pen[0].CreatePen(PS_DASHDOT, 1, RGB(0, 0, 255)); //������ʼ������
	brush[0].CreateStockObject(NULL_BRUSH); //��ʼ��ʵ�ĵĿջ�ˢ��û�б�����ɫ��
	dc.SelectObject(&brush[0]); //����ˢѡ��dc
	dc.SelectObject(&pen[0]);  //������ѡ��dc
	dc.SetBkMode(TRANSPARENT); //���ñ���ģʽΪ͸����Ҳ����ʹ��SetBkColor���ñ���ɫ
	dc.Rectangle(10, 342, 200, 466); //����һ��͸�����ı���
	//pen[0].DeleteObject(); //�ͷ�dc
	//brush[0].DeleteObject();  //ע�͵����ΪʲôҲ���ԣ��ѵ�������ͷ���

	pen[1].CreatePen(PS_DASHDOT, 1, RGB(0, 0, 255)); //������ʼ������
	brush[1].CreateStockObject(NULL_BRUSH); //��ʼ��ʵ�ĵĿջ�ˢ��û�б�����ɫ��
	dc.SelectObject(&brush[1]); //����ˢѡ��dc
	dc.SelectObject(&pen[1]);  //������ѡ��dc
	dc.SetBkMode(TRANSPARENT); //���ñ���ģʽΪ͸����Ҳ����ʹ��SetBkColor���ñ���ɫ
	dc.Rectangle(10, 58, 200, 330); //����һ��͸�����ı���
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CmenuDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CmenuDlg::OnOpen() //����˵������ļ�->�򿪡�����
{
	// TODO:  �ڴ���������������
	//MessageBox(_T("U choose copy"), _T("menu ID"));


	//*******************���ļ�*********************
		//���ù�����
	TCHAR szFilter[] = _T("�ı��ļ�(*.txt)|*.txt|�����ļ�(*.*)|*.*||"); //��������������⣬�򲻿�txt�ļ�
	//������ļ��Ի���
	CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);
	CString strFilePath;

	//��ʾ�ļ��򿪶Ի���
	if (IDOK == fileDlg.DoModal())
	{
		//�������ˡ��򿪡���ť����ѡ����ļ�·����ʾ���༭����
		strFilePath = fileDlg.GetPathName();
		SetDlgItemText(IDC_OPENFILE_EDIT, strFilePath);
	}

	//******************�����ļ������Ի���*********************
	INT_PTR nRes;   //���ڱ���DoModal�����ķ���ֵ

	CFileViewDlg  fileviewDlg;   //����Ի�����CFileViewDlg��ʵ��������
	nRes = fileviewDlg.DoModal();  //�����Ի���
	if (IDCANCEL == nRes)           //�ж϶Ի����Ƴ���ķ���ֵ�Ƿ�ΪIDCANCEL
	{
		return;
	}



}

// Ϊm_tab��ǩ�ؼ���֪ͨ��ϢTCN_SELCHANGE��Ӵ�����
void CmenuDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	CRect tabRect;  //��ǩ�ؼ��ͻ�����Rect

	//��ȡRect��ʹ�串�Ƿ�Χ�ʺϷ��ñ�ǩҳ
	m_tab.GetClientRect(&tabRect);
	tabRect.left += 1;
	tabRect.right -= 1;
	tabRect.top += 25;
	tabRect.bottom -= 1;
	/*   �������ֻ�ǲ�����*/
//	int	protocolmode = 1;

	if (quanshuanggong)
	{
		switch (m_tab.GetCurSel()) // ������ǩ����
		{
			//���ѡ��ǰ��ǩ������ʾ��Ի������������Ի���
		case 0:
			m_parameterset.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
			m_duplex.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_statusdisplydlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);

			break;

		case 1:
			m_parameterset.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_duplex.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
			m_statusdisplydlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);

			break;
		case 2:
			m_duplex.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_parameterset.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_statusdisplydlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);

	/*		{   //Switch����г�ʼ�����̣��������ж��岿�֣���Ҫ�����岿���ô�����������
				CString strfilepath;
				m_parameterset.GetDlgItem(IDC_SENDSOUCER_EDIT)->GetWindowText(strfilepath);
				CFile file(strfilepath, CFile::modeRead | CFile::typeBinary);
				char *pBuf;
				DWORD dwFileLen;
				dwFileLen = file.GetLength();
				pBuf = new char[dwFileLen + 1];
				pBuf[dwFileLen] = 0;
				file.Read(pBuf, dwFileLen);

				CString strDisplay;
				//	strDisplay.Format(_T("%s"), pBuf);
				for (int i = 0; (size_t)i < dwFileLen; i++) //size_tֻ��Ϊ����߿���ֲ��
				{
					strDisplay += pBuf[i];

				}
				m_statusdisplydlg.GetDlgItem(IDC_RECEIVEDATA_EDIT)->SetWindowText(strDisplay);
				file.Close();
				delete[]pBuf;
			}*/
			
			break;
		default:
			break;
		}
	}
	if (banshuanggong)
	{
		switch (m_tab.GetCurSel()) // ������ǩ����
		{
			//���ѡ��ǰ��ǩ������ʾ��Ի������������Ի���
		case 0:
			m_parameterset.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
			m_halfduplexdlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_statusdisplydlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);

			break;

		case 1:
			m_parameterset.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_halfduplexdlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
			m_statusdisplydlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);

			break;
		case 2:
			m_halfduplexdlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_parameterset.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_statusdisplydlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);

			break;

		default:
			break;
		}
	}

	if (dangong)
	{
		switch (m_tab.GetCurSel()) // ������ǩ����
		{
			//���ѡ��ǰ��ǩ������ʾ��Ի������������Ի���
		case 0:
			m_parameterset.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
			m_simplexdlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_statusdisplydlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);

			break;

		case 1:
			m_parameterset.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_simplexdlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
			m_statusdisplydlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);

			break;
		case 2:
			m_parameterset.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_simplexdlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_statusdisplydlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);

			break;

		default:
			break;
		}
	}

}


//void CmenuDlg::OnLoadconfig() //���������ļ�
//{
//	// TODO:  �ڴ���������������
//	//*******************���ļ�*********************
//	//���ù�����
//	TCHAR szFilter[] = _T("�ı��ļ�(*.ini)|*.ini|�����ļ�(*.*)|*.*||"); 
//	//������ļ��Ի���
//	CFileDialog fileDlg(TRUE, _T("ini"), NULL, 0, szFilter, this);
//	CString strFilePath;
//
//	//��ʾ�ļ��򿪶Ի���
//	if (IDOK == fileDlg.DoModal())
//	{
//		//�������ˡ��򿪡���ť����ѡ����ļ�·����ʾ���༭����
//		strFilePath = fileDlg.GetPathName();
//		SetDlgItemText(IDC_OPENFILE_EDIT, strFilePath);
//		m_parameterset.OnLoadconfig();
//	}
//
//}


void CmenuDlg::OnSave()  //����˵������ļ�->���桱���� ������
{
	// TODO:  �ڴ���������������
	// ���ù�����   
	TCHAR szFilter[] = _T("�ı��ļ�(*.txt)|*.txt|Word�ļ�(*.doc)|*.doc|�����ļ�(*.*)|*.*||");
	// ���챣���ļ��Ի���   
	CFileDialog fileDlg(FALSE, _T("doc"), _T("my"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	CString strFilePath;

	// ��ʾ�����ļ��Ի���   
	if (IDOK == fileDlg.DoModal())
	{
		// ���������ļ��Ի����ϵġ����桱��ť����ѡ����ļ�·����ʾ���༭����   
		strFilePath = fileDlg.GetPathName();
		//SetDlgItemText(IDC_SAVE_EDIT, strFilePath);
	}

}


//void CmenuDlg::OnParaset() //����˵������ļ�->�������á����� 
//{
//	// TODO:  �ڴ���������������
//
//	//INT_PTR nRes;   //���ڱ���DoModal�����ķ���ֵ
//
//	//CParameterSet parameterset;   //����Ի�����CFileViewDlg��ʵ��������
//	//nRes = parameterset.DoModal();  //�����Ի���
//	if (IDCANCEL == nRes)           //�ж϶Ի����Ƴ���ķ���ֵ�Ƿ�ΪIDCANCEL
//	{
//	//	return;
//	}
//}



//void CmenuDlg::OnBnClickedOk()
//{
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//	CDialogEx::OnOK();
//}


int CmenuDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;



	// TODO:  �ڴ������ר�õĴ�������
	
//	HBITMAP hBmp;
//	bitmap.LoadBitmap(IDB_OPENFILE_BITMAP);
//	GetMenu()->GetSubMenu(0)->SetMenuItemBitmaps(0, MF_BYPOSITION, &bitmap, &bitmap);

//	CBitmap *pMenuBitmap;// �����Ҫ�ڳ�Ա�����ﶨ��
//	pMenuBitmap = new CBitmap;
//	pMenuBitmap->LoadBitmap(IDB_OPENFILE_BITMAP);//��Ҫ���ص�ͼ����Դ
//	CMenu *m_menu;
//	m_menu = GetMenu()->GetSubMenu(0);//�Ӳ˵���0�������˵��ĵ�һ���Ӳ˵�
//	m_menu->SetMenuItemBitmaps(1, MF_BYPOSITION, pMenuBitmap, pMenuBitmap);
	return 0;
}





void CmenuDlg::OnUserguider() //����->ʹ��˵�� �����ⲿ������ĵ�  �ĵ�Ҫ���ڹ���Ŀ¼��
{
	// TODO:  �ڴ���������������
	//ShellExecute(this->m_hWnd, "open", "ʹ��˵��.docx", NULL, NULL, SW_SHOWNORMAL);  //����ʹ��˵���ĵ������ǲ���������
	ShellExecute(this->m_hWnd, (LPCWSTR)L"open", (LPCWSTR)L"ʹ��˵��.docx", NULL,NULL, SW_SHOWNORMAL);  // ����������ʹ�õ����
	//ShellExecute(this->m_hWnd, (LPCWSTR)L"open", (LPCWSTR)L"http://nuaa.edu.cn", NULL, NULL, SW_SHOW);   //������������Һ���ҳ
	//ShellExecute(this->m_hWnd, (LPCWSTR)L"open", (LPCWSTR)L" mailto:maoxiaoke@outlook.com", NULL, NULL, SW_SHOWNORMAL); //����ϵͳ�ʼ�
}
void CmenuDlg::OnSendmail()
{
	// TODO:  �ڴ���������������
	ShellExecute(this->m_hWnd, (LPCWSTR)L"open", (LPCWSTR)L" mailto:maoxiaoke@outlook.com", (LPCWSTR)L"", (LPCWSTR)L"", SW_SHOWNORMAL);
}


void CmenuDlg::OnLoadconfig()//���������ļ� ��������
{
	// TODO:  �ڴ���������������
	//*******************���ļ�*********************
		//���ù�����
		TCHAR szFilter[] = _T("�ı��ļ�(*.ini)|*.ini|�����ļ�(*.*)|*.*||"); 
		//������ļ��Ի���
		CFileDialog fileDlg(TRUE, _T("ini"), NULL, 0, szFilter, this);
		CString strFilePath;

		//��ʾ�ļ��򿪶Ի���
		if (IDOK == fileDlg.DoModal())
		{
			m_parameterset.ConfigureLoadFlag = true; //����ini�ļ���־ true��ʾ������ini�ļ�
			//�������ˡ��򿪡���ť����ѡ����ļ�·����ʾ���༭����
			strFilePath = fileDlg.GetPathName();
			SetDlgItemText(IDC_OPENFILE_EDIT, strFilePath);
			m_parameterset.ConFigure(strFilePath);
		}
}


//BOOL CmenuDlg::OnCommand(WPARAM wParam, LPARAM lParam)
//{
//	// TODO:  �ڴ����ר�ô����/����û���
//
//	return CDialogEx::OnCommand(wParam, lParam);
//}


void CmenuDlg::OnSaveconfig() //���������ļ�
{
	// TODO:  �ڴ���������������
	CString strFilePath;
	if (m_parameterset.ConfigureLoadFlag) //����Ѿ�������ini�ļ�����ֱ�ӱ��浽ԭ�����ļ���
	{
		GetDlgItemText(IDC_OPENFILE_EDIT, strFilePath); //��ȡҪ����������ļ�·��
	}
	else //�����½�ini�����ļ���������������
	{
		TCHAR szFilter[] = _T("�����ļ�(*.ini)|*.ini|�ı��ļ�(*.txt)|*.txt|�����ļ�(*.*)|*.*||");
		// ���챣���ļ��Ի���   
		CFileDialog fileDlg(FALSE, _T("ini"), _T("my"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
		if (IDOK == fileDlg.DoModal())
		{
			// ���������ļ��Ի����ϵġ����桱��ť����ѡ����ļ�·����ʾ���༭����   
			strFilePath = fileDlg.GetPathName();
			//SetDlgItemText(IDC_SAVE_EDIT, strFilePath);
		}
		else
		{
			return;
		}
		CFile file;
		if (!file.Open(strFilePath, CFile::modeCreate | CFile::modeWrite))
		{
			MessageBox(_T("�����ļ�����ʧ�ܣ�"));
			return;
		}
		file.Close();
	}
	m_parameterset.ConFigSave(strFilePath); //�������ò����洢����
}

void CmenuDlg::ModeChange(int i)
{
	m_parameterset.m_ProtocolMode.SetCurSel(i);

	int t = m_tab.GetCurSel();
	int y = i;

	if (y == 0)
	{
		quanshuanggong = true;
		banshuanggong = false;
		dangong = false;
		if (comboFirstChange)
		{

		}
		else
		{
			if (halfduplexExistFlag)
				m_halfduplexdlg.ShowWindow(false);
			if (simplexExistFlag)
				m_simplexdlg.ShowWindow(false);
		}
	}
	if (y == 1)
	{
		quanshuanggong = false;
		banshuanggong = true;
		dangong = false;
		m_duplex.ShowWindow(false);
		if (simplexExistFlag)
			m_simplexdlg.ShowWindow(false);
		if (!halfduplexExistFlag)
		{
			CRect tabRect;
			m_tab.GetClientRect(&tabRect);
			tabRect.left += 1;
			tabRect.right -= 1;
			tabRect.top += 25;
			tabRect.bottom -= 1;
			m_halfduplexdlg.Create(IDD_HALFDUPLEX_DIALOG, &m_tab);
			m_halfduplexdlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);

			comboFirstChange = false;
			halfduplexExistFlag = true;

		}


	}
	if (y == 2)
	{
		quanshuanggong = false;
		banshuanggong = false;
		dangong = true;
		m_duplex.ShowWindow(false);
		if (halfduplexExistFlag)
			m_halfduplexdlg.ShowWindow(false);
		if (!simplexExistFlag)
		{
			CRect tabRect;    // ��ǩ�ؼ��ͻ�����Rect   

			// ��ȡ��ǩ�ؼ��ͻ���Rect����������������ʺϷ��ñ�ǩҳ   
			m_tab.GetClientRect(&tabRect);
			tabRect.left += 0;
			tabRect.right -= 0;
			tabRect.top += 20;
			tabRect.bottom -= 1;

			m_simplexdlg.Create(IDD_SIMPLEX_DIALOG, &m_tab);//****************
			m_simplexdlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			comboFirstChange = false;
			simplexExistFlag = true;
		}
	}
}

/**************************************����ϵͳ*********************************************/
void CmenuDlg::OnBootsystem()
{
	// TODO:  �ڴ���������������
	CString strTime;
	CTime tm; 
	
	//������ʼ��
	SetTransmitterParameters = 0;
	SetControlParameters = 0;
	SetReceiverParameters = 0;
	SetVR = 0;
	ReportRequest = 0;
	HallCommond = 0;
	SetPLExtensions = 0;
	ReportSourceSCID = 0;

	RNMD_T = 0;
	LNMD_T = 0;
	Start_Hail_T = 0;
	Hailresponse_T = 0;
	ReceiveOver_T = 0;
	LNMD2_T = 0;
	RNMD2_T = 0;
	CarrierSend_T = 0;
	ResponseSend_T = 0;
	WaitCarrier_T = 0;

	RNMD_R = 0;
	LNMD_R = 0;
	Start_Hail_R = 0;
	Hailresponse_R = 0;
	ReceiveOver_R = 0;
	LNMD2_R = 0;
	RNMD2_R = 0;
	CarrierSend_R = 0;
	ResponseSend_R = 0;
	WaitCarrier_R = 0;

	messagestate = 0;					//�������ݷ���
	commondstate = 0;					//����ָ���
	missnumber = 0;						//��ʧ֡����ʼ��
	receivenumber = 1;					//ÿ�������յ���֡�����¼���
	NeedSerialNumber = 0;			//��Ҫ��֡��

	CommondGroup = (int *)malloc(24 * sizeof(int));				//��������ָ��洢�������ռ�
	ArqGroup = (int *)malloc(16 * sizeof(int));


	/*************��ձ༭������**************/
	m_statusdisplydlg.m_HistSendData.SetWindowText(_T(""));
	m_statusdisplydlg.m_HistReceiveData.SetWindowText(_T(""));
	m_statusdisplydlg.GetDlgItem(IDC_SEND_EDIT)->SetWindowText(_T(""));
	m_statusdisplydlg.GetDlgItem(IDC_RECEIVE_EDIT)->SetWindowText(_T(""));
	m_statusdisplydlg.GetDlgItem(IDC_AVERAGEERRORTATE_EDIT)->SetWindowText(_T(""));
	m_statusdisplydlg.GetDlgItem(IDC_CURRENTSENDNUM_EDIT)->SetWindowText(_T(""));
	m_statusdisplydlg.GetDlgItem(IDC_RESEND_FRAME_NUM_EDIT)->SetWindowText(_T(""));
	m_statusdisplydlg.GetDlgItem(IDC_MISSING_FRAME_NUM_EDIT)->SetWindowText(_T(""));
	m_statusdisplydlg.GetDlgItem(IDC_MISS_FRAME_RATE_EDIT)->SetWindowText(_T(""));
	m_statusdisplydlg.GetDlgItem(IDC_CURRENT_SERIAL_NUM_EDIT)->SetWindowText(_T(""));
	m_statusdisplydlg.GetDlgItem(IDC_CURRENTERRORRATE_EDIT)->SetWindowText(_T(""));
	/*****************************************/

	if (ConnectOkFlag == 1)
	{
		CString strFlag[2];
		m_parameterset.GetDlgItem(IDC_SENDSOUCER_EDIT)->GetWindowText(strFlag[0]);
		m_parameterset.GetDlgItem(IDC_RECEIVESOUCER_EDIT)->GetWindowText(strFlag[1]);
		if (strFlag[0].IsEmpty() || strFlag[1].IsEmpty())
		{
			MessageBox(_T("��ʾ�����������Դ�ļ���"));			//���ж��Ƿ����������Դ�ļ�
		}
		else
		{
			runandstopflag = true;  //����ϵͳ
			OperatingRecord(); //���ò�����¼��������֤������¼����Ĩ��

			int protocolmode = m_parameterset.m_ProtocolMode.GetCurSel(); //��ȡЭ�鷽ʽ
			// if(quanshuanggong == true)
			if (protocolmode == 0)  //ȫ˫��
			{
				tm = CTime::GetCurrentTime(); //��ȡϵͳ��ǰʱ��
				strTime = tm.Format("%Y.%m.%d %X"); //��ʽת��
				m_Hist.SetSel(m_Hist.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
				m_Hist.ReplaceSel(strTime + "\r\n" + _T("˫��Э�����\r\n")); //�滻��ǰ�ı�
				//		MessageBox(strTime);
				m_parameterset.GetSendAParameterValue(1);		//��ò������ý�������������������
				m_parameterset.GetReceiveAParameterValue(1); //��ý��ջ�����
				m_parameterset.GetSystemParameterValue(1);	//���ϵͳ����ֵ

				m_duplex.StartRunDuplex(1);		 //��ʼȫ˫��


			}
			if (protocolmode == 1)
			{
				tm = CTime::GetCurrentTime(); //��ȡϵͳ��ǰʱ��
				strTime = tm.Format("%Y.%m.%d %X"); //��ʽת��
				m_Hist.SetSel(m_Hist.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
				m_Hist.ReplaceSel(strTime + "\r\n" + _T("��˫��Э�����\r\n")); //�滻��ǰ�ı�
				//		MessageBox(strTime);
				m_parameterset.GetSendAParameterValue(1);		//��ò������ý�������������������
				m_parameterset.GetReceiveAParameterValue(1); //��ý��ջ�����
				m_parameterset.GetSystemParameterValue(1);	//���ϵͳ����ֵ

				m_halfduplexdlg.StartRunHalfDuplex(1);		 //��ʼ��˫��
			}
			if (protocolmode == 2)
			{
				tm = CTime::GetCurrentTime(); //��ȡϵͳ��ǰʱ��
				strTime = tm.Format("%Y.%m.%d %X"); //��ʽת��
				m_Hist.SetSel(m_Hist.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
				m_Hist.ReplaceSel(strTime + "\r\n" + _T("����Э�����\r\n")); //�滻��ǰ�ı�
				//		MessageBox(strTime);
				m_parameterset.GetSendAParameterValue(1);		//��ò������ý�������������������
				m_parameterset.GetReceiveAParameterValue(1); //��ý��ջ�����
				m_parameterset.GetSystemParameterValue(1);	//���ϵͳ����ֵ

				m_simplexdlg.StartRunSimplex(1);		 //��ʼ��˫��
			}
		}
		
	}
	else
	{
		MessageBox(_T("��ʾ�����������ӣ�"));
	}

}

/********************************������¼��������֤������¼����Ĩ��*********************************************/
void CmenuDlg::OperatingRecord()
{
	CString strTime;
	CTime tm;
	m_Hist.SetSel(m_Hist.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
	tm = CTime::GetCurrentTime(); //��ȡϵͳ��ǰʱ��
	strTime = tm.Format("%Y.%m.%d %X"); //��ʽת��
	if (runandstopflag)
	{
		m_Hist.ReplaceSel(strTime + "\r\n" + _T("����ϵͳ\r\n"));
	}
	else
	{
		m_Hist.ReplaceSel(strTime + "\r\n" + _T("ֹͣϵͳ\r\n"));
	}
	
}

/****************��ʼ����*************************/
void CmenuDlg::OnBnClickedStartmonitorButton()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	BYTE nFild[4] ;
	CString sIP, sP;
	UpdateData();			//ˢ������
	ServerIP.GetAddress(nFild[0], nFild[1], nFild[2], nFild[3]);
	sIP.Format(_T("%d.%d.%d.%d"), nFild[0], nFild[1], nFild[2], nFild[3]);
	sP.Format(_T("%d"), sPort); //�����ʾ��
//	sPort = GetDlgItemInt(IDC_SPORT_EDIT);//Ҳ����������ȡ�˿ں�
	if (sPort <= 1024 || sPort > 65535)
	{
		MessageBox(_T("��������ʵĶ˿ںţ���1025~65535��"));
		SetDlgItemText(IDC_SPORT_EDIT, _T(""));
//		SetDlgItemInt(IDC_SPORT_EDIT, 1026); ����Ҳ����
		GetDlgItem(IDC_SPORT_EDIT)->SetFocus(); //���ô��ڽ��㣬��˼���ǲ���������ı�����ͻ��Զ���λ���ı�����
		return;
	}

	m_ListenSocket.Create(sPort, 1, FD_ACCEPT, sIP); //��������˼���Socket
	m_ListenSocket.Listen(1);        //��ʼ����

	CString str;
	str = SystemTime();
	m_Hist.SetSel(m_Hist.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
	m_Hist.ReplaceSel(str + "\r\n" + _T("������ʼ\r\n")+_T("��ַ")+ sIP + _T("�˿�")+ sP+"\r\n"+_T("�ȴ��ͻ����ӡ���\r\n")); //�滻��ǰ�ı�

	//�ؼ�����
	ServerIP.EnableWindow(false);
	m_ServerPort.EnableWindow(false);
	m_ListenButton.EnableWindow(false);
	m_ListenEndButton.EnableWindow();

}


void CmenuDlg::OnBnClickedEndmonitorButton()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_ListenSocket.Close();//�رշ���˼���Socket

	//��ʾ
	CString str;
	str = SystemTime();
	m_Hist.SetSel(m_Hist.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
	m_Hist.ReplaceSel(str + "\r\n" + _T("ֹͣ����\r\n")); //�滻��ǰ�ı�

	//�ؼ�����
	ServerIP.EnableWindow();
	m_ServerPort.EnableWindow();
	m_ListenButton.EnableWindow();
	m_ListenEndButton.EnableWindow(false);

}

void CmenuDlg::SendMessagepro(int *P_SE, int fLen)
{
	m_ServerSocket.Send(P_SE, (fLen+1)* 4);  //����Ϣ��Send�����ֽڳ��ȣ�int��Ϊ�ĸ��ֽ�

}


//void CmenuDlg::OnBnClickedSendButton()
//{
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//	UpdateData();
//	m_ServerSocket.Send(m_sWords, (m_sWords.GetLength()+1)*2);  //����Ϣ
//}




void CmenuDlg::OnStatusdisplay()
{
	// TODO:  �ڴ���������������
	m_tab.SetCurSel(2);
	m_parameterset.ShowWindow(false);
	m_statusdisplydlg.ShowWindow(true);
	if (quanshuanggong)
		m_duplex.ShowWindow(false);
	if (banshuanggong)
		m_halfduplexdlg.ShowWindow(false);
}


void CmenuDlg::OnParaset()
{
	// TODO:  �ڴ���������������
	m_tab.SetCurSel(0);
	m_parameterset.ShowWindow(true);
	m_statusdisplydlg.ShowWindow(false);
	if (quanshuanggong)
		m_duplex.ShowWindow(false);
	if (banshuanggong)
		m_halfduplexdlg.ShowWindow(false);
}


void CmenuDlg::OnLogout()
{
	// TODO: Add your command handler code here
	CDialogEx::OnOK();
}


void CmenuDlg::OnBnClickedCleanupButton()
{
	// TODO: Add your control notification handler code here
	SetDlgItemText(IDC_HIST_EDIT, _T(" "));
}
