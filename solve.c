#include "solve.h"
typedef struct robosta_st
{
    coord_t robopos;
    int Time;
    int index;//ͣ��λ�����Ӧ����˳����е�λ�ã�-1����ڣ�-2�ǳ���
} robosta_def;

robosta_def robosta[ROBOMAX];
int coordisequ(coord_t x,coord_t y);
void updatesta(int n,int *sche,int *parkpos,int entnum);

void solvepos(population_def *solu)
{
    int i,j;
    int *parkpos=solu->Car_parkpos;
    int *sche=solu->robo_sche;//robo_sche[2*CARMAX];


        for(i=0; i<robocnt; i++)
        {
            robosta[i].robopos=entrance_loc;//���л����˳�ʼ�������λ��
            robosta[i].index=-1;
            robosta[i].Time=0;
        }


    for(i=0; ent_sort[i]>0; i++) //���µ�һ�γ���ǰ������¼�������״̬
    {
        updatesta(ent_sort[i]-1,sche,parkpos,i);//����ע�⣬ent_sort������ǳ��ӵ�id�����Ի��������1

    }

}
void initsolu(population_def *solu)
{

}

int GetTpout(int n)
{

}
/*
����˵����  nΪ������������0��ʼ
            scheΪ���ȱ�ǰһ�������ģ���һ���ǳ����
            parkpos������parknode_list˳��������
            entnum�ǵڼ����¼�
*/
void updatesta(int n,int *sche,int *parkpos,int entnum)
{
    int min,robosel=0,temp,i,j,k=0;
    coord_t path_temp[STACKDEPTH];
    int pathlen_temp;

//    min=abs(robosta[0].x-parknode_list[parkpos[n]]->loc.x)+ abs(robosta[0].y-parknode_list[parkpos[n]]->loc.y);
//    min=abs(robosta[0].robopos.x-entrance_loc.x)+ abs(robosta[0].robopos.y-entrance_loc.y);
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
    if(robosel<0)//�Ƿ�Ϊ����������
    {
        //���Ƿ�������
        if(coordisequ(robosta[robosel].robopos,entrance_loc))//�������ڲ������λ��
        {
            //��������������λ��
            robosta[robosel].robopos=parknode_list[parkpos[n]]->loc;
            robosta[robosel].index=parkpos[n];
            Tin_p[n]=data_st.car[n].T_in+parknode_list[parkpos[n]]->I_len;
            robosta[robosel].Time=Tin_p[n];
            T1[n]=0;

        }
        else
        {
            //��������˲������λ��
            if(coordisequ(robosta[robosel].robopos,exit_loc))//�ڲ��ڳ���λ��
            {
                //�ڳ���λ��
                pathfind(&exit_loc,&entrance_loc,path_temp,&pathlen_temp);
                temp=robosta[robosel].Time+pathlen_temp;//������ڵ��ʱ��temp
            }
            else
            {
                //���ڳ���λ��
                temp=robosta[robosel].Time+parknode_list[robosta[robosel].index]->I_len;//������ڵ��ʱ��temp
            }


            if(temp<=data_st.car[n].T_in+data_st.car[n].T_Mwait)//�Ƿ�ʱ
            {
                //û�г�ʱ
                robosta[robosel].robopos=parknode_list[parkpos[n]]->loc;//���»�����λ��
                robosta[robosel].index=parkpos[n];
                if(temp<=data_st.car[n].T_in)//�Ƿ���ǰ����
                {
                    //��ǰ����
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
                sche[n]=-1;//�ٶ�����
                k=0;
                for(i=0; i<robocnt; i++) //�����û�в���ʱ��
                {
                    if(!coordisequ(robosta[i].robopos,exit_loc))//�ڳ��ڵĻ�ֱ�ӿ����ų���
                    {

                        temp=robosta[i].Time+parknode_list[robosta[i].index]->I_len;//������ڵ��ʱ��temp
                        if(temp<data_st.car[n].T_in+data_st.car[n].T_Mwait)
                        {
                            //���в���ʱ�ܽӵ��Ļ�����
                            k=1;
                            sche[n]=i;
                            break;
                        }
                    }
                }
                if(k==0)//�������Ҳ���
                {
                    sche[n+data_st.carnum]=-1;//������ȱ�ҲҪ����
                }

                updatesta(n,sche,parkpos,entnum);//������һ��

                //���ڲ���ʱ�Ļ�����
            }
        }
    }
    else
    {
        Tin_p[n]=0;
        T1[n]=0;
        Tout_p[n]=0;
        T2[n]=0;


    }

}
int coordisequ(coord_t x,coord_t y)
{
    if((x.x==y.x)&&(x.y==y.y))return 1;
    else return 0;

}
