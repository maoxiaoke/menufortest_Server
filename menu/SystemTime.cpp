/*

��ȡϵͳʱ��

*/

#include "stdafx.h"
#include "menuDlg.h"

CString CmenuDlg::SystemTime()
{
	CString strTime;
	CTime tm;
	tm = CTime::GetCurrentTime(); //��ȡϵͳ��ǰʱ��
	strTime = tm.Format("%Y.%m.%d %X"); //��ʽת��

	return strTime;
}