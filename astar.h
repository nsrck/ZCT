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

int pathfind(coord_t *S,coord_t *E,coord_t coord[]);

//private
void adjust_heap( int i );
void filter_up(int start);
void _swap( int idx1, int idx2 );
void insert_to_opentable( int x, int y, pAStarNode curr_node, pAStarNode end_node, int w );
void get_neighbors( pAStarNode curr_node, pAStarNode end_node );

#endif //
