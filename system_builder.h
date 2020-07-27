#ifndef MSR_MATRIX_BUILDER_H
#define MSR_MATRIX_BUILDER_H
#include "helper_functions.h"

#include "grid.h"
#include <math.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

class system_builder
{

public:
    system_builder() = default;
    system_builder (int n_, polygon *p_, std::function<double (double, double)> f,
                    double *matrix_, double *rhs_, int *I_);
    ~system_builder();

    void fill_MSR_matrix (int p, int k);
    void fill_rhs (int p, int idx);

    void set_matrix (double *matrix_) {matrix = matrix_;}
    void set_rhs (double *rhs_) {rhs = rhs_;}
    void set_I (int *I_) {I = I_;}
    void set_all (double *matrix_, int *I_, double *rhs_) {matrix = matrix_; rhs = rhs_; I = I_;}


private:

    double fill_rhs_at (int k);
    int  get_num_of_diag (int k);
    int allocation_size ();


    void carcass ();

    int get_off_diag (int k, double *a_diag, double *a,
                      int *I);


private:
    int n = 0;
    double *matrix = nullptr;
    int *I = nullptr;
    double *rhs = nullptr;
    grid *gr;
    std::function<double (double, double)> f;
};

#endif // MSR_MATRIX_BUILDER_H
