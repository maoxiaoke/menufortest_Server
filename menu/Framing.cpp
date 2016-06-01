/*==================*/
//
//本文件定义指令帧编码函数
//
/*==================*/
#include "stdafx.h"
#include "TransRevShare.h"
#include  "ParameterSet.h"
#include "Framing.h"


/*****************组SPDU帧*********************/
int* SPDU_framing(void)
{
	int *Transmitter_P;
	int *Control_P;
	int *Receiver_P;
	int *VR;
	int *Report_Request;
	int *Hall_Commond;
	int *PL_Extensions;
	int *Report_Source_SCID;
	int *Pre_SPDU_Data;
	int *SPDU_Data;
	int Num_Commond = 0;
	Pre_SPDU_Data = (int *)malloc(128 * sizeof(int));
	if (SetTransmitterParameters == 1)
	{
		Transmitter_P = (int *)malloc(16 * sizeof(int));
		Transmitter_P = SET_TRANSMITTER();
		for (int n = 0; n<16; n++)
		{
			*(Pre_SPDU_Data + n) = *(Transmitter_P + n);
		}
		Num_Commond++;
	}
	if (SetControlParameters == 1)
	{
		Control_P = (int *)malloc(16 * sizeof(int));
		Control_P = SET_CONTROL();
		for (int n = 0; n<16; n++)
		{
			*(Pre_SPDU_Data + 16 * Num_Commond + n) = *(Control_P + n);
		}
		Num_Commond++;
	}
	if (SetReceiverParameters == 1)
	{
		Receiver_P = (int *)malloc(16 * sizeof(int));
		Receiver_P = SET_RECEIVER();
		for (int n = 0; n<16; n++)
		{
			*(Pre_SPDU_Data + 16 * Num_Commond + n) = *(Receiver_P + n);
		}
		Num_Commond++;
	}
	if (SetVR == 1)
	{
		VR = (int *)malloc(16 * sizeof(int));
		VR = SET_VR();
		for (int n = 0; n<16; n++)
		{
			*(Pre_SPDU_Data + 16 * Num_Commond + n) = *(VR + n);
		}
		Num_Commond++;
	}
	if (ReportRequest == 1)
	{
		Report_Request = (int *)malloc(16 * sizeof(int));
		Report_Request = REPORT_REQUEST();
		for (int n = 0; n<16; n++)
		{
			*(Pre_SPDU_Data + 16 * Num_Commond + n) = *(Report_Request + n);
		}
		Num_Commond++;
	}
	if (HallCommond == 1)
	{
		Hall_Commond = (int *)malloc(16 * sizeof(int));
		Hall_Commond = HALL_COMMOND();
		for (int n = 0; n<16; n++)
		{
			*(Pre_SPDU_Data + 16 * Num_Commond + n) = *(Hall_Commond + n);
		}
		Num_Commond++;
	}
	if (SetPLExtensions == 1)
	{
		PL_Extensions = (int *)malloc(16 * sizeof(int));
		PL_Extensions = SET_PL_EXTENSIONS();
		for (int n = 0; n<16; n++)
		{
			*(Pre_SPDU_Data + 16 * Num_Commond + n) = *(PL_Extensions + n);
		}
		Num_Commond++;
	}
	if (ReportSourceSCID == 1)
	{
		Report_Source_SCID = (int *)malloc(16 * sizeof(int));
		Report_Source_SCID = REPORT_SOURCE_SCID();
		for (int n = 0; n<16; n++)
		{
			*(Pre_SPDU_Data + 16 * Num_Commond + n) = *(Report_Source_SCID + n);
		}
		Num_Commond++;
	}
	SPDU_Data = (int *)malloc((8 + 16 * Num_Commond)*sizeof(int));

	for (int i = 0; i<16 * Num_Commond; i++)
	{
		*(SPDU_Data + 8 + i) = *(Pre_SPDU_Data + i);
	}

	for (int j = 0; j<4; j++)
	{
		*(SPDU_Data + j) = 0;
	}
	int l = 2 * Num_Commond - 1;
	for (int k = 0; k<4; k++)
	{
		*(SPDU_Data + 7 - k) = l % 2;
		l = l / 2;
	}
	return SPDU_Data;
}

int* SET_TRANSMITTER(void)
{
	int *Set_Parameters0;
	Set_Parameters0 = (int *)malloc(16 * sizeof(int));
	for (int i = 0; i<16; i++)
	{
		*(Set_Parameters0 + i) = 0; //初始化发射机设置参数
	}
	return Set_Parameters0;
}

int* SET_CONTROL(void)
{
	int *Set_Parameters1;
	Set_Parameters1 = (int *)malloc(16 * sizeof(int));
	for (int i = 0; i<16; i++)
	{
		*(Set_Parameters1 + i) = 0; //初始化控制设置参数
	}
	*(Set_Parameters1 + 15) = 1;
	*(Set_Parameters1 + 11) = RNMD_T;
	return Set_Parameters1;
}


int* SET_RECEIVER(void)
{
	int *Set_Parameters2;
	Set_Parameters2 = (int *)malloc(16 * sizeof(int));
	for (int i = 0; i<16; i++)
	{
		*(Set_Parameters2 + i) = 0; //初始化接收机设置参数
	}
	*(Set_Parameters2 + 14) = 1;
	return Set_Parameters2;
}

int* SET_VR(void)
{
	int *Set_Parameters3;
	Set_Parameters3 = (int *)malloc(16 * sizeof(int));
	for (int i = 0; i<16; i++)
	{
		*(Set_Parameters3 + i) = 0; //初始化VR设置参数
	}
	*(Set_Parameters3 + 14) = 1;
	*(Set_Parameters3 + 15) = 1;
	return Set_Parameters3;
}

int* REPORT_REQUEST(void)
{
	int *Set_Parameters4;
	Set_Parameters4 = (int *)malloc(16 * sizeof(int));
	for (int i = 0; i<16; i++)
	{
		*(Set_Parameters4 + i) = 0; //初始化report request设置参数
	}
	*(Set_Parameters4 + 13) = 1;
	return Set_Parameters4;
}

int* HALL_COMMOND(void)
{
	int *Set_Parameters5;
	Set_Parameters5 = (int *)malloc(16 * sizeof(int));
	for (int i = 0; i<16; i++)
	{
		*(Set_Parameters5 + i) = 0;//   初始化握手命令
	}
	*(Set_Parameters5 + 13) = 1;
	*(Set_Parameters5 + 15) = 1;
	*(Set_Parameters5) = Start_Hail_T;
	*(Set_Parameters5 + 1) = Hailresponse_T;
	*(Set_Parameters5 + 2) = LNMD_T;
	*(Set_Parameters5 + 3) = ReceiveOver_T;
	*(Set_Parameters5 + 4) = LNMD2_T;
	*(Set_Parameters5 + 5) = RNMD2_T;
	*(Set_Parameters5 + 6) = CarrierSend_T;
	*(Set_Parameters5 + 7) = ResponseSend_T;
	*(Set_Parameters5 + 8) = WaitCarrier_T;

	return Set_Parameters5;
}

int* SET_PL_EXTENSIONS(void)
{
	int *Set_Parameters6;
	Set_Parameters6 = (int *)malloc(16 * sizeof(int));
	for (int i = 0; i<16; i++)
	{
		*(Set_Parameters6 + i) = 0;// 	 初始化PL EXTENSIONS
	}
	*(Set_Parameters6 + 13) = 1;
	*(Set_Parameters6 + 14) = 1;
	return Set_Parameters6;
}

int* REPORT_SOURCE_SCID(void)
{
	int *Set_Parameters7;
	Set_Parameters7 = (int *)malloc(16 * sizeof(int));
	for (int i = 0; i<16; i++)
	{
		*(Set_Parameters7 + i) = 0;// 	 初始化SCID参数
	}
	*(Set_Parameters7 + 13) = 1;
	*(Set_Parameters7 + 14) = 1;
	*(Set_Parameters7 + 15) = 1;
	return Set_Parameters7;
}


/*****************拆P帧*********************/
void UNFRAMING(int *P_Frame, int len)
{
	int protocol_num;
	protocol_num = len / 16;
	int *ProtocolData;
	ProtocolData = (int *)malloc(16 * sizeof(int));
	for (int i = 0; i<protocol_num; i++)
	{
		for (int j = 0; j<16; j++)
		{
			*(ProtocolData + j) = *(P_Frame + 8 + 16 * i + j);
		}
		int DirectiveType;
		DirectiveType = *(ProtocolData + 13) * 4 + *(ProtocolData + 14) * 2 + *(ProtocolData + 15);
		switch (DirectiveType)
		{
		case 0:
			break;
		case 1:
			if (*(ProtocolData + 11) == 1)
				RNMD_R = 1;
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			if (*(ProtocolData) == 1)
				Start_Hail_R = 1;
			if (*(ProtocolData + 1) == 1)
				Hailresponse_R = 1;
			if (*(ProtocolData + 2) == 1)
				LNMD_R = 1;
			if (*(ProtocolData + 3) == 1)
				ReceiveOver_R = 1;
			if (*(ProtocolData + 4) == 1)
				LNMD2_R = 1;
			if (*(ProtocolData + 5) == 1)
				RNMD2_R = 1;
			if (*(ProtocolData + 6) == 1)
				CarrierSend_R = 1;
			if (*(ProtocolData + 7) == 1)
				ResponseSend_R = 1;
			if (*(ProtocolData + 8) == 1)
				WaitCarrier_R = 1;
			//	Hailresponse_R=*(ProtocolData+1); 
			//	LNMD_R=*(ProtocolData+2); 
			//	ReceiveOver_R=*(ProtocolData+3); 
			//	LNMD2_R=*(ProtocolData+4); 
			//	RNMD2_R=*(ProtocolData+5); 
			break;
		case 6:
			break;
		case 7:
			break;
		}
	}
}
int GET_ARQ_NUM(int *r_PLCW)
{
	int a;
	int b = 0;
	for (int i = 0; i<8; i++)
	{
		a = *(r_PLCW + 15 - i)*pow((double)2, i);
		b = b + a;
	}
	return b;
}

int *PLCW_framing(int Retrans_Number)
{
	int *PLCW;
	PLCW = (int *)malloc(16 * sizeof(int));
	for (int i = 0; i<16; i++)
	{
		*(PLCW + i) = 0; //PLCW初始化
	}
	for (int k = 0; k<3; k++)
	{
		*(PLCW + k) = 1;
	}
	int j = Retrans_Number;
	for (int m = 0; m<8; m++)
	{
		*(PLCW + 15 - m) = j % 2;
		j = j / 2;
	}
	return PLCW;
}

