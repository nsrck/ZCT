#include "solve.h"
typedef struct robosta_st
{
    coord_t robopos;
    int Time;
    int index;//ͣ��λ�����Ӧ����˳����е�λ�ã�-1����ڣ�-2�ǳ���
} robosta_def;
robosta_def robosta[ROBOMAX];

void updatesta_in(int *sche,int *parkpos,int entnum,robosta_def* robosta);
void updatesta_out(int *sche,int *parkpos,int entnum,robosta_def* robosta);

int solveNout(int *sche,int *parkpos,int n);
int isconflict(void);
int solveconflict(void);

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

    for(i=0;i<data_st.carnum;i++)
    {
        solveNout(sche,parkpos,i+1);
    }





}

int solveNout(int *sche,int *parkpos,int n)
{
    int i=1,k=0,j;

    for(j=0; j<robocnt; j++)
    {
        robosta[j].robopos=entrance_loc;//���л����˳�ʼ�������λ��
        robosta[j].index=-1;
        robosta[j].Time=0;
    }

    while(ent_sort[i-1]!=-n)//
    {


        while(ent_sort[i]>0) //���µڳ���ǰ������¼�������״̬
        {
            updatesta_in(sche,parkpos,i,robosta);//����ע�⣬ent_sort������ǳ��ӵ�id�����Ի��������1
            i++;
        }

        updatesta_out(sche,parkpos,i,robosta);//�������ʱ�䣬�õ�����λʱ��
        i++;
        if(isconflict(-ent_sort[i-1]-1))//����ͻ
        {
            //���ڳ�ͻ
            k=solveconflict();//k�ǳ�ͻ�������һ�������¼���solveconflict���°����˳�ͻ��λ��ע��k�ǳ�id��
            for(j=0; j<2*data_st.carnum; j++)
            {
                if(ent_sort[j]==-k)
                {
                    i=j+1;
                    break;
                }
            }

            solveNout(sche,parkpos,k);
        }
        else
        {
            //�����ڳ�ͻ

        }
    }
}
int isconflict(int n)
{
    int i=0;
//    for(i=0;;i++)
//    {
//        T1[i]Tout_p[n]
//    }

}
int solveconflict(void)
{

}
void initsolu(population_def *solu)
{

}

void updatesta_out(int *sche,int *parkpos,int entnum,robosta_def* robosta)
{
    int i,j,rososel=-1,temp,robosel;
    int n=-ent_sort[entnum]-1;
    coord_t path_temp[STACKDEPTH];
    int pathlen_temp;

    robosel=sche[n+data_st.carnum];
    if(robosel>=0)
    {
        //���Ƿ�������
        if(robosta[robosel].index==-2)
        {
            //��������һʱ���ڳ���
            temp=robosta[robosel].Time+parknode_list[parkpos[n]]->E_len;//���ﳵλ���ʱ��temp

        }
        else
        {
            //��������һʱ�̲��ڳ���
            pathfind(&(parknode_list[robosta[robosel].index]->I_loc),&(parknode_list[parkpos[n]]->I_loc),path_temp,&pathlen_temp);
            pathlen_temp++;
            temp=robosta[robosel].Time+pathlen_temp;


        }

        if(temp+parknode_list[parkpos[n]]->E_len<=data_st.car[n].T_out)
        {
            //���ﳵλʱ��С�ڵ����������λʱ��
            T2[n]=0;
            Tout_p[n]=data_st.car[n].T_out-parknode_list[parkpos[n]]->E_len;
            robosta[robosel].robopos=exit_loc;
            robosta[robosel].index=-2;
            robosta[robosel].Time=data_st.car[n].T_out;

        }
        else
        {
            //���ﳵλʱ������������λʱ��
            T2[n]=temp+parknode_list[parkpos[n]]->E_len-data_st.car[n].T_out;
            Tout_p[n]=temp;
            robosta[robosel].robopos=exit_loc;
            robosta[robosel].index=-2;
            robosta[robosel].Time=temp+parknode_list[parkpos[n]]->E_len;

        }

    }
    else
    {
        //�Ƿ�������
        T2[n]=0;
        Tout_p[n]=0;
    }
}
/*
����˵����  nΪ������������0��ʼ
            scheΪ���ȱ�ǰһ�������ģ���һ���ǳ����
            parkpos������parknode_list˳��������
            entnum�ǵڼ����¼�
*/
void updatesta_in(int *sche,int *parkpos,int entnum,robosta_def* robosta)
{
    int min,robosel=0,temp,i,j,k=0;
    int n=ent_sort[entnum]-1;
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
    if(robosel>=0)//�Ƿ�Ϊ����������
    {
        //���Ƿ�������
        if(robosta[robosel].index==-1)//�������ڲ������λ��
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
            if(robosta[robosel].index==-2)//�ڲ��ڳ���λ��
            {
                //�ڳ���λ��
                pathfind(&exit_loc,&entrance_loc,path_temp,&pathlen_temp);
                temp=robosta[robosel].Time+(pathlen_temp-1);//������ڵ��ʱ��temp
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
                    if(robosta[robosel].index!=-2)//�ڳ��ڵĻ�ֱ�ӿ����ų���
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

                updatesta_in(sche,parkpos,entnum,robosta);//������һ��

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
//int coordisequ(coord_t x,coord_t y)
//{
//    if((x.x==y.x)&&(x.y==y.y))return 1;
//    else return 0;
//
//}
