#ifndef STRUCTS_AND_STUFF_H
#define STRUCTS_AND_STUFF_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <functional>
#include <memory>
#include "defines.h"
#define MAX_IT 1000
#define max_it 50
struct point;
struct input;
struct Js;
struct us;
struct polygon;
class grid;
struct thread_info;
struct builder_solver_data;
struct ranges;

struct ranges
{
  double max;
  double min;
};

enum func
{
  one,
  x,
  y,
  x_plus_y,
  x_2_plus_y_2__2,
  x_2_plus_y_2,
  exp_x_2_minus_y_2,
  one_div_tw_five
};

struct builder_solver_data
{
  std::unique_ptr<double[]> matrix;
  std::unique_ptr<int[]> I;
  std::unique_ptr<double[]> rhs;
  std::unique_ptr<double[]> x;

  //additional memory
  std::unique_ptr<double[]> u;
  std::unique_ptr<double[]> r;
  std::unique_ptr<double[]> v;
  std::unique_ptr<double[]> buf;
};

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
    double BbC2;
    double AaB2;
    double Bab2;
    double Cbc2;
    double CcD2;
    double Dcd2;
    double DdA2;
    double Ada2;
    double
    get_u2 (int odd, int trapeze_num)
    {
        int num = 2 * trapeze_num + odd;
        switch (num)
          {
            case 0: return AaB2;
            case 1: return Bab2;
            case 2: return BbC2;
            case 3: return Cbc2;
            case 4: return CcD2;
            case 5: return Dcd2;
            case 6: return DdA2;
            case 7: return Ada2;
          }
        abort ();
        return -100;
    }
};
enum state
{
  given_function,
  approximation,
  error,
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
    double get_J (int odd, int trapeze_num)
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
