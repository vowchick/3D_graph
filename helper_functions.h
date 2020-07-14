#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <iostream>
#include "defines.h"
struct point;
struct polygon;
struct input;
struct Js;
struct us;
int find_ABCD1_points (polygon *p);
double get_u (int odd, int trapeze_num, us u);
struct point
{
    double x;
    double y;
};
struct us
{
    double BbC;
    double AaB;
    double Bab;
    double Cbc;
    double CcD;
    double Dcd;
    double DdA;
    double Ada;
};
struct Js
{
    double AaB;
    double Bab;
    double BbC;
    double Cbc;
    double CcD;
    double Dcd;
    double DdA;
    double Ada;
};

struct polygon
{
    point A;
    point B;
    point C;
    point D;
    double k;
    point a;
    point b;
    point c;
    point d;
//    point A1;  //aA1 || bB and is on AB
//    point B1;  //bB1 || cC and is on BC
//    point C1;  //cC1 || dD and is on CD
//    point D1;  //dD1 || aD and is on DA
};
struct input
{
    int nx;
    int ny;
    int k;
    int p;
    double eps;
    char *file_name;
};
#endif // HELPER_FUNCTIONS_H
