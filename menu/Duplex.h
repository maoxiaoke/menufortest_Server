#pragma once
#include "afxwin.h"
#include "ParameterSet.h"

//UINT ThreadFunc(LPVOID lpParam);
void ThreadFunc(LPVOID lpParam); //���������̺߳���


// CDuplex �Ի���

class CDuplex : public CDialogEx
{
	DECLARE_DYNAMIC(CDuplex)

public:
	CDuplex(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDuplex();

// �Ի�������
	enum { IDD = IDD_DUPLEX_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_led1;
	CStatic m_led2;
	CStatic m_led3;
	CStatic m_led6;
	CStatic m_led5;
	CStatic m_led7;
	CStatic m_led8;
	CStatic m_led9;
	CStatic m_led10;
	CStatic m_led11;
	CStatic m_led12;
	CStatic m_led13;
	CStatic m_led14;
//	afx_msg void OnBnClickedOk();
	int SetLedOff(int a);
	CStatic m_led4;
	afx_msg void OnPaint();

	int StartRunDuplex(int a);
	void shuanggongsend();
	void SystemTime(); //��ȡϵͳʱ��

	HBITMAP m_grey;  // ��Ӿ������
	HBITMAP m_red;
	CFont font;


protected:
	HANDLE hThread; //�߳̾��
	DWORD ThreadID; //�߳�ID

public:
//	CEdit m_histrecord;
	CParameterSet *psDlg;
	CStatusDisplayDlg * d_sdDlg;  //˫��״̬�·���StatusDisplay�Ի���  d = duplex
	void arqarray(int framecounter);
	void arqsend(int framecounter);
//	CEdit m_Text;
	int state_inactive;  //��ʼ�ȴ�
	int state_waithail;    //�ȴ�����
	int state_starthail;   //��ʼ�ز�ͬ��
	int state_hailacquisition;   //��ʼ����ͬ��
	int state_haildirectives;     //��������ָ��
	int state_hailtail;                //��������β����
	int state_hailresponse;   //�ȴ�������Ӧ
	int state_carrieronly;       //�ŵ��ز�ά��
	int state_acquisition;     //���Ͳ�������
	int state_duplexon;          //˫�����ݴ���
	int state_rnmdend;         //Զ�̷��ͳɹ�
	int state_lnmdend;           //���ط��ͳɹ�
	int state_duplexend;       //˫�����ݴ������
	int state_terminatingtail;   //β����
	int StopFlag;  //ǿ��ֹͣ�ı�־���� ?

	int lnmdsign;						//���ط�����ɱ�־
	int rnmdsign;					//Զ�̷�����ɱ�־

	int DuplexState;			//��ǰȫ˫��״̬
	virtual BOOL OnInitDialog();
	UINT oldTickCount, newTickCount;
};
