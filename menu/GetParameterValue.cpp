/*
	��cpp�ļ���ȡ�Ի���PARAMETERSET�пؼ���ֵ������ŵ�ȫ�ֱ�����
	������ͷ�ļ���ParameterSet.h
*/
#include "stdafx.h"
#include "ParameterSet.h"
#include "SystemParameter.h"


/*===============================*/
//FunctionName:GetSendAParameterValue
//Description: ��ȡ���ط��������ֵ
/*===============================*/
int CParameterSet::GetSendAParameterValue(int a)
{	
	SendA.FrameLength = GetDlgItemInt(IDC_FRAMESPIN_EDIT);					//���֡��
	SendA.ModulationMethod = m_ModulationCombo.GetCurSel();			//���Ʒ�ʽ
	SendA.CC = m_CcCodeCombo.GetCurSel();													//�Ƿ�CC����
	SendA.ChannelStatus = m_ChannelStatusCombo.GetCurSel();					// �ŵ�״̬
	GetDlgItemText(IDC_SENDSOUCER_EDIT,SendA.gSendDataPath);			//�������ַ
	SendA.CRC = 1;																									//ǿ��CRC����
	SendA.Num_Frame = 1;																						//���δ���֡��Ϊ1֡
	return 0;
}


/*===============================*/
//FunctionName:GetReceiveAParameterValue
//Description: ��ȡ���ؽ��ջ�����ֵ
/*===============================*/
int CParameterSet::GetReceiveAParameterValue(int a)
{	
	ReceiveA.ModulationMethod = m_ModulationCombo2.GetCurSel();
	ReceiveA.CC = m_CcCodeCombo2.GetCurSel();
	GetDlgItemText(IDC_RECEIVESAVE_EDIT, ReceiveA.gReceiveDataPath);
	GetDlgItemText(IDC_RECEIVESOUCER_EDIT, ReceiveA.gRemoteDataPath);
	ReceiveA.CRC = 1;																												//ǿ��CRC����

	return 0;
}

/*===============================*/
//FunctionName:GetSystemParameterValue
//Description: ��ȡϵͳ����ֵ
/*===============================*/
int CParameterSet::GetSystemParameterValue(int a)
{
	SystemParameter.protocolmode = m_ProtocolMode.GetCurSel();
	SystemParameter.Arq = m_AutoArq.GetCurSel();

	return 0;
}