#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H
#include "helper_functions.h"
#include <math.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
void
fill_the_matrix_msr_format (double *matrix,     //pointer to the matrix
                            int *I,
                            int n,              //number of points
                            polygon Polygon);
double
triangle_to_right_triangle_jacob (
        double x1, double y1,     // ->(0, 1)
        double x2, double y2,     // -> (0, 0)
        double x3, double y3,
        int n);    // -> (1, 0)
double
ultimate_scalar_counter (double J,
                         double f1, double f2, double f3,
                         double g1, double g2, double g3);
int get_off_diag (int n, int k, double *a_diag, double *a,
                  int *I, us u);
void
fill_js (Js &j, polygon p, int n);
void
fill_us (Js &j, us &us);
int
get_k (int i, int j, int trapeze_num, int n);
void
get_ijtrapeze (int *i, int *j, int *trapeze_num, int k, int n);
int
get_num_of_diag (int k, int n);
int
allocation_size (int n);
void
carcass (int n, int *I);
void fill_MSR_matrix (int n, double *a, int *I,
                      int p, int k, us u);
void reduce_sum (int p, int *a, int n);
#endif // MATRIX_OPERATIONS_H
