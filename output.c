#include "output.h"

void output_result(population_def *solu)
{
    FILE *fp;
    int i,j;
    if( (fp=fopen(".//data//result.txt","wt+")) == NULL ){
        printf("Cannot open file, press any key exit!");
        getch();
        exit(1);
    }
    if(mapvalid==0)  //
    {
        fprintf(fp,"NO\n");
    }
    else
    {
        fprintf(fp,"YES\n");
        fprintf(fp,"%d %d %d\n",robocnt ,T_count,W_count);//机器人各数，所有车等待时间T，总能耗W
        for(i=0;i<data_st.carnum;i++) //i<车总数
        {
            if(abortlist[i]==1) //放弃停车
            {
                fprintf(fp,"%d yes\n",data_st.car[i].ID);//输出yes结束改行
            }
            else // 不放弃停车
            {
                 fprintf(fp,"%d no %d %d",data_st.car[i].ID,solu->robo_sche[i], data_st.car[i].T_in+T1[i]);  //停车序号,入库泊车机器人编号（0开始）

                 for(j=0;j<parknode_list[solu->Car_parkpos[i]]->I_len;j++)
                 {
                     fprintf(fp," (%d,%d)",parknode_list[solu->Car_parkpos[i]]->I_Path[j].y,parknode_list[solu->Car_parkpos[i]]->I_Path[j].x);
                 }
                 fprintf(fp," (%d,%d)",parknode_list[solu->Car_parkpos[i]]->loc.y,parknode_list[solu->Car_parkpos[i]]->loc.x);
                 fprintf(fp," %d %d",solu->robo_sche[i+data_st.carnum], Tout_p[i]);     //出库泊车机器人编号  出库时间点
                 fprintf(fp," (%d,%d)",parknode_list[solu->Car_parkpos[i]]->loc.y,parknode_list[solu->Car_parkpos[i]]->loc.x);
                 for(j=0;j<parknode_list[solu->Car_parkpos[i]]->E_len;j++)
                 {
                    fprintf(fp," (%d,%d)",parknode_list[solu->Car_parkpos[i]]->E_Path[j].y,parknode_list[solu->Car_parkpos[i]]->E_Path[j].x);
                 }
                 fprintf(fp,"\n");
              //  data_st.car[i].ID;  //停车序号
             //   solu->robo_sche[i];//入库泊车机器人编号（0开始）
             //   Tin_p[i];//入库时间点（机器人从入库出搬运的时间点）
               // parknode_list[solu->Car_parkpos[i]].I_Path;//入库路径
               // solu->robo_sche[i+data_st.carnum];//出库泊车机器人编号
              //  Tout_p[i];//出库时间点（泊车机器人从车位搬运的时间点）
              //  parknode_list[solu->Car_parkpos[i]].E_Path;//出库路径
            }
        }

    }
    fflush(fp);
    fclose(fp);
}


