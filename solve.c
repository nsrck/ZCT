#include "solve.h"
typedef struct robosta_st
{
    coord_t robopos;
    int Time;
    int index;//停车位坐标对应的在顺序表中的位置，-1是入口，-2是出口
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
            robosta[i].robopos=entrance_loc;//所有机器人初始都在入口位置
            robosta[i].index=-1;
            robosta[i].Time=0;
        }


    for(i=0; ent_sort[i]>0; i++) //更新第一次出库前的入库事件产生的状态
    {
        updatesta(ent_sort[i]-1,sche,parkpos,i);//这里注意，ent_sort保存的是车子的id，所以会比索引大1

    }

}
void initsolu(population_def *solu)
{

}

int GetTpout(int n)
{

}
/*
参数说明：  n为车序索引，从0开始
            sche为调度表，前一半是入库的，后一半是出库的
            parkpos内容是parknode_list顺序表的索引
            entnum是第几次事件
*/
void updatesta(int n,int *sche,int *parkpos,int entnum)
{
    int min,robosel=0,temp,i,j,k=0;
    coord_t path_temp[STACKDEPTH];
    int pathlen_temp;

//    min=abs(robosta[0].x-parknode_list[parkpos[n]]->loc.x)+ abs(robosta[0].y-parknode_list[parkpos[n]]->loc.y);
//    min=abs(robosta[0].robopos.x-entrance_loc.x)+ abs(robosta[0].robopos.y-entrance_loc.y);
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
    if(robosel<0)//是否为放弃车辆？
    {
        //不是放弃车辆
        if(coordisequ(robosta[robosel].robopos,entrance_loc))//机器人在不在入口位置
        {
            //如果机器人在入口位置
            robosta[robosel].robopos=parknode_list[parkpos[n]]->loc;
            robosta[robosel].index=parkpos[n];
            Tin_p[n]=data_st.car[n].T_in+parknode_list[parkpos[n]]->I_len;
            robosta[robosel].Time=Tin_p[n];
            T1[n]=0;

        }
        else
        {
            //如果机器人不在入口位置
            if(coordisequ(robosta[robosel].robopos,exit_loc))//在不在出口位置
            {
                //在出口位置
                pathfind(&exit_loc,&entrance_loc,path_temp,&pathlen_temp);
                temp=robosta[robosel].Time+pathlen_temp;//到达入口点的时刻temp
            }
            else
            {
                //不在出口位置
                temp=robosta[robosel].Time+parknode_list[robosta[robosel].index]->I_len;//到达入口点的时刻temp
            }


            if(temp<=data_st.car[n].T_in+data_st.car[n].T_Mwait)//是否超时
            {
                //没有超时
                robosta[robosel].robopos=parknode_list[parkpos[n]]->loc;//更新机器人位置
                robosta[robosel].index=parkpos[n];
                if(temp<=data_st.car[n].T_in)//是否提前到达
                {
                    //提前到达
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
                sche[n]=-1;//假定放弃
                k=0;
                for(i=0; i<robocnt; i++) //检查有没有不超时的
                {
                    if(!coordisequ(robosta[i].robopos,exit_loc))//在出口的话直接可以排除了
                    {

                        temp=robosta[i].Time+parknode_list[robosta[i].index]->I_len;//到达入口点的时刻temp
                        if(temp<data_st.car[n].T_in+data_st.car[n].T_Mwait)
                        {
                            //真有不超时能接到的机器人
                            k=1;
                            sche[n]=i;
                            break;
                        }
                    }
                }
                if(k==0)//看来是找不到
                {
                    sche[n+data_st.carnum]=-1;//出库调度表也要改正
                }

                updatesta(n,sche,parkpos,entnum);//重新来一下

                //存在不超时的机器人
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
