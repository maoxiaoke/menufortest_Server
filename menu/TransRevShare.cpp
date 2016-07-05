/*

	该cpp文件为TransRevShare.h头文件的参数定义文件

*/


#include "stdafx.h"
#include "TransRevShare.h"

/***************标识符**********************/
int endSystemFlag;				//终止系统标识符
int validframeflag;					//收到有效帧标识
/***************指令帧**********************/
int UorP;						//选择发送U帧还是P帧
int messagestate;		//有无数据发送
int commondstate;	//有无指令发送

/***************指令帧数据域类型**********************/
int SetTransmitterParameters;		//发射机参数
int SetControlParameters;				//控制参数
int SetReceiverParameters;			//接收机参数
int SetVR;											//设置V（R）
int ReportRequest;							//报告请求
int HallCommond;							//握手指令
int SetPLExtensions;						//PL扩展
int ReportSourceSCID;					//报告源SCID

/********************交互指令************************/
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

int *CommondGroup;						//存储发送指令数组
int *ArqGroup;									//存储arq指令数组

/***************配置************************/
int Length_Data  //每帧发送数据的长度（bit）
	, Num_Frame   //单次传输 帧数
	, Num_Data		//单次传输 总数据 （bit）
//发送端
//	, M_source_rand  //数据随机生成选项
//	, M_source_load	//数据加载选项
	, M_CRC					//CRC选项
	, M_CC					//CC选项
	, M_Depth				//帧内交织深度选项
	, M_Scramble		//加扰方式
	, M_Mod;				//调制方式选项

/***************接收端********************/
int F_CRC
	, F_CC
	, F_Depth
	, F_Scramble
	, F_Mod
	, F_Channel;
/***************编码*********************/
int *P_Data							//随机生成或载入的数据的指针
, *P_Data_CC									//帧加CRC加ASM加CC的指针
, *P_Data_FH									//数据加帧头的指针
, *P_Data_CRC								//（数据+CRC32）的指针
//	, *Data_CRC32								//CRC返回值
, *P_Data_CRC_CC							//（数据+CRC32）经CC卷积后 的指针
, *P_Data_CRC_CC_Itl					//（数据+CRC32）经CC卷积交织后 的指针
, *P_Data_Scramble						//数据加扰后的指针
, *P_PLTU										//PLTU数据的指针
, Len_DataInProcess						//处理过程中的数据长度
, Len_DataInProcess1;

/***************拆帧*********************/
int *P_FS_Location			//帧同步之后的帧头位置
, *P_Dem										//解调后的数据 指针
, *P_Descramble							//解扰后的数据 指针
, *P_DeInterleave							//解交织后的数据
, *P_CC											//CC译码之后的数据 指针
, *P_CRC;										//CRC解码之后的数据 指针




int num_frame;						//帧序列号
int SerialNumber1;					//接收端拆帧读取的序列号
int datalength1;						//接收端拆帧读取的帧长度
int missnumber;						//丢失帧数

int *P_DeASM;						//去ASM后的数据指针
int *P_Rev;							//最后存的数据指针
int *P_RE;								//读取的数据指针

double	Error;						//?
int *SourceFile;					//对方发送文件
int fileSize1;							//对方发送文件的大小

double AverageErrorRate; //平均误码率
double CurrentErrorRate;	//当前误码率

int receivenumber;		//收到数据的帧数

/*********重传ARQ*********/
int Arq_data[160000];					//重传的数组的缓存指针
int arqreceiveflag;			//arq标识符
int ResendNumber_R;				//接收的重传帧号
int NeedSerialNumber;			//需要的帧号

/*********网络连接*********/
int ConnectOkFlag;					//成功连接标识符