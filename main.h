#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#define CARMAX 5000
#define ROBOMAX 100
#define POPUNUM 100 //��ʼ��Ⱥ����

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

typedef struct sortst_s
{
    int carid;
    int enttype;
    int T;
}sortst_def;

typedef struct population_s
{
    int Car_parkpos[CARMAX];//ֵ�������ڳ�λ�����Ա��е�����
    int robo_sche[2*CARMAX];//ÿ��Ԫ�ص�ֵ������ѡ��ڼ��������ˣ���0�ſ�ʼ������-1��˵����������¼��ˡ�
}population_def;//���������һ����λ��͵��ȱ�

extern data_st_def data_st;
extern PARKNODE_def parknode[8191];
extern pPARKNODE_def parknode_heap[8192];//����ʵ�ֶ���ѵ�����
extern pPARKNODE_def parknode_list[8192];//ͣ��λ��˳���
extern int parkcount;//nodecount ���ܹ��ж���ͣ��λ������
extern coord_t entrance_loc;
extern coord_t exit_loc;
extern population_def population[POPUNUM];
extern int robocnt;//�����˵�����
extern int Tout_p[CARMAX];//����λʱ���
extern int Tin_p[CARMAX];//�복λʱ���
extern int T1[CARMAX];//�ȴ�ʱ��
extern int T2[CARMAX];//�ȴ�ʱ��
extern int ent_sort[CARMAX*2];//����ʱ���˳���+1�ǵ�һ���������¼���-1�ǵ�һ���������¼�

#endif
