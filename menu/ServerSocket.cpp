// ServerSocket.cpp : ʵ���ļ�
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


// CServerSocket ��Ա����


void CServerSocket::OnReceive(int nErrorCode)
{
	// TODO:  �ڴ����ר�ô����/����û���
	//���տͻ��˷�������Ϣ

	int *Protocoldata;
	int *szTemp;
	int Errorbit = 0;
	szTemp = (int*)malloc(5000 * sizeof(int)); //Ԥ��5000�����ݵ���
	int n = Receive(szTemp, 5000 * sizeof(int)); //�յ������ݣ������յ����ֽ���

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
			makewrong(PE, datalen);																							//����Ӵ�
			int ASMerror = 0;
			int ASM[24] = { 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0 };
			for (int i = 0; i < 24; i++)
			{
				if (PE[i] != ASM[i])
				{
					ASMerror++;																										//ASM���
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
						Errorbit++;																									//CRC���
					}
				}
				break;
			}
			decodenumber(PE, datalen);																					//��֡֡��
			//Դ������δ֪�����
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
				ds_sdDlg->m_MissingFrameNumEdit.SetSel(ds_sdDlg->m_MissingFrameNumEdit.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
				ds_sdDlg->m_MissingFrameNumEdit.ReplaceSel(frame_missing); //�滻��ǰ�ı�
				ds_sdDlg->m_MissingFrameNumEdit.SetSel(ds_sdDlg->m_MissingFrameNumEdit.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
				ds_sdDlg->m_MissingFrameNumEdit.ReplaceSel(_T(",")); //�滻��ǰ�ı�
				CString str;
				str = ((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->SystemTime();
				((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->m_Hist.SetSel(((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->m_Hist.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
				((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->m_Hist.ReplaceSel(str + "\r\n" + _T("��ǰ֡ASM����\r\n")); //�滻��ǰ�ı�
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
				ds_sdDlg->m_MissingFrameNumEdit.SetSel(ds_sdDlg->m_MissingFrameNumEdit.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
				ds_sdDlg->m_MissingFrameNumEdit.ReplaceSel(frame_missing); //�滻��ǰ�ı�
				ds_sdDlg->m_MissingFrameNumEdit.SetSel(ds_sdDlg->m_MissingFrameNumEdit.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
				ds_sdDlg->m_MissingFrameNumEdit.ReplaceSel(_T(",")); //�滻��ǰ�ı�
				CString str;
				str = ((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->SystemTime();
				((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->m_Hist.SetSel(((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->m_Hist.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
				((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->m_Hist.ReplaceSel(str + "\r\n" + _T("��ǰ֡CRC����\r\n")); //�滻��ǰ�ı�
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
				ds_sdDlg->m_MissingFrameNumEdit.SetSel(ds_sdDlg->m_MissingFrameNumEdit.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
				ds_sdDlg->m_MissingFrameNumEdit.ReplaceSel(frame_missing); //�滻��ǰ�ı�
				ds_sdDlg->m_MissingFrameNumEdit.SetSel(ds_sdDlg->m_MissingFrameNumEdit.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
				ds_sdDlg->m_MissingFrameNumEdit.ReplaceSel(_T(",")); //�滻��ǰ�ı�
				CString str;
				str = ((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->SystemTime();
				((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->m_Hist.SetSel(((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->m_Hist.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
				((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->m_Hist.ReplaceSel(str + "\r\n" + _T("��ǰ֡֡�ų���\r\n")); //�滻��ǰ�ı�
				return;
			}
			else
			{
				decode(PE, datalen);					//��֡
				CString	*str1;
				str1 = new CString[10000];
				CString strDisplay1;
				for (int i = 0; i < (datalen - 96); i++) //Ϊ�˴�int������תCString���������������
				{
					str1[i].Format(_T("%d"), P_Rev[i]);
					strDisplay1 += str1[i];	//����CString��������+=������
				}

				//��Ҫ���͵������͵�CStatusDisply�Ի������еķ������ݱ༭��
				ds_sdDlg->m_HistReceiveData.SetSel(ds_sdDlg->m_HistReceiveData.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
				ds_sdDlg->m_HistReceiveData.ReplaceSel(strDisplay1); //�滻��ǰ�ı�
				//		ds_sdDlg->GetDlgItem(IDC_RECEIVEDATA_EDIT)->SetWindowText(strDisplay1);
				ds_sdDlg->SetDlgItemInt(IDC_CURRENT_SERIAL_NUM_EDIT, NeedSerialNumber);
				ds_sdDlg->SetDlgItemInt(IDC_RECEIVE_EDIT, receivenumber*datalength1);
				CString AverageErrorRate_R;
				AverageErrorRate_R.Format(_T("%f"), AverageErrorRate); //����SetDlgItemText��ʾdouble�Ͳ���
				ds_sdDlg->SetDlgItemText(IDC_AVERAGEERRORTATE_EDIT, AverageErrorRate_R); //ƽ��������
				CString CurrentErrorRate_R;
				CurrentErrorRate_R.Format(_T("%f"), CurrentErrorRate); //����SetDlgItemText��ʾdouble�Ͳ���
				ds_sdDlg->SetDlgItemText(IDC_CURRENTERRORRATE_EDIT, CurrentErrorRate_R); //ƽ��������

				receivenumber++;
				NeedSerialNumber++;

			}
		}
		else
		{
			makewrong(PE, datalen);																							//����Ӵ�
			
			int ASMerror = 0;
			int ASM[24] = { 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0 };
			for (int i = 0; i < 24; i++)
			{
				if (PE[i] != ASM[i])
				{
					ASMerror++;																										//ASM���
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
							Errorbit++;																									//CRC���
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
							for (int i = 0; i < (datalen - 96); i++) //Ϊ�˴�int������תCString���������������
							{
								str1[i].Format(_T("%d"), P_Rev[i]);
								strDisplay1 += str1[i];	//����CString��������+=������
							}

							//��Ҫ���͵������͵�CStatusDisply�Ի������еķ������ݱ༭��
							ds_sdDlg->m_HistReceiveData.SetSel(ds_sdDlg->m_HistReceiveData.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
							ds_sdDlg->m_HistReceiveData.ReplaceSel(strDisplay1); //�滻��ǰ�ı�
							//		ds_sdDlg->GetDlgItem(IDC_RECEIVEDATA_EDIT)->SetWindowText(strDisplay1);
							ds_sdDlg->SetDlgItemInt(IDC_CURRENT_SERIAL_NUM_EDIT, NeedSerialNumber);
							ds_sdDlg->SetDlgItemInt(IDC_RECEIVE_EDIT, receivenumber*datalength1);
							CString AverageErrorRate_R;
							AverageErrorRate_R.Format(_T("%f"), AverageErrorRate); //����SetDlgItemText��ʾdouble�Ͳ���
							ds_sdDlg->SetDlgItemText(IDC_AVERAGEERRORTATE_EDIT, AverageErrorRate_R); //ƽ��������
							CString CurrentErrorRate_R;
							CurrentErrorRate_R.Format(_T("%f"), CurrentErrorRate); //����SetDlgItemText��ʾdouble�Ͳ���
							ds_sdDlg->SetDlgItemText(IDC_CURRENTERRORRATE_EDIT, CurrentErrorRate_R); //ƽ��������

							receivenumber++;
							NeedSerialNumber++;
						}
						else
						{
							NeedSerialNumber++;
							missnumber++;
							CString frame_missing;
							frame_missing.Format(_T("%d"), NeedSerialNumber);
							ds_sdDlg->m_MissingFrameNumEdit.SetSel(ds_sdDlg->m_MissingFrameNumEdit.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
							ds_sdDlg->m_MissingFrameNumEdit.ReplaceSel(frame_missing); //�滻��ǰ�ı�
							ds_sdDlg->m_MissingFrameNumEdit.SetSel(ds_sdDlg->m_MissingFrameNumEdit.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
							ds_sdDlg->m_MissingFrameNumEdit.ReplaceSel(_T(",")); //�滻��ǰ�ı�
							CString str;
							str = ((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->SystemTime();
							((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->m_Hist.SetSel(((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->m_Hist.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
							((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->m_Hist.ReplaceSel(str + "\r\n" + _T("��ǰ֡֡�ų���\r\n")); //�滻��ǰ�ı�
						}
					}
					else
					{
						NeedSerialNumber++;
						missnumber++;
						CString frame_missing;
						frame_missing.Format(_T("%d"), NeedSerialNumber);
						ds_sdDlg->m_MissingFrameNumEdit.SetSel(ds_sdDlg->m_MissingFrameNumEdit.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
						ds_sdDlg->m_MissingFrameNumEdit.ReplaceSel(frame_missing); //�滻��ǰ�ı�
						ds_sdDlg->m_MissingFrameNumEdit.SetSel(ds_sdDlg->m_MissingFrameNumEdit.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
						ds_sdDlg->m_MissingFrameNumEdit.ReplaceSel(_T(",")); //�滻��ǰ�ı�
						CString str;
						str = ((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->SystemTime();
						((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->m_Hist.SetSel(((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->m_Hist.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
						((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->m_Hist.ReplaceSel(str + "\r\n" + _T("��ǰ֡CRC����\r\n")); //�滻��ǰ�ı�
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
				ds_sdDlg->m_MissingFrameNumEdit.SetSel(ds_sdDlg->m_MissingFrameNumEdit.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
				ds_sdDlg->m_MissingFrameNumEdit.ReplaceSel(frame_missing); //�滻��ǰ�ı�
				ds_sdDlg->m_MissingFrameNumEdit.SetSel(ds_sdDlg->m_MissingFrameNumEdit.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
				ds_sdDlg->m_MissingFrameNumEdit.ReplaceSel(_T(",")); //�滻��ǰ�ı�
				CString str;
				str = ((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->SystemTime();
				((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->m_Hist.SetSel(((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->m_Hist.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
				((CmenuDlg*)(AfxGetApp()->m_pMainWnd))->m_Hist.ReplaceSel(str + "\r\n" + _T("��ǰ֡ASM����\r\n")); //�滻��ǰ�ı�
			}
			double missrate = 100 * missnumber / NeedSerialNumber;
			CString missrate_R;
			missrate_R.Format(_T("%f"), missrate); //����SetDlgItemText��ʾdouble�Ͳ���
			ds_sdDlg->SetDlgItemText(IDC_MISS_FRAME_RATE_EDIT, missrate_R); //ƽ��������
		}
	}

	/*
	int *Protocoldata;
	int *szTemp;
	szTemp = (int*)malloc(50000 * sizeof(int)); //Ԥ��50000�����ݵ���
	int n = Receive(szTemp, 50000 * sizeof(int)); //�յ������ݣ������յ����ֽ���

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
		//����
		decode(PE, datalen);
		CString	*str1;
		str1 = new CString[10000];
		CString strDisplay1;
		for (int i = 0; i <(datalen - 96); i++) //Ϊ�˴�int������תCString���������������
		{
			str1[i].Format(_T("%d"), P_Rev[i]);
			strDisplay1 += str1[i];	//����CString��������+=������
		}

		//��Ҫ���͵������͵�CStatusDisply�Ի������еķ������ݱ༭��
		ds_sdDlg->m_HistReceiveData.SetSel(ds_sdDlg->m_HistReceiveData.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
		ds_sdDlg->m_HistReceiveData.ReplaceSel(strDisplay1); //�滻��ǰ�ı�
//		ds_sdDlg->GetDlgItem(IDC_RECEIVEDATA_EDIT)->SetWindowText(strDisplay1);
		ds_sdDlg->SetDlgItemInt(IDC_CURRENT_SERIAL_NUM_EDIT, num_frame_receive);
		ds_sdDlg->SetDlgItemInt(IDC_RECEIVE_EDIT,(num_frame_receive + 1)*(datalen - 96));
		CString AverageErrorRate_R;
		AverageErrorRate_R.Format(_T("%f"), AverageErrorRate); //����SetDlgItemText��ʾdouble�Ͳ���
		ds_sdDlg->SetDlgItemText(IDC_AVERAGEERRORTATE_EDIT, AverageErrorRate_R); //ƽ��������
		CString CurrentErrorRate_R;
		CurrentErrorRate_R.Format(_T("%f"), CurrentErrorRate); //����SetDlgItemText��ʾdouble�Ͳ���
		ds_sdDlg->SetDlgItemText(IDC_CURRENTERRORRATE_EDIT, CurrentErrorRate_R); //ƽ��������
		
		num_frame_receive++;
	}
	*/


	CAsyncSocket::OnReceive(nErrorCode);
}


void CServerSocket::OnClose(int nErrorCode)
{
	// TODO:  �ڴ����ר�ô����/����û���
	CString str;
	str = ((CmenuDlg  *)(AfxGetApp()->m_pMainWnd))->SystemTime();
	((CmenuDlg  *)(AfxGetApp()->m_pMainWnd))->m_Hist.SetSel(((CmenuDlg  *)(AfxGetApp()->m_pMainWnd))->m_Hist.GetWindowTextLength(), -1); //��ȡ��ǰ�༭���ַ�
	((CmenuDlg  *)(AfxGetApp()->m_pMainWnd))->m_Hist.ReplaceSel(str + "\r\n" + _T("�ͻ��˶Ͽ�����\r\n")); //�滻��ǰ�ı�

	Close();
	//�ؼ�����
	CAsyncSocket::OnClose(nErrorCode);
}
