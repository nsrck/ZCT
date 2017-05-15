# include "assignpath.h"

//计算路径和，并对其进行排序
 void  BubbleSort(Path_SqList *L)
 {
    int i,j;
    int flag = 1;
    int a[8192];
    for (i=0;i<parkcount;i++)
    {
        a[i]=L->parknode_list[i]->I_len+L->parknode_list[i]->E_len ;   //先算出所有路径和，方便下面计算
    }
    for(i=0;i<parkcount&&flag;i++)                  //开始冒泡排序
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
 //根据质量选择对应的路径
 int get1pos(int i)     //  i为输入的车的序号
 {
    int assign_range,end_result;
    float percent,assign_mass;          //车质量的重量级
    assign_mass = data_st.car[i].mass;
    percent = (assign_mass-5)/35;
    assign_range = parkcount*percent;
   end_result=rand()%assign_range;
   return end_result;                            //返回第几个parknode_list
 }



