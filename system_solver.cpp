#include "system_solver.h"

system_solver::system_solver()
{

}
system_solver::system_solver (double *matrix_, int *I_,
                              double *rhs_, int n_,
                              pthread_barrier_t *barrier_)
{
    matrix = matrix_;
    I = I_;
    rhs = rhs_;
    n = n_;
    barrier = barrier_;
}

