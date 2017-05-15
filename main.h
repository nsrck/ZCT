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
    car_property car[CARMAX];
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

typedef struct sortst_s
{
    int carid;
    int enttype;
    int T;
}sortst_def;

typedef struct population_s
{
    int Car_parkpos[CARMAX];//值代表了在车位表线性表中的索引
    int robo_sche[2*CARMAX];//每个元素的值代表了选择第几个机器人，从0号开始。等于-1就说明放弃这个事件了。
}population_def;//个体包含了一个车位表和调度表

extern data_st_def data_st;
extern PARKNODE_def parknode[8191];
extern pPARKNODE_def parknode_heap[8192];//用来实现二叉堆的数组
extern pPARKNODE_def parknode_list[8192];//停车位的顺序表
extern int parkcount;//nodecount 是总共有多少停车位的数量
extern coord_t entrance_loc;
extern coord_t exit_loc;
extern population_def population[POPUNUM];
extern int robocnt;//机器人的数量
extern int Tout_p[CARMAX];//出车位时间表
extern int Tin_p[CARMAX];//入车位时间表
extern int T1[CARMAX];//等待时间
extern int T2[CARMAX];//等待时间
extern int ent_sort[CARMAX*2];//申请时间的顺序表：+1是第一辆车出库事件，-1是第一辆车出库事件

#endif
