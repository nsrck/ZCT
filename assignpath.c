# include "assignpath.h"

//����·���ͣ��������������
 void  BubbleSort(Path_SqList *L)
 {
    int i,j;
    int flag = 1;
    int a[8192];
    for (i=0;i<parkcount;i++)
    {
        a[i]=L->parknode_list[i]->I_len+L->parknode_list[i]->E_len ;   //���������·���ͣ������������
    }
    for(i=0;i<parkcount&&flag;i++)                  //��ʼð������
    {
        flag =0;
        for (j =parkcount-2;j>=i;j--)
        {
            if (a[j]>a[j+1])
                swap_temp =L->parknode_list[j];
                L->parknode_list[j] = L->parknode_list[j+1];
                L->parknode_list[j+1] =swap_temp;
                flag = 1;
        }
    }

}
 //��������ѡ���Ӧ��·��
 int get1pos(int i)     //  iΪ����ĳ������
 {
    int assign_range,end_result;
    float percent,assign_mass;          //��������������
    assign_mass = data_st.car[i].mass;
    percent = (assign_mass-5)/35;
    assign_range = parkcount*percent;
   end_result=rand()%assign_range;
   return end_result;                            //���صڼ���parknode_list
 }



