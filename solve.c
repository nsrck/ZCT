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
        robosta[i].robopos=entrance_loc;//所有机器人初始都在入口位置
    }
    for(i=0; ent_sort[i]>0; i++) //更新第一次出库前的入库事件产生的状态
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
//    for(j=0; j<robocnt; j++)//找到距离入口最近的机器人
//    {
//        temp=abs(robosta[j].x-entrance_loc.x)+ abs(robosta[j].y-entrance_loc.y);
//        if(temp<min)
//        {
//            robosel=j;
//            min=temp;
//        }
//    }
    robosel=sche[n];


    if(coordisequ(robosta[robosel].robopos,entrance_loc))//机器人在不在入口位置
    {
        robosta[robosel].robopos=parknode_list[parkpos[n]]->loc;//如果机器人在入口位置
        Tin_p[n]=data_st.car[n].T_in+parknode_list[parkpos[n]]->I_len;
        robosta[robosel].Time=Tin_p[n];
        T1[n]=0;

    }
    else
    {
        pathfind(&(robosta[robosel].robopos),&entrance_loc,path_temp,&pathlen_temp);//如果机器人不在入口位置
        temp=robosta[robosel].Time+pathlen_temp;//到达出口点的时刻temp
        if(temp<=data_st.car[n].T_in+data_st.car[n].T_Mwait)//是否超时
        {

            robosta[robosel].robopos=parknode_list[parkpos[n]]->loc;
            if(temp<=data_st.car[n].T_in)//是否提前到达
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
            //超时了
            for(i=0;i<robocnt;i++)//检查有没有不超时的
            {
                pathfind(&(robosta[i].robopos),&entrance_loc,path_temp,&pathlen_temp);//如果机器人不在入口位置
                temp=robosta[i].Time+pathlen_temp;//到达出口点的时刻temp
                if(temp<data_st.car[n].T_in+data_st.car[n].T_Mwait)
                {
                    k=1;
                    sche[n]=i;
                    break;
                }
            }
            if(k==0)
            {//不存在不超时的机器人
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
            //存在不超时的机器人
        }
    }


}
int coordisequ(coord_t x,coord_t y)
{
    if((x.x==y.x)&&(x.y==y.y))return 1;
    else return 0;

}
