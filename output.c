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
        fprintf(fp,"%d %d %d\n",robocnt ,T_count,W_count);//�����˸��������г��ȴ�ʱ��T�����ܺ�W
        for(i=0;i<data_st.carnum;i++) //i<������
        {
            if(abortlist[i]==1) //����ͣ��
            {
                fprintf(fp,"%d yes\n",data_st.car[i].ID);//���yes��������
            }
            else // ������ͣ��
            {
                 fprintf(fp,"%d no %d %d",data_st.car[i].ID,solu->robo_sche[i], data_st.car[i].T_in+T1[i]);  //ͣ�����,��Ⲵ�������˱�ţ�0��ʼ��

                 for(j=0;j<parknode_list[solu->Car_parkpos[i]]->I_len;j++)
                 {
                     fprintf(fp," (%d,%d)",parknode_list[solu->Car_parkpos[i]]->I_Path[j].y,parknode_list[solu->Car_parkpos[i]]->I_Path[j].x);
                 }
                 fprintf(fp," (%d,%d)",parknode_list[solu->Car_parkpos[i]]->loc.y,parknode_list[solu->Car_parkpos[i]]->loc.x);
                 fprintf(fp," %d %d",solu->robo_sche[i+data_st.carnum], Tout_p[i]);     //���Ⲵ�������˱��  ����ʱ���
                 fprintf(fp," (%d,%d)",parknode_list[solu->Car_parkpos[i]]->loc.y,parknode_list[solu->Car_parkpos[i]]->loc.x);
                 for(j=0;j<parknode_list[solu->Car_parkpos[i]]->E_len;j++)
                 {
                    fprintf(fp," (%d,%d)",parknode_list[solu->Car_parkpos[i]]->E_Path[j].y,parknode_list[solu->Car_parkpos[i]]->E_Path[j].x);
                 }
                 fprintf(fp,"\n");
              //  data_st.car[i].ID;  //ͣ�����
             //   solu->robo_sche[i];//��Ⲵ�������˱�ţ�0��ʼ��
             //   Tin_p[i];//���ʱ��㣨�����˴��������˵�ʱ��㣩
               // parknode_list[solu->Car_parkpos[i]].I_Path;//���·��
               // solu->robo_sche[i+data_st.carnum];//���Ⲵ�������˱��
              //  Tout_p[i];//����ʱ��㣨���������˴ӳ�λ���˵�ʱ��㣩
              //  parknode_list[solu->Car_parkpos[i]].E_Path;//����·��
            }
        }

    }
    fflush(fp);
    fclose(fp);
}


