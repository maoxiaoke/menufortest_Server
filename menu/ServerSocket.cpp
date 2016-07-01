// ServerSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "ServerSocket.h"
#include "menuDlg.h"

#include "encode.h"
#include "Framing.h"
#include "TransRevShare.h"
#include "SystemParameter.h"

// CServerSocket

CServerSocket::CServerSocket()
{
}

CServerSocket::~CServerSocket()
{
}


// CServerSocket 成员函数


void CServerSocket::OnReceive(int nErrorCode)
{
	// TODO:  在此添加专用代码和/或调用基类
	//接收客户端发来的信息

	int *Protocoldata;
	int *szTemp;
	int Errorbit = 0;
	szTemp = (int*)malloc(5000 * sizeof(int)); //预备5000个数据的量
	int n = Receive(szTemp, 5000 * sizeof(int)); //收到的数据，返回收到的字节数

	int datalen = n / (sizeof(int)) - 1;
	int *PE;
	PE = (int*)malloc(datalen*sizeof(int));
	for (int i = 0; i <datalen; i++)
	{
		PE[i] = szTemp[i];
	}


	if (datalen <= 232)
	{
		if (*(PE + 64) == 0)
		{
			Protocoldata = (int *)malloc((datalen - 96)*sizeof(int));
			for (int i = 0; i < (datalen - 96); i++)
			{
				*(Protocoldata + i) = *(PE + 64 + i);
			}
			UNFRAMING(Protocoldata, datalen - 96);
		}
		if (*(PE + 64) == 1)
		{
			Protocoldata = (int *)malloc((datalen - 96)*sizeof(int));
			for (int i = 0; i < (datalen - 96); i++)
			{
				*(Protocoldata + i) = *(PE + 64 + i);
			}
			ResendNumber_R = GET_ARQ_NUM(Protocoldata);
			arqreceiveflag = 1;
		}
	}
	else
	{
		if (SystemParameter.Arq == 1)
		{
			makewrong(PE, datalen);																							//随机加错
			int ASMerror = 0;
			int ASM[24] = { 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0 };
			for (int i = 0; i < 24; i++)
			{
				if (PE[i] != ASM[i])
				{
					ASMerror++;																										//ASM检错
				}
			}
			F_CRC = ReceiveA.CRC;
			
			switch (1)
			{
			case 1:
				int *Rev_crc32;
				Rev_crc32 = (int *)malloc(32 * sizeof(int));
				CRC32(PE + 24, datalen - 56, Rev_crc32);
				for (int k = 0; k < 32; k++)
				{
					if (PE[datalen - 32 + k] != Rev_crc32[k])
					{
						Errorbit++;																									//CRC检错
					}
				}
				break;
			}
			decodenumber(PE, datalen);																					//拆帧帧号
			//源程序有未知代码段
			if (ASMerror != 0)
			{
				Sleep(5000);
				while (1)
				{
					if (messagestate == 0)
					{
						commondstate = 1;
						ArqGroup = PLCW_framing(NeedSerialNumber);
						encodearq(ArqGroup);
						((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->SendMessagepro(P_Data_CC, Len_DataInProcess);
						break;
					}
				}
				commondstate = 0;
				CString frame_missing;
				frame_missing.Format(_T("%d"), NeedSerialNumber);
				ds_sdDlg->m_MissingFrameNumEdit.SetSel(ds_sdDlg->m_MissingFrameNumEdit.GetWindowTextLength(), -1); //获取当前编辑框字符
				ds_sdDlg->m_MissingFrameNumEdit.ReplaceSel(frame_missing); //替换当前文本
				ds_sdDlg->m_MissingFrameNumEdit.SetSel(ds_sdDlg->m_MissingFrameNumEdit.GetWindowTextLength(), -1); //获取当前编辑框字符
				ds_sdDlg->m_MissingFrameNumEdit.ReplaceSel(_T(",")); //替换当前文本
				CString str;
				str = ((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->SystemTime();
				((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->m_Hist.SetSel(((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->m_Hist.GetWindowTextLength(), -1); //获取当前编辑框字符
				((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->m_Hist.ReplaceSel(str + "\r\n" + _T("当前帧ASM出错！\r\n")); //替换当前文本
				return;
			}
			else if (Errorbit != 0)
			{
				Sleep(5000);
				while (1)
				{
					if (messagestate == 0)
					{
						commondstate = 1;
						ArqGroup = PLCW_framing(NeedSerialNumber);
						encodearq(ArqGroup);
						((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->SendMessagepro(P_Data_CC, Len_DataInProcess);
						break;
					}
				}
				commondstate = 0;
				CString frame_missing;
				frame_missing.Format(_T("%d"), NeedSerialNumber);
				ds_sdDlg->m_MissingFrameNumEdit.SetSel(ds_sdDlg->m_MissingFrameNumEdit.GetWindowTextLength(), -1); //获取当前编辑框字符
				ds_sdDlg->m_MissingFrameNumEdit.ReplaceSel(frame_missing); //替换当前文本
				ds_sdDlg->m_MissingFrameNumEdit.SetSel(ds_sdDlg->m_MissingFrameNumEdit.GetWindowTextLength(), -1); //获取当前编辑框字符
				ds_sdDlg->m_MissingFrameNumEdit.ReplaceSel(_T(",")); //替换当前文本
				CString str;
				str = ((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->SystemTime();
				((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->m_Hist.SetSel(((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->m_Hist.GetWindowTextLength(), -1); //获取当前编辑框字符
				((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->m_Hist.ReplaceSel(str + "\r\n" + _T("当前帧CRC出错！\r\n")); //替换当前文本
				return;
			}
			else if (NeedSerialNumber != SerialNumber1)
			{
				Sleep(5000);
				while (1)
				{
					if (messagestate == 0)
					{
						commondstate = 1;
						ArqGroup = PLCW_framing(NeedSerialNumber);
						encodearq(ArqGroup);
						((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->SendMessagepro(P_Data_CC, Len_DataInProcess);
						break;
					}
				}
				commondstate = 0;
				CString frame_missing;
				frame_missing.Format(_T("%d"), NeedSerialNumber);
				ds_sdDlg->m_MissingFrameNumEdit.SetSel(ds_sdDlg->m_MissingFrameNumEdit.GetWindowTextLength(), -1); //获取当前编辑框字符
				ds_sdDlg->m_MissingFrameNumEdit.ReplaceSel(frame_missing); //替换当前文本
				ds_sdDlg->m_MissingFrameNumEdit.SetSel(ds_sdDlg->m_MissingFrameNumEdit.GetWindowTextLength(), -1); //获取当前编辑框字符
				ds_sdDlg->m_MissingFrameNumEdit.ReplaceSel(_T(",")); //替换当前文本
				CString str;
				str = ((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->SystemTime();
				((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->m_Hist.SetSel(((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->m_Hist.GetWindowTextLength(), -1); //获取当前编辑框字符
				((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->m_Hist.ReplaceSel(str + "\r\n" + _T("当前帧帧号出错！\r\n")); //替换当前文本
				return;
			}
			else
			{
				decode(PE, datalen);					//拆帧
				CString	*str1;
				str1 = new CString[10000];
				CString strDisplay1;
				for (int i = 0; i < (datalen - 96); i++) //为了从int型数组转CString真是累死你爹地了
				{
					str1[i].Format(_T("%d"), P_Rev[i]);
					strDisplay1 += str1[i];	//利用CString类型重载+=的性质
				}

				//将要发送的数据送到CStatusDisply对话框类中的发送数据编辑框
				ds_sdDlg->m_HistReceiveData.SetSel(ds_sdDlg->m_HistReceiveData.GetWindowTextLength(), -1); //获取当前编辑框字符
				ds_sdDlg->m_HistReceiveData.ReplaceSel(strDisplay1); //替换当前文本
				//		ds_sdDlg->GetDlgItem(IDC_RECEIVEDATA_EDIT)->SetWindowText(strDisplay1);
				ds_sdDlg->SetDlgItemInt(IDC_CURRENT_SERIAL_NUM_EDIT, NeedSerialNumber);
				ds_sdDlg->SetDlgItemInt(IDC_RECEIVE_EDIT, receivenumber*datalength1);
				CString AverageErrorRate_R;
				AverageErrorRate_R.Format(_T("%f"), AverageErrorRate); //利用SetDlgItemText显示double型参量
				ds_sdDlg->SetDlgItemText(IDC_AVERAGEERRORTATE_EDIT, AverageErrorRate_R); //平均误码率
				CString CurrentErrorRate_R;
				CurrentErrorRate_R.Format(_T("%f"), CurrentErrorRate); //利用SetDlgItemText显示double型参量
				ds_sdDlg->SetDlgItemText(IDC_CURRENTERRORRATE_EDIT, CurrentErrorRate_R); //平均误码率

				receivenumber++;
				NeedSerialNumber++;

			}
		}
		else
		{
			makewrong(PE, datalen);																							//随机加错
			
			int ASMerror = 0;
			int ASM[24] = { 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0 };
			for (int i = 0; i < 24; i++)
			{
				if (PE[i] != ASM[i])
				{
					ASMerror++;																										//ASM检错
				}
			}
			if (ASMerror == 0)
			{
				F_CRC = ReceiveA.CRC;
				switch (1)
				{
				case 1:
					int Errorbit = 0;
					int *Rev_crc32;
					Rev_crc32 = (int *)malloc(32 * sizeof(int));
					CRC32(PE + 24, datalen - 56, Rev_crc32);
					for (int k = 0; k < 32; k++)
					{
						if (PE[datalen - 32 + k] != Rev_crc32[k])
						{
							Errorbit++;																									//CRC检错
						}
					}
					if (Errorbit == 0)
					{
						decode(PE, datalen);
						if (NeedSerialNumber == SerialNumber1)
						{
							CString	*str1;
							str1 = new CString[10000];
							CString strDisplay1;
							for (int i = 0; i < (datalen - 96); i++) //为了从int型数组转CString真是累死你爹地了
							{
								str1[i].Format(_T("%d"), P_Rev[i]);
								strDisplay1 += str1[i];	//利用CString类型重载+=的性质
							}

							//将要发送的数据送到CStatusDisply对话框类中的发送数据编辑框
							ds_sdDlg->m_HistReceiveData.SetSel(ds_sdDlg->m_HistReceiveData.GetWindowTextLength(), -1); //获取当前编辑框字符
							ds_sdDlg->m_HistReceiveData.ReplaceSel(strDisplay1); //替换当前文本
							//		ds_sdDlg->GetDlgItem(IDC_RECEIVEDATA_EDIT)->SetWindowText(strDisplay1);
							ds_sdDlg->SetDlgItemInt(IDC_CURRENT_SERIAL_NUM_EDIT, NeedSerialNumber);
							ds_sdDlg->SetDlgItemInt(IDC_RECEIVE_EDIT, receivenumber*datalength1);
							CString AverageErrorRate_R;
							AverageErrorRate_R.Format(_T("%f"), AverageErrorRate); //利用SetDlgItemText显示double型参量
							ds_sdDlg->SetDlgItemText(IDC_AVERAGEERRORTATE_EDIT, AverageErrorRate_R); //平均误码率
							CString CurrentErrorRate_R;
							CurrentErrorRate_R.Format(_T("%f"), CurrentErrorRate); //利用SetDlgItemText显示double型参量
							ds_sdDlg->SetDlgItemText(IDC_CURRENTERRORRATE_EDIT, CurrentErrorRate_R); //平均误码率

							receivenumber++;
							NeedSerialNumber++;
						}
						else
						{
							NeedSerialNumber++;
							missnumber++;
							CString frame_missing;
							frame_missing.Format(_T("%d"), NeedSerialNumber);
							ds_sdDlg->m_MissingFrameNumEdit.SetSel(ds_sdDlg->m_MissingFrameNumEdit.GetWindowTextLength(), -1); //获取当前编辑框字符
							ds_sdDlg->m_MissingFrameNumEdit.ReplaceSel(frame_missing); //替换当前文本
							ds_sdDlg->m_MissingFrameNumEdit.SetSel(ds_sdDlg->m_MissingFrameNumEdit.GetWindowTextLength(), -1); //获取当前编辑框字符
							ds_sdDlg->m_MissingFrameNumEdit.ReplaceSel(_T(",")); //替换当前文本
							CString str;
							str = ((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->SystemTime();
							((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->m_Hist.SetSel(((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->m_Hist.GetWindowTextLength(), -1); //获取当前编辑框字符
							((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->m_Hist.ReplaceSel(str + "\r\n" + _T("当前帧帧号出错！\r\n")); //替换当前文本
						}
					}
					else
					{
						NeedSerialNumber++;
						missnumber++;
						CString frame_missing;
						frame_missing.Format(_T("%d"), NeedSerialNumber);
						ds_sdDlg->m_MissingFrameNumEdit.SetSel(ds_sdDlg->m_MissingFrameNumEdit.GetWindowTextLength(), -1); //获取当前编辑框字符
						ds_sdDlg->m_MissingFrameNumEdit.ReplaceSel(frame_missing); //替换当前文本
						ds_sdDlg->m_MissingFrameNumEdit.SetSel(ds_sdDlg->m_MissingFrameNumEdit.GetWindowTextLength(), -1); //获取当前编辑框字符
						ds_sdDlg->m_MissingFrameNumEdit.ReplaceSel(_T(",")); //替换当前文本
						CString str;
						str = ((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->SystemTime();
						((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->m_Hist.SetSel(((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->m_Hist.GetWindowTextLength(), -1); //获取当前编辑框字符
						((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->m_Hist.ReplaceSel(str + "\r\n" + _T("当前帧CRC出错！\r\n")); //替换当前文本
					}
					break;
				}
			}
			else
			{
				NeedSerialNumber++;
				missnumber++;
				CString frame_missing;
				frame_missing.Format(_T("%d"), NeedSerialNumber);
				ds_sdDlg->m_MissingFrameNumEdit.SetSel(ds_sdDlg->m_MissingFrameNumEdit.GetWindowTextLength(), -1); //获取当前编辑框字符
				ds_sdDlg->m_MissingFrameNumEdit.ReplaceSel(frame_missing); //替换当前文本
				ds_sdDlg->m_MissingFrameNumEdit.SetSel(ds_sdDlg->m_MissingFrameNumEdit.GetWindowTextLength(), -1); //获取当前编辑框字符
				ds_sdDlg->m_MissingFrameNumEdit.ReplaceSel(_T(",")); //替换当前文本
				CString str;
				str = ((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->SystemTime();
				((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->m_Hist.SetSel(((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->m_Hist.GetWindowTextLength(), -1); //获取当前编辑框字符
				((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->m_Hist.ReplaceSel(str + "\r\n" + _T("当前帧ASM出错！\r\n")); //替换当前文本
			}
			double missrate = 100 * missnumber / NeedSerialNumber;
			CString missrate_R;
			missrate_R.Format(_T("%f"), missrate); //利用SetDlgItemText显示double型参量
			ds_sdDlg->SetDlgItemText(IDC_MISS_FRAME_RATE_EDIT, missrate_R); //平均误码率
		}
	}

	/*
	int *Protocoldata;
	int *szTemp;
	szTemp = (int*)malloc(50000 * sizeof(int)); //预备50000个数据的量
	int n = Receive(szTemp, 50000 * sizeof(int)); //收到的数据，返回收到的字节数

	int datalen = n / (sizeof(int)) - 1;
	int *PE;
	PE = (int*)malloc(datalen*sizeof(int));
	for (int i = 0; i <datalen; i++)
	{
		PE[i] = szTemp[i];
	}


	if (datalen <= 232)
	{
		if (*(PE + 64) == 0)
		{
			Protocoldata = (int *)malloc((datalen - 96)*sizeof(int));
			for (int i = 0; i < (datalen - 96); i++)
			{
				*(Protocoldata + i) = *(PE + 64 + i);
			}
			UNFRAMING(Protocoldata, datalen - 96);
		}
	}
	else
	{
		//解码
		decode(PE, datalen);
		CString	*str1;
		str1 = new CString[10000];
		CString strDisplay1;
		for (int i = 0; i <(datalen - 96); i++) //为了从int型数组转CString真是累死你爹地了
		{
			str1[i].Format(_T("%d"), P_Rev[i]);
			strDisplay1 += str1[i];	//利用CString类型重载+=的性质
		}

		//将要发送的数据送到CStatusDisply对话框类中的发送数据编辑框
		ds_sdDlg->m_HistReceiveData.SetSel(ds_sdDlg->m_HistReceiveData.GetWindowTextLength(), -1); //获取当前编辑框字符
		ds_sdDlg->m_HistReceiveData.ReplaceSel(strDisplay1); //替换当前文本
//		ds_sdDlg->GetDlgItem(IDC_RECEIVEDATA_EDIT)->SetWindowText(strDisplay1);
		ds_sdDlg->SetDlgItemInt(IDC_CURRENT_SERIAL_NUM_EDIT, num_frame_receive);
		ds_sdDlg->SetDlgItemInt(IDC_RECEIVE_EDIT,(num_frame_receive + 1)*(datalen - 96));
		CString AverageErrorRate_R;
		AverageErrorRate_R.Format(_T("%f"), AverageErrorRate); //利用SetDlgItemText显示double型参量
		ds_sdDlg->SetDlgItemText(IDC_AVERAGEERRORTATE_EDIT, AverageErrorRate_R); //平均误码率
		CString CurrentErrorRate_R;
		CurrentErrorRate_R.Format(_T("%f"), CurrentErrorRate); //利用SetDlgItemText显示double型参量
		ds_sdDlg->SetDlgItemText(IDC_CURRENTERRORRATE_EDIT, CurrentErrorRate_R); //平均误码率
		
		num_frame_receive++;
	}
	*/


	CAsyncSocket::OnReceive(nErrorCode);
}


void CServerSocket::OnClose(int nErrorCode)
{
	// TODO:  在此添加专用代码和/或调用基类
	CString str;
	str = ((CmenuDlg  *)(AfxGetApp()->m_pMainWnd))->SystemTime();
	((CmenuDlg  *)(AfxGetApp()->m_pMainWnd))->m_Hist.SetSel(((CmenuDlg  *)(AfxGetApp()->m_pMainWnd))->m_Hist.GetWindowTextLength(), -1); //获取当前编辑框字符
	((CmenuDlg  *)(AfxGetApp()->m_pMainWnd))->m_Hist.ReplaceSel(str + "\r\n" + _T("客户端断开连接\r\n")); //替换当前文本

	Close();
	//控件禁用
	CAsyncSocket::OnClose(nErrorCode);
}
