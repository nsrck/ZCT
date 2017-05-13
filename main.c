#include <stdio.h>
#include <stdlib.h>
#include "astar.h"
#include "readdata.h"
#include "mapcheck.h"
#include "main.h"
#include "gene.h"


data_st_def data_st;
PARKNODE_def parknode[8191];//停车位信息
pPARKNODE_def parknode_heap[8192];//停车位的二叉堆
coord_t entrance_loc;//入口坐标
coord_t exit_loc;//出口坐标
population_def population[POPUNUM];//初始种群
int robocnt=3;//机器人的数量
int Tout_p[CARMAX];//出车位时间表
int Tin_p[CARMAX];//入车位时间表
int ent_sort[CARMAX*2];//申请时间的顺序表：1是入库，0是出库。对前n个数据求和得到m，就能知道是第m个入库事件或是n-m+1个出库事件
int parkcount;//车位数量

int main()
{
    int pathlen,i;
    coord_t startloc,endloc;
    startloc.x=0;
    startloc.y=5;
    endloc.x=5;
    endloc.y=0;
    coord_t coord[STACKDEPTH];

    readdata();
    map_check();


    for(i=0;i<100;i++)
    {
        pathfind(&startloc,&endloc,coord,&pathlen);
    }






    return 1;
}

