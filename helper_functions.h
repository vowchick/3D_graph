#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
struct point;
struct polygon;
int
find_ABCD1_points (polygon *p);

int
read_polygon_from_file (char *file_name,
                        polygon *Polygon);
void
print_polygon (polygon P);
int
find_inside_points (polygon *p);
int
find_middle (polygon *p, point *middle);
struct point
{
    double x;
    double y;
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
#endif // HELPER_FUNCTIONS_H
