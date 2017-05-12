#include "astar.h"

    pAStarNode open_table[LISTLENGTH];			// open��
    pAStarNode close_table[LISTLENGTH];		// close��

    int		   open_node_count=0;			// open���нڵ�����
    int		   close_node_count=0;		// close���н������
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

    pAStarNode path_stack[STACKDEPTH];			// ����·����ջ
    int        top = -1;				// ջ��
    AStarNode *start_node;			// ��ʼ��
    AStarNode *end_node;			// ������
    AStarNode *curr_node;			// ��ǰ��
    int       is_found;				// �Ƿ��ҵ�·��
    int i,j;


//    pmapnode=(AStarNode **)malloc(sizeof(AStarNode *)*data_st.h);//������ͼ����
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


			if ( pmapnode[i][j].s_style == STARTNODE )		// ���Ĩȥ
			{
				pmapnode[i][j].s_style=ROAD;
			}
			else if( pmapnode[i][j].s_style == ENDNODE )	// �յ�Ĩȥ
			{
				pmapnode[i][j].s_style=ROAD;
			}

		}


	}
	pmapnode[S->y][S->x].s_style = STARTNODE;//���������յ�
	start_node = &(pmapnode[S->y][S->x]);
	pmapnode[E->y][E->x].s_style = ENDNODE;
	end_node = &(pmapnode[E->y][E->x]);


    // ����ʹ��A*�㷨�õ�·��
    //
    open_table[open_node_count++] = start_node;			// ��ʼ�����open��

    start_node->s_is_in_opentable = 1;					// ����open��
    start_node->s_g = 0;
    start_node->s_h = abs(end_node->s_x - start_node->s_x) + abs(end_node->s_y - start_node->s_y);
    start_node->s_parent = NULL;

    if ( start_node->s_x == end_node->s_x && start_node->s_y == end_node->s_y )
    {
 //       printf("���==�յ㣡\n");
        return 0;
    }

    is_found = 0;

    while( 1 )
    {
        curr_node = open_table[0];						// open��ĵ�һ����һ����fֵ��С�ĵ�(ͨ��������õ���)
        open_table[0] = open_table[--open_node_count];	// ���һ����ŵ���һ���㣬Ȼ����жѵ���
        adjust_heap( 0 );								// ������

        close_table[close_node_count++] = curr_node;	// ��ǰ�����close��
        curr_node->s_is_in_closetable = 1;				// �Ѿ���close������

        if ( curr_node->s_x == end_node->s_x && curr_node->s_y == end_node->s_y )	// �յ���close�У�����
        {
            is_found = 1;
            break;
        }

        get_neighbors( curr_node, end_node );			// ���ھӵĴ���
 //       adjust_heap( 0 );
        if ( open_node_count == 0 )						// û��·������
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
//        printf("ô���ҵ�·��");
//        memset(open_table,0,sizeof(pAStarNode)*LISTLENGTH);
//        memset(close_table,0,sizeof(pAStarNode)*LISTLENGTH);
        open_node_count=0;
        close_node_count=0;

//        free(pmapnode[0]);
//        free(pmapnode);
        return 0;

    }


}

// ��������Ԫ��
//
void _swap( int idx1, int idx2 )
{
    pAStarNode tmp = open_table[idx1];
    open_table[idx1] = open_table[idx2];
    open_table[idx2] = tmp;
}

// �ѵ���
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
    int lc = 2 * i + 1;       //���ӽڵ����
    int rc = 2 * i + 2;   //�Һ��ӽڵ����
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
            adjust_heap( min ); //�������֮����minΪ���ڵ���������Ƕ�
        }
    }
}
// �ж��ھӵ��Ƿ���Խ���open��
//
void insert_to_opentable( int x, int y, pAStarNode curr_node, pAStarNode end_node, int w )
{
    int i;

    if ( pmapnode[y][x].s_style != BARRIER && pmapnode[y][x].s_style != PARK)		// �����ϰ���Ҳ����ͣ����
    {
        if ( !pmapnode[y][x].s_is_in_closetable )	// ���ڱձ���
        {
            if ( pmapnode[y][x].s_is_in_opentable )	// ��open����
            {
                // ��Ҫ�ж��Ƿ���һ�����Ż���·��
                //
                if ( pmapnode[y][x].s_g > curr_node->s_g + w )	// ������Ż�
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

                    adjust_heap( i );					// ���������
                }
            }
            else										// ����open��
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

// �����ھ�
// ����������8���ھӽ��в���
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

