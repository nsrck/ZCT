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
	int s_x;	// 坐标(最终输出路径需要)
	int s_y;
	int s_g;	// 起点到此点的距离( 由g和h可以得到f，此处f省略，f=g+h )
	int	s_h;	// 启发函数预测的此点到终点的距离
	int s_style;// 结点类型：起始点，终点，障碍物
	struct AStarNode_s * s_parent;	// 父节点
	int s_is_in_closetable;			// 是否在close表中
	int s_is_in_opentable;			// 是否在open表中
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
