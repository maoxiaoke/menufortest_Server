
// menuDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "ParameterSet.h"
#include "Duplex.h"
#include "StatusDisplayDlg.h"
#include "HalfDuplexDlg.h"
#include "SimplexDlg.h"

#include "ListenSocket.h"
#include "ServerSocket.h"


#include "SystemParameter.h"
#include "afxwin.h"



// CmenuDlg �Ի���
class CmenuDlg : public CDialogEx
{
// ����
public:
	CmenuDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MENU_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnOpen();
	
	CTabCtrl m_tab;
	//CString strfilepath;  //����ļ��������ַ�����������Ϊ�Ը��ַ������в���

	//��ӱ�ǩ�ؼ��Ի�������Ա����
	CDuplex m_duplex;
	CParameterSet m_parameterset;
	CStatusDisplayDlg m_statusdisplydlg;
	CHalfDuplexDlg m_halfduplexdlg;
	CSimplexDlg m_simplexdlg;
	CListenSocket m_ListenSocket;							//����socket��ĳ�Ա����
	CServerSocket m_ServerSocket;							//�����ͻ��˵���������������socket��Ա����

	void ModeChange(int i); //��ӦЭ�鵥Ԫ��Э�鹤����ʽ��������ı仯
	bool quanshuanggong;
	bool banshuanggong;
	bool dangong;
	bool halfduplexExistFlag; //�жϰ�˫��tabҳ���Ƿ���ڱ�־
	bool simplexExistFlag;
	bool comboFirstChange; //

	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnLoadconfig();
	afx_msg void OnSave();
//	afx_msg void OnParaset();
//	CComboBox m_lala;
//	afx_msg void OnBnClickedOk();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
//	CBitmap bitmap;
//	CBitmap *pMenuBitmap;
//	afx_msg void OnUserguider();
	afx_msg void OnUserguider();
	afx_msg void OnLoadconfig();
//	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSaveconfig();
	afx_msg void OnBootsystem(); //����ϵͳ
	void OperatingRecord();
	CEdit m_Hist; //������¼
	bool runandstopflag; //��������ֹϵͳ��ʶ
	CIPAddressCtrl ServerIP;
	int sPort;
	afx_msg void OnBnClickedStartmonitorButton();

	CString SystemTime();
	afx_msg void OnBnClickedEndmonitorButton();
	CEdit m_ServerPort;
	CButton m_ListenButton;
	CButton m_ListenEndButton;

	void SendMessagepro(int *P_SE, int fLen); //������Ϣ
	CString m_sWords;
//	afx_msg void OnBnClickedSendButton();
	afx_msg void OnSendmail();
	afx_msg void OnStatusdisplay();
	afx_msg void OnParaset();

	CFont font;
	afx_msg void OnLogout();
	afx_msg void OnBnClickedCleanupButton();
};
