//˫��״̬�µ�ϵͳ��������
//
int state_inactive;  //��ʼ�ȴ�
int state_waithail;    //�ȴ�����
int state_starthail;   //��ʼ�ز�ͬ��
int state_hailacquisition;   //��ʼ����ͬ��
int state_haildirectives;     //��������ָ��
int state_hailtail;                //��������β����
int state_hailresponse;   //�ȴ�������Ӧ
int state_carrieronly;       //�ŵ��ز�ά��
int state_acquisition;     //���Ͳ�������
int state_duplexon;          //˫�����ݴ���
int state_rnmdend;         //Զ�̷��ͳɹ�
int state_lnmdend;           //���ط��ͳɹ�
int state_duplexend;       //˫�����ݴ������
int state_terminatingtail;   //β����
static int StopFlag;  //ǿ��ֹͣ�ı�־���� ?

int lnmdsign;						//���ط�����ɱ�־
int rnmdsign;					//Զ�̷�����ɱ�־