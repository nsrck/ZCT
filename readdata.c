#include "readdata.h"

char prmap[]="PBIEX";

//void readdata(data_st_def * data_st)
void readdata(void)
{
    int k,p,a,b,w,h,i,j,carnum;
    int tmp;
    FILE *pFile=fopen(".//data//4.txt","r"); //获取文件的指针
    char *pBuf;  //定义文件buff

    pBuf=(char *)malloc(128);



    fscanf(pFile,"%d %d %d %d",&k,&p,&a,&b);
    printf("k=%d p=%d a=%d b=%d \r\n",k,p,a,b);  //显示读到的数据
    fscanf(pFile,"%d %d",&h,&w);
    printf("h=%d w=%d \r\n",h,w);  //显示读到的数据


//    pmap=(mapsta **)malloc(sizeof(mapsta *)*h);//构建地图数组
//    pmap[0]=(mapsta *)malloc(w*h*sizeof(mapsta));
//    for(i=1;i<h;i++)pmap[i]=pmap[0]+i*w;
    fgets(pBuf,128,pFile);


    for(i=0; i<h; i++)
    {
        fgets(pBuf,128,pFile);
        for(j=0; j<w; j++)
        {

            tmp=pBuf[2*j];
            switch(tmp)
            {
            case 'P':
                data_st.pmap[i][j]=P;
                break;
            case 'B':
                data_st.pmap[i][j]=B;
                break;
            case 'I':
                data_st.pmap[i][j]=I;
                break;
            case 'E':
                data_st.pmap[i][j]=E;
                break;
            case 'X':
                data_st.pmap[i][j]=X;
                break;

            }


        }


    }

    for(i=0; i<h; i++)
    {

        for(j=0; j<w; j++)
        {
            switch(data_st.pmap[i][j])
            {
            case P:
                printf("%c ",prmap[0]);
                break;
            case B:
                printf("%c ",prmap[1]);
                break;
            case I:
                printf("%c ",prmap[2]);
                break;
            case E:
                printf("%c ",prmap[3]);
                break;
            case X:
                printf("%c ",prmap[4]);
                break;

            }


        }
        printf("\n");
    }

    fscanf(pFile,"%d",&carnum);
    printf("carnum=%d\r\n",carnum);  //显示读到的数据

    for(i=0; i<carnum; i++)
    {
        fscanf(pFile,"%d %d %d %d %d",&data_st.car[i].ID,&data_st.car[i].T_in,&data_st.car[i].T_out,&data_st.car[i].T_Mwait,&data_st.car[i].mass);
        printf("%d %d %d %d %d\r\n",data_st.car[i].ID,data_st.car[i].T_in,data_st.car[i].T_out,data_st.car[i].T_Mwait,data_st.car[i].mass);

    }


    fclose(pFile); // 关闭文件
    free(pBuf);

    data_st.a=a;
    data_st.b=b;
    data_st.k=k;
    data_st.p=p;
    data_st.carnum=carnum;
    data_st.h=h;
    data_st.w=w;


}


