/*==================*/
//
//本文件定义编码函数
//
/*==================*/
#include "stdafx.h"
#include "TransRevShare.h"
#include "SystemParameter.h"
#include "encode.h"



/*===============================*/
//FunctionName:encode
//Description: 对数据帧进行组帧
/*===============================*/
int encode(int *P_Data)
{
	int i, j, k;

	Num_Data = SendA.FrameLength * 8 * SendA.Num_Frame;
	M_Mod = SendA.ModulationMethod;
	Len_DataInProcess = Num_Data;

	/*-----------------------加帧头----------------------------*/
	int fLen_fh = SendA.FrameLength * 8 + 40            //一帧加了帧头之后的数据长度
		, dLen_fh = fLen_fh*SendA.Num_Frame;      //所有帧加了帧头之后的数据长度
	Len_DataInProcess = dLen_fh;

	P_Data_FH = (int *)malloc(dLen_fh*sizeof(int));  //分配存储空间
	int	*Data_FH40;
	Data_FH40 = (int *)malloc(40 * sizeof(int));

	for (i = 0; i<SendA.Num_Frame; i++)					  //将帧长加入帧头
	{
		for (j = 0; j<SendA.FrameLength * 8; j++)
		{
			*(40 + P_Data_FH + i*fLen_fh + j) = *(P_Data + i*SendA.FrameLength * 8 + j);
		}
		FH40(SendA.FrameLength * 8, Data_FH40);
		for (k = 0; k<40; k++)
		{
			*(P_Data_FH + i*fLen_fh + k) = Data_FH40[k];

		}
		k = num_frame;
		
		//将帧序列号加入帧头
		for (j = 0; j<8; j++)
		{
			*(P_Data_FH + i*fLen_fh + 39 - j) = k % 2;
			k = k / 2;
		}
	}

	/*--------------------CRC32------------------------*/
	int fLen_crc = fLen_fh + 32													  //加帧头之后一帧crc之后的数据长度
		, dLen_crc = fLen_crc*SendA.Num_Frame;					   //所有crc之后的数据长度
	Len_DataInProcess = dLen_crc;

	P_Data_CRC = (int *)malloc(dLen_crc*sizeof(int));			  //分配存储空间
	int *Data_CRC32;																     //CRC返回值
	Data_CRC32 = (int *)malloc(32 * sizeof(int));				    //分配存储空间

	M_CRC = SendA.CRC;
	switch (M_CRC)
	{
	case 1:
		for (i = 0; i<SendA.Num_Frame; i++)
		{
			for (j = 0; j<fLen_fh; j++)
			{
				*(P_Data_CRC + i*fLen_crc + j) = *(P_Data_FH + i*fLen_fh + j);
			}

			CRC32(P_Data_FH + i*fLen_fh, fLen_fh, Data_CRC32);				  //对整个数据域做CRC

			for (k = 0; k<32; k++)
			{
				*(P_Data_CRC + fLen_fh + i*fLen_crc + k) = Data_CRC32[k];
			}
		}
	}

	/*----------------------加ASM组帧------------------------*/
	int fLen_crc_pltu = 24 + fLen_crc																				  //一帧CRC组帧之后的pltu数据长度
		, dLen_crc_pltu = fLen_crc_pltu*SendA.Num_Frame;										 //所有CRC之后组帧的pltu数据长度
	int ASM[24] = { 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0 };
	Len_DataInProcess = Len_DataInProcess + 24 * SendA.Num_Frame;				//刷新传输数据长度

	P_PLTU = (int *)malloc(dLen_crc_pltu*sizeof(int));												//分配存储空间

	for (i = 0; i<SendA.Num_Frame; i++)
	{
		for (j = 0; j<24; j++)
		{
			P_PLTU[i*fLen_crc_pltu + j] = ASM[j];
		}
		for (k = 0; k<fLen_crc; k++)
		{
			P_PLTU[i*fLen_crc_pltu + 24 + k] = P_Data_CRC[i*fLen_crc + k];
		}
	}


	/*---------------------CC-----------------------------*/
	int dLen_crc_pltu_cc = (dLen_crc_pltu)* 2 + 12;										//cc之后的数据长度
	int *Data_CC;																										//CC217返回值

	M_CC = SendA.CC;
	switch (M_CC)
	{
	case 1:																												//做（2,1,7）卷积
		P_Data_CC = (int *)malloc(dLen_crc_pltu_cc*sizeof(int));					  //分配存储空间
		Data_CC = CC217(P_PLTU, dLen_crc_pltu);
		for (j = 0; j<dLen_crc_pltu_cc; j++)
		{
			*(P_Data_CC + j) = Data_CC[j];
		}
		Len_DataInProcess = dLen_crc_pltu_cc;
		break;

	case 0:																											//不做卷积
		P_Data_CC = (int *)malloc(Len_DataInProcess*sizeof(int));				//分配存储空间
		for (i = 0; i<Len_DataInProcess; i++)
		{
			*(P_Data_CC + i) = *(P_PLTU + i);
		}
		break;
	}


	/*****自己敲的代码
	int k;
	Num_Data = SendA.FrameLength * 8;
	M_Mod = SendA.ModulationMethod;
	Len_DataInProcess = Num_Data;	

	/==============加帧头==============/
	int fLen_fh = SendA.FrameLength * 8 + 40				  //一帧加了帧头之后的数据长度
		, dLen_fh = fLen_fh*SendA.Num_Frame;				//所有帧加帧头之后的数据
	Len_DataInProcess = dLen_fh;
		
	P_Data_FH = (int *)malloc(dLen_fh*sizeof(int));
	int *Data_FH40;
	Data_FH40 = (int *)malloc(40 * sizeof(int));
	for (int i = 0; i < SendA.Num_Frame; i++)
	{
		for (int j = 0;  j < SendA.FrameLength*8;  j++)
		{
			*(40+P_Data_FH+i+fLen_fh+j) = *(P_Data + i *SendA.FrameLength * 8 + j);
		}
		FH40(SendA.FrameLength * 8, Data_FH40);
		for (k = 0; k < 40; k++)
		{
			*(P_Data_FH + i*fLen_fh + k) = Data_FH40[k];
		}
		k = num_frame;
		//将帧序列号加入帧头
		for (int j = 0; j < 8; j++)
		{
			*(P_Data_FH + i*fLen_fh + 39 - j) = k % 2;
			k = k / 2;
		}
	}

	free(Data_FH40);

	/===============CRC32================/
	int fLen_crc = fLen_fh + 32												//加帧头之后一帧数据CRC之后的数据长度
		, dLen_crc = fLen_crc*SendA.Num_Frame;				//所有帧CRC之后的数据长度

	Len_DataInProcess = dLen_crc;
	P_Data_CRC = (int *)malloc(dLen_crc*sizeof(int));		//分配存储空间

	int *Data_CRC32;																//CRC返回值
	Data_CRC32 = (int *)malloc(32 * sizeof(int));
	M_CRC = SendA.CRC;
//	M_CRC = 1;
	switch (M_CRC)
	{	
	case 1:
		for (int i = 0; i < SendA.Num_Frame; i++)
		{
			for (int j = 0; j < fLen_fh; j++)
			{
				*(P_Data_CRC + i*fLen_crc + j) = *(P_Data_FH +i*fLen_fh + j);
			}
			CRC32(P_Data_FH + i*fLen_fh, fLen_fh, Data_CRC32);				//调用CRC32，对整个数域做CRC
			for (int k = 0; k < 32; k++)
			{
				*(P_Data_CRC + fLen_fh + i*fLen_crc + k) = Data_CRC32[k];
			}
		}
		break;
	default:
		break;
	}

	free(P_Data_FH);

	/==============加ASM组帧==============/
	int fLen_crc_pltu = 24 + fLen_crc														//一帧CRC组帧之后的pltu数据长度
		, dLen_crc_pltu = fLen_crc_pltu*SendA.Num_Frame;				//所有CRC之后组帧的pltu数据长度
	int ASM[24] = { 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0 };
	Len_DataInProcess = Len_DataInProcess + 24 * SendA.Num_Frame;		//刷新传输数据长度

	P_PLTU = (int *)malloc(dLen_crc_pltu*sizeof(int));
	for (int i = 0; i<SendA.Num_Frame; i++)
	{
		for (int j = 0; j<24; j++)
		{
			P_PLTU[i*fLen_crc_pltu + j] = ASM[j];
		}
		for (k = 0; k<fLen_crc; k++)
		{
			P_PLTU[i*fLen_crc_pltu + 24 + k] = P_Data_CRC[i*fLen_crc + k];
		}
	}

	/=================CC===================/

	int dLen_crc_pltu_cc = (dLen_crc_pltu)* 2 + 12;						//CC之后的数据长度
	int *Data_CC;

	M_CC = SendA.CC;																			//读取CC值
	switch (M_CC)
	{
	case 1:																								//做CC217卷积
		P_Data_CC = (int *)malloc(dLen_crc_pltu_cc*sizeof(int));		//分配存储空间

		Data_CC = CC217(P_PLTU, dLen_crc_pltu);
		for (int j = 0; j<dLen_crc_pltu_cc; j++)
		{
			*(P_Data_CC + j) = Data_CC[j];
		}
		Len_DataInProcess = dLen_crc_pltu_cc;
		break;

	case 0:																								//不做卷积
		P_Data_CC = (int *)malloc(Len_DataInProcess*sizeof(int));	  //分配存储空间
		for (int i = 0; i<Len_DataInProcess; i++)
		{
			*(P_Data_CC + i) = *(P_PLTU + i);
		}
		break;
	default:
		break;
	}
*/
	
	return 0;
}


/*===============================*/
//FunctionName:decode
//Description: 对数据帧进行拆帧
/*===============================*/
int decode(int *P_RE, int FileSize)
{
	int i, j, k;

	Len_DataInProcess1 = FileSize;

	//CC
	int fLenRevCC		//一帧CC解码之后的数据长度
		, dLenRevCC		//所有数据CC解码之后的数据长度
		, *Temp_CC;



	//CRC
	int fLenRevCRC		//一帧CRC解码之后的数据长度
		, dLenRevCRC		//所有数据CRC解码之后的数据长度
		, *Rev_CRC32;   //CRC32返回值
	double error = 0;

	//处理之后最终要存到文件的数据
	int fLenRev     //一帧数据的长度
		, dLenRev;   //所有数据的长度

	/*-----------------------CC译码-------------------------*/
	F_CC = ReceiveA.CC;
	switch (F_CC)
	{
	case 0:							//不做卷积译码
		dLenRevCC = Len_DataInProcess1;
		P_CC = (int *)malloc(dLenRevCC * sizeof(int));
		for (i = 0; i<dLenRevCC; i++)
		{
			*(P_CC + i) = *(P_RE + i);
		}
		break;
	case 1:							//做卷积译码
		dLenRevCC = (Len_DataInProcess1 - 12) / 2;
		//分配存储空间
		P_CC = (int *)malloc(dLenRevCC * sizeof(int));
		Temp_CC = DeCC217(P_RE, Len_DataInProcess1);
		for (j = 0; j<dLenRevCC; j++)
		{
			*(P_CC + j) = Temp_CC[j];
		}
		Len_DataInProcess1 = dLenRevCC;
		break;
	}

	/*-----------------------读帧头获取帧长度和帧数以及帧序列号-------------------------*/
	int *length;
	int Len = 1;
	int SerialNumber = 0;
	int *serialnumber;

	serialnumber = (int *)malloc(8 * sizeof(int));
	length = (int *)malloc(11 * sizeof(int));
	for (i = 0; i<11; i++)
	{
		length[i] = P_RE[55 - i] * pow((double)2, i);
		Len = Len + length[i];
	}
	Num_Frame = Len_DataInProcess1 / (Len + 56);
	fLenRevCC = Len + 56;
	for (k = 0; k<8; k++)
	{
		serialnumber[k] = P_RE[63 - k] * pow((double)2, k);
		SerialNumber = SerialNumber + serialnumber[k];
	}
	datalength1 = Len - 40;
	SerialNumber1 = SerialNumber;

	int *mod;
	int Mod = 0;
	mod = (int *)malloc(2 * sizeof(int));
	for (j = 0; j<2; j++)
	{
		mod[j] = P_RE[29 - j] * pow((double)2, j);
		Mod = Mod + mod[j];
	}

	/*-----------------------去ASM位-------------------------*/
	P_DeASM = (int *)malloc((Len_DataInProcess1 - 24 * Num_Frame)*sizeof(int));
	for (i = 0; i<Num_Frame; i++)
	{
		for (j = 0; j<(Len_DataInProcess1 / Num_Frame - 24); j++)
		{
			P_DeASM[i*(Len_DataInProcess1 / Num_Frame - 24) + j] = P_CC[i*(Len_DataInProcess1 / Num_Frame) + 24 + j];
		}
	}
	Len_DataInProcess1 = Len_DataInProcess1 - 24 * Num_Frame;

	/*-----------------------去CRC----------------------------*/
	F_CRC = ReceiveA.CRC;

	/***定义成全局变量
	double AverageErrorRate;
	double CurrentErrorRate;
	*/
	switch (1)  //本来应该是F_CRC
	{
	case 1:
		fLenRevCRC = fLenRevCC - 56;
		dLenRevCRC = fLenRevCRC*Num_Frame;

		Rev_CRC32 = (int *)malloc(32 * sizeof(int));	 //分配存储空间
		P_CRC = (int *)malloc(dLenRevCRC*sizeof(int));
		for (i = 0; i<Num_Frame; i++)							//做CRC32
		{
			for (j = 0; j<fLenRevCRC; j++)
			{
				P_CRC[j + i*fLenRevCRC] = P_DeASM[j + i*(fLenRevCRC + 32)];
			}
		}
		break;
	}
	Len_DataInProcess1 = Len_DataInProcess1 - 32 * Num_Frame;

	/*-----------------------去帧头----------------------------*/
	fLenRev = fLenRevCRC - 40;
	dLenRev = fLenRev*Num_Frame;

	P_Rev = (int *)malloc(dLenRev*sizeof(int));//分配存储空间

	for (i = 0; i<Num_Frame; i++)
	{
		for (j = 0; j<fLenRev; j++)
		{
			P_Rev[j + i*fLenRev] = P_CRC[40 + j + i*fLenRevCRC];

		}
	}
	Len_DataInProcess1 = Len_DataInProcess1 - 40 * Num_Frame;

	if (fileSize1<fLenRev*(SerialNumber + 1))
	{
		for (k = 0; k<fileSize1%fLenRev; k++)
		{
			if (P_Rev[k] != SourceFile[k + fLenRev*SerialNumber])
			{
				error++;
				Error++;
			}
		}
	}
	else
	{
		for (k = 0; k<fLenRev; k++)
		{
			if (P_Rev[k] != SourceFile[k + fLenRev*SerialNumber])
			{
				error++;
				Error++;
			}
		}
	}
	CurrentErrorRate = 100 * error / (Len - 40);
	AverageErrorRate = 100 * Error / (datalength1*(SerialNumber1 + 1));


	return 0;
}

/*===============================*/
//FunctionName:FH40
//Description: 加入40位帧头
//							输入：一帧发送的数据
//										发送的数据长度
/*===============================*/
void FH40(int len, int *r40)
{
	for (int i = 0; i < 40 ; i++)
	{
		*(r40 + i) = 0;
	}
	*(r40) = 1;
	if (UorP == 1)
	{
		*(r40 + 2) = 1;
		*(r40 + 3) = 1;
	}

	/*帧头第四位和第五位数据域结构标识符不需要，替换成调制方式：00：BPSK，01：QPSK，其余备用*/
	switch (M_Mod)
	{
	case 0:
		*(r40 + 4) = 0;
		*(r40 + 5) = 0;
		break;
	case 1:
		*(r40 + 4) = 0;
		*(r40 + 5) = 1;
		break;
	default:
		break;
	}
	int k = 39 + len;
	for (int i = 0; i < 11; i++)
	{
		if (k != 0)
		{
			*(r40 + 31 - i) = k % 2;
			k = k / 2;
		}
		else
		{
			*(r40 + 31 - i) = 0;
		}
	}
}


/*===============================*/
//FunctionName:CRC32
//Description: 32位冗余校验
//							输入：一帧发送的数据
//										一帧发送的数据长度
//										32位CRC（用于返回CRC32）
/*===============================*/
void CRC32(int *pv3, int len, int *r32)
{
	int s1 = 0, s2 = 0, s3 = 0, s4 = 0, s5 = 0;

	for (int i = 0; i < 32; i++) //r32复位零
	{
		*(r32 + i) = 0;
	}
	for (int i = 0; i < len; i++)
	{
		s1 = pv3[i] ^ r32[0];
		s2 = s1 ^ r32[9];
		s3 = s1 ^ r32[11];
		s4 = s1 ^ r32[21];
		s5 = s1 ^ r32[30];

		for (int j = 0; j < 31; j++)
		{
			r32[j] = r32[j + 1];
		}

		r32[31] = s1;
		r32[8] = s2;
		r32[10] = s3;
		r32[20] = s4;
		r32[29] = s5;
	}
}


/*===============================*/
//FunctionName:CC217
//Description: CC编码
//							输入：一帧Data + CRC32(int 型指针)
//										发送的数据长度
//							输出：CC(2,1,7)编码 (int 型指针)
/*===============================*/
int *CC217(int *buffer_crc32, int Length)
{
	int len_cc, len_crc32, last;

	len_crc32 = Length;		//(2,1,7)卷积码前，序列的长度
	len_cc = len_crc32 * 2 + 12;		//(2,1,7)卷积码后，序列的长度 

	int *buffer_cc;
	buffer_cc =(int *) malloc((len_cc)*sizeof(int));		//分配存储空间

	buffer_cc[0 + 0] = buffer_crc32[0];
	buffer_cc[0 + 1] = buffer_crc32[0];

	buffer_cc[1 * 2 + 0] = buffer_crc32[1] ^ buffer_crc32[0];
	buffer_cc[1 * 2 + 1] = buffer_crc32[1];

	buffer_cc[2 * 2 + 0] = buffer_crc32[2] ^ buffer_crc32[1] ^ buffer_crc32[0];
	buffer_cc[2 * 2 + 1] = buffer_crc32[2] ^ buffer_crc32[0];

	buffer_cc[3 * 2 + 0] = buffer_crc32[3] ^ buffer_crc32[2] ^ buffer_crc32[1] ^ buffer_crc32[0];
	buffer_cc[3 * 2 + 1] = buffer_crc32[3] ^ buffer_crc32[1] ^ buffer_crc32[0];

	buffer_cc[4 * 2 + 0] = buffer_crc32[4] ^ buffer_crc32[3] ^ buffer_crc32[2] ^ buffer_crc32[1];
	buffer_cc[4 * 2 + 1] = buffer_crc32[4] ^ buffer_crc32[2] ^ buffer_crc32[1];

	buffer_cc[5 * 2 + 0] = buffer_crc32[5] ^ buffer_crc32[4] ^ buffer_crc32[3] ^ buffer_crc32[2];
	buffer_cc[5 * 2 + 1] = buffer_crc32[5] ^ buffer_crc32[3] ^ buffer_crc32[2] ^ buffer_crc32[0];

	for (int i = 6; i<len_crc32; i++)
	{
		buffer_cc[i * 2 + 0] = buffer_crc32[i] ^ buffer_crc32[i - 1] ^ buffer_crc32[i - 2] ^ buffer_crc32[i - 3] ^ buffer_crc32[i - 6];
		buffer_cc[i * 2 + 1] = buffer_crc32[i] ^ buffer_crc32[i - 2] ^ buffer_crc32[i - 3] ^ buffer_crc32[i - 5] ^ buffer_crc32[i - 6];
	}

	last = len_crc32 - 1;

	buffer_cc[len_crc32 * 2 + 0] = buffer_crc32[last] ^ buffer_crc32[last - 1] ^ buffer_crc32[last - 2] ^ buffer_crc32[last - 5];
	buffer_cc[len_crc32 * 2 + 1] = buffer_crc32[last - 1] ^ buffer_crc32[last - 2] ^ buffer_crc32[last - 4] ^ buffer_crc32[last - 5];

	buffer_cc[(len_crc32 + 1) * 2 + 0] = buffer_crc32[last] ^ buffer_crc32[last - 1] ^ buffer_crc32[last - 4];
	buffer_cc[(len_crc32 + 1) * 2 + 1] = buffer_crc32[last] ^ buffer_crc32[last - 1] ^ buffer_crc32[last - 3];

	buffer_cc[(len_crc32 + 2) * 2 + 0] = buffer_crc32[last] ^ buffer_crc32[last - 3];
	buffer_cc[(len_crc32 + 2) * 2 + 1] = buffer_crc32[last] ^ buffer_crc32[last - 2];

	buffer_cc[(len_crc32 + 3) * 2 + 0] = buffer_crc32[last - 2];
	buffer_cc[(len_crc32 + 3) * 2 + 1] = buffer_crc32[last - 1] ^ buffer_crc32[last - 2];

	buffer_cc[(len_crc32 + 4) * 2 + 0] = buffer_crc32[last - 1];
	buffer_cc[(len_crc32 + 4) * 2 + 1] = buffer_crc32[last] ^ buffer_crc32[last - 1];

	buffer_cc[(len_crc32 + 5) * 2 + 0] = buffer_crc32[last];
	buffer_cc[(len_crc32 + 5) * 2 + 1] = buffer_crc32[last];

	return buffer_cc;		//返回指针
}


/*===============================*/
//FunctionName:DeCC217
//Description: 解CC编码
//							输入：解交织后的数据（int指针） 
//										输入数据长度（int）		
//							输出：CC(2,1,7)解码后的数据 (int 型指针)
/*===============================*/
int* DeCC217(int *buffer, int len)
{
//	(2015.1.25 这里调用了matlab的算法，暂时不进行cc编码)
	/*
	HRESULT stat;
	static CAObjHandle hMatlab = 0;
	int result = 0;

	double *matrixReal = NULL;
	double *matrixImag = NULL;

	unsigned my_dim1, my_dim2
		, dim1, dim2
		, dim3, dim4;

	stat = MLApp_NewDIMLApp(NULL, 1, LOCALE_NEUTRAL, 0, &hMatlab);
	MinMaxMatlab(hMatlab, 0);

	double *buffer_cc;
	buffer_cc = malloc(len * sizeof(double));		//分配存储空间
	for (int j = 0; j<len; j++)
	{
		buffer_cc[j] = (double)(buffer[j]);
	}
	my_dim1 = 1;
	my_dim2 = len;

	result = SendMatrix(hMatlab, "receive", buffer_cc, NULL, my_dim1, my_dim2);
	if (result != SUCCESS)
	{
		MessagePopup("ERROR", "Error in sending Matrix to Matlab");
	}

	result = RunMatlabCommand(hMatlab, "[decode]=CC_Decode(receive);");
	if (result != SUCCESS)
	{
		MessagePopup("ERROR", "Error in sending command to Matlab");
	}

	result = GetMatrix(hMatlab, "decode", &matrixReal, &matrixImag, &dim1, &dim2);
	if (result != SUCCESS)
	{
		MessagePopup("ERROR", "Error in Getting Matrix from Matlab");
	}

	int *temp_cc;
	temp_cc = malloc(dim2 * sizeof(int));		//分配存储空间
	for (int i = 0; i<dim2; i++)
	{
		if (matrixReal[i] == 1)
			temp_cc[i] = 1;
		else
			temp_cc[i] = 0;
	}

	return temp_cc;
	*/

	return 0;
}

/*===============================*/
//FunctionName:encodecommond
//Description: 对指令帧帧进行编码
/*===============================*/
int encodecommond(int *P_Data)
{
	int  Num_Data1;
	//	char *datareceive;
	int i, j, k;

	/*----生成数据----*/

	Num_Data1 = 24 * SendA.Num_Frame;
	M_Mod = SendA.ModulationMethod;
	Len_DataInProcess = Num_Data1;

	/*------加帧头----------------*/
	int fLen_fh = 24 + 40            //一帧加了帧头之后的数据长度
		, dLen_fh = fLen_fh*SendA.Num_Frame;      //所有帧加了帧头之后的数据长度
	Len_DataInProcess = dLen_fh;

	P_Data_FH = (int *)malloc(dLen_fh*sizeof(int));  //分配存储空间
	int	*Data_FH40;
	Data_FH40 = (int *)malloc(40 * sizeof(int));

	for (i = 0; i<SendA.Num_Frame; i++)					  //将帧长加入帧头
	{
		for (j = 0; j<24; j++)
		{
			*(40 + P_Data_FH + i*fLen_fh + j) = *(P_Data + i * 24 + j);
		}
		FH40(24, Data_FH40);
		for (k = 0; k<40; k++)
		{
			*(P_Data_FH + i*fLen_fh + k) = Data_FH40[k];
		}
		k = num_frame;
		//将帧序列号加入帧头

		for (j = 0; j<8; j++)
		{
			*(P_Data_FH + i*fLen_fh + 39 - j) = k % 2;
			k = k / 2;
		}

	}

	/*-------------CRC32--------------------*/
	int fLen_crc = fLen_fh + 32								   //加帧头之后一帧crc之后的数据长度
		, dLen_crc = fLen_crc*SendA.Num_Frame;			           //所有crc之后的数据长度
	Len_DataInProcess = dLen_crc;

	P_Data_CRC = (int *)malloc(dLen_crc*sizeof(int));			  //分配存储空间
	int *Data_CRC32;                                         //CRC返回值
	Data_CRC32 = (int *)malloc(32 * sizeof(int));                 //分配存储空间

	//读取CRC选项
	M_CRC = SendA.CRC;
	switch (1)
	{
	case 1:
		for (i = 0; i<SendA.Num_Frame; i++)
		{
			for (j = 0; j<fLen_fh; j++)
			{
				*(P_Data_CRC + i*fLen_crc + j) = *(P_Data_FH + i*fLen_fh + j);
			}
			CRC32(P_Data_FH + i*fLen_fh, fLen_fh, Data_CRC32);
			for (k = 0; k<32; k++)
			{
				*(P_Data_CRC + fLen_fh + i*fLen_crc + k) = Data_CRC32[k];
			}
		}
	}

	/*-------------------加ASM组帧-------------------*/
	int fLen_crc_pltu = 24 + fLen_crc			  //一帧CRC组帧之后的pltu数据长度
		, dLen_crc_pltu = fLen_crc_pltu*SendA.Num_Frame;	  //所有CRC之后组帧的pltu数据长度
	int ASM[24] = { 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0 };
	Len_DataInProcess = Len_DataInProcess + 24 * SendA.Num_Frame;   //刷新传输数据长度

	P_PLTU = (int *)malloc(dLen_crc_pltu*sizeof(int)); //分配存储空间
	for (i = 0; i<SendA.Num_Frame; i++)
	{
		for (j = 0; j<24; j++)
		{
			P_PLTU[i*fLen_crc_pltu + j] = ASM[j];
		}
		for (k = 0; k<fLen_crc; k++)
		{
			P_PLTU[i*fLen_crc_pltu + 24 + k] = P_Data_CRC[i*fLen_crc + k];
		}
	}


	/*---------------------CC-----------------------------*/
	int dLen_crc_pltu_cc = (dLen_crc_pltu)* 2 + 12;		//cc之后的数据长度
	int *Data_CC;//CC217返回值

	//读取CC选项
	M_CC = SendA.CC;
	switch (M_CC)
	{
	case 1:     //做（2,1,7）卷积
		P_Data_CC = (int *)malloc(dLen_crc_pltu_cc*sizeof(int));	  //分配存储空间

		Data_CC = CC217(P_PLTU, dLen_crc_pltu);
		for (j = 0; j<dLen_crc_pltu_cc; j++)
		{
			*(P_Data_CC + j) = Data_CC[j];
		}

		Len_DataInProcess = dLen_crc_pltu_cc;
		break;

	case 0:   //不做卷积
		P_Data_CC = (int *)malloc(Len_DataInProcess*sizeof(int));	  //分配存储空间
		for (i = 0; i<Len_DataInProcess; i++)
		{
			*(P_Data_CC + i) = *(P_PLTU + i);
		}
		break;
	}
	return 0;
}


/*===============================*/
//FunctionName:makewrong
//Description: 随机加错
/*===============================*/
void makewrong(int *initial, int linelength)
{
	int wrongnumber[4];
	F_Channel = SendA.ChannelStatus;				//读取信道状态
//	F_Channel = 1;

	if (F_Channel == 0)
	{

		srand((int)time(0));
		for (int i = 0; i<2; i++)
		{
			wrongnumber[i] = rand() % (50000);
			if (wrongnumber[i] <= linelength)
			{
				if (*(initial + wrongnumber[i]) == 0)
					*(initial + wrongnumber[i]) = 1;
				else
					*(initial + wrongnumber[i]) = 0;
			}
		}
	}
	if (F_Channel == 1)
	{

		srand((int)time(0));
		for (int i = 0; i<3; i++)
		{
			wrongnumber[i] = rand() % (50000);
			if (wrongnumber[i] <= linelength)
			{
				if (*(initial + wrongnumber[i]) == 0)
					*(initial + wrongnumber[i]) = 1;
				else
					*(initial + wrongnumber[i]) = 0;
			}
		}
	}

}


/*===============================*/
//FunctionName:decodenumber
//Description: 拆帧号
/*===============================*/
int decodenumber(int *P_RE, int FileSize)
{
	int i, j, k;
	Len_DataInProcess1 = FileSize;

	//CC
	int fLenRevCC		//一帧CC解码之后的数据长度
		, dLenRevCC		//所有数据CC解码之后的数据长度
		, *Temp_CC;

	//CRC
	int fLenRevCRC		//一帧CRC解码之后的数据长度
		, dLenRevCRC		//所有数据CRC解码之后的数据长度
		, *Rev_CRC32;   //CRC32返回值
	double error = 0;

	//处理之后最终要存到文件的数据
	int fLenRev     //一帧数据的长度
		, dLenRev;   //所有数据的长度

	/*----CC----*/
	//	GetCtrlVal(TabPanelHandleR, RECEIVE_CC, &F_CC);		//读取CC解码选项
	F_CC = ReceiveA.CC;
	switch (F_CC)
	{
	case 0://不做卷积译码
		dLenRevCC = Len_DataInProcess1;
		P_CC = (int *)malloc(dLenRevCC * sizeof(int));
		for (i = 0; i<dLenRevCC; i++)
		{
			*(P_CC + i) = *(P_RE + i);
		}
		break;
	case 1://做卷积译码
		dLenRevCC = (Len_DataInProcess1 - 12) / 2;
		//分配存储空间
		P_CC = (int *)malloc(dLenRevCC * sizeof(int));
		Temp_CC = DeCC217(P_RE, Len_DataInProcess1);
		for (j = 0; j<dLenRevCC; j++)
		{
			*(P_CC + j) = Temp_CC[j];
		}
		Len_DataInProcess1 = dLenRevCC;
		break;
	}
	/*********************************读帧头获取帧长度和帧数以及帧序列号***********************/
	int *length;
	int Len = 1;
	int SerialNumber = 0;
	int *serialnumber;

	serialnumber = (int *)malloc(8 * sizeof(int));
	length = (int *)malloc(11 * sizeof(int));
	for (i = 0; i<11; i++)
	{
		length[i] = P_RE[55 - i] * pow((double)2, i);
		Len = Len + length[i];

	}
	Num_Frame = Len_DataInProcess1 / (Len + 56);
	fLenRevCC = Len + 56;
	for (k = 0; k<8; k++)
	{
		serialnumber[k] = P_RE[63 - k] * pow((double)2, k);
		SerialNumber = SerialNumber + serialnumber[k];
	}
	datalength1 = Len - 40;
	SerialNumber1 = SerialNumber;

	return 0;
}

/*===============================*/
//FunctionName:encodearq
//Description: 对arq进行编码
/*===============================*/
int encodearq(int *P_Data)
{
	int Num_Data1;
	char *datareceive;
	int i, j, k;

	Num_Data1 = 16 * SendA.Num_Frame;
	M_Mod = SendA.ModulationMethod;
	Len_DataInProcess = Num_Data1;

	/*------加帧头----------------*/
	int fLen_fh = 16 + 40            //一帧加了帧头之后的数据长度
		, dLen_fh = fLen_fh*SendA.Num_Frame;      //所有帧加了帧头之后的数据长度
	Len_DataInProcess = dLen_fh;

	P_Data_FH = (int *)malloc(dLen_fh*sizeof(int));  //分配存储空间
	int	*Data_FH40;
	Data_FH40 = (int *)malloc(40 * sizeof(int));

	for (i = 0; i<SendA.Num_Frame; i++)					  //将帧长加入帧头
	{
		for (j = 0; j<16; j++)
		{
			*(40 + P_Data_FH + i*fLen_fh + j) = *(P_Data + i * 16 + j);
		}
		FH40(16, Data_FH40);
		for (k = 0; k<40; k++)
		{
			*(P_Data_FH + i*fLen_fh + k) = Data_FH40[k];

		}
		k = num_frame;
		//将帧序列号加入帧头

		for (j = 0; j<8; j++)
		{
			*(P_Data_FH + i*fLen_fh + 39 - j) = k % 2;
			k = k / 2;
		}

	}

	/*-------------CRC32--------------------*/
	int fLen_crc = fLen_fh + 32								   //加帧头之后一帧crc之后的数据长度
		, dLen_crc = fLen_crc*SendA.Num_Frame;			           //所有crc之后的数据长度

	Len_DataInProcess = dLen_crc;

	P_Data_CRC = (int *)malloc(dLen_crc*sizeof(int));			  //分配存储空间

	int *Data_CRC32;                                         //CRC返回值

	Data_CRC32 = (int *)malloc(32 * sizeof(int));                 //分配存储空间

	//读取CRC选项
	M_CRC = SendA.CRC;
	switch (1)
	{
	case 1:
		for (i = 0; i<SendA.Num_Frame; i++)
		{
			for (j = 0; j<fLen_fh; j++)
			{
				*(P_Data_CRC + i*fLen_crc + j) = *(P_Data_FH + i*fLen_fh + j);
			}

			CRC32(P_Data_FH + i*fLen_fh, fLen_fh, Data_CRC32);

			for (k = 0; k<32; k++)
			{
				*(P_Data_CRC + fLen_fh + i*fLen_crc + k) = Data_CRC32[k];
			}
		}
	}


	/*-------------------加ASM组帧-------------------*/
	int fLen_crc_pltu = 24 + fLen_crc			  //一帧CRC组帧之后的pltu数据长度
		, dLen_crc_pltu = fLen_crc_pltu*SendA.Num_Frame;	  //所有CRC之后组帧的pltu数据长度
	int ASM[24] = { 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0 };
	Len_DataInProcess = Len_DataInProcess + 24 * SendA.Num_Frame;   //刷新传输数据长度

	P_PLTU = (int *)malloc(dLen_crc_pltu*sizeof(int)); //分配存储空间

	for (i = 0; i<SendA.Num_Frame; i++)
	{
		for (j = 0; j<24; j++)
		{
			P_PLTU[i*fLen_crc_pltu + j] = ASM[j];
		}
		for (k = 0; k<fLen_crc; k++)
		{
			P_PLTU[i*fLen_crc_pltu + 24 + k] = P_Data_CRC[i*fLen_crc + k];
		}
	}
	/*---------------------CC-----------------------------*/
	int dLen_crc_pltu_cc = (dLen_crc_pltu)* 2 + 12;		//cc之后的数据长度


	int *Data_CC;//CC217返回值

	//读取CC选项
	M_CC = SendA.CC;
	switch (M_CC)
	{
	case 1:     //做（2,1,7）卷积
		P_Data_CC = (int *)malloc(dLen_crc_pltu_cc*sizeof(int));	  //分配存储空间

		Data_CC = CC217(P_PLTU, dLen_crc_pltu);
		for (j = 0; j<dLen_crc_pltu_cc; j++)
		{
			*(P_Data_CC + j) = Data_CC[j];
		}

		Len_DataInProcess = dLen_crc_pltu_cc;
		break;

	case 0:   //不做卷积
		P_Data_CC = (int *)malloc(Len_DataInProcess*sizeof(int));	  //分配存储空间
		for (i = 0; i<Len_DataInProcess; i++)
		{
			*(P_Data_CC + i) = *(P_PLTU + i);
		}
		break;
	}

	return 0;
}