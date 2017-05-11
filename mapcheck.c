#include "mapcheck.h"
int heapcount=0;
static void _swap( int idx1, int idx2 );

int map_check(void)
{
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
    int lc = 2 * i + 1;       //左孩子节点序号
    int rc = 2 * i + 2;   //右孩子节点序号
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
            filter_dw( min ); //避免调整之后以min为父节点的子树不是堆
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

