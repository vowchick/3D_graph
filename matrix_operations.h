#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H
#include "helper_functions.h"
void msr_matrix_mult_vector (double *A, int *I, int M,
                             double *x, double *b, int k,
                             int p,
                             pthread_barrier_t *barrier);
int msr_apply_preconditioner (
                          double *A, int n,
                          double *x, double *b,
                          int k, int p,
                          pthread_barrier_t *barrier);
double scalar_product (double *x, double *y, int n,
                       int p, int k, double *buf,
                       pthread_barrier_t *barrier);
void linear_combination (double *x, double *y,
                         int n, double a,
                         int p, int k,
                         pthread_barrier_t *barrier);
int check_matrix (double *a, int *I, int n, int p, int k);
void print_matrix (int matrix_size, double *a, int *I);
#endif // MATRIX_OPERATIONS_H
