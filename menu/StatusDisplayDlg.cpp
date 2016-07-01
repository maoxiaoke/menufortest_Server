// StatusDisplayDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "menu.h"
#include "StatusDisplayDlg.h"
#include "afxdialogex.h"
#include "ParameterSet.h"


// CStatusDisplayDlg �Ի���

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


// CStatusDisplayDlg ��Ϣ�������


void CStatusDisplayDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()

	CPen pen[3]; //���廭�ʶ���
	CBrush brush[2]; //�����ˢ����
	pen[0].CreatePen(PS_DASHDOT, 1, RGB(0, 0, 255)); //������ʼ������
	brush[0].CreateStockObject(NULL_BRUSH); //��ʼ��ʵ�ĵĿջ�ˢ��û�б�����ɫ��
	dc.SelectObject(&brush[0]); //����ˢѡ��dc
	dc.SelectObject(&pen[0]);  //������ѡ��dc
	dc.SetBkMode(TRANSPARENT); //���ñ���ģʽΪ͸����Ҳ����ʹ��SetBkColor���ñ���ɫ
	dc.Rectangle(15, 20, 500, 310); //����һ��͸�����ı���
	//pen[0].DeleteObject(); //�ͷ�dc
	//brush[0].DeleteObject();  //ע�͵����ΪʲôҲ���ԣ��ѵ�������ͷ���

	pen[1].CreatePen(PS_DASHDOT, 1, RGB(0, 0, 255)); //������ʼ������
	dc.SelectObject(&pen[1]);  //����ˢѡ��dc
	dc.MoveTo(15, 165); //��ֱ��
	dc.LineTo(500, 165); //��ֱ��
	//	pen[1].DeleteObject();

	pen[2].CreatePen(PS_DASHDOT, 1, RGB(0, 0, 255)); //������ʼ������
	brush[1].CreateStockObject(NULL_BRUSH); //��ʼ��ʵ�ĵĿջ�ˢ��û�б�����ɫ��
	dc.SelectObject(&brush[1]); //����ˢѡ��dc
	dc.SelectObject(&pen[2]);  //������ѡ��dc
	dc.SetBkMode(TRANSPARENT); //���ñ���ģʽΪ͸����Ҳ����ʹ��SetBkColor���ñ���ɫ
	dc.Rectangle(15, 318, 500, 430); //����һ��͸�����ı���
	//pen[2].DeleteObject(); //�ͷ�dc
	//brush[1].DeleteObject();  //ע�͵����ΪʲôҲ���ԣ��ѵ�������ͷ���

	
}


BOOL CStatusDisplayDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	/********************************��������******************************************/
	font.CreatePointFont(120, _T("΢���ź�")); //����������ʽ������120����12������
	GetDlgItem(IDC_SENDDATA_STATIC)->SetFont(&font); //�����崫�ݸ���̬��
	GetDlgItem(IDC_RECEIVEDATA_STATIC)->SetFont(&font); //�����崫�ݸ���̬��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


//void CStatusDisplayDlg::OnBnClickedShowtextButton()
//{
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
//	for (int i = 0; (size_t)i < dwFileLen; i++) //size_tֻ��Ϊ����߿���ֲ��
//	{
//		strDisplay += pBuf[i];
//
//	}
//	SetDlgItemText(IDC_RECEIVEDATA_EDIT, strDisplay);
//	file.Close();
//	delete[]pBuf;
//	*/
//}
