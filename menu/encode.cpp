/*==================*/
//
//���ļ�������뺯��
//
/*==================*/
#include "stdafx.h"
#include "TransRevShare.h"
#include "SystemParameter.h"
#include "encode.h"



/*===============================*/
//FunctionName:encode
//Description: ������֡������֡
/*===============================*/
int encode(int *P_Data)
{
	int i, j, k;

	Num_Data = SendA.FrameLength * 8 * SendA.Num_Frame;
	M_Mod = SendA.ModulationMethod;
	Len_DataInProcess = Num_Data;

	/*-----------------------��֡ͷ----------------------------*/
	int fLen_fh = SendA.FrameLength * 8 + 40            //һ֡����֡ͷ֮������ݳ���
		, dLen_fh = fLen_fh*SendA.Num_Frame;      //����֡����֡ͷ֮������ݳ���
	Len_DataInProcess = dLen_fh;

	P_Data_FH = (int *)malloc(dLen_fh*sizeof(int));  //����洢�ռ�
	int	*Data_FH40;
	Data_FH40 = (int *)malloc(40 * sizeof(int));

	for (i = 0; i<SendA.Num_Frame; i++)					  //��֡������֡ͷ
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
		
		//��֡���кż���֡ͷ
		for (j = 0; j<8; j++)
		{
			*(P_Data_FH + i*fLen_fh + 39 - j) = k % 2;
			k = k / 2;
		}
	}

	/*--------------------CRC32------------------------*/
	int fLen_crc = fLen_fh + 32													  //��֡ͷ֮��һ֡crc֮������ݳ���
		, dLen_crc = fLen_crc*SendA.Num_Frame;					   //����crc֮������ݳ���
	Len_DataInProcess = dLen_crc;

	P_Data_CRC = (int *)malloc(dLen_crc*sizeof(int));			  //����洢�ռ�
	int *Data_CRC32;																     //CRC����ֵ
	Data_CRC32 = (int *)malloc(32 * sizeof(int));				    //����洢�ռ�

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

			CRC32(P_Data_FH + i*fLen_fh, fLen_fh, Data_CRC32);				  //��������������CRC

			for (k = 0; k<32; k++)
			{
				*(P_Data_CRC + fLen_fh + i*fLen_crc + k) = Data_CRC32[k];
			}
		}
	}

	/*----------------------��ASM��֡------------------------*/
	int fLen_crc_pltu = 24 + fLen_crc																				  //һ֡CRC��֮֡���pltu���ݳ���
		, dLen_crc_pltu = fLen_crc_pltu*SendA.Num_Frame;										 //����CRC֮����֡��pltu���ݳ���
	int ASM[24] = { 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0 };
	Len_DataInProcess = Len_DataInProcess + 24 * SendA.Num_Frame;				//ˢ�´������ݳ���

	P_PLTU = (int *)malloc(dLen_crc_pltu*sizeof(int));												//����洢�ռ�

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
	int dLen_crc_pltu_cc = (dLen_crc_pltu)* 2 + 12;										//cc֮������ݳ���
	int *Data_CC;																										//CC217����ֵ

	M_CC = SendA.CC;
	switch (M_CC)
	{
	case 1:																												//����2,1,7�����
		P_Data_CC = (int *)malloc(dLen_crc_pltu_cc*sizeof(int));					  //����洢�ռ�
		Data_CC = CC217(P_PLTU, dLen_crc_pltu);
		for (j = 0; j<dLen_crc_pltu_cc; j++)
		{
			*(P_Data_CC + j) = Data_CC[j];
		}
		Len_DataInProcess = dLen_crc_pltu_cc;
		break;

	case 0:																											//�������
		P_Data_CC = (int *)malloc(Len_DataInProcess*sizeof(int));				//����洢�ռ�
		for (i = 0; i<Len_DataInProcess; i++)
		{
			*(P_Data_CC + i) = *(P_PLTU + i);
		}
		break;
	}


	/*****�Լ��õĴ���
	int k;
	Num_Data = SendA.FrameLength * 8;
	M_Mod = SendA.ModulationMethod;
	Len_DataInProcess = Num_Data;	

	/==============��֡ͷ==============/
	int fLen_fh = SendA.FrameLength * 8 + 40				  //һ֡����֡ͷ֮������ݳ���
		, dLen_fh = fLen_fh*SendA.Num_Frame;				//����֡��֡ͷ֮�������
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
		//��֡���кż���֡ͷ
		for (int j = 0; j < 8; j++)
		{
			*(P_Data_FH + i*fLen_fh + 39 - j) = k % 2;
			k = k / 2;
		}
	}

	free(Data_FH40);

	/===============CRC32================/
	int fLen_crc = fLen_fh + 32												//��֡ͷ֮��һ֡����CRC֮������ݳ���
		, dLen_crc = fLen_crc*SendA.Num_Frame;				//����֡CRC֮������ݳ���

	Len_DataInProcess = dLen_crc;
	P_Data_CRC = (int *)malloc(dLen_crc*sizeof(int));		//����洢�ռ�

	int *Data_CRC32;																//CRC����ֵ
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
			CRC32(P_Data_FH + i*fLen_fh, fLen_fh, Data_CRC32);				//����CRC32��������������CRC
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

	/==============��ASM��֡==============/
	int fLen_crc_pltu = 24 + fLen_crc														//һ֡CRC��֮֡���pltu���ݳ���
		, dLen_crc_pltu = fLen_crc_pltu*SendA.Num_Frame;				//����CRC֮����֡��pltu���ݳ���
	int ASM[24] = { 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0 };
	Len_DataInProcess = Len_DataInProcess + 24 * SendA.Num_Frame;		//ˢ�´������ݳ���

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

	int dLen_crc_pltu_cc = (dLen_crc_pltu)* 2 + 12;						//CC֮������ݳ���
	int *Data_CC;

	M_CC = SendA.CC;																			//��ȡCCֵ
	switch (M_CC)
	{
	case 1:																								//��CC217���
		P_Data_CC = (int *)malloc(dLen_crc_pltu_cc*sizeof(int));		//����洢�ռ�

		Data_CC = CC217(P_PLTU, dLen_crc_pltu);
		for (int j = 0; j<dLen_crc_pltu_cc; j++)
		{
			*(P_Data_CC + j) = Data_CC[j];
		}
		Len_DataInProcess = dLen_crc_pltu_cc;
		break;

	case 0:																								//�������
		P_Data_CC = (int *)malloc(Len_DataInProcess*sizeof(int));	  //����洢�ռ�
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
//Description: ������֡���в�֡
/*===============================*/
int decode(int *P_RE, int FileSize)
{
	int i, j, k;

	Len_DataInProcess1 = FileSize;

	//CC
	int fLenRevCC		//һ֡CC����֮������ݳ���
		, dLenRevCC		//��������CC����֮������ݳ���
		, *Temp_CC;



	//CRC
	int fLenRevCRC		//һ֡CRC����֮������ݳ���
		, dLenRevCRC		//��������CRC����֮������ݳ���
		, *Rev_CRC32;   //CRC32����ֵ
	double error = 0;

	//����֮������Ҫ�浽�ļ�������
	int fLenRev     //һ֡���ݵĳ���
		, dLenRev;   //�������ݵĳ���

	/*-----------------------CC����-------------------------*/
	F_CC = ReceiveA.CC;
	switch (F_CC)
	{
	case 0:							//�����������
		dLenRevCC = Len_DataInProcess1;
		P_CC = (int *)malloc(dLenRevCC * sizeof(int));
		for (i = 0; i<dLenRevCC; i++)
		{
			*(P_CC + i) = *(P_RE + i);
		}
		break;
	case 1:							//���������
		dLenRevCC = (Len_DataInProcess1 - 12) / 2;
		//����洢�ռ�
		P_CC = (int *)malloc(dLenRevCC * sizeof(int));
		Temp_CC = DeCC217(P_RE, Len_DataInProcess1);
		for (j = 0; j<dLenRevCC; j++)
		{
			*(P_CC + j) = Temp_CC[j];
		}
		Len_DataInProcess1 = dLenRevCC;
		break;
	}

	/*-----------------------��֡ͷ��ȡ֡���Ⱥ�֡���Լ�֡���к�-------------------------*/
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

	/*-----------------------ȥASMλ-------------------------*/
	P_DeASM = (int *)malloc((Len_DataInProcess1 - 24 * Num_Frame)*sizeof(int));
	for (i = 0; i<Num_Frame; i++)
	{
		for (j = 0; j<(Len_DataInProcess1 / Num_Frame - 24); j++)
		{
			P_DeASM[i*(Len_DataInProcess1 / Num_Frame - 24) + j] = P_CC[i*(Len_DataInProcess1 / Num_Frame) + 24 + j];
		}
	}
	Len_DataInProcess1 = Len_DataInProcess1 - 24 * Num_Frame;

	/*-----------------------ȥCRC----------------------------*/
	F_CRC = ReceiveA.CRC;

	/***�����ȫ�ֱ���
	double AverageErrorRate;
	double CurrentErrorRate;
	*/
	switch (1)  //����Ӧ����F_CRC
	{
	case 1:
		fLenRevCRC = fLenRevCC - 56;
		dLenRevCRC = fLenRevCRC*Num_Frame;

		Rev_CRC32 = (int *)malloc(32 * sizeof(int));	 //����洢�ռ�
		P_CRC = (int *)malloc(dLenRevCRC*sizeof(int));
		for (i = 0; i<Num_Frame; i++)							//��CRC32
		{
			for (j = 0; j<fLenRevCRC; j++)
			{
				P_CRC[j + i*fLenRevCRC] = P_DeASM[j + i*(fLenRevCRC + 32)];
			}
		}
		break;
	}
	Len_DataInProcess1 = Len_DataInProcess1 - 32 * Num_Frame;

	/*-----------------------ȥ֡ͷ----------------------------*/
	fLenRev = fLenRevCRC - 40;
	dLenRev = fLenRev*Num_Frame;

	P_Rev = (int *)malloc(dLenRev*sizeof(int));//����洢�ռ�

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
//Description: ����40λ֡ͷ
//							���룺һ֡���͵�����
//										���͵����ݳ���
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

	/*֡ͷ����λ�͵���λ������ṹ��ʶ������Ҫ���滻�ɵ��Ʒ�ʽ��00��BPSK��01��QPSK�����౸��*/
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
//Description: 32λ����У��
//							���룺һ֡���͵�����
//										һ֡���͵����ݳ���
//										32λCRC�����ڷ���CRC32��
/*===============================*/
void CRC32(int *pv3, int len, int *r32)
{
	int s1 = 0, s2 = 0, s3 = 0, s4 = 0, s5 = 0;

	for (int i = 0; i < 32; i++) //r32��λ��
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
//Description: CC����
//							���룺һ֡Data + CRC32(int ��ָ��)
//										���͵����ݳ���
//							�����CC(2,1,7)���� (int ��ָ��)
/*===============================*/
int *CC217(int *buffer_crc32, int Length)
{
	int len_cc, len_crc32, last;

	len_crc32 = Length;		//(2,1,7)�����ǰ�����еĳ���
	len_cc = len_crc32 * 2 + 12;		//(2,1,7)���������еĳ��� 

	int *buffer_cc;
	buffer_cc =(int *) malloc((len_cc)*sizeof(int));		//����洢�ռ�

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

	return buffer_cc;		//����ָ��
}


/*===============================*/
//FunctionName:DeCC217
//Description: ��CC����
//							���룺�⽻֯������ݣ�intָ�룩 
//										�������ݳ��ȣ�int��		
//							�����CC(2,1,7)���������� (int ��ָ��)
/*===============================*/
int* DeCC217(int *buffer, int len)
{
//	(2015.1.25 ���������matlab���㷨����ʱ������cc����)
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
	buffer_cc = malloc(len * sizeof(double));		//����洢�ռ�
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
	temp_cc = malloc(dim2 * sizeof(int));		//����洢�ռ�
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
//Description: ��ָ��֡֡���б���
/*===============================*/
int encodecommond(int *P_Data)
{
	int  Num_Data1;
	//	char *datareceive;
	int i, j, k;

	/*----��������----*/

	Num_Data1 = 24 * SendA.Num_Frame;
	M_Mod = SendA.ModulationMethod;
	Len_DataInProcess = Num_Data1;

	/*------��֡ͷ----------------*/
	int fLen_fh = 24 + 40            //һ֡����֡ͷ֮������ݳ���
		, dLen_fh = fLen_fh*SendA.Num_Frame;      //����֡����֡ͷ֮������ݳ���
	Len_DataInProcess = dLen_fh;

	P_Data_FH = (int *)malloc(dLen_fh*sizeof(int));  //����洢�ռ�
	int	*Data_FH40;
	Data_FH40 = (int *)malloc(40 * sizeof(int));

	for (i = 0; i<SendA.Num_Frame; i++)					  //��֡������֡ͷ
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
		//��֡���кż���֡ͷ

		for (j = 0; j<8; j++)
		{
			*(P_Data_FH + i*fLen_fh + 39 - j) = k % 2;
			k = k / 2;
		}

	}

	/*-------------CRC32--------------------*/
	int fLen_crc = fLen_fh + 32								   //��֡ͷ֮��һ֡crc֮������ݳ���
		, dLen_crc = fLen_crc*SendA.Num_Frame;			           //����crc֮������ݳ���
	Len_DataInProcess = dLen_crc;

	P_Data_CRC = (int *)malloc(dLen_crc*sizeof(int));			  //����洢�ռ�
	int *Data_CRC32;                                         //CRC����ֵ
	Data_CRC32 = (int *)malloc(32 * sizeof(int));                 //����洢�ռ�

	//��ȡCRCѡ��
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

	/*-------------------��ASM��֡-------------------*/
	int fLen_crc_pltu = 24 + fLen_crc			  //һ֡CRC��֮֡���pltu���ݳ���
		, dLen_crc_pltu = fLen_crc_pltu*SendA.Num_Frame;	  //����CRC֮����֡��pltu���ݳ���
	int ASM[24] = { 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0 };
	Len_DataInProcess = Len_DataInProcess + 24 * SendA.Num_Frame;   //ˢ�´������ݳ���

	P_PLTU = (int *)malloc(dLen_crc_pltu*sizeof(int)); //����洢�ռ�
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
	int dLen_crc_pltu_cc = (dLen_crc_pltu)* 2 + 12;		//cc֮������ݳ���
	int *Data_CC;//CC217����ֵ

	//��ȡCCѡ��
	M_CC = SendA.CC;
	switch (M_CC)
	{
	case 1:     //����2,1,7�����
		P_Data_CC = (int *)malloc(dLen_crc_pltu_cc*sizeof(int));	  //����洢�ռ�

		Data_CC = CC217(P_PLTU, dLen_crc_pltu);
		for (j = 0; j<dLen_crc_pltu_cc; j++)
		{
			*(P_Data_CC + j) = Data_CC[j];
		}

		Len_DataInProcess = dLen_crc_pltu_cc;
		break;

	case 0:   //�������
		P_Data_CC = (int *)malloc(Len_DataInProcess*sizeof(int));	  //����洢�ռ�
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
//Description: ����Ӵ�
/*===============================*/
void makewrong(int *initial, int linelength)
{
	int wrongnumber[4];
	F_Channel = SendA.ChannelStatus;				//��ȡ�ŵ�״̬
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
//Description: ��֡��
/*===============================*/
int decodenumber(int *P_RE, int FileSize)
{
	int i, j, k;
	Len_DataInProcess1 = FileSize;

	//CC
	int fLenRevCC		//һ֡CC����֮������ݳ���
		, dLenRevCC		//��������CC����֮������ݳ���
		, *Temp_CC;

	//CRC
	int fLenRevCRC		//һ֡CRC����֮������ݳ���
		, dLenRevCRC		//��������CRC����֮������ݳ���
		, *Rev_CRC32;   //CRC32����ֵ
	double error = 0;

	//����֮������Ҫ�浽�ļ�������
	int fLenRev     //һ֡���ݵĳ���
		, dLenRev;   //�������ݵĳ���

	/*----CC----*/
	//	GetCtrlVal(TabPanelHandleR, RECEIVE_CC, &F_CC);		//��ȡCC����ѡ��
	F_CC = ReceiveA.CC;
	switch (F_CC)
	{
	case 0://�����������
		dLenRevCC = Len_DataInProcess1;
		P_CC = (int *)malloc(dLenRevCC * sizeof(int));
		for (i = 0; i<dLenRevCC; i++)
		{
			*(P_CC + i) = *(P_RE + i);
		}
		break;
	case 1://���������
		dLenRevCC = (Len_DataInProcess1 - 12) / 2;
		//����洢�ռ�
		P_CC = (int *)malloc(dLenRevCC * sizeof(int));
		Temp_CC = DeCC217(P_RE, Len_DataInProcess1);
		for (j = 0; j<dLenRevCC; j++)
		{
			*(P_CC + j) = Temp_CC[j];
		}
		Len_DataInProcess1 = dLenRevCC;
		break;
	}
	/*********************************��֡ͷ��ȡ֡���Ⱥ�֡���Լ�֡���к�***********************/
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
//Description: ��arq���б���
/*===============================*/
int encodearq(int *P_Data)
{
	int Num_Data1;
	char *datareceive;
	int i, j, k;

	Num_Data1 = 16 * SendA.Num_Frame;
	M_Mod = SendA.ModulationMethod;
	Len_DataInProcess = Num_Data1;

	/*------��֡ͷ----------------*/
	int fLen_fh = 16 + 40            //һ֡����֡ͷ֮������ݳ���
		, dLen_fh = fLen_fh*SendA.Num_Frame;      //����֡����֡ͷ֮������ݳ���
	Len_DataInProcess = dLen_fh;

	P_Data_FH = (int *)malloc(dLen_fh*sizeof(int));  //����洢�ռ�
	int	*Data_FH40;
	Data_FH40 = (int *)malloc(40 * sizeof(int));

	for (i = 0; i<SendA.Num_Frame; i++)					  //��֡������֡ͷ
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
		//��֡���кż���֡ͷ

		for (j = 0; j<8; j++)
		{
			*(P_Data_FH + i*fLen_fh + 39 - j) = k % 2;
			k = k / 2;
		}

	}

	/*-------------CRC32--------------------*/
	int fLen_crc = fLen_fh + 32								   //��֡ͷ֮��һ֡crc֮������ݳ���
		, dLen_crc = fLen_crc*SendA.Num_Frame;			           //����crc֮������ݳ���

	Len_DataInProcess = dLen_crc;

	P_Data_CRC = (int *)malloc(dLen_crc*sizeof(int));			  //����洢�ռ�

	int *Data_CRC32;                                         //CRC����ֵ

	Data_CRC32 = (int *)malloc(32 * sizeof(int));                 //����洢�ռ�

	//��ȡCRCѡ��
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


	/*-------------------��ASM��֡-------------------*/
	int fLen_crc_pltu = 24 + fLen_crc			  //һ֡CRC��֮֡���pltu���ݳ���
		, dLen_crc_pltu = fLen_crc_pltu*SendA.Num_Frame;	  //����CRC֮����֡��pltu���ݳ���
	int ASM[24] = { 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0 };
	Len_DataInProcess = Len_DataInProcess + 24 * SendA.Num_Frame;   //ˢ�´������ݳ���

	P_PLTU = (int *)malloc(dLen_crc_pltu*sizeof(int)); //����洢�ռ�

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
	int dLen_crc_pltu_cc = (dLen_crc_pltu)* 2 + 12;		//cc֮������ݳ���


	int *Data_CC;//CC217����ֵ

	//��ȡCCѡ��
	M_CC = SendA.CC;
	switch (M_CC)
	{
	case 1:     //����2,1,7�����
		P_Data_CC = (int *)malloc(dLen_crc_pltu_cc*sizeof(int));	  //����洢�ռ�

		Data_CC = CC217(P_PLTU, dLen_crc_pltu);
		for (j = 0; j<dLen_crc_pltu_cc; j++)
		{
			*(P_Data_CC + j) = Data_CC[j];
		}

		Len_DataInProcess = dLen_crc_pltu_cc;
		break;

	case 0:   //�������
		P_Data_CC = (int *)malloc(Len_DataInProcess*sizeof(int));	  //����洢�ռ�
		for (i = 0; i<Len_DataInProcess; i++)
		{
			*(P_Data_CC + i) = *(P_PLTU + i);
		}
		break;
	}

	return 0;
}