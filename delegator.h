#ifndef DELEGATOR_H
#define DELEGATOR_H
#include "system_builder.h"
#include "system_solver.h"

class delegator
{
public:
    delegator();

    delegator (pthread_barrier_t *barrier, polygon *pol, int p, double eps);

    system_solver *get_solver () const {return solver;}
    system_builder *get_builder () const {return builder;}

    int allocate (int n_, std::function<double (double, double)> f);
    void solve (int k);
    void erase ();
    double *get_x () const {return x;}

private:
    system_solver *solver;
    system_builder *builder;
    double *matrix;
    double *rhs;
    int *I;
    int n;
    double *x;
    pthread_barrier_t *barrier;
    polygon *pol;
    int p;
    double eps;
    std::function<double (double, double)> f;
};

#endif // DELEGATOR_H
