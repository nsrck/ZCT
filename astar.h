#ifndef ASTAR_H_INCLUDED
#define ASTAR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "readdata.h"


#define ROAD 4
#define STARTNODE	2
#define ENDNODE		3
#define BARRIER		1
#define PARK        0
#define LISTLENGTH 100
#define STACKDEPTH 100
typedef struct AStarNode_s
{
	int s_x;	// ����(�������·����Ҫ)
	int s_y;
	int s_g;	// ��㵽�˵�ľ���( ��g��h���Եõ�f���˴�fʡ�ԣ�f=g+h )
	int	s_h;	// ��������Ԥ��Ĵ˵㵽�յ�ľ���
	int s_style;// ������ͣ���ʼ�㣬�յ㣬�ϰ���
	struct AStarNode_s * s_parent;	// ���ڵ�
	int s_is_in_closetable;			// �Ƿ���close����
	int s_is_in_opentable;			// �Ƿ���open����
} AStarNode, *pAStarNode;

typedef struct coord_s
{
    int x;
    int y;
}coord_t;

typedef struct PARKNODE_s
{
    coord_t loc;
    coord_t I_loc;
    int I_len;
    int E_len;
    coord_t I_Path[256];
    coord_t E_Path[256];

}PARKNODE_def;
typedef PARKNODE_def *pPARKNODE_def;

/*
����ֵ��1˵��Ѱ��·��������ֵ��0˵��û�У�
·�����Ⱦ���coord·����ջ�Ķ�ջ��ȡ����磺����·����pathlen����2��
*/
int pathfind(coord_t *S,coord_t *E,coord_t coord[],int *pathlen);


#endif //
