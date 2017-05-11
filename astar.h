#ifndef ASTAR_H_INCLUDED
#define ASTAR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
//#include "readdata.h"
#include "main.h"

#define ROAD 4
#define STARTNODE	2
#define ENDNODE		3
#define BARRIER		1
#define PARK        0
#define LISTLENGTH 100
#define STACKDEPTH 100


/*
返回值是1说明寻到路径，返回值是0说明没有；
路径长度就是coord路径堆栈的堆栈深度。例如：两个路径点pathlen就是2。
*/
int pathfind(coord_t *S,coord_t *E,coord_t coord[],int *pathlen);


#endif //
