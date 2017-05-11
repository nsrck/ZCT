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
����ֵ��1˵��Ѱ��·��������ֵ��0˵��û�У�
·�����Ⱦ���coord·����ջ�Ķ�ջ��ȡ����磺����·����pathlen����2��
*/
int pathfind(coord_t *S,coord_t *E,coord_t coord[],int *pathlen);


#endif //
