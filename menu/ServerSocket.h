#pragma once

#include "StatusDisplayDlg.h"

// CServerSocket ����Ŀ��

class CServerSocket : public CAsyncSocket
{
public:
	CServerSocket();
	virtual ~CServerSocket();
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);

	CStatusDisplayDlg * ds_sdDlg;
};


