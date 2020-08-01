#ifndef THREAD_INFO_H
#define THREAD_INFO_H
#include "helper_functions.h"

struct thread_info
{
  int n;
  int p;
  int idx;
  std::function<double (double, double)> f;
  double eps;
  grid *gr;
  pthread_barrier_t *barrier;
};
void *
pthread_func (void *arg);
#endif // THREAD_INFO_H
