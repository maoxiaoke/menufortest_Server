
// menuDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "menu.h"
#include "menuDlg.h"
#include "afxdialogex.h"
#include "FileViewDlg.h" //为了在菜单栏文件操作中打开文件操作面板 IDD_FILEHANDLE_DIALOG
#include "ParameterSet.h"
#include "shellapi.h" //菜单->帮助->使用文档 调用外部程序时需要的头文件
#include "windows.h"
#include "TransRevShare.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CmenuDlg 对话框



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


// CmenuDlg 消息处理程序

BOOL CmenuDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	//初始化IP控件
	BYTE nFild[4] = { 10	, 28, 155, 20 };
	ServerIP.SetAddress(nFild[0], nFild[1], nFild[2], nFild[3]);
	//默认端口号
	SetDlgItemText(IDC_SPORT_EDIT, _T("1026"));//默认端口号
	//控件禁用
	m_ListenEndButton.EnableWindow(false);
	


    //加载菜单
	CMenu m_menu;
	m_menu.LoadMenu(IDR_MENU1);
	SetMenu(&m_menu);

	/********************************设置字体******************************************/
	font[0].CreatePointFont(100, _T("微软雅黑")); //创建字体样式，传递100请求10点字体
	GetDlgItem(IDC_RECODE_STATIC)->SetFont(&font[0]); //将字体传递给静态框
	GetDlgItem(IDC_IP_STATIC)->SetFont(&font[0]); //将字体传递给静态框
	GetDlgItem(IDC_PORT_STATIC)->SetFont(&font[0]); //将字体传递给静态框

	font[1].CreatePointFont(120, _T("微软雅黑")); //创建字体样式，传递120请求12点字体
	GetDlgItem(IDC_NUAA_STATIC)->SetFont(&font[1]); //将字体传递给静态框


	//添加热键
	//HACCEL m_hAcc = LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_ACCELERATOR1));
	//INT_PTR nRes;   //用于保存DoModal函数的返回值

	//CParameterSet parameterset;   //构造对话框类CFileViewDlg的实例（对象）
	//nRes = m_parameterset.DoModal();  //弹出对话框
	//if (IDCANCEL == nRes)           //判断对话框推出后的返回值是否为IDCANCEL
	//{
	//	return ;
//	}



	//初始化标签
	CRect tabRect; //标签控件客户区的位置和大小
	m_tab.InsertItem(0, _T("参数设置"));    //插入第一个标签,m_tab是标签控件关联的变量
	m_tab.InsertItem(1, _T("协议监控"));    //插入第二个标签
	m_tab.InsertItem(2, _T("性能评估")); //插入第三个标签

	//m_tab.SetCurSel(0);

	m_parameterset.Create(IDD_PARAMETER_DIALOG, &m_tab); //创建第一个标签
	m_duplex.Create(IDD_DUPLEX_DIALOG, &m_tab);  //创建第二个标签
	//m_halfduplexdlg.Create(IDD_HALFDUPLEX_DIALOG, &m_tab); //半双工测试标签
	m_statusdisplydlg.Create(IDD_STATUSDISPLAY_DIALOG, &m_tab);  //创建第三个标签

//	m_parameterset.sdDlg = &m_statusdisplydlg; //子对话框之间参数传递的说明
	m_duplex.psDlg = &m_parameterset;//子对话框之间参数传递的说明
	m_duplex.d_sdDlg = &m_statusdisplydlg; 
	m_ServerSocket.ds_sdDlg = &m_statusdisplydlg;
	m_halfduplexdlg.psHDlg = &m_parameterset;
	m_halfduplexdlg.d_sdHDlg = &m_statusdisplydlg;

	

	m_tab.GetClientRect(&tabRect); //获取标签控件客户区Rect
	//调整tabRect，使其覆盖范围适合放置标签页
	tabRect.left += 1;
	tabRect.right -= 1;
	tabRect.top += 25;
	tabRect.bottom -= 1;

	//根据调整好的tabRect放置第一个对话框，设置为隐藏
	m_parameterset.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
	//放置好第二个对话框，设置为隐藏
	m_duplex.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	//m_halfduplexdlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	//放置好第三个对话框，设置为显示
	m_statusdisplydlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);


	//IDD_PARAMETERSET_DIALOG面板控件初始化，也可以直接在ParameterSet.cpp的OnInitdialog()函数中直接初始化
	/*****************************组合框初始化**********************************************************************************************/
	
	//（参数设置中协议模式） 组合框控件的初始化
	m_parameterset.m_ProtocolMode.AddString(_T("全双工A<->B")); //添加列表项“全双工A<->B” 不能直接m_ProtocolMode.AddString(.....)
	m_parameterset.m_ProtocolMode.AddString(_T("半双工"));
	m_parameterset.m_ProtocolMode.AddString(_T("单工A<-->B"));
//	m_parameterset.m_ProtocolMode.AddString(_T("单工B-->A"));

	m_parameterset.m_ProtocolMode.SetCurSel(0); //列表框默认选择第一项

	//（参数设置中自动重传） 组合框控件初始化
	m_parameterset.m_AutoArq.AddString(_T("无ARQ"));
	m_parameterset.m_AutoArq.AddString(_T("有ARQ"));
	m_parameterset.m_AutoArq.SetCurSel(0);

	//（参数设置中调制方式） 组合框控件初始化
	m_parameterset.m_ModulationCombo.AddString(_T("BPSK"));
	m_parameterset.m_ModulationCombo.AddString(_T("QPSK"));
	m_parameterset.m_ModulationCombo.SetCurSel(0);
	//（参数设置中信道状况） 组合框控件初始化
	m_parameterset.m_ChannelStatusCombo.AddString(_T("好"));
	m_parameterset.m_ChannelStatusCombo.AddString(_T("差"));
	m_parameterset.m_ChannelStatusCombo.SetCurSel(0);
	//（参数设置中发射机卷积编码） 组合框控件初始化
	m_parameterset.m_CcCodeCombo.AddString(_T("无"));
	m_parameterset.m_CcCodeCombo.AddString(_T("有"));
	m_parameterset.m_CcCodeCombo.SetCurSel(0);
	//（参数设置中接收机卷积编码） 组合框控件初始化
	m_parameterset.m_CcCodeCombo2.AddString(_T("无"));
	m_parameterset.m_CcCodeCombo2.AddString(_T("有"));
	m_parameterset.m_CcCodeCombo2.SetCurSel(0);
	//（参数设置中接收机卷积编码） 组合框控件初始化
	m_parameterset.m_ModulationCombo2.AddString(_T("BPSK"));
	m_parameterset.m_ModulationCombo2.AddString(_T("QPSK"));
	m_parameterset.m_ModulationCombo2.SetCurSel(0);



	/******************************Spin控件初始化**********************************************************************************************/
	m_parameterset.m_FrameLenSpin.SetBuddy(GetDlgItem(IDC_FRAMESPIN_EDIT)); // 关联旋转按钮和编辑框控件对象 旋转控件自动关联tab序前一个
	m_parameterset.m_FrameLenSpin.SetRange(0, 10000); // 设置空间按钮范围
	m_parameterset.m_FrameLenSpin.SetPos(200); //设置旋转按钮当前位置

	/************************************配置文件初始化*****************************************************/
	m_parameterset.ConfigureLoadFlag = false;

	quanshuanggong = true;
	banshuanggong = false;
	dangong = false;
	halfduplexExistFlag = false;
	simplexExistFlag = false;
	comboFirstChange = true;



	
	
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CmenuDlg::OnPaint()
{
	

	/*if (IsIconic())
	{*/
		CPaintDC dc(this); // 用于绘制的设备上下文

//		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	//}
	//else
	//{
	//	CDialogEx::OnPaint();
	//}

	CPen pen[2]; //定义画笔对象
	CBrush brush[2]; //定义笔刷对象
	pen[0].CreatePen(PS_DASHDOT, 1, RGB(0, 0, 255)); //创建初始化画笔
	brush[0].CreateStockObject(NULL_BRUSH); //初始化实心的空画刷（没有背景颜色）
	dc.SelectObject(&brush[0]); //将画刷选入dc
	dc.SelectObject(&pen[0]);  //将画笔选入dc
	dc.SetBkMode(TRANSPARENT); //设置背景模式为透明，也可以使用SetBkColor设置背景色
	dc.Rectangle(10, 342, 200, 466); //创建一个透明的文本框
	//pen[0].DeleteObject(); //释放dc
	//brush[0].DeleteObject();  //注释掉这个为什么也可以？难道用完就释放了

	pen[1].CreatePen(PS_DASHDOT, 1, RGB(0, 0, 255)); //创建初始化画笔
	brush[1].CreateStockObject(NULL_BRUSH); //初始化实心的空画刷（没有背景颜色）
	dc.SelectObject(&brush[1]); //将画刷选入dc
	dc.SelectObject(&pen[1]);  //将画笔选入dc
	dc.SetBkMode(TRANSPARENT); //设置背景模式为透明，也可以使用SetBkColor设置背景色
	dc.Rectangle(10, 58, 200, 330); //创建一个透明的文本框
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CmenuDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CmenuDlg::OnOpen() //点击菜单栏“文件->打开”动作
{
	// TODO:  在此添加命令处理程序代码
	//MessageBox(_T("U choose copy"), _T("menu ID"));


	//*******************打开文件*********************
		//设置过滤器
	TCHAR szFilter[] = _T("文本文件(*.txt)|*.txt|所有文件(*.*)|*.*||"); //？这里好像有问题，打不开txt文件
	//构造打开文件对话框
	CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);
	CString strFilePath;

	//显示文件打开对话框
	if (IDOK == fileDlg.DoModal())
	{
		//如果点击了“打开”按钮，则将选择的文件路径显示到编辑框中
		strFilePath = fileDlg.GetPathName();
		SetDlgItemText(IDC_OPENFILE_EDIT, strFilePath);
	}

	//******************弹出文件操作对话框*********************
	INT_PTR nRes;   //用于保存DoModal函数的返回值

	CFileViewDlg  fileviewDlg;   //构造对话框类CFileViewDlg的实例（对象）
	nRes = fileviewDlg.DoModal();  //弹出对话框
	if (IDCANCEL == nRes)           //判断对话框推出后的返回值是否为IDCANCEL
	{
		return;
	}



}

// 为m_tab标签控件的通知消息TCN_SELCHANGE添加处理函数
void CmenuDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;

	CRect tabRect;  //标签控件客户区的Rect

	//获取Rect，使其覆盖范围适合放置标签页
	m_tab.GetClientRect(&tabRect);
	tabRect.left += 1;
	tabRect.right -= 1;
	tabRect.top += 25;
	tabRect.bottom -= 1;
	/*   下面这句只是测试用*/
//	int	protocolmode = 1;

	if (quanshuanggong)
	{
		switch (m_tab.GetCurSel()) // 检索标签属性
		{
			//如果选择当前标签，则显示其对话框，隐藏其他对话框
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

	/*		{   //Switch语句有初始化过程，不可以有定义部分，需要将定义部分用大括号括起来
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
				for (int i = 0; (size_t)i < dwFileLen; i++) //size_t只是为了提高可移植性
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
		switch (m_tab.GetCurSel()) // 检索标签属性
		{
			//如果选择当前标签，则显示其对话框，隐藏其他对话框
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
		switch (m_tab.GetCurSel()) // 检索标签属性
		{
			//如果选择当前标签，则显示其对话框，隐藏其他对话框
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


//void CmenuDlg::OnLoadconfig() //加载配置文件
//{
//	// TODO:  在此添加命令处理程序代码
//	//*******************打开文件*********************
//	//设置过滤器
//	TCHAR szFilter[] = _T("文本文件(*.ini)|*.ini|所有文件(*.*)|*.*||"); 
//	//构造打开文件对话框
//	CFileDialog fileDlg(TRUE, _T("ini"), NULL, 0, szFilter, this);
//	CString strFilePath;
//
//	//显示文件打开对话框
//	if (IDOK == fileDlg.DoModal())
//	{
//		//如果点击了“打开”按钮，则将选择的文件路径显示到编辑框中
//		strFilePath = fileDlg.GetPathName();
//		SetDlgItemText(IDC_OPENFILE_EDIT, strFilePath);
//		m_parameterset.OnLoadconfig();
//	}
//
//}


void CmenuDlg::OnSave()  //点击菜单栏“文件->保存”动作 ？？？
{
	// TODO:  在此添加命令处理程序代码
	// 设置过滤器   
	TCHAR szFilter[] = _T("文本文件(*.txt)|*.txt|Word文件(*.doc)|*.doc|所有文件(*.*)|*.*||");
	// 构造保存文件对话框   
	CFileDialog fileDlg(FALSE, _T("doc"), _T("my"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	CString strFilePath;

	// 显示保存文件对话框   
	if (IDOK == fileDlg.DoModal())
	{
		// 如果点击了文件对话框上的“保存”按钮，则将选择的文件路径显示到编辑框里   
		strFilePath = fileDlg.GetPathName();
		//SetDlgItemText(IDC_SAVE_EDIT, strFilePath);
	}

}


//void CmenuDlg::OnParaset() //点击菜单栏“文件->参数设置”动作 
//{
//	// TODO:  在此添加命令处理程序代码
//
//	//INT_PTR nRes;   //用于保存DoModal函数的返回值
//
//	//CParameterSet parameterset;   //构造对话框类CFileViewDlg的实例（对象）
//	//nRes = parameterset.DoModal();  //弹出对话框
//	if (IDCANCEL == nRes)           //判断对话框推出后的返回值是否为IDCANCEL
//	{
//	//	return;
//	}
//}



//void CmenuDlg::OnBnClickedOk()
//{
//	// TODO:  在此添加控件通知处理程序代码
//	CDialogEx::OnOK();
//}


int CmenuDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;



	// TODO:  在此添加您专用的创建代码
	
//	HBITMAP hBmp;
//	bitmap.LoadBitmap(IDB_OPENFILE_BITMAP);
//	GetMenu()->GetSubMenu(0)->SetMenuItemBitmaps(0, MF_BYPOSITION, &bitmap, &bitmap);

//	CBitmap *pMenuBitmap;// 这个需要在成员变量里定义
//	pMenuBitmap = new CBitmap;
//	pMenuBitmap->LoadBitmap(IDB_OPENFILE_BITMAP);//需要加载的图标资源
//	CMenu *m_menu;
//	m_menu = GetMenu()->GetSubMenu(0);//子菜单，0代表主菜单的第一个子菜单
//	m_menu->SetMenuItemBitmaps(1, MF_BYPOSITION, pMenuBitmap, pMenuBitmap);
	return 0;
}





void CmenuDlg::OnUserguider() //帮助->使用说明 调用外部程序打开文档  文档要放在工程目录下
{
	// TODO:  在此添加命令处理程序代码
	//ShellExecute(this->m_hWnd, "open", "使用说明.docx", NULL, NULL, SW_SHOWNORMAL);  //调用使用说明文档，但是参数不兼容
	ShellExecute(this->m_hWnd, (LPCWSTR)L"open", (LPCWSTR)L"使用说明.docx", NULL,NULL, SW_SHOWNORMAL);  // 参数不兼容使用的语句
	//ShellExecute(this->m_hWnd, (LPCWSTR)L"open", (LPCWSTR)L"http://nuaa.edu.cn", NULL, NULL, SW_SHOW);   //调用浏览器打开我航主页
	//ShellExecute(this->m_hWnd, (LPCWSTR)L"open", (LPCWSTR)L" mailto:maoxiaoke@outlook.com", NULL, NULL, SW_SHOWNORMAL); //调用系统邮件
}
void CmenuDlg::OnSendmail()
{
	// TODO:  在此添加命令处理程序代码
	ShellExecute(this->m_hWnd, (LPCWSTR)L"open", (LPCWSTR)L" mailto:maoxiaoke@outlook.com", (LPCWSTR)L"", (LPCWSTR)L"", SW_SHOWNORMAL);
}


void CmenuDlg::OnLoadconfig()//加载配置文件 参数设置
{
	// TODO:  在此添加命令处理程序代码
	//*******************打开文件*********************
		//设置过滤器
		TCHAR szFilter[] = _T("文本文件(*.ini)|*.ini|所有文件(*.*)|*.*||"); 
		//构造打开文件对话框
		CFileDialog fileDlg(TRUE, _T("ini"), NULL, 0, szFilter, this);
		CString strFilePath;

		//显示文件打开对话框
		if (IDOK == fileDlg.DoModal())
		{
			m_parameterset.ConfigureLoadFlag = true; //加载ini文件标志 true表示加载了ini文件
			//如果点击了“打开”按钮，则将选择的文件路径显示到编辑框中
			strFilePath = fileDlg.GetPathName();
			SetDlgItemText(IDC_OPENFILE_EDIT, strFilePath);
			m_parameterset.ConFigure(strFilePath);
		}
}


//BOOL CmenuDlg::OnCommand(WPARAM wParam, LPARAM lParam)
//{
//	// TODO:  在此添加专用代码和/或调用基类
//
//	return CDialogEx::OnCommand(wParam, lParam);
//}


void CmenuDlg::OnSaveconfig() //保存配置文件
{
	// TODO:  在此添加命令处理程序代码
	CString strFilePath;
	if (m_parameterset.ConfigureLoadFlag) //如果已经加载了ini文件，则直接保存到原来的文件中
	{
		GetDlgItemText(IDC_OPENFILE_EDIT, strFilePath); //获取要保存的配置文件路径
	}
	else //否则新建ini配置文件，并将参数保存
	{
		TCHAR szFilter[] = _T("配置文件(*.ini)|*.ini|文本文件(*.txt)|*.txt|所有文件(*.*)|*.*||");
		// 构造保存文件对话框   
		CFileDialog fileDlg(FALSE, _T("ini"), _T("my"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
		if (IDOK == fileDlg.DoModal())
		{
			// 如果点击了文件对话框上的“保存”按钮，则将选择的文件路径显示到编辑框里   
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
			MessageBox(_T("配置文件创建失败！"));
			return;
		}
		file.Close();
	}
	m_parameterset.ConFigSave(strFilePath); //调用配置参数存储函数
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
			CRect tabRect;    // 标签控件客户区的Rect   

			// 获取标签控件客户区Rect，并对其调整，以适合放置标签页   
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

/**************************************启动系统*********************************************/
void CmenuDlg::OnBootsystem()
{
	// TODO:  在此添加命令处理程序代码
	CString strTime;
	CTime tm; 
	
	//参数初始化
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

	messagestate = 0;					//有无数据发送
	commondstate = 0;					//有无指令发送
	missnumber = 0;						//丢失帧数初始化
	receivenumber = 1;					//每次启动收到的帧数重新计数
	NeedSerialNumber = 0;			//需要的帧号

	CommondGroup = (int *)malloc(24 * sizeof(int));				//给流程内指令存储数组分配空间
	ArqGroup = (int *)malloc(16 * sizeof(int));


	/*************清空编辑框内容**************/
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
			MessageBox(_T("提示：请加载数据源文件！"));			//再判断是否加载了数据源文件
		}
		else
		{
			runandstopflag = true;  //开启系统
			OperatingRecord(); //调用操作记录函数，保证操作记录不被抹掉

			int protocolmode = m_parameterset.m_ProtocolMode.GetCurSel(); //获取协议方式
			// if(quanshuanggong == true)
			if (protocolmode == 0)  //全双工
			{
				tm = CTime::GetCurrentTime(); //获取系统当前时间
				strTime = tm.Format("%Y.%m.%d %X"); //格式转换
				m_Hist.SetSel(m_Hist.GetWindowTextLength(), -1); //获取当前编辑框字符
				m_Hist.ReplaceSel(strTime + "\r\n" + _T("双工协议仿真\r\n")); //替换当前文本
				//		MessageBox(strTime);
				m_parameterset.GetSendAParameterValue(1);		//获得参数设置界面参数（发射机参数）
				m_parameterset.GetReceiveAParameterValue(1); //获得接收机参数
				m_parameterset.GetSystemParameterValue(1);	//获得系统参数值

				m_duplex.StartRunDuplex(1);		 //开始全双工


			}
			if (protocolmode == 1)
			{
				tm = CTime::GetCurrentTime(); //获取系统当前时间
				strTime = tm.Format("%Y.%m.%d %X"); //格式转换
				m_Hist.SetSel(m_Hist.GetWindowTextLength(), -1); //获取当前编辑框字符
				m_Hist.ReplaceSel(strTime + "\r\n" + _T("半双工协议仿真\r\n")); //替换当前文本
				//		MessageBox(strTime);
				m_parameterset.GetSendAParameterValue(1);		//获得参数设置界面参数（发射机参数）
				m_parameterset.GetReceiveAParameterValue(1); //获得接收机参数
				m_parameterset.GetSystemParameterValue(1);	//获得系统参数值

				m_halfduplexdlg.StartRunHalfDuplex(1);		 //开始半双工
			}
			if (protocolmode == 2)
			{
				tm = CTime::GetCurrentTime(); //获取系统当前时间
				strTime = tm.Format("%Y.%m.%d %X"); //格式转换
				m_Hist.SetSel(m_Hist.GetWindowTextLength(), -1); //获取当前编辑框字符
				m_Hist.ReplaceSel(strTime + "\r\n" + _T("单工协议仿真\r\n")); //替换当前文本
				//		MessageBox(strTime);
				m_parameterset.GetSendAParameterValue(1);		//获得参数设置界面参数（发射机参数）
				m_parameterset.GetReceiveAParameterValue(1); //获得接收机参数
				m_parameterset.GetSystemParameterValue(1);	//获得系统参数值

				m_simplexdlg.StartRunSimplex(1);		 //开始半双工
			}
		}
		
	}
	else
	{
		MessageBox(_T("提示：无网络连接！"));
	}

}

/********************************操作记录函数，保证操作记录不被抹掉*********************************************/
void CmenuDlg::OperatingRecord()
{
	CString strTime;
	CTime tm;
	m_Hist.SetSel(m_Hist.GetWindowTextLength(), -1); //获取当前编辑框字符
	tm = CTime::GetCurrentTime(); //获取系统当前时间
	strTime = tm.Format("%Y.%m.%d %X"); //格式转换
	if (runandstopflag)
	{
		m_Hist.ReplaceSel(strTime + "\r\n" + _T("启动系统\r\n"));
	}
	else
	{
		m_Hist.ReplaceSel(strTime + "\r\n" + _T("停止系统\r\n"));
	}
	
}

/****************开始监听*************************/
void CmenuDlg::OnBnClickedStartmonitorButton()
{
	// TODO:  在此添加控件通知处理程序代码
	BYTE nFild[4] ;
	CString sIP, sP;
	UpdateData();			//刷新数据
	ServerIP.GetAddress(nFild[0], nFild[1], nFild[2], nFild[3]);
	sIP.Format(_T("%d.%d.%d.%d"), nFild[0], nFild[1], nFild[2], nFild[3]);
	sP.Format(_T("%d"), sPort); //输出显示用
//	sPort = GetDlgItemInt(IDC_SPORT_EDIT);//也可以这样获取端口号
	if (sPort <= 1024 || sPort > 65535)
	{
		MessageBox(_T("请输入合适的端口号！（1025~65535）"));
		SetDlgItemText(IDC_SPORT_EDIT, _T(""));
//		SetDlgItemInt(IDC_SPORT_EDIT, 1026); 这样也可以
		GetDlgItem(IDC_SPORT_EDIT)->SetFocus(); //设置窗口焦点，意思就是不用鼠标点击文本框光标就会自动定位到文本框里
		return;
	}

	m_ListenSocket.Create(sPort, 1, FD_ACCEPT, sIP); //创建服务端监听Socket
	m_ListenSocket.Listen(1);        //开始监听

	CString str;
	str = SystemTime();
	m_Hist.SetSel(m_Hist.GetWindowTextLength(), -1); //获取当前编辑框字符
	m_Hist.ReplaceSel(str + "\r\n" + _T("监听开始\r\n")+_T("地址")+ sIP + _T("端口")+ sP+"\r\n"+_T("等待客户连接……\r\n")); //替换当前文本

	//控件禁用
	ServerIP.EnableWindow(false);
	m_ServerPort.EnableWindow(false);
	m_ListenButton.EnableWindow(false);
	m_ListenEndButton.EnableWindow();

}


void CmenuDlg::OnBnClickedEndmonitorButton()
{
	// TODO:  在此添加控件通知处理程序代码
	m_ListenSocket.Close();//关闭服务端监听Socket

	//显示
	CString str;
	str = SystemTime();
	m_Hist.SetSel(m_Hist.GetWindowTextLength(), -1); //获取当前编辑框字符
	m_Hist.ReplaceSel(str + "\r\n" + _T("停止监听\r\n")); //替换当前文本

	//控件禁用
	ServerIP.EnableWindow();
	m_ServerPort.EnableWindow();
	m_ListenButton.EnableWindow();
	m_ListenEndButton.EnableWindow(false);

}

void CmenuDlg::SendMessagepro(int *P_SE, int fLen)
{
	m_ServerSocket.Send(P_SE, (fLen+1)* 4);  //发信息，Send发送字节长度，int型为四个字节

}


//void CmenuDlg::OnBnClickedSendButton()
//{
//	// TODO:  在此添加控件通知处理程序代码
//	UpdateData();
//	m_ServerSocket.Send(m_sWords, (m_sWords.GetLength()+1)*2);  //发信息
//}




void CmenuDlg::OnStatusdisplay()
{
	// TODO:  在此添加命令处理程序代码
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
	// TODO:  在此添加命令处理程序代码
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
