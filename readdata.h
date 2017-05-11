#ifndef READDATA_H_INCLUDED
#define READDATA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "astar.h"


typedef    struct
{
    int ID;
    int T_in;
    int T_out;
    int T_Mwait;
    int mass;
} car_property;

typedef enum  {P=0,B,I,E,X} mapsta;

typedef struct
{
    int k;
    int p;
    int a;
    int b;
    int w;
    int h;
    int carnum;
//    mapsta **pmap;
    mapsta pmap[100][100];
    car_property car[4095];
}data_st_def;



extern  data_st_def data_st;
void readdata(data_st_def * data_st);
//private


#endif // READDATA_H_INCLUDED
