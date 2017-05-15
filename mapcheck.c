#include "mapcheck.h"
int heapcount=0;
static void _swap( int idx1, int idx2 );

int map_check(void)
{
    int i,j,count_X,count_I=0,count_E=0;
    parkcount=0;
    int h=data_st.h;
    int w=data_st.w;
    int temp=0;
    /*       1.�жϳ����        */
    for(i=0; i<h; i++)
    {
        for(j=0; j<w; j++)
        {
            if(data_st.pmap[i][j]==I) {count_I++;entrance_loc.y=i;entrance_loc.x=j;}
            if(data_st.pmap[i][j]==E) {count_E++;exit_loc.y=i;exit_loc.x=j;}
        }
    }
    if(count_I!=1||count_E!=1) {return 0;}//������Ƿ�Ψһ
    if(entrance_loc.x!=0&&entrance_loc.y!=0&&entrance_loc.x!=w-1&&entrance_loc.y!=h-1) {return 0;}//����Ƿ��ڱ߽�
    if(exit_loc.x!=0&&exit_loc.y!=0&&exit_loc.x!=w-1&&exit_loc.y!=h-1) {return 0;}//�����Ƿ��ڱ߽�
    //printf("\nI:(%d,%d)\nE:(%d,%d)\ncount_I=%d,count_E=%d",entrance_loc.x,entrance_loc.y,exit_loc.x,exit_loc.y,count_I,count_E);
    //XXXXX��ͼ��Ч!!XXXXX
    /*       2.�жϳ�λ        */
     for(i=0; i<h; i++)
    {
        for(j=0; j<w; j++)
        {
            count_X=0;
            temp=0;
            if(i==0&&j==0&&data_st.pmap[i][j]==P)//����1
            {
                if(data_st.pmap[i][j+1]==X) {count_X ++;parkcount ++;parknode[parkcount-1].I_loc.y=i;parknode[parkcount-1].I_loc.x=j+1;parknode[parkcount-1].loc.y=i;parknode[parkcount-1].loc.x=j;temp=map_data();}
                if(data_st.pmap[i+1][j]==X) {count_X ++;parkcount ++;parknode[parkcount-1].I_loc.y=i+1;parknode[parkcount-1].I_loc.x=j;parknode[parkcount-1].loc.y=i;parknode[parkcount-1].loc.x=j;temp=map_data();}
                if(count_X!=1||temp==0) {return 0;}
                }
            if(i==0&&j==w-1&&data_st.pmap[i][j]==P)//����2
                {
                    if(data_st.pmap[i][j-1]==X) {count_X ++;parkcount ++;parknode[parkcount-1].I_loc.y=i;parknode[parkcount-1].I_loc.x=j-1;parknode[parkcount-1].loc.y=i;parknode[parkcount-1].loc.x=j;temp=map_data();}
                    if(data_st.pmap[i+1][j]==X) {count_X ++;parkcount ++;parknode[parkcount-1].I_loc.y=i+1;parknode[parkcount-1].I_loc.x=j;parknode[parkcount-1].loc.y=i;parknode[parkcount-1].loc.x=j;temp=map_data();}
                    if(count_X!=1||temp==0) {return 0;}
                    //XXXXX��ͼ��Ч!!XXXXX
                    }
            if(i==0&&j!=0&&j!=w-1&&data_st.pmap[i][j]==P)//�ϱ߽�
                {
                    if(data_st.pmap[i][j-1]==X) {count_X ++;parkcount ++;parknode[parkcount-1].I_loc.y=i;parknode[parkcount-1].I_loc.x=j-1;parknode[parkcount-1].loc.y=i;parknode[parkcount-1].loc.x=j;temp=map_data();}
                    if(data_st.pmap[i][j+1]==X) {count_X ++;parkcount ++;parknode[parkcount-1].I_loc.y=i;parknode[parkcount-1].I_loc.x=j+1;parknode[parkcount-1].loc.y=i;parknode[parkcount-1].loc.x=j;temp=map_data();}
                    if(data_st.pmap[i+1][j]==X) {count_X ++;parkcount ++;parknode[parkcount-1].I_loc.y=i+1;parknode[parkcount-1].I_loc.x=j;parknode[parkcount-1].loc.y=i;parknode[parkcount-1].loc.x=j;temp=map_data();}
                    if(count_X!=1||temp==0) {return 0;}
                }
            if(i==h-1&&j==0&&data_st.pmap[i][j]==P)
            {
                if(data_st.pmap[i][j+1]==X) {count_X ++;parkcount ++;parknode[parkcount-1].I_loc.y=i;parknode[parkcount-1].I_loc.x=j+1;parknode[parkcount-1].loc.y=i;parknode[parkcount-1].loc.x=j;temp=map_data();}
                if(data_st.pmap[i-1][j]==X) {count_X ++;parkcount ++;parknode[parkcount-1].I_loc.y=i-1;parknode[parkcount-1].I_loc.x=j;parknode[parkcount-1].loc.y=i;parknode[parkcount-1].loc.x=j;temp=map_data();}
                if(count_X!=1||temp==0) {return 0;}
                }
            if(i==h-1&&j==w-1&&data_st.pmap[i][j]==P)//����4
                {
                    if(data_st.pmap[i][j-1]==X) {count_X ++;parkcount ++;parknode[parkcount-1].I_loc.y=i;parknode[parkcount-1].I_loc.x=j-1;parknode[parkcount-1].loc.y=i;parknode[parkcount-1].loc.x=j;temp=map_data();}
                    if(data_st.pmap[i-1][j]==X) {count_X ++;parkcount ++;parknode[parkcount-1].I_loc.y=i-1;parknode[parkcount-1].I_loc.x=j;parknode[parkcount-1].loc.y=i;parknode[parkcount-1].loc.x=j;temp=map_data();}
                    if(count_X!=1||temp==0) {return 0;}
                }
            if(i==h-1&&j!=0&&j!=w-1&&data_st.pmap[i][j]==P)//�±߽�
                {
                    if(data_st.pmap[i][j-1]==X) {count_X ++;parkcount ++;parknode[parkcount-1].I_loc.y=i;parknode[parkcount-1].I_loc.x=j-1;parknode[parkcount-1].loc.y=i;parknode[parkcount-1].loc.x=j;temp=map_data();}
                    if(data_st.pmap[i][j+1]==X) {count_X ++;parkcount ++;parknode[parkcount-1].I_loc.y=i;parknode[parkcount-1].I_loc.x=j+1;parknode[parkcount-1].loc.y=i;parknode[parkcount-1].loc.x=j;temp=map_data();}
                    if(data_st.pmap[i-1][j]==X) {count_X ++;parkcount ++;parknode[parkcount-1].I_loc.y=i-1;parknode[parkcount-1].I_loc.x=j;parknode[parkcount-1].loc.y=i;parknode[parkcount-1].loc.x=j;temp=map_data();}
                    if(count_X!=1||temp==0) {return 0;}
                }
            if(j==0&&i!=0&&i!=h-1&&data_st.pmap[i][j]==P)//��߽�
            {
                if(data_st.pmap[i-1][j]==X) {count_X ++;parkcount ++;parknode[parkcount-1].I_loc.y=i-1;parknode[parkcount-1].I_loc.x=j;parknode[parkcount-1].loc.y=i;parknode[parkcount-1].loc.x=j;temp=map_data();}
                if(data_st.pmap[i+1][j]==X) {count_X ++;parkcount ++;parknode[parkcount-1].I_loc.y=i+1;parknode[parkcount-1].I_loc.x=j;parknode[parkcount-1].loc.y=i;parknode[parkcount-1].loc.x=j;temp=map_data();}
                if(data_st.pmap[i][j+1]==X) {count_X ++;parkcount ++;parknode[parkcount-1].I_loc.y=i;parknode[parkcount-1].I_loc.x=j+1;parknode[parkcount-1].loc.y=i;parknode[parkcount-1].loc.x=j;temp=map_data();}
                if(count_X!=1||temp==0) {return 0;}
            }
            if(j==w-1&&i!=0&&i!=h-1&&data_st.pmap[i][j]==P)//�ұ߽�
            {
                if(data_st.pmap[i-1][j]==X) {count_X ++;parkcount ++;parknode[parkcount-1].I_loc.y=i-1;parknode[parkcount-1].I_loc.x=j;parknode[parkcount-1].loc.y=i;parknode[parkcount-1].loc.x=j;temp=map_data();}
                if(data_st.pmap[i+1][j]==X) {count_X ++;parkcount ++;parknode[parkcount-1].I_loc.y=i+1;parknode[parkcount-1].I_loc.x=j;parknode[parkcount-1].loc.y=i;parknode[parkcount-1].loc.x=j;temp=map_data();}
                if(data_st.pmap[i][j-1]==X) {count_X ++;parkcount ++;parknode[parkcount-1].I_loc.y=i;parknode[parkcount-1].I_loc.x=j-1;parknode[parkcount-1].loc.y=i;parknode[parkcount-1].loc.x=j;temp=map_data();}
                if(count_X!=1||temp==0) {return 0;}
            }
            if(j!=0&&i!=0&&i!=h-1&&j!=w-1&&data_st.pmap[i][j]==P)//�ڲ���
            {
                if(data_st.pmap[i-1][j]==X) {count_X ++;parkcount ++;parknode[parkcount-1].I_loc.y=i-1;parknode[parkcount-1].I_loc.x=j;parknode[parkcount-1].loc.y=i;parknode[parkcount-1].loc.x=j;temp=map_data();}
                if(data_st.pmap[i][j-1]==X) {count_X ++;parkcount ++;parknode[parkcount-1].I_loc.y=i;parknode[parkcount-1].I_loc.x=j-1;parknode[parkcount-1].loc.y=i;parknode[parkcount-1].loc.x=j;temp=map_data();}
                if(data_st.pmap[i+1][j]==X) {count_X ++;parkcount ++;parknode[parkcount-1].I_loc.y=i+1;parknode[parkcount-1].I_loc.x=j;parknode[parkcount-1].loc.y=i;parknode[parkcount-1].loc.x=j;temp=map_data();}
                if(data_st.pmap[i][j+1]==X) {count_X ++;parkcount ++;parknode[parkcount-1].I_loc.y=i;parknode[parkcount-1].I_loc.x=j+1;parknode[parkcount-1].loc.y=i;parknode[parkcount-1].loc.x=j;temp=map_data();}
                if(count_X!=1||temp==0) {return 0;}
            }

        }
    }

    return 1;
}
int map_data(void)//1:��·�� 0:��·��
{
    int m=parkcount-1;
    int temp1=0,temp2=0;
    temp1=pathfind(&entrance_loc,&(parknode[m].I_loc),parknode[m].I_Path,&(parknode[m].I_len));
    temp2=pathfind(&(parknode[m].I_loc),&exit_loc,parknode[m].E_Path,&(parknode[m].E_len));
    if(temp1&&temp2)
        return 1;
    else
        return 0;
}

int abort_map(void)
{
    printf("Invalid map!!\n");
    printf("�˳��㣺(%d,%d)",parknode[parkcount-1].loc.y,parknode[parkcount-1].loc.x);//��Գ�λ�����������ο�
    return 1;
}


int heapgene(void)
{
    int i=0;
    for(i=0;i<parkcount;i++)
    {
        parknode_heap[heapcount++]=&parknode[i];
        filter_up(heapcount-1);
    }
    return 1;

}
void filter_dw( int i )
{
    int lc = 2 * i + 1;       //���ӽڵ����
    int rc = 2 * i + 2;   //�Һ��ӽڵ����
    int min = i;

    if( i < heapcount / 2 )
    {
        if( lc < heapcount && parknode_heap[lc]->E_len + parknode_heap[lc]->I_len > parknode_heap[min]->E_len + parknode_heap[min]->I_len )
        {
            min = lc;
        }
        if( rc < heapcount && parknode_heap[rc]->E_len + parknode_heap[rc]->I_len > parknode_heap[min]->E_len + parknode_heap[min]->I_len )
        {
            min = rc;
        }
        if( min != i )
        {
            _swap( i, min );
            filter_dw( min ); //�������֮����minΪ���ڵ���������Ƕ�
        }
    }
}
void filter_up(int start)
{
    int c=start;
    int p=(start-1)/2;
    int tmp=parknode_heap[c]->I_len+parknode_heap[c]->E_len;
    if(c>0)
    {
        if((parknode_heap[p]->I_len+parknode_heap[p]->E_len) > tmp)

            _swap(c,p);
            filter_up(p);
    }
}
void _swap( int idx1, int idx2 )
{
    pPARKNODE_def tmp = parknode_heap[idx1];
    parknode_heap[idx1] = parknode_heap[idx2];
    parknode_heap[idx2] = tmp;
}
