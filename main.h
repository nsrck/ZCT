#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#define CARMAX 5000
#define ROBOMAX 100
#define POPUNUM 100 //初始种群数量

typedef    struct
{
    int ID;
    int T_in;
    int T_out;
    int T_Mwait;
    int mass;
} car_property;

typedef enum  {P=0,B,I,E,X} mapsta;

typedef struct
{
    int k;
    int p;
    int a;
    int b;
    int w;
    int h;
    int carnum;
//    mapsta **pmap;
    mapsta pmap[100][100];
    car_property car[4095];
}data_st_def;

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

typedef struct population_s
{
    coord_t Car_parkpos[CARMAX];
    int robo_sche[ROBOMAX][2*CARMAX];
}population_def;
extern data_st_def data_st;
extern PARKNODE_def parknode[8191];
extern pPARKNODE_def parknode_heap[8192];//用来实现二叉堆的数组
extern int parkcount;//nodecount 是总共有多少停车位的数量
extern coord_t entrance_loc;
extern coord_t exit_loc;

extern population_def population[POPUNUM];


#endif
