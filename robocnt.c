#include "robocnt.h"

typedef struct robocnteva_st
{
    int Sum_len;//·���ܳ���
} robocnteva_def;

robocnteva_def robocnteva[ROBOMAX];

int roboeval(void)
{
    int i,Sum_lenmax,Sum_lenmin,T_final=data_st.car[parkcount-1].T_out;
    char evalue;
    for(i=0;i<parkcount;i++)
    {
        robocnteva[i].Sum_len=parknode[i].I_len+parknode[i].E_len;//��ÿ����λ��·���ͱ�����Sum_len��
    }
    Sum_lenmax=robocnteva[0].Sum_len;
    Sum_lenmin=robocnteva[0].Sum_len;
    for(i=0;i<parkcount;i++)
    {
        if(robocnteva[i].Sum_len>=Sum_lenmax) Sum_lenmax=robocnteva[i].Sum_len;//�õ����·�����Ⱥ�
    }
    for(i=0;i<parkcount;i++)
    {
        if(robocnteva[i].Sum_len<=Sum_lenmin) Sum_lenmin=robocnteva[i].Sum_len;//�õ����·�����Ⱥ�
    }
    evalue=2*Sum_lenmax*data_st.carnum/T_final;
    robocnt=ceil(evalue);

    return 1;
}
