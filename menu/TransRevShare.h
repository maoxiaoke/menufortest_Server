#pragma once //微软编译器独有的，只编译一次
#ifndef		_TransRevShare_H //避免重复包含头文件，在声明每个头文件时采用“头文件卫士”加以保护
#define		_TransRevShare_H
/*======================*/
//
//本头函数定义一些全局变量
//
/*======================*/

extern int endSystemFlag;				//终止系统标识符
extern int validframeflag;					//收到有效帧
/***************指令帧**********************/
extern int UorP;						//选择发送U帧还是P帧
extern int messagestate;		//有无数据发送
extern int commondstate;   //有无指令发送

/***************指令帧数据域类型**********************/
extern int SetTransmitterParameters;		//发射机参数
extern int SetControlParameters;				//控制参数
extern int SetReceiverParameters;			//接收机参数
extern int SetVR;											//设置V（R）
extern int ReportRequest;							//报告请求
extern int HallCommond;							//握手指令
extern int SetPLExtensions;						//PL扩展
extern int ReportSourceSCID;					//报告源SCID

/********************交互指令************************/
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

extern int *CommondGroup;						//存储发送指令数组
extern int *ArqGroup;									//存储arq指令数组

/***************配置**********************/
extern int Length_Data  //每帧发送数据的长度（bit）
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
extern int F_CRC
	, F_CC
	, F_Depth
	, F_Scramble
	, F_Mod
	, F_Channel;
/***************组帧*********************/
extern	 int *P_Data							//随机生成或载入的数据的指针
	,*P_Data_CC									//帧加CRC加ASM加CC的指针
	, *P_Data_FH									//数据加帧头的指针
	,*P_Data_CRC								//（数据+CRC32）的指针
//	,*Data_CRC32								//CRC返回值
	,*P_Data_CRC_CC							//（数据+CRC32）经CC卷积后 的指针
	,*P_Data_CRC_CC_Itl					//（数据+CRC32）经CC卷积交织后 的指针
	,*P_Data_Scramble						//数据加扰后的指针
	,*P_PLTU										//PLTU数据的指针
	, Len_DataInProcess					//处理过程中的数据长度
	, Len_DataInProcess1;

/***************拆帧*********************/
extern int *P_FS_Location			//帧同步之后的帧头位置
, *P_Dem										//解调后的数据 指针
, *P_Descramble							//解扰后的数据 指针
, *P_DeInterleave							//解交织后的数据
, *P_CC											//CC译码之后的数据 指针
, *P_CRC;										//CRC解码之后的数据 指针

extern int num_frame;						//帧序列号
extern int SerialNumber1;				//接收端拆帧读取的序列号
extern	 int datalength1;					//接收端拆帧读取的帧长度
extern int missnumber;						//丢失帧数

extern int *P_DeASM;						//去ASM后的数据指针
extern int *P_Rev;							//最后存的数据指针
extern int *P_RE;								//读取的数据指针

extern double	Error;						//?
extern int *SourceFile;					//对方发送文件
extern	 int fileSize1;							//对方发送文件的大小

extern double AverageErrorRate; //平均误码率
extern double CurrentErrorRate;	//当前误码率

extern int receivenumber;		//收到数据的帧数

/*********重传ARQ*********/
extern int Arq_data[160000];					//重传的数组的缓存指针		
extern int arqreceiveflag;			//arq标识符
extern int ResendNumber_R;				//接收的重传帧号
extern int NeedSerialNumber;			//需要的帧号

/*********网络连接*********/
extern int ConnectOkFlag;					//成功连接标识符

	


#endif