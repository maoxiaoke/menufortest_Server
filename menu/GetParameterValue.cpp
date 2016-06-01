/*
	本cpp文件获取对话框PARAMETERSET中控件的值，并存放到全局变量中
	函数的头文件是ParameterSet.h
*/
#include "stdafx.h"
#include "ParameterSet.h"
#include "SystemParameter.h"


/*===============================*/
//FunctionName:GetSendAParameterValue
//Description: 获取本地发射机参数值
/*===============================*/
int CParameterSet::GetSendAParameterValue(int a)
{	
	SendA.FrameLength = GetDlgItemInt(IDC_FRAMESPIN_EDIT);					//获得帧长
	SendA.ModulationMethod = m_ModulationCombo.GetCurSel();			//调制方式
	SendA.CC = m_CcCodeCombo.GetCurSel();													//是否CC编码
	SendA.ChannelStatus = m_ChannelStatusCombo.GetCurSel();					// 信道状态
	GetDlgItemText(IDC_SENDSOUCER_EDIT,SendA.gSendDataPath);			//发射机地址
	SendA.CRC = 1;																									//强制CRC编码
	SendA.Num_Frame = 1;																						//单次传输帧数为1帧
	return 0;
}


/*===============================*/
//FunctionName:GetReceiveAParameterValue
//Description: 获取本地接收机参数值
/*===============================*/
int CParameterSet::GetReceiveAParameterValue(int a)
{	
	ReceiveA.ModulationMethod = m_ModulationCombo2.GetCurSel();
	ReceiveA.CC = m_CcCodeCombo2.GetCurSel();
	GetDlgItemText(IDC_RECEIVESAVE_EDIT, ReceiveA.gReceiveDataPath);
	GetDlgItemText(IDC_RECEIVESOUCER_EDIT, ReceiveA.gRemoteDataPath);
	ReceiveA.CRC = 1;																												//强制CRC编码

	return 0;
}

/*===============================*/
//FunctionName:GetSystemParameterValue
//Description: 获取系统参数值
/*===============================*/
int CParameterSet::GetSystemParameterValue(int a)
{
	SystemParameter.protocolmode = m_ProtocolMode.GetCurSel();
	SystemParameter.Arq = m_AutoArq.GetCurSel();

	return 0;
}