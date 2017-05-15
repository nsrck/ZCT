#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "astar.h"

# define MAXSIZE_path  parkcount
pPARKNODE_def swap_temp;
typedef  struct
{
    pPARKNODE_def parknode_list[8192]  ;
}Path_SqList;

 void  BubbleSort(Path_SqList *L);
 int get1pos(int i)  ;
