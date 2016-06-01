/*

��ͷ�ļ�����ϵͳ����

*/

#pragma once 
#ifndef		DEFINE_H
#define		DEFINE_H

#include "stdafx.h"


//�����A
 typedef struct Send
{	
	int			CheckFlag;				//�Լ��ź�
	double	DataRate;				//��������
	int			FrameLength;		//֡����
	int			Num_Frame;			//֡����
	int			ModulationMethod;		//���Ʒ�ʽ
	int			WorkChannel;		//����Ƶ��
	double	WorkFrequency;	//����Ƶ��
	int			CRC;						//CRC
	int			CC;							//CC
	int			InterWeave;			//��֯
	int			Scramble;				//����
	int			ChannelStatus;		//�ŵ�״��
	CString	gSendDataPath;	//����Դ�ļ���ַ
 }	T_SEND;
 extern T_SEND				SendA, SendB;  //�������������Ϊ�ⲿ������ȫ�ֱ�����


 //���ջ�A
 typedef struct RECEIVE
 {
	 int			CheckFlag;				//�Լ��ź�
	 double	DataRate;				//��������
	 int			FrameLength;		//֡����
	 int			ModulationMethod;		//���Ʒ�ʽ
	 int			WorkChannel;		//����Ƶ��
	 double	WorkFrequency;	//����Ƶ��
	 int			CRC;						//CRC
	 int			CC;							//CC
	 int			InterWeave;			//��֯
	 int			Scramble;				//����
	 CString	gReceiveDataPath; //����Դ�ļ���ַ
	 CString	gRemoteDataPath;	//����Դ�ļ���ַ
 }	T_RECEIVE;
 extern	T_RECEIVE			ReceiveA, ReceiveB;

 //ϵͳ����
 typedef struct  SYSTEMPARAMETER
 {
	 int protocolmode;				//Э�鹤����ʽ��ȫ˫������˫����������
	 int Arq;									//�ش�
 }T_SYSTEMPARAMETER;
 extern T_SYSTEMPARAMETER				SystemParameter;



#endif