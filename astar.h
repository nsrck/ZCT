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
返回值是1说明寻到路径，返回值是0说明没有；
路径长度就是coord路径堆栈的堆栈深度。例如：两个路径点pathlen就是2。
*/
int pathfind(coord_t *S,coord_t *E,coord_t coord[],int *pathlen);


#endif //
