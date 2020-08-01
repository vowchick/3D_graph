#ifndef THREAD_INFO_H
#define THREAD_INFO_H
#include "helper_functions.h"
#include "window.h"
class Window;

struct thread_info
{
  int n;
  int p;
  int idx;
  std::function<double (double, double)> f;
  double eps;
  grid *gr;
  pthread_barrier_t *barrier;
  bool proceed;
  builder_solver_data *data;
  Window *window;
  pthread_cond_t *cond;
  int *p_out;
};
void *
pthread_func (void *arg);
void synchronize
(int p, Window *window, pthread_cond_t &c_out, int &t_out);
#endif // THREAD_INFO_H
