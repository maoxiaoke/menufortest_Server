#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "resource.h"
#include "StatusDisplayDlg.h"


// CParameterSet �Ի���

class CParameterSet : public CDialogEx
{
	DECLARE_DYNAMIC(CParameterSet)

public:
	CParameterSet(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CParameterSet();

// �Ի�������
	enum { IDD = IDD_PARAMETER_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

	

//	afx_msg void OnCbnSelchangeCombo1();

	CComboBox m_ProtocolMode;
	CComboBox m_AutoArq;
	afx_msg void OnBnClickedSendsoucerButton();
	CSpinButtonCtrl m_FrameLenSpin;
	int m_FrameSpinedit;
	afx_msg void OnEnChangeFramespinEdit();
	CComboBox m_ModulationCombo;
	CComboBox m_ChannelStatusCombo;
	CComboBox m_CcCodeCombo;
//	CStatic m_GroupBox1;
	afx_msg void OnBnClickedReceivesaveButton();
	afx_msg void OnBnClickedReceivesoucerButton();
	CComboBox m_CcCodeCombo2;
	CComboBox m_ModulationCombo2;

	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();

	CFont font;
	bool ConfigureLoadFlag;
	afx_msg void OnCbnSelchangeProtocolmodeCombo();
//	afx_msg void OnLoadconfig(CString strFilePath);
//	afx_msg void OnLoadconfig();
//	afx_msg void OnBnClickedLoadconfigButton();
	void ConFigure(CString strFilePath);  //��ȡ�����ļ�
	void ConFigSave(CString strFilePath);

//	CStatusDisplayDlg  sddlg;

	CEdit m_SendSoucerEdit;
//	CStatusDisplayDlg* sdDlg;  //Ϊ�˷���StatusDisplay�Ի���ʹ�õ�ָ��
//	afx_msg void OnBnClickedSaveconfigButton();
	int GetSendAParameterValue(int a); //��ȡ���ط��������ֵ
	int GetReceiveAParameterValue(int a); //��ȡ���ؽ��ջ�����ֵ
	int GetSystemParameterValue(int a);	//��ȡϵͳ����ֵ
};

//extern CParameterSet *ps_Dlg = NULL;