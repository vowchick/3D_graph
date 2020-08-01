#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H
#include "structs_and_stuff.h"

void fill_js (Js &J, polygon *p, int n);
int get_k (int i, int j, int trapeze_num, int n);
void get_ijtrapeze (int *i, int *j, int *trapeze_num, int k, int n);

void reduce_sum (int p, int *a, int n);
int allocation_size (int n);
int get_num_of_diag (int k, int n);

int find_ABCD1_points (polygon *p);
double triangle_to_right_triangle_jacob (
        double x1, double y1,     // ->(0, 1)
        double x2, double y2,     // -> (0, 0)
        double x3, double y3,
        int n);    // -> (1, 0)

double ultimate_scalar_counter (double J,
                         double f1, double f2, double f3,
                         double g1, double g2, double g3);
std::function<double (double, double)>
int_to_f (int f_);
#endif // HELPER_FUNCTIONS_H
