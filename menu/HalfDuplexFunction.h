/*

本头文件定义了半双工下的头文件

*/
int state_inactiveH; //初始状态
int state_waithailH;  //等待握手
int state_starthailH; //开始载波同步
int state_hailacquisitionH; // 开始符号同步
int state_haildirectivesH; //发送握手指令
int state_hailtailH;  //发送握手指令
int state_hailresponseH;  //等待握手响应
int state_carrieronlyH; //信道载波维持
int state_acquisitionH;  //发送捕获序列
int state_receiveDataH;  //接收数据
int state_waitfirstframeH; //等待第一帧
int state_waitcarrierH; // 等待载波
int state_tailswitchH; //尾序列转换
int state_tokenexchangeH; //状态转换
int state_senddataH; //发送数据
int state_responseendH; //终止应答
int state_tailquitH; //结束尾序列

static int StopFlagH;

