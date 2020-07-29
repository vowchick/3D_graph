#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include "system_builder.h"
#include "system_solver.h"
#include "helper_functions.h"
#include "io.h"
#include "delegator.h"
struct thread_info
{
  delegator *delegate;
  int n;
  int idx;
  std::function<double (double, double)> f;
  double eps;
  pthread_barrier_t *barrier;
};

void *
pthread_func (void *arg)
{
    thread_info *info = static_cast<thread_info *> (arg);

    if (info->idx == 0)
      {
        info->delegate->allocate (info->n, info->f, info->eps);
      }

    pthread_barrier_wait (info->barrier);
      info->delegate->solve (info->idx);
    pthread_barrier_wait (info->barrier);

    if (info->idx == 0)
      {
        info->delegate->erase ();
      }

    return 0;
}
int main (int argc, char *argv[])
{
  if (argc != 7)
    {
      printf ("usage ./a.out a.txt nx ny k eps p\n");
      return -1;
    }
  input in;
  polygon pol;
  int res = process_input (argv, in, pol);
  if (res < 0)
    {
      printf ("Couldn't init\n");
      return -1;
    }

  print_polygon(pol);

  int n = in.nx + 1;
  auto func = [] (double x, double y)
  {
    FIX_UNUSED(x, y);
    return 1;
  };



  pthread_barrier_t barrier;
  pthread_t tid;
  pthread_barrier_init (&barrier, NULL, in.p);

  thread_info *info = new thread_info [in.p];
  delegator delegate (&barrier, &pol, in.p);
  for (int i = 0; i < in.p; i++)
    {
      info[i].n = n;
      info[i].idx = i;
      info[i].f = func;
      info[i].eps = in.eps;
      info[i].delegate = &delegate;
      info[i].barrier = &barrier;
    }

  for (int i = 1; i < in.p; i++)
    {
      if (pthread_create (&tid, 0, pthread_func, info + i))
        {
          fprintf (stderr, "cannot create thread #%d!\n", i);
          abort ();
        }
    }
  pthread_func (info + 0);
  pthread_barrier_destroy(&barrier);

//  delegate.allocate (n, func, in.eps);
//  delegate.solve(0);

//  auto x = delegate.get_x ();
//  FIX_UNUSED (x);

//  delegate.erase();
  delete []info;
  return 0;
}
