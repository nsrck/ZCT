#include <stdio.h>
#include <stdlib.h>
#include "astar.h"
#include "readdata.h"
#include "mapcheck.h"
#include "main.h"
#include "gene.h"


data_st_def data_st;
PARKNODE_def parknode[8191];//ͣ��λ��Ϣ
pPARKNODE_def parknode_heap[8192];//ͣ��λ�Ķ����
coord_t entrance_loc;//�������
coord_t exit_loc;//��������
population_def population[POPUNUM];//��ʼ��Ⱥ
int robocnt=3;//�����˵�����
int Tout_p[CARMAX];//����λʱ���
int Tin_p[CARMAX];//�복λʱ���
int ent_sort[CARMAX*2];//����ʱ���˳���1����⣬0�ǳ��⡣��ǰn��������͵õ�m������֪���ǵ�m������¼�����n-m+1�������¼�
int parkcount;//��λ����

int main()
{
    int pathlen,i;
    coord_t startloc,endloc;
    startloc.x=0;
    startloc.y=5;
    endloc.x=5;
    endloc.y=0;
    coord_t coord[STACKDEPTH];

    readdata();
    map_check();


    for(i=0;i<100;i++)
    {
        pathfind(&startloc,&endloc,coord,&pathlen);
    }






    return 1;
}

