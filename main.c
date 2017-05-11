#include <stdio.h>
#include <stdlib.h>
#include "astar.h"
#include "readdata.h"
#include "mapcheck.h"


data_st_def data_st;
PARKNODE_def parknode[8191];
pPARKNODE_def parknode_heap[8192];
int parkcount;

int main()
{
    int pathlen;
    coord_t startloc,endloc;
    startloc.x=0;
    startloc.y=5;
    endloc.x=5;
    endloc.y=0;
    coord_t coord[STACKDEPTH];
    readdata();

//    pathfind(&startloc,&endloc,coord,&pathlen);







    return 0;
}

