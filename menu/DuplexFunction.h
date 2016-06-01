//双工状态下的系统参数设置
//
int state_inactive;  //初始等待
int state_waithail;    //等待握手
int state_starthail;   //开始载波同步
int state_hailacquisition;   //开始符号同步
int state_haildirectives;     //发送握手指令
int state_hailtail;                //发送握手尾序列
int state_hailresponse;   //等待握手响应
int state_carrieronly;       //信道载波维持
int state_acquisition;     //发送捕获序列
int state_duplexon;          //双向数据传递
int state_rnmdend;         //远程发送成功
int state_lnmdend;           //本地发送成功
int state_duplexend;       //双向数据传递完成
int state_terminatingtail;   //尾序列
static int StopFlag;  //强制停止的标志变量 ?

int lnmdsign;						//本地发送完成标志
int rnmdsign;					//远程发送完成标志