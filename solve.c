#include "solve.h"
typedef struct robosta_st
{
    coord_t robopos;
    int Time;
    int index;//停车位坐标对应的在顺序表中的位置，-1是入口，-2是出口
} robosta_def;
robosta_def robosta[ROBOMAX];
int *sche;
int *parkpos;

void updatesta_in(int entnum);
void updatesta_out(int entnum);

int getnewpos(int n);
int solveNout(int n);
int isconflict(int envnum);
int solveconflict(int envnum);

void solvepos(population_def *solu)
{
    int i,j;

    parkpos=solu->Car_parkpos;
    sche=solu->robo_sche;//robo_sche[2*CARMAX];


    for(i=0; i<robocnt; i++)
    {
        robosta[i].robopos=entrance_loc;//所有机器人初始都在入口位置
        robosta[i].index=-1;
        robosta[i].Time=0;
    }


        solveNout(data_st.carnum);


}

int solveNout(int n)
{
    int i=1,k=0,j;

    for(j=0; j<robocnt; j++)
    {
        robosta[j].robopos=entrance_loc;//所有机器人初始都在入口位置
        robosta[j].index=-1;
        robosta[j].Time=0;
    }

    while(ent_sort[i-1]!=-n)//
    {


        while(ent_sort[i]>0) //更新第出库前的入库事件产生的状态
        {
            updatesta_in(i);//这里注意，ent_sort保存的是车子的id，所以会比索引大1
            i++;
        }

        updatesta_out(i);//解决出库时间，得到出车位时间
        i++;
        if(isconflict(i-1))//监测冲突
        {
            //存在冲突
            k=solveconflict(i-1);//k是冲突点最近的一个出库事件的索引，solveconflict重新安排了冲突车位
            solveNout(-ent_sort[k]-1);//解决这个出库事件

            i=k+1;
        }
        else
        {
            //不存在冲突

        }
    }
}
int isconflict(int envnum)
{
    int i=0;
    int n=-ent_sort[envnum]-1;//第n辆车的出库事件
    int m;

    for(i=envnum;(ent_sort[i]<0&&i<2*data_st.carnum);i++);

    if(i==2*data_st.carnum)
    {
        m=data_st.carnum;
    }
    else
    {
        m=ent_sort[i]-1;//m是出库事件之后的入库事件的车索引
    }

    for(i=n+1;i<m;i++)//查找n入库之后和m入库之前的，车的车位是否有冲突
    {
        if(parkpos[i]==parkpos[n]&&Tin_p[i]<Tout_p[n])
        {
            return 1;
        }
    }
    return 0;


}
int solveconflict(int envnum)
{
    int i,j;
    int n=-ent_sort[envnum]-1;//第索引为n的车的出库事件
    int m;
    for(i=envnum;(ent_sort[i]<0&&i<2*data_st.carnum);i++);

    if(i==2*data_st.carnum)
    {
        m=data_st.carnum;
    }
    else
    {
        m=ent_sort[i]-1;//m是出库事件之后的入库事件的车索引
    }
    for(i=n+1;i<m;i++)//查找n入库之后和m入库之前的，车的车位是否有冲突
    {
        if(parkpos[i]==parkpos[n]&&Tin_p[i]<Tout_p[n])
        {
             break;
        }
    }
    parkpos[i]=getnewpos(i);//给冲突的i车重新分配车位(i是索引)

    for(j=0;ent_sort[j]==i+1;j++);//确定i车的入库事件
    for(i=j;ent_sort[i]<0;i++);//确定距离i车入库最近的出库事件
    return i;//返回出库事件的索引

}
int getnewpos(int n)//在车位冲突过程中解决车位重新分配的问题
{

}
void initsolu(population_def *solu)//初始化一个个体
{

}

void updatesta_out(int entnum)
{
    int i,j,rososel=-1,temp,robosel;
    int n=-ent_sort[entnum]-1;
    coord_t path_temp[STACKDEPTH];
    int pathlen_temp;

    robosel=sche[n+data_st.carnum];
    if(robosel>=0)
    {
        //不是放弃车辆
        if(robosta[robosel].index==-2)
        {
            //机器人上一时刻在出口
            temp=robosta[robosel].Time+parknode_list[parkpos[n]]->E_len;//到达车位点的时刻temp

        }
        else
        {
            //机器人上一时刻不在出口
            pathfind(&(parknode_list[robosta[robosel].index]->I_loc),&(parknode_list[parkpos[n]]->I_loc),path_temp,&pathlen_temp);
            pathlen_temp++;
            temp=robosta[robosel].Time+pathlen_temp;


        }

        if(temp+parknode_list[parkpos[n]]->E_len<=data_st.car[n].T_out)
        {
            //到达车位时间小于等于申请出车位时间
            T2[n]=0;
            Tout_p[n]=data_st.car[n].T_out-parknode_list[parkpos[n]]->E_len;
            robosta[robosel].robopos=exit_loc;
            robosta[robosel].index=-2;
            robosta[robosel].Time=data_st.car[n].T_out;

        }
        else
        {
            //到达车位时间大于申请出车位时间
            T2[n]=temp+parknode_list[parkpos[n]]->E_len-data_st.car[n].T_out;
            Tout_p[n]=temp;
            robosta[robosel].robopos=exit_loc;
            robosta[robosel].index=-2;
            robosta[robosel].Time=temp+parknode_list[parkpos[n]]->E_len;

        }

    }
    else
    {
        //是放弃车辆
        T2[n]=0;
        Tout_p[n]=0;
    }
}
/*
参数说明：  n为车序索引，从0开始
            sche为调度表，前一半是入库的，后一半是出库的
            parkpos内容是parknode_list顺序表的索引
            entnum是第几次事件
*/
void updatesta_in(int entnum)
{
    int min,robosel=0,temp,i,j,k=0;
    int n=ent_sort[entnum]-1;
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
    if(robosel>=0)//是否为放弃车辆？
    {
        //不是放弃车辆
        if(robosta[robosel].index==-1)//机器人在不在入口位置
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
            if(robosta[robosel].index==-2)//在不在出口位置
            {
                //在出口位置
                pathfind(&exit_loc,&entrance_loc,path_temp,&pathlen_temp);
                temp=robosta[robosel].Time+(pathlen_temp-1);//到达入口点的时刻temp
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
                    if(robosta[robosel].index!=-2)//在出口的话直接可以排除了
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

                updatesta_in(entnum);//重新来一下

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
//int coordisequ(coord_t x,coord_t y)
//{
//    if((x.x==y.x)&&(x.y==y.y))return 1;
//    else return 0;
//
//}
