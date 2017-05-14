#include "solve.h"
typedef struct robosta_st
{
    coord_t robopos;
    int Time;
} robosta_def;

robosta_def robosta[ROBOMAX];
int coordisequ(coord_t x,coord_t y);
void updatesta(int n,int *sche,int *parkpos);

void solvepos(population_def *solu)
{
    int i,j;
    int *parkpos=solu->Car_parkpos;
    int *sche=solu->robo_sche;//robo_sche[2*CARMAX];
    for(i=0; i<robocnt; i++)
    {
        robosta[i].robopos=entrance_loc;//���л����˳�ʼ�������λ��
    }
    for(i=0; ent_sort[i]>0; i++) //���µ�һ�γ���ǰ������¼�������״̬
    {
        updatesta(i,sche,parkpos);

    }

}
void initsolu(population_def *solu)
{

}

int GetTpout(int n)
{

}
void updatesta(int n,int *sche,int *parkpos)
{
    int min,robosel=0,temp,i,j,k=0;
    coord_t path_temp[STACKDEPTH];
    int pathlen_temp;

//    min=abs(robosta[0].x-parknode_list[parkpos[n]]->loc.x)+ abs(robosta[0].y-parknode_list[parkpos[n]]->loc.y);
    min=abs(robosta[0].robopos.x-entrance_loc.x)+ abs(robosta[0].robopos.y-entrance_loc.y);
//    for(j=0; j<robocnt; j++)//�ҵ������������Ļ�����
//    {
//        temp=abs(robosta[j].x-entrance_loc.x)+ abs(robosta[j].y-entrance_loc.y);
//        if(temp<min)
//        {
//            robosel=j;
//            min=temp;
//        }
//    }
    robosel=sche[n];


    if(coordisequ(robosta[robosel].robopos,entrance_loc))//�������ڲ������λ��
    {
        robosta[robosel].robopos=parknode_list[parkpos[n]]->loc;//��������������λ��
        Tin_p[n]=data_st.car[n].T_in+parknode_list[parkpos[n]]->I_len;
        robosta[robosel].Time=Tin_p[n];
        T1[n]=0;

    }
    else
    {
        pathfind(&(robosta[robosel].robopos),&entrance_loc,path_temp,&pathlen_temp);//��������˲������λ��
        temp=robosta[robosel].Time+pathlen_temp;//������ڵ��ʱ��temp
        if(temp<=data_st.car[n].T_in+data_st.car[n].T_Mwait)//�Ƿ�ʱ
        {

            robosta[robosel].robopos=parknode_list[parkpos[n]]->loc;
            if(temp<=data_st.car[n].T_in)//�Ƿ���ǰ����
            {

                Tin_p[n]=data_st.car[n].T_in+parknode_list[parkpos[n]]->I_len;
                robosta[robosel].Time=Tin_p[n];
                T1[n]=0;
            }
            else
            {
                Tin_p[n]=temp+parknode_list[parkpos[n]]->I_len;
                robosta[robosel].Time=Tin_p[n];
                T1[n]=temp-data_st.car[n].T_in;
            }
        }
        else
        {
            //��ʱ��
            for(i=0;i<robocnt;i++)//�����û�в���ʱ��
            {
                pathfind(&(robosta[i].robopos),&entrance_loc,path_temp,&pathlen_temp);//��������˲������λ��
                temp=robosta[i].Time+pathlen_temp;//������ڵ��ʱ��temp
                if(temp<data_st.car[n].T_in+data_st.car[n].T_Mwait)
                {
                    k=1;
                    sche[n]=i;
                    break;
                }
            }
            if(k==0)
            {//�����ڲ���ʱ�Ļ�����
                sche[n]=robocnt;
                Tin_p[n]=0;
                T1[n]=0;
                Tout_p[n]=0;
                T2[n]=0;
            }
            else
            {
                updatesta(i,sche,parkpos);
            }
            //���ڲ���ʱ�Ļ�����
        }
    }


}
int coordisequ(coord_t x,coord_t y)
{
    if((x.x==y.x)&&(x.y==y.y))return 1;
    else return 0;

}
