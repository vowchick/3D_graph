#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H
#include "helper_functions.h"
#include <math.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
void
fill_the_matrix_msr_format (double *matrix,     //pointer to the matrix
                            int n,              //number of points
                            polygon Polygon);
double
triangle_to_right_triangle_jacob (
        double x1, double y1,     // ->(0, 1)
        double x2, double y2,     // -> (0, 0)
        double x3, double y3);    // -> (1, 0)
double
ultimate_scalar_counter (double J,
                         double f1, double f2, double f3,
                         double g1, double g2, double g3);
void
fill_js (double *J_AaB, double *J_Bab, double *J_BbC,
         double *J_Cbc, double *J_CcD, double *J_Dcd,
         double *J_DdA, double *J_Ada, polygon p);
void
starting_fill (double *matrix, int *start, int n, double u_second,
               double u_main, double u_last, double u_first);
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
#endif // MATRIX_OPERATIONS_H
