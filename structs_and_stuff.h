#ifndef STRUCTS_AND_STUFF_H
#define STRUCTS_AND_STUFF_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <functional>
#include "defines.h"
struct point;
struct input;
struct Js;
struct us;
struct polygon;
class grid;

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
    double
    get_u (int odd, int trapeze_num)
    {
        int num = 2 * trapeze_num + odd;
        switch (num)
          {
            case 0: return AaB;
            case 1: return Bab;
            case 2: return BbC;
            case 3: return Cbc;
            case 4: return CcD;
            case 5: return Dcd;
            case 6: return DdA;
            case 7: return Ada;
          }
        abort ();
        return -100;
    }
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
#endif // STRUCTS_AND_STUFF_H
