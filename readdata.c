#include "readdata.h"

char prmap[]="PBIEX";

void readdata(data_st_def * data_st)
{
    int k,p,a,b,w,h,i,j,carnum;
    mapsta **pmap;
    car_property *car;
    int tmp;
    FILE *pFile=fopen(".//data//4.txt","r"); //获取文件的指针
    char *pBuf;  //定义文件buff

    pBuf=(char *)malloc(128);



    fscanf(pFile,"%d %d %d %d",&k,&p,&a,&b);
    printf("k=%d p=%d a=%d b=%d \r\n",k,p,a,b);  //显示读到的数据
    fscanf(pFile,"%d %d",&h,&w);
    printf("h=%d w=%d \r\n",h,w);  //显示读到的数据

    pmap=(mapsta **)malloc(sizeof(mapsta *)*h);//构建地图数组
    pmap[0]=(mapsta *)malloc(w*h*sizeof(mapsta));
    for(i=1;i<h;i++)pmap[i]=pmap[0]+i*w;
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
                pmap[i][j]=P;
                break;
            case 'B':
                pmap[i][j]=B;
                break;
            case 'I':
                pmap[i][j]=I;
                break;
            case 'E':
                pmap[i][j]=E;
                break;
            case 'X':
                pmap[i][j]=X;
                break;

            }


        }


    }

    for(i=0; i<h; i++)
    {

        for(j=0; j<w; j++)
        {
            switch(pmap[i][j])
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
    car=(car_property *)malloc(sizeof(car_property)*carnum);

    for(i=0; i<carnum; i++)
    {
        fscanf(pFile,"%d %d %d %d %d",&car[i].ID,&car[i].T_in,&car[i].T_out,&car[i].T_Mwait,&car[i].mass);
        printf("%d %d %d %d %d\r\n",car[i].ID,car[i].T_in,car[i].T_out,car[i].T_Mwait,car[i].mass);

    }


    fclose(pFile); // 关闭文件
    free(pBuf);

    data_st->a=a;
    data_st->b=b;
    data_st->k=k;
    data_st->p=p;
    data_st->carnum=carnum;
    data_st->h=h;
    data_st->w=w;
    data_st->pmap=pmap;
    data_st->car=car;

}


