#include <stdio.h>
#include <stdlib.h>
#include "readdata.h"
#include "astar.h"
/*

data_st_def
{
    int k;
    int p;
    int a;
    int b;
    int w;
    int h;
    int carnum;
    mapsta **pmap;
    AStarNode **pmapnode;//节点数组
    car_property *car;
};
*/


data_st_def data_st;

int main()
{
    coord_t startloc,endloc;
    startloc.x=0;
    startloc.y=5;
    endloc.x=5;
    endloc.y=0;
    coord_t coord[STACKDEPTH];
    readdata(&data_st);
//    pathfind(&startloc,&endloc,coord);







    free(data_st.car);
    free(data_st.pmap);


    return 0;
}

