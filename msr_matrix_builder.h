#ifndef MSR_MATRIX_BUILDER_H
#define MSR_MATRIX_BUILDER_H
#include "helper_functions.h"
#include <math.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

class msr_matrix_builder
{

public:
    msr_matrix_builder();
    msr_matrix_builder (int n_, polygon *p_);
    ~msr_matrix_builder();

    void fill_MSR_matrix (int p, int k);

private:

    int  get_num_of_diag (int k);
    int allocation_size ();

    void fill_us ();

    void carcass ();

    int get_off_diag (int k, double *a_diag, double *a,
                      int *I);


private:
    int n = 0;
    double *matrix = nullptr;
    int *I = nullptr;
    double *rhs = nullptr;
    us u;
    polygon *pol;
};

#endif // MSR_MATRIX_BUILDER_H
