#ifndef SYSTEM_SOLVER_H
#define SYSTEM_SOLVER_H

#include "matrix_operations.h"

class system_solver
{
public:
    system_solver() = default;
    system_solver (double *matrix_, int *I_,
                   double *x_,
                   double *rhs_, int n_,
                   double *u_, double *r_, double *v_,
                   double *buf,
                   pthread_barrier_t *barrier_,
                   int p_,
                   double eps_);
    ~system_solver ();

    int solve (int MAXIT, int k);

private:
    void initialize ();
    int solve_stage (int k, int maxit);
private:
    double *matrix = nullptr;
    int *I = nullptr;
    double *rhs = nullptr;
    double *x;
    int n = 0;
    int p = 0;
    double eps = 0;
    pthread_barrier_t *barrier;

    //additional memory
    double *u = nullptr;
    double *r = nullptr;
    double *v = nullptr;
    double *buf = nullptr;
};

#endif // SYSTEM_SOLVER_H
