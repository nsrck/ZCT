#ifndef MAPCHECK_H_INCLUDED
#define MAPCHECK_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "astar.h"

int map_check(void);
int map_data(void);//������������
int abort_map(void);//�����ж���ֹ
int heapgene(void);
//����������ʵ�ֶѲ���
void filter_dw( int i );
void filter_up( int start );

#endif
