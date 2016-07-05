/*

	��cpp�ļ�ΪTransRevShare.hͷ�ļ��Ĳ��������ļ�

*/


#include "stdafx.h"
#include "TransRevShare.h"

/***************��ʶ��**********************/
int endSystemFlag;				//��ֹϵͳ��ʶ��
int validframeflag;					//�յ���Ч֡��ʶ
/***************ָ��֡**********************/
int UorP;						//ѡ����U֡����P֡
int messagestate;		//�������ݷ���
int commondstate;	//����ָ���

/***************ָ��֡����������**********************/
int SetTransmitterParameters;		//���������
int SetControlParameters;				//���Ʋ���
int SetReceiverParameters;			//���ջ�����
int SetVR;											//����V��R��
int ReportRequest;							//��������
int HallCommond;							//����ָ��
int SetPLExtensions;						//PL��չ
int ReportSourceSCID;					//����ԴSCID

/********************����ָ��************************/
int RNMD_T;
int LNMD_T;
int Start_Hail_T;
int Hailresponse_T;
int ReceiveOver_T;
int LNMD2_T;
int RNMD2_T;
int CarrierSend_T;
int ResponseSend_T;
int WaitCarrier_T;

int RNMD_R;
int LNMD_R;
int Start_Hail_R;
int Hailresponse_R;
int ReceiveOver_R;
int LNMD2_R;
int RNMD2_R;
int CarrierSend_R;
int ResponseSend_R;
int WaitCarrier_R;

int *CommondGroup;						//�洢����ָ������
int *ArqGroup;									//�洢arqָ������

/***************����************************/
int Length_Data  //ÿ֡�������ݵĳ��ȣ�bit��
	, Num_Frame   //���δ��� ֡��
	, Num_Data		//���δ��� ������ ��bit��
//���Ͷ�
//	, M_source_rand  //�����������ѡ��
//	, M_source_load	//���ݼ���ѡ��
	, M_CRC					//CRCѡ��
	, M_CC					//CCѡ��
	, M_Depth				//֡�ڽ�֯���ѡ��
	, M_Scramble		//���ŷ�ʽ
	, M_Mod;				//���Ʒ�ʽѡ��

/***************���ն�********************/
int F_CRC
	, F_CC
	, F_Depth
	, F_Scramble
	, F_Mod
	, F_Channel;
/***************����*********************/
int *P_Data							//������ɻ���������ݵ�ָ��
, *P_Data_CC									//֡��CRC��ASM��CC��ָ��
, *P_Data_FH									//���ݼ�֡ͷ��ָ��
, *P_Data_CRC								//������+CRC32����ָ��
//	, *Data_CRC32								//CRC����ֵ
, *P_Data_CRC_CC							//������+CRC32����CC����� ��ָ��
, *P_Data_CRC_CC_Itl					//������+CRC32����CC�����֯�� ��ָ��
, *P_Data_Scramble						//���ݼ��ź��ָ��
, *P_PLTU										//PLTU���ݵ�ָ��
, Len_DataInProcess						//��������е����ݳ���
, Len_DataInProcess1;

/***************��֡*********************/
int *P_FS_Location			//֡ͬ��֮���֡ͷλ��
, *P_Dem										//���������� ָ��
, *P_Descramble							//���ź������ ָ��
, *P_DeInterleave							//�⽻֯�������
, *P_CC											//CC����֮������� ָ��
, *P_CRC;										//CRC����֮������� ָ��




int num_frame;						//֡���к�
int SerialNumber1;					//���ն˲�֡��ȡ�����к�
int datalength1;						//���ն˲�֡��ȡ��֡����
int missnumber;						//��ʧ֡��

int *P_DeASM;						//ȥASM�������ָ��
int *P_Rev;							//���������ָ��
int *P_RE;								//��ȡ������ָ��

double	Error;						//?
int *SourceFile;					//�Է������ļ�
int fileSize1;							//�Է������ļ��Ĵ�С

double AverageErrorRate; //ƽ��������
double CurrentErrorRate;	//��ǰ������

int receivenumber;		//�յ����ݵ�֡��

/*********�ش�ARQ*********/
int Arq_data[160000];					//�ش�������Ļ���ָ��
int arqreceiveflag;			//arq��ʶ��
int ResendNumber_R;				//���յ��ش�֡��
int NeedSerialNumber;			//��Ҫ��֡��

/*********��������*********/
int ConnectOkFlag;					//�ɹ����ӱ�ʶ��