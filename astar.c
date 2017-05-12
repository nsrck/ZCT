#include "astar.h"

    pAStarNode open_table[LISTLENGTH];			// open表
    pAStarNode close_table[LISTLENGTH];		// close表

    int		   open_node_count=0;			// open表中节点数量
    int		   close_node_count=0;		// close表中结点数量
//    AStarNode **pmapnode;
    AStarNode pmapnode[100][100];

 //private
static void adjust_heap( int i );
static void filter_up(int start);
static void _swap( int idx1, int idx2 );
static void insert_to_opentable( int x, int y, pAStarNode curr_node, pAStarNode end_node, int w );
static void get_neighbors( pAStarNode curr_node, pAStarNode end_node );

int pathfind(coord_t *S,coord_t *E,coord_t coord[],int *pathlen)
{

    pAStarNode path_stack[STACKDEPTH];			// 保存路径的栈
    int        top = -1;				// 栈顶
    AStarNode *start_node;			// 起始点
    AStarNode *end_node;			// 结束点
    AStarNode *curr_node;			// 当前点
    int       is_found;				// 是否找到路径
    int i,j;


//    pmapnode=(AStarNode **)malloc(sizeof(AStarNode *)*data_st.h);//构建地图数组
//    pmapnode[0]=(AStarNode *)malloc(data_st.w*data_st.h*sizeof(AStarNode));
//    for(i=1;i<data_st.h;i++)pmapnode[i]=pmapnode[0]+i*data_st.w;

    for( i = 0; i < data_st.h; ++i )
	{
		for ( j = 0; j < data_st.w; ++j )
		{
			pmapnode[i][j].s_g = 0;
			pmapnode[i][j].s_h = 0;
			pmapnode[i][j].s_is_in_closetable = 0;
			pmapnode[i][j].s_is_in_opentable = 0;
			pmapnode[i][j].s_style = data_st.pmap[i][j];
			pmapnode[i][j].s_x = j;
			pmapnode[i][j].s_y = i;
			pmapnode[i][j].s_parent = NULL;


			if ( pmapnode[i][j].s_style == STARTNODE )		// 起点抹去
			{
				pmapnode[i][j].s_style=ROAD;
			}
			else if( pmapnode[i][j].s_style == ENDNODE )	// 终点抹去
			{
				pmapnode[i][j].s_style=ROAD;
			}

		}


	}
	pmapnode[S->y][S->x].s_style = STARTNODE;//设置起点和终点
	start_node = &(pmapnode[S->y][S->x]);
	pmapnode[E->y][E->x].s_style = ENDNODE;
	end_node = &(pmapnode[E->y][E->x]);


    // 下面使用A*算法得到路径
    //
    open_table[open_node_count++] = start_node;			// 起始点加入open表

    start_node->s_is_in_opentable = 1;					// 加入open表
    start_node->s_g = 0;
    start_node->s_h = abs(end_node->s_x - start_node->s_x) + abs(end_node->s_y - start_node->s_y);
    start_node->s_parent = NULL;

    if ( start_node->s_x == end_node->s_x && start_node->s_y == end_node->s_y )
    {
 //       printf("起点==终点！\n");
        return 0;
    }

    is_found = 0;

    while( 1 )
    {
        curr_node = open_table[0];						// open表的第一个点一定是f值最小的点(通过堆排序得到的)
        open_table[0] = open_table[--open_node_count];	// 最后一个点放到第一个点，然后进行堆调整
        adjust_heap( 0 );								// 调整堆

        close_table[close_node_count++] = curr_node;	// 当前点加入close表
        curr_node->s_is_in_closetable = 1;				// 已经在close表中了

        if ( curr_node->s_x == end_node->s_x && curr_node->s_y == end_node->s_y )	// 终点在close中，结束
        {
            is_found = 1;
            break;
        }

        get_neighbors( curr_node, end_node );			// 对邻居的处理
 //       adjust_heap( 0 );
        if ( open_node_count == 0 )						// 没有路径到达
        {
            is_found = 0;
            break;
        }
    }

    if ( is_found )
    {
        curr_node = end_node;

        i=0;
        while( curr_node )
        {
            path_stack[++top] = curr_node;
            curr_node = curr_node->s_parent;
        }

        while( top >= 0 )
        {
            if ( top > 0 )
            {
                coord[i].x=path_stack[top]->s_x;
                coord[i].y=path_stack[top]->s_y;
                i++;


//                printf("(%d,%d)-->", path_stack[top]->s_x, path_stack[top]->s_y);

                top--;
            }
            else
            {

//                printf("(%d,%d)", path_stack[top]->s_x, path_stack[top]->s_y);

                coord[i].x=path_stack[top]->s_x;
                coord[i].y=path_stack[top]->s_y;
                i++;
                *pathlen=i;
                top--;
                coord[i].x=32767;
                coord[i].y=32767;
                i=0;
            }
        }
//        memset(open_table,0,sizeof(pAStarNode)*LISTLENGTH);
//        memset(close_table,0,sizeof(pAStarNode)*LISTLENGTH);
        open_node_count=0;
        close_node_count=0;
//        free(pmapnode[0]);
//        free(pmapnode);
        return 1;
    }
    else
    {
//        printf("么有找到路径");
//        memset(open_table,0,sizeof(pAStarNode)*LISTLENGTH);
//        memset(close_table,0,sizeof(pAStarNode)*LISTLENGTH);
        open_node_count=0;
        close_node_count=0;

//        free(pmapnode[0]);
//        free(pmapnode);
        return 0;

    }


}

// 交换两个元素
//
void _swap( int idx1, int idx2 )
{
    pAStarNode tmp = open_table[idx1];
    open_table[idx1] = open_table[idx2];
    open_table[idx2] = tmp;
}

// 堆调整
//
void filter_up(int start)
{
    int c=start;
    int p=(start-1)/2;
    int tmp=open_table[c]->s_g+open_table[c]->s_h;
    if(c>0)
    {
        if((open_table[p]->s_g+open_table[p]->s_h) > tmp)

            _swap(c,p);
            filter_up(p);
    }

}

void adjust_heap( int i )
{
    int lc = 2 * i + 1;       //左孩子节点序号
    int rc = 2 * i + 2;   //右孩子节点序号
    int min = i;

    if( i < open_node_count/2  )
    {
        if( lc < open_node_count && open_table[lc]->s_g + open_table[lc]->s_h > open_table[min]->s_g + open_table[min]->s_h )
        {
            min = lc;
        }
        if( rc < open_node_count && open_table[rc]->s_g + open_table[rc]->s_h > open_table[min]->s_g + open_table[min]->s_h )
        {
            min = rc;
        }
        if( min != i )
        {
            _swap( i, min );
            adjust_heap( min ); //避免调整之后以min为父节点的子树不是堆
        }
    }
}
// 判断邻居点是否可以进入open表
//
void insert_to_opentable( int x, int y, pAStarNode curr_node, pAStarNode end_node, int w )
{
    int i;

    if ( pmapnode[y][x].s_style != BARRIER && pmapnode[y][x].s_style != PARK)		// 不是障碍物也不是停车点
    {
        if ( !pmapnode[y][x].s_is_in_closetable )	// 不在闭表中
        {
            if ( pmapnode[y][x].s_is_in_opentable )	// 在open表中
            {
                // 需要判断是否是一条更优化的路径
                //
                if ( pmapnode[y][x].s_g > curr_node->s_g + w )	// 如果更优化
                {
                    pmapnode[y][x].s_g = curr_node->s_g + w;
                    pmapnode[y][x].s_parent = curr_node;

                    for ( i = 0; i < open_node_count; ++i )
                    {
                        if ( open_table[i]->s_x == pmapnode[y][x].s_x && open_table[i]->s_y == pmapnode[y][x].s_y )
                        {
                            break;
                        }
                    }

                    adjust_heap( i );					// 下面调整点
                }
            }
            else										// 不在open中
            {
                pmapnode[y][x].s_g = curr_node->s_g + w;
                pmapnode[y][x].s_h = abs(end_node->s_x - x ) + abs(end_node->s_y - y);
                pmapnode[y][x].s_parent = curr_node;
                pmapnode[y][x].s_is_in_opentable = 1;
                open_table[open_node_count++] = &(pmapnode[y][x]);
                filter_up(open_node_count-1);
            }
        }
    }
}

// 查找邻居
// 对上下左右8个邻居进行查找
//
void get_neighbors( pAStarNode curr_node, pAStarNode end_node )
{
    int x = curr_node->s_x;
    int y = curr_node->s_y;

    if ( ( x + 1 ) >= 0 && ( x + 1 ) < data_st.w && y >= 0 && y < data_st.h )
    {
        insert_to_opentable( x+1, y, curr_node, end_node, 10 );
    }

    if ( ( x - 1 ) >= 0 && ( x - 1 ) < data_st.w && y >= 0 && y < data_st.h )
    {
        insert_to_opentable( x-1, y, curr_node, end_node, 10 );
    }

    if ( x >= 0 && x < data_st.w && ( y + 1 ) >= 0 && ( y + 1 ) < data_st.h )
    {
        insert_to_opentable( x, y+1, curr_node, end_node, 10 );
    }

    if ( x >= 0 && x < data_st.w && ( y - 1 ) >= 0 && ( y - 1 ) < data_st.h )
    {
        insert_to_opentable( x, y-1, curr_node, end_node, 10 );
    }

//    if ( ( x + 1 ) >= 0 && ( x + 1 ) < data_st.w && ( y + 1 ) >= 0 && ( y + 1 ) < data_st.h )
//    {
//        insert_to_opentable( x+1, y+1, curr_node, end_node, 14 );
//    }
//
//    if ( ( x + 1 ) >= 0 && ( x + 1 ) < data_st.w && ( y - 1 ) >= 0 && ( y - 1 ) < data_st.h )
//    {
//        insert_to_opentable( x+1, y-1, curr_node, end_node, 14 );
//    }
//
//    if ( ( x - 1 ) >= 0 && ( x - 1 ) < data_st.w && ( y + 1 ) >= 0 && ( y + 1 ) < data_st.h )
//    {
//        insert_to_opentable( x-1, y+1, curr_node, end_node, 14 );
//    }
//
//    if ( ( x - 1 ) >= 0 && ( x - 1 ) < data_st.w && ( y - 1 ) >= 0 && ( y - 1 ) < data_st.h )
//    {
//        insert_to_opentable( x-1, y-1, curr_node, end_node, 14 );
//    }
}

