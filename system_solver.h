#ifndef SYSTEM_SOLVER_H
#define SYSTEM_SOLVER_H

#include "matrix_operations.h"

class system_solver
{
public:
    system_solver();
    system_solver (double *matrix_, int *I_,
                   double *rhs_, int n_,
                   pthread_barrier_t *barrier_);

private:
private:
    double *matrix = nullptr;
    int *I = nullptr;
    double *rhs = nullptr;
    int n = 0;
    pthread_barrier_t *barrier;
};

#endif // SYSTEM_SOLVER_H
