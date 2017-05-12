#ifndef MAPCHECK_H_INCLUDED
#define MAPCHECK_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "astar.h"

int map_check(void);
int map_data(void);//用来保存数据
int abort_map(void);//用来判断终止
int heapgene(void);
//函数，用来实现堆操作
void filter_dw( int i );
void filter_up( int start );

#endif
