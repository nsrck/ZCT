#ifndef MAPCHECK_H_INCLUDED
#define MAPCHECK_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "astar.h"
#include "readdata.h"

int map_check(data_st_def * data_st,PARKNODE_def *parknode,int *pnodecount);//nodecount 是总共有多少停车位的数量
int heapgene(pPARKNODE_def parknode_heap[],PARKNODE_def parknode[],int *pnodecount);
#endif
