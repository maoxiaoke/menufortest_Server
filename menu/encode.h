/*
	本头文件定义编码函数
*/

#include "stdafx.h"



extern		int encode(int *P_Data);
extern		void FH40(int len, int *r40);
extern		void CRC32(int *pv3, int len, int *r32);
extern		int *CC217(int *buffer_crc32, int Length);
extern		int decode(int *P_RE, int FileSize);
extern		int* DeCC217(int *buffer, int len);
extern		int encodecommond(int *P_Data);
extern		void makewrong(int *initial, int linelength);
extern		int decodenumber(int *P_RE, int FileSize);
extern		int encodearq(int *P_Data);
