#pragma once //΢����������еģ�ֻ����һ��
#ifndef		_TransRevShare_H //�����ظ�����ͷ�ļ���������ÿ��ͷ�ļ�ʱ���á�ͷ�ļ���ʿ�����Ա���
#define		_TransRevShare_H
/*======================*/
//
//��ͷ��������һЩȫ�ֱ���
//
/*======================*/

extern int endSystemFlag;				//��ֹϵͳ��ʶ��
extern int validframeflag;					//�յ���Ч֡
/***************ָ��֡**********************/
extern int UorP;						//ѡ����U֡����P֡
extern int messagestate;		//�������ݷ���
extern int commondstate;   //����ָ���

/***************ָ��֡����������**********************/
extern int SetTransmitterParameters;		//���������
extern int SetControlParameters;				//���Ʋ���
extern int SetReceiverParameters;			//���ջ�����
extern int SetVR;											//����V��R��
extern int ReportRequest;							//��������
extern int HallCommond;							//����ָ��
extern int SetPLExtensions;						//PL��չ
extern int ReportSourceSCID;					//����ԴSCID

/********************����ָ��************************/
extern int RNMD_T;
extern int LNMD_T;
extern int Start_Hail_T;
extern int Hailresponse_T;
extern int ReceiveOver_T;
extern int LNMD2_T;
extern int RNMD2_T;
extern int CarrierSend_T;
extern int ResponseSend_T;
extern int WaitCarrier_T;

extern int RNMD_R;
extern int LNMD_R;
extern int Start_Hail_R;
extern int Hailresponse_R;
extern int ReceiveOver_R;
extern int LNMD2_R;
extern int RNMD2_R;
extern int CarrierSend_R;
extern int ResponseSend_R;
extern int WaitCarrier_R;

extern int *CommondGroup;						//�洢����ָ������
extern int *ArqGroup;									//�洢arqָ������

/***************����**********************/
extern int Length_Data  //ÿ֡�������ݵĳ��ȣ�bit��
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
extern int F_CRC
	, F_CC
	, F_Depth
	, F_Scramble
	, F_Mod
	, F_Channel;
/***************��֡*********************/
extern	 int *P_Data							//������ɻ���������ݵ�ָ��
	,*P_Data_CC									//֡��CRC��ASM��CC��ָ��
	, *P_Data_FH									//���ݼ�֡ͷ��ָ��
	,*P_Data_CRC								//������+CRC32����ָ��
//	,*Data_CRC32								//CRC����ֵ
	,*P_Data_CRC_CC							//������+CRC32����CC����� ��ָ��
	,*P_Data_CRC_CC_Itl					//������+CRC32����CC�����֯�� ��ָ��
	,*P_Data_Scramble						//���ݼ��ź��ָ��
	,*P_PLTU										//PLTU���ݵ�ָ��
	, Len_DataInProcess					//��������е����ݳ���
	, Len_DataInProcess1;

/***************��֡*********************/
extern int *P_FS_Location			//֡ͬ��֮���֡ͷλ��
, *P_Dem										//���������� ָ��
, *P_Descramble							//���ź������ ָ��
, *P_DeInterleave							//�⽻֯�������
, *P_CC											//CC����֮������� ָ��
, *P_CRC;										//CRC����֮������� ָ��

extern int num_frame;						//֡���к�
extern int SerialNumber1;				//���ն˲�֡��ȡ�����к�
extern	 int datalength1;					//���ն˲�֡��ȡ��֡����
extern int missnumber;						//��ʧ֡��

extern int *P_DeASM;						//ȥASM�������ָ��
extern int *P_Rev;							//���������ָ��
extern int *P_RE;								//��ȡ������ָ��

extern double	Error;						//?
extern int *SourceFile;					//�Է������ļ�
extern	 int fileSize1;							//�Է������ļ��Ĵ�С

extern double AverageErrorRate; //ƽ��������
extern double CurrentErrorRate;	//��ǰ������

extern int receivenumber;		//�յ����ݵ�֡��

/*********�ش�ARQ*********/
extern int Arq_data[160000];					//�ش�������Ļ���ָ��		
extern int arqreceiveflag;			//arq��ʶ��
extern int ResendNumber_R;				//���յ��ش�֡��
extern int NeedSerialNumber;			//��Ҫ��֡��

/*********��������*********/
extern int ConnectOkFlag;					//�ɹ����ӱ�ʶ��

	


#endif