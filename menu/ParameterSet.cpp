// ParameterSet.cpp : 实现文件
//

#include "stdafx.h"
#include "menu.h"
#include "ParameterSet.h"
#include "afxdialogex.h"
#include "menuDlg.h"
//#include "StatusDisplayDlg.h"


// CParameterSet 对话框

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
	//  DDX_Control(pDX, IDC_GROUPBOX1, m_GroupBox1); //GroupBox控件变量
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


// CParameterSet 消息处理程序


//void CParameterSet::OnInitMenu(CMenu* pMenu)
//{
//	CDialogEx::OnInitMenu(pMenu);
//
//	return ;
//
//
//	// TODO:  在此处添加消息处理程序代码
//}


//BOOL CParameterSet::OnInitDialog()
//{
//	CDialogEx::OnInitDialog();
//	m_ParaSet.AddString(_T("全双工模式A<-->B"));
//	m_ParaSet.AddString(_T("半双工模式"));
//
//	m_ParaSet.SetCurSel(0);
//	SetDlgItemText(IDC_PROTOCOLMODE_COMBO, _T("全双工模式A<-->B"));
//	// TODO:  在此添加额外的初始化
//
//	return TRUE;  // return TRUE unless you set the focus to a control
//	// 异常:  OCX 属性页应返回 FALSE
//}


//BOOL CParameterSet::OnInitDialog()
//{
//	CDialogEx::OnInitDialog();
//
//	// TODO:  在此添加额外的初始化
//	m_ProtocolMode.AddString(_T("全双工模式A<-->B"));
//	m_ProtocolMode.AddString(_T("半双工模式"));
//
//	m_ProtocolMode.SetCurSel(0);
//	SetDlgItemText(IDC_PROTOCOLMODE_COMBO, _T("全双工模式A<-->B"));
//	return TRUE;  // return TRUE unless you set the focus to a control
//	// 异常:  OCX 属性页应返回 FALSE
//}


//void CParameterSet::OnCbnSelchangeCombo1()
//{
//	// TODO:  在此添加控件通知处理程序代码
//	//m_ProtocolMode.GetCurSel();
//	CmenuDlg *pDlg = (CmenuDlg*)AfxGetMainWnd();
//	//pDlg->ModeChange(i);
//}


void CParameterSet::OnBnClickedSendsoucerButton() //发射机打开数据源文件
{
	// TODO:  在此添加控件通知处理程序代码
	//*******************打开文件*********************
	
	//设置过滤器
	TCHAR szFilter[] = _T("数据源文件(*.dat)|*.dat|所有文件(*.*)|*.*||");
	//构造打开文件对话框
	CFileDialog fileDlg(TRUE, _T("dat"), NULL, 0, szFilter, this);
	CString strFilePath;

	//显示文件打开对话框
	if (IDOK == fileDlg.DoModal())
	{
		//如果点击了“打开”按钮，则将选择的文件路径显示到编辑框中
		strFilePath = fileDlg.GetPathName();
		SetDlgItemText(IDC_SENDSOUCER_EDIT, strFilePath);

		/*==================================*/
		//测试用代码（code for test）
		//下面这段代码的目的是: 把加载的数据文件读出来并且在StatusDisplayDlg对话框中的编辑框中显示出来
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
		for (int i = 0; (size_t)i < dwFileLen; i++) //size_t只是为了提高可移植性
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


void CParameterSet::OnEnChangeFramespinEdit() //窗口编辑框控件的数据随旋转按钮一起变化
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	m_FrameSpinedit = GetDlgItemInt(IDC_FRAMESPIN_EDIT);

	// TODO:  在此添加控件通知处理程序代码
}


void CParameterSet::OnBnClickedReceivesaveButton() //接收机保存源文件
{
	// TODO:  在此添加控件通知处理程序代码

	// 设置过滤器   
	TCHAR szFilter[] = _T("数据源文件(*.dat)|*.dat|文本文件(*.txt)|*.txt|所有文件(*.*)|*.*||");
	// 构造保存文件对话框   
	CFileDialog fileDlg(FALSE, _T("dat"), _T("my"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	CString strFilePath;

	// 显示保存文件对话框   
	if (IDOK == fileDlg.DoModal())
	{
		// 如果点击了文件对话框上的“保存”按钮，则将选择的文件路径显示到编辑框里   
		strFilePath = fileDlg.GetPathName();

		SetDlgItemText(IDC_RECEIVESAVE_EDIT, strFilePath);
	}
}


void CParameterSet::OnBnClickedReceivesoucerButton() //接收机打开数据源文件
{
	// TODO:  在此添加控件通知处理程序代码
	//设置过滤器
	TCHAR szFilter[] = _T("数据源文件(*.dat)|*.dat|所有文件(*.*)|*.*||"); //？这里好像有问题，打不开txt文件
	//构造打开文件对话框
	CFileDialog fileDlg(TRUE, _T("dat"), NULL, 0, szFilter, this);
	CString strFilePath;

	//显示文件打开对话框
	if (IDOK == fileDlg.DoModal())
	{
		//如果点击了“打开”按钮，则将选择的文件路径显示到编辑框中
		strFilePath = fileDlg.GetPathName();
		SetDlgItemText(IDC_RECEIVESOUCER_EDIT, strFilePath);
	}
}


void CParameterSet::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()

	CPen pen[4]; //定义画笔对象
	CBrush brush[3]; //定义笔刷对象
	pen[0].CreatePen(PS_DASHDOT, 1, RGB(0, 0, 255)); //创建初始化画笔
	brush[0].CreateStockObject(NULL_BRUSH); //初始化实心的空画刷（没有背景颜色）
	dc.SelectObject(&brush[0]); //将画刷选入dc
	dc.SelectObject(&pen[0]);  //将画笔选入dc
	dc.SetBkMode(TRANSPARENT); //设置背景模式为透明，也可以使用SetBkColor设置背景色
	dc.Rectangle(15, 30, 500, 100); //创建一个透明的文本框
	//pen[0].DeleteObject(); //释放dc
	//brush[0].DeleteObject();  //注释掉这个为什么也可以？难道用完就释放了

	pen[1].CreatePen(PS_DASHDOT, 1, RGB(0, 0, 255)); //创建初始化画笔
	brush[1].CreateStockObject(NULL_BRUSH); //初始化实心的空画刷（没有背景颜色）
	dc.SelectObject(&brush[1]); //
	dc.SelectObject(&pen[1]);  //将画刷选入dc
	//	dc.SetBkMode(TRANSPARENT);
	dc.SetBkMode(TRANSPARENT); //设置背景模式为透明，也可以使用SetBkColor设置背景色
	//DrawRect(&dc);
	dc.Rectangle(15, 120, 500, 270); //创建一个透明的文本框

	//pen[1].DeleteObject();
	//brush[1].DeleteObject();
	pen[2].CreatePen(PS_DASHDOT, 1, RGB(0, 0, 255)); //创建初始化画笔
	brush[2].CreateStockObject(NULL_BRUSH); //初始化实心的空画刷（没有背景颜色）
	dc.SelectObject(&brush[2]); //
	dc.SelectObject(&pen[2]);  //将画刷选入dc
	//	dc.SetBkMode(TRANSPARENT);
	dc.SetBkMode(TRANSPARENT); //设置背景模式为透明，也可以使用SetBkColor设置背景色
	//DrawRect(&dc);
	dc.Rectangle(15, 290, 500, 430); //创建一个透明的文本框

	//pen[2].DeleteObject();
	//brush[2].DeleteObject();

	pen[3].CreatePen(PS_DASHDOT, 1, RGB(0, 0, 255)); //创建初始化画笔
	dc.SelectObject(&pen[3]);  //将画刷选入dc
	dc.MoveTo(240, 190); //画直线
	dc.LineTo(240, 250); //画直线
	//	pen[3].DeleteObject();

}


BOOL CParameterSet::OnInitDialog()
{
	CDialogEx::OnInitDialog();
// TODO:  在此添加额外的初始化
//	CParameterSet *ps_Dlg;
//	ps_Dlg = this;
	/********************************设置字体******************************************/
	font.CreatePointFont(120, _T("微软雅黑")); //创建字体样式，传递120请求12点字体
	GetDlgItem(IDC_SYSTEMPARAMETER_STATIC)->SetFont(&font); //将字体传递给静态框
	GetDlgItem(IDC_SENDER_STATIC)->SetFont(&font); //将字体传递给静态框
	GetDlgItem(IDC_RECEIVER_STATIC)->SetFont(&font); //将字体传递给静态框

	

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CParameterSet::OnCbnSelchangeProtocolmodeCombo() //点击模式选择组合框->协议共工作方式
{
	// TODO:  在此添加控件通知处理程序代码
	int i = m_ProtocolMode.GetCurSel();
	CmenuDlg *pDlg = (CmenuDlg*)AfxGetMainWnd();//获得父窗口的指针
	pDlg->ModeChange(i);
}


//void CParameterSet::OnLoadconfig(CString strFilePath)  //加载配置文件
//{
//	// TODO:  在此添加命令处理程序代码
//}


//void CParameterSet::OnLoadconfig()
//{
//	// TODO:  在此添加命令处理程序代码
//	
//		//*******************打开文件*********************
//		//设置过滤器
//		TCHAR szFilter[] = _T("文本文件(*.ini)|*.ini|所有文件(*.*)|*.*||"); 
//		//构造打开文件对话框
//		CFileDialog fileDlg(TRUE, _T("ini"), NULL, 0, szFilter, this);
//		CString strFilePath;
//	
//		//显示文件打开对话框
//	if (IDOK == fileDlg.DoModal())
//		{
//		//如果点击了“打开”按钮，则将选择的文件路径显示到编辑框中
//		strFilePath = fileDlg.GetPathName();
//		SetDlgItemText(IDC_OPENFILE_EDIT, strFilePath);
//		//m_parameterset.OnLoadconfig();
//		}
//}


//void CParameterSet::OnBnClickedLoadconfigButton()
//{
//	// TODO:  在此添加控件通知处理程序代码
//}

/*************************读取配置信息******************************************************/
//配置文件格式如下
/*
[配置文件属性]
type = "Config"

[系统参数]
EquipMode = 0
ProtocolMode = 0
ARQ = 1

[发射机A参数]
FrameLength = 200
ModulationMethod = 0
CC = 0
ChannelStatus = 0
SendDataPathA = "c:\\Users\\Administrator\\Desktop\\09Last_InstrCommunicationVer\\SendData.dat"

[接收机A参数]
FrameLength = 0
ModulationMethod = 0
CC = 0
ReceiveDataPathA = "c:\\Users\\Administrator\\Desktop\\09Last_InstrCommunicationVer\\ReceiveData.dat"
RemoteDataPathA = "c:\\Users\\Administrator\\Desktop\\09Last_InstrCommunicationVer\\SendData.dat"

[发射机B参数]
FrameLength = 200
ModulationMethod = 0
CC = 0
ChannelStatus = 0
SendDataPathB = "c:\\Users\\Administrator\\Desktop\\InstrCommunicationVer\\SendData.dat"

[接收机B参数]
FrameLength = 0
ModulationMethod = 0
CC = 0
ReceiveDataPathB = "c:\\Users\\Administrator\\Desktop\\InstrCommunicationVer\\ReceiveData.dat"
RemoteDataPathB = "c:\\Users\\Administrator\\Desktop\\InstrCommunicationVer\\SendData.dat"

//GetPrivateProfileString函数
DWORD WINAPI GetPrivateProfileString(
_In_  LPCTSTR lpAppName,
_In_  LPCTSTR lpKeyName,
_In_  LPCTSTR lpDefault,
_Out_ LPTSTR  lpReturnedString,
_In_  DWORD   nSize,
_In_  LPCTSTR lpFileName
);
lpAppName：段名
lpKeyName：键名
lpDefault：默认值
lpReturnedString：目的缓存器
nSize：目的缓存器的大小
lpFileName：要读取的配置文件的文件路径

//GetPrivateProfileInt函数  取得一个特定配置文件的键名值（整数值）
UINT WINAPI GetPrivateProfileInt(
_In_ LPCTSTR lpAppName,
_In_ LPCTSTR lpKeyName,
_In_ INT     nDefault,
_In_ LPCTSTR lpFileName
);
lpAppName：段名
lpKeyName：键名
nDefault：如果没有找到配置文件的默认返回值
lpFileName：配置文件的文件路径


*/

void CParameterSet::ConFigure(CString strFilePath)
{
	//协议工作方式
	int ProtocolMode;
	ProtocolMode = (int)GetPrivateProfileInt(_T("系统参数"), _T("ProtocolMode"), 0, strFilePath);
	m_ProtocolMode.SetCurSel(ProtocolMode);
	OnCbnSelchangeProtocolmodeCombo(); //配置文件参数加载后调用函数更改协议监控面板

	//ARQ
	int arq = (int)GetPrivateProfileInt(_T("系统参数"), _T("ARQ"), 0, strFilePath);
	m_AutoArq.SetCurSel(arq);

	//发射机参数  as A的发射机
	//帧长度
	int as_framelen = (int)GetPrivateProfileInt(_T("发射机A参数"), _T("FrameLength"), 0, strFilePath);
	CString len;
	len.Format(_T("%d"), as_framelen);
	SetDlgItemText(IDC_FRAMESPIN_EDIT, len);

	//调制方式
	int as_Moudulation;
	as_Moudulation = (int)GetPrivateProfileInt(_T("发射机A参数"), _T("ModulationMethod"), 0, strFilePath);
	m_ModulationCombo.SetCurSel(as_Moudulation);
	//((CComboBox*)GetDlgItem(IDC_MODULATION_COMBO))->SetCurSel(a_Moudulation);   //这是通过调用CComboBox 对象来设置参数

	//CC
	int as_CC = (int)GetPrivateProfileInt(_T("发射机A参数"), _T("CC"), 0, strFilePath);
	m_CcCodeCombo.SetCurSel(as_CC);

	//信道状态
	int as_ChannelStatus = (int)GetPrivateProfileInt(_T("发射机A参数"), _T("ChannelStatus"), 0, strFilePath);
	m_ChannelStatusCombo.SetCurSel(as_ChannelStatus);

	//发射机数据源文件
	CString as_SendDataPath;
	GetPrivateProfileString(_T("发射机A参数"), _T("SendDataPathA"), _T(""), as_SendDataPath.GetBuffer(100), 100, strFilePath);
	as_SendDataPath.ReleaseBuffer();//释放
	SetDlgItemText(IDC_SENDSOUCER_EDIT, as_SendDataPath);


	//接收机A参数  ar A的接收机
	//调制方式
	int ar_Moudulation;
	ar_Moudulation = (int)GetPrivateProfileInt(_T("接收机A参数"), _T("ModulationMethod"), 0, strFilePath);
	m_ModulationCombo2.SetCurSel(ar_Moudulation);

	//CC
	int ar_CC = (int)GetPrivateProfileInt(_T("接收机A参数"), _T("CC"), 0, strFilePath);
	m_CcCodeCombo.SetCurSel(ar_CC);

	//接收机保存文件
	CString ar_SendDataPath1;
	GetPrivateProfileString(_T("接收机A参数"), _T("ReceiveDataPathA"), _T(""), ar_SendDataPath1.GetBuffer(100), 100, strFilePath);
	ar_SendDataPath1.ReleaseBuffer();//释放
	SetDlgItemText(IDC_RECEIVESAVE_EDIT, ar_SendDataPath1);

	//接收机数据源文件
	CString ar_SendDataPath2;
	GetPrivateProfileString(_T("接收机A参数"), _T("RemoteDataPathA"), _T(""), ar_SendDataPath2.GetBuffer(100), 100, strFilePath);
	ar_SendDataPath2.ReleaseBuffer();//释放
	SetDlgItemText(IDC_RECEIVESOUCER_EDIT, ar_SendDataPath2);

	MessageBox(_T("参数设置成功！"));
}
void CParameterSet::ConFigSave(CString strFilePath) //保存配置文件
{
	//配置文件属性
	WritePrivateProfileString(_T("配置文件属性"), _T("type"), _T("Config"), strFilePath);

	//系统参数
	WritePrivateProfileString(_T("系统参数"), _T("EquipMode"), _T("0"), strFilePath);

	int pm = m_ProtocolMode.GetCurSel();
	//int pm = ((CComboBox*)GetDlgItem(IDC_PROTOCOLMODE_COMBO))->GetCurSel();
	CString ProtocolMode;
	ProtocolMode.Format(_T("%d"), pm);
	WritePrivateProfileString(_T("系统参数"), _T("ProtocolMode"), ProtocolMode, strFilePath);

	int ar = m_AutoArq.GetCurSel();
	CString arq;
	arq.Format(_T("%d"), ar);
	WritePrivateProfileString(_T("系统参数"), _T("ARQ"), arq, strFilePath);

	//发射机参数
	CString as_framelen;
	GetDlgItemText(IDC_FRAMESPIN_EDIT,as_framelen);
	WritePrivateProfileString(_T("发射机A参数"), _T("FrameLength"), as_framelen, strFilePath);

	int as_m = m_ModulationCombo.GetCurSel();
	CString as_modulation;
	as_modulation.Format(_T("%d"), as_m);
	WritePrivateProfileString(_T("发射机A参数"), _T("ModulationMethod"), as_modulation, strFilePath);

	int as_c = m_CcCodeCombo.GetCurSel();
	CString as_CC;
	as_CC.Format(_T("%d"), as_c);
	WritePrivateProfileString(_T("发射机A参数"), _T("CC"), as_CC, strFilePath);

	int as_cs = m_ChannelStatusCombo.GetCurSel();
	CString as_ChannelStatus;
	as_ChannelStatus.Format(_T("%d"), as_cs);
	WritePrivateProfileString(_T("发射机A参数"), _T("ChannelStatus"), as_ChannelStatus, strFilePath);

	CString as_DataPath;
	GetDlgItemText(IDC_SENDSOUCER_EDIT, as_DataPath);
	WritePrivateProfileString(_T("发射机A参数"), _T("SendDataPathA"), as_DataPath, strFilePath);

	//接收机参数
	int ar_m = m_ModulationCombo2.GetCurSel();
	CString ar_modulation;
	ar_modulation.Format(_T("%d"), ar_m);
	WritePrivateProfileString(_T("接收机A参数"), _T("ModulationMethod"), ar_modulation, strFilePath);
	
	int ar_c = m_CcCodeCombo2.GetCurSel();
	CString ar_CC;
	ar_CC.Format(_T("%d"), ar_c);
	WritePrivateProfileString(_T("接收机A参数"), _T("CC"), ar_CC, strFilePath);

	CString ar_ReceiveData;
	GetDlgItemText(IDC_RECEIVESAVE_EDIT, ar_ReceiveData);
	WritePrivateProfileString(_T("接收机A参数"), _T("ReceiveDataPathA"), ar_ReceiveData, strFilePath);

	CString ar_RemoteData;
	GetDlgItemText(IDC_RECEIVESOUCER_EDIT, ar_RemoteData);
	WritePrivateProfileString(_T("接收机A参数"), _T("RemoteDataPathA"), ar_RemoteData, strFilePath);

	MessageBox(_T("参数保存成功"));
}

//void CParameterSet::OnBnClickedSaveconfigButton()
//{
//	// TODO:  在此添加控件通知处理程序代码
//}
