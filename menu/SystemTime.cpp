/*

获取系统时间

*/

#include "stdafx.h"
#include "menuDlg.h"

CString CmenuDlg::SystemTime()
{
	CString strTime;
	CTime tm;
	tm = CTime::GetCurrentTime(); //获取系统当前时间
	strTime = tm.Format("%Y.%m.%d %X"); //格式转换

	return strTime;
}