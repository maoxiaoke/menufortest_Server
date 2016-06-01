/*
本头文件定义指令帧编码函数
*/
#include  "stdafx.h"



extern int* SPDU_framing(void);
extern int* SET_TRANSMITTER(void);
extern int* SET_CONTROL(void);
extern int* SET_RECEIVER(void);
extern int* SET_VR(void);
extern int* REPORT_REQUEST(void);
extern int* HALL_COMMOND(void);
extern int* SET_PL_EXTENSIONS(void);
extern int* REPORT_SOURCE_SCID(void);

extern void UNFRAMING(int *P_Frame, int len);
extern int GET_ARQ_NUM(int *r_PLCW);
extern int *PLCW_framing(int Retrans_Number);