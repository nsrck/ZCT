#include <math.h>
#include "robocnt.h"

typedef struct robocnteva_st
{
    int Sum_len;//·���ܳ���
} robocnteva_def;

robocnteva_def robocnteva[ROBOMAX];

int roboeval(void)
{
    int i,Sum_lenmax,Sum_lenmin,T_final,carnum,robocnt1,robocnt2;
    float evalue1,evalue2;
    carnum=data_st.carnum;
    T_final=data_st.car[carnum-1].T_out;

    for(i=0;i<parkcount;i++)
    {
        robocnteva[i].Sum_len=parknode[i].I_len+parknode[i].E_len;//��ÿ����λ��·���ͱ�����Sum_len��
    }
    Sum_lenmax=robocnteva[0].Sum_len;
    Sum_lenmin=robocnteva[0].Sum_len;
    for(i=0;i<parkcount;i++)
    {
        if(robocnteva[i].Sum_len>=Sum_lenmax)
        {Sum_lenmax=robocnteva[i].Sum_len;//�õ����·�����Ⱥ�
        }
    }
    for(i=0;i<parkcount;i++)
    {
        if(robocnteva[i].Sum_len<=Sum_lenmin)
        {Sum_lenmin=robocnteva[i].Sum_len;//�õ����·�����Ⱥ�
        }
    }
    evalue1=(2.0*Sum_lenmax*carnum)/T_final;//����ֵ
    evalue2=(2.0*Sum_lenmin*carnum)/T_final;//����ֵ
    printf("evalue1=%f,evalue2=%f\n",evalue1,evalue2);

    robocnt1=ceil(evalue1);
    robocnt2=floor(evalue2);
    if(robocnt2<1) robocnt2=1;
    printf("robocnt1=%d,robocnt2=%d",robocnt1,robocnt2);

 //   for(i=robocnt2;i<=robocnt1;i++)
 //   {

 //   }

    return 1;
}
