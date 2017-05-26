#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "gene.h"
#include "solve.h"
#include "mapcheck.h"
#include "readdata.h"
#include "output.h"

data_st_def data_st;
PARKNODE_def parknode[8191];//ͣ��λ��Ϣ
pPARKNODE_def parknode_heap[8192];//ͣ��λ�Ķ����
pPARKNODE_def parknode_list[8192];//ͣ��λ��˳���
coord_t entrance_loc;//�������
coord_t exit_loc;//��������
int pathlen_StoE;
coord_t path_StoE[STACKDEPTH];
population_def population[POPUNUM];//��ʼ��Ⱥ
int robocnt=4;//�����˵�����
int Tout_p[CARMAX]={0};//����λʱ���
int Tin_p[CARMAX]={0};//�복λʱ���
int T1[CARMAX]={0};//�ȴ�ʱ��
int T2[CARMAX]={0};//�ȴ�ʱ��
int ent_sort[CARMAX*2]={0};//����ʱ���˳���
int parkcount;//��λ����
int mapvalid;
int Z;
int T_count;
int W_count;
void Init_list(void);
void sortent(void);
int main()
{
//    int pathlen,i;
//    coord_t startloc,endloc;
//    startloc.x=3;
//    startloc.y=1;
//    endloc.x=4;
//    endloc.y=1;
//    coord_t coord[STACKDEPTH];

    readdata();


    if(map_check()==0)
    {
        mapvalid=0;
    }

    else
    {
        mapvalid=1;
        sortent();
        Init_list();
        initsolu(&(population[0]));
        roboeval();
//        solvepos(&(population[0]));

    }
    output_result(&(population[0]));


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
    for(i=0; i<data_st.carnum; i++)
    {
        sortst[i].carid=i+1;
        sortst[i].enttype=0;
        sortst[i].T=data_st.car[i].T_in;
    }
    for(i=0; i<data_st.carnum; i++)
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

void  Init_list(void)
{
    pPARKNODE_def swap_temp;
    int i,j,k,q,temp;
    int a[parkcount];
    for(k=0; k<parkcount; k++) //��ʼ��
    {
        parknode_list[k]=&parknode[k];
    }
    for (q=0; q<parkcount; q++)
    {
        a[q]=(parknode_list[q]->I_len+parknode_list[q]->E_len );   //���������·���ͣ������������
    }
    for(i=0; i<parkcount; i++)                //��ʼð������
    {
        for (j =1; j<parkcount-i; j++)
        {
            if (a[j-1]>a[j])
            {
                swap_temp =parknode_list[j-1];
                parknode_list[j-1] = parknode_list[j];
                parknode_list[j] =swap_temp;
                temp = a[j-1];
                a[j-1] = a[j];
                a[j] = temp;
            }
        }
    }
//    for (i=0; i<parkcount; i++)
//    {
//        printf("%d\n",(parknode_list[i]->I_len+parknode_list[i]->E_len)) ;
//        printf("%d\n",a[i]) ;
//        }

}
