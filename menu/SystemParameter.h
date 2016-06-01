/*

本头文件定义系统参数

*/

#pragma once 
#ifndef		DEFINE_H
#define		DEFINE_H

#include "stdafx.h"


//发射机A
 typedef struct Send
{	
	int			CheckFlag;				//自检信号
	double	DataRate;				//数据速率
	int			FrameLength;		//帧长度
	int			Num_Frame;			//帧个数
	int			ModulationMethod;		//调制方式
	int			WorkChannel;		//工作频道
	double	WorkFrequency;	//工作频率
	int			CRC;						//CRC
	int			CC;							//CC
	int			InterWeave;			//交织
	int			Scramble;				//加扰
	int			ChannelStatus;		//信道状况
	CString	gSendDataPath;	//数据源文件地址
 }	T_SEND;
 extern T_SEND				SendA, SendB;  //将对象变量声明为外部变量（全局变量）


 //接收机A
 typedef struct RECEIVE
 {
	 int			CheckFlag;				//自检信号
	 double	DataRate;				//数据速率
	 int			FrameLength;		//帧长度
	 int			ModulationMethod;		//调制方式
	 int			WorkChannel;		//工作频道
	 double	WorkFrequency;	//工作频率
	 int			CRC;						//CRC
	 int			CC;							//CC
	 int			InterWeave;			//交织
	 int			Scramble;				//加扰
	 CString	gReceiveDataPath; //保存源文件地址
	 CString	gRemoteDataPath;	//数据源文件地址
 }	T_RECEIVE;
 extern	T_RECEIVE			ReceiveA, ReceiveB;

 //系统参数
 typedef struct  SYSTEMPARAMETER
 {
	 int protocolmode;				//协议工作方式（全双工，半双工，单工）
	 int Arq;									//重传
 }T_SYSTEMPARAMETER;
 extern T_SYSTEMPARAMETER				SystemParameter;



#endif