#include <stdio.h>
#include <stdlib.h>
#include "astar.h"
#include "readdata.h"
#include "mapcheck.h"
#include "main.h"
#include "gene.h"
#include "solve.h"


data_st_def data_st;
PARKNODE_def parknode[8191];//ͣ��λ��Ϣ
pPARKNODE_def parknode_heap[8192];//ͣ��λ�Ķ����
pPARKNODE_def parknode_list[8192];//ͣ��λ��˳���
coord_t entrance_loc;//�������
coord_t exit_loc;//��������
population_def population[POPUNUM];//��ʼ��Ⱥ
int robocnt=3;//�����˵�����
int Tout_p[CARMAX];//����λʱ���
int Tin_p[CARMAX];//�복λʱ���
int T1[CARMAX];//�ȴ�ʱ��
int T2[CARMAX];//�ȴ�ʱ��
int ent_sort[CARMAX*2];//����ʱ���˳���
int parkcount;//��λ����


void sortent(void);
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
//    if(map_check()==0)
//    {
//        abort_map();
//    }
    sortent();
    initsolu(&(population[0]));
    solvepos(&(population[0]));

//
//
//    for(i=0;i<100;i++)
//    {
//        pathfind(&startloc,&endloc,coord,&pathlen);
//    }






    return 1;
}

void sortent(void)
{
    int i,j;
    sortst_def sortst[CARMAX*2];
    sortst_def temp;
    for(i=0;i<data_st.carnum;i++)
    {
        sortst[i].carid=i+1;
        sortst[i].enttype=0;
        sortst[i].T=data_st.car[i].T_in;
    }
        for(i=0;i<data_st.carnum;i++)
    {
        sortst[i+data_st.carnum].carid=i+1;
        sortst[i+data_st.carnum].enttype=1;
        sortst[i+data_st.carnum].T=data_st.car[i].T_out;
    }
    for(i = 0; i < 2*data_st.carnum; i++)
    {
        for(j = 0; j < 2*data_st.carnum - 1 - i; j++)
        {
            if(sortst[j].T > sortst[j + 1].T)
            {
                temp=sortst[j];
                sortst[j]=sortst[j+1];
                sortst[j+1]=temp;
            }
        }
    }
    for(i = 0; i < 2*data_st.carnum; i++)
    {
        if(sortst[i].enttype==0)
        {
            ent_sort[i]=sortst[i].carid;
        }
        else
        {
            ent_sort[i]=-sortst[i].carid;
        }
    }


}

