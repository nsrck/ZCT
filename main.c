#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "gene.h"
#include "solve.h"
#include "mapcheck.h"
#include "readdata.h"
#include "output.h"

data_st_def data_st;
PARKNODE_def parknode[8191];//停车位信息
pPARKNODE_def parknode_heap[8192];//停车位的二叉堆
pPARKNODE_def parknode_list[8192];//停车位的顺序表
coord_t entrance_loc;//入口坐标
coord_t exit_loc;//出口坐标
int pathlen_StoE;
coord_t path_StoE[STACKDEPTH];
population_def population[POPUNUM];//初始种群
int robocnt=4;//机器人的数量
int Tout_p[CARMAX]={0};//出车位时间表
int Tin_p[CARMAX]={0};//入车位时间表
int T1[CARMAX]={0};//等待时间
int T2[CARMAX]={0};//等待时间
int ent_sort[CARMAX*2]={0};//申请时间的顺序表：
int parkcount;//车位数量
int mapvalid;
int Z;
int T_count;
int W_count;
void Init_list(void);
void sortent(void);
int main()
{
//    int pathlen,i;
//    coord_t startloc,endloc;
//    startloc.x=3;
//    startloc.y=1;
//    endloc.x=4;
//    endloc.y=1;
//    coord_t coord[STACKDEPTH];

    readdata();


    if(map_check()==0)
    {
        mapvalid=0;
    }

    else
    {
        mapvalid=1;
        sortent();
        Init_list();
        initsolu(&(population[0]));
        roboeval();
//        solvepos(&(population[0]));

    }
    output_result(&(population[0]));


//    for(i=0;i<100;i++)
//    {
//        pathfind(&startloc,&endloc,coord,&pathlen);
//    }





    return 1;
}

void sortent(void)
{
    int i,j;
    sortst_def sortst[CARMAX*2];
    sortst_def temp;
    for(i=0; i<data_st.carnum; i++)
    {
        sortst[i].carid=i+1;
        sortst[i].enttype=0;
        sortst[i].T=data_st.car[i].T_in;
    }
    for(i=0; i<data_st.carnum; i++)
    {
        sortst[i+data_st.carnum].carid=i+1;
        sortst[i+data_st.carnum].enttype=1;
        sortst[i+data_st.carnum].T=data_st.car[i].T_out;
    }
    for(i = 0; i < 2*data_st.carnum; i++)
    {
        for(j = 0; j < 2*data_st.carnum - 1 - i; j++)
        {
            if(sortst[j].T > sortst[j + 1].T)
            {
                temp=sortst[j];
                sortst[j]=sortst[j+1];
                sortst[j+1]=temp;
            }
        }
    }
    for(i = 0; i < 2*data_st.carnum; i++)
    {
        if(sortst[i].enttype==0)
        {
            ent_sort[i]=sortst[i].carid;
        }
        else
        {
            ent_sort[i]=-sortst[i].carid;
        }
    }


}

void  Init_list(void)
{
    pPARKNODE_def swap_temp;
    int i,j,k,q,temp;
    int a[parkcount];
    for(k=0; k<parkcount; k++) //初始化
    {
        parknode_list[k]=&parknode[k];
    }
    for (q=0; q<parkcount; q++)
    {
        a[q]=(parknode_list[q]->I_len+parknode_list[q]->E_len );   //先算出所有路径和，方便下面计算
    }
    for(i=0; i<parkcount; i++)                //开始冒泡排序
    {
        for (j =1; j<parkcount-i; j++)
        {
            if (a[j-1]>a[j])
            {
                swap_temp =parknode_list[j-1];
                parknode_list[j-1] = parknode_list[j];
                parknode_list[j] =swap_temp;
                temp = a[j-1];
                a[j-1] = a[j];
                a[j] = temp;
            }
        }
    }
//    for (i=0; i<parkcount; i++)
//    {
//        printf("%d\n",(parknode_list[i]->I_len+parknode_list[i]->E_len)) ;
//        printf("%d\n",a[i]) ;
//        }

}
