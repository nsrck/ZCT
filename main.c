#include <stdio.h>
#include <stdlib.h>
#include "astar.h"
#include "readdata.h"
#include "mapcheck.h"
#include "main.h"


data_st_def data_st;
PARKNODE_def parknode[8191];//停车位信息
pPARKNODE_def parknode_heap[8192];//停车位的二叉堆
coord_t entrance_loc;//入口坐标
coord_t exit_loc;//出口坐标
coord_t Car_parkpos[CARMAX];//车位分配表
int robo_sche[ROBOMAX][2*CARMAX];//机器人调度表


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

    for(i=0;i<100;i++)
    {
        pathfind(&startloc,&endloc,coord,&pathlen);
    }






    return 0;
}

