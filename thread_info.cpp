#include "thread_info.h"
#include "system_builder.h"
#include "system_solver.h"
void *
pthread_func (void *arg)
{
    thread_info *info = static_cast<thread_info *> (arg);
    while (info->proceed)
      {
        auto d  = info->data;
        int idx = info->idx, p = info->p;
        double *matrix = d->matrix,
               *rhs    = d->rhs,
               *x      = d->x,
               *u      = d->u,
               *r      = d->r,
               *v      = d->v,
               *buf    = d->buf;
        int    *I      = d->I;
        system_builder *builder = nullptr;
        if (idx == 0)
          {
            builder = new system_builder (info->gr, info->f, matrix, rhs, I);
          }
        builder->fill_MSR_matrix (p, idx);
        builder->fill_rhs (p, idx);

        pthread_barrier_wait (info->barrier);
        if (idx == 0)
          {
            delete builder;
          }
        int n = info->n;
        int diag_length = 4 * n * (n - 1);

        system_solver solver (matrix, I, x, rhs, diag_length, u, r, v, buf, info->barrier, p, info->eps);
        solver.solve (MAX_IT, idx);
        synchronize (p, info->window, *(info->cond), *(info->p_out));
      }

    return 0;
}
void synchronize (int p, Window *window, pthread_cond_t &c_out, int &t_out)
{
  static pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
  static pthread_cond_t c_in = PTHREAD_COND_INITIALIZER;

  static int t_in = 0;

  pthread_mutex_lock (&m);

  t_in++;

  if (t_in >= p)
    {
      t_out = 0;
      pthread_cond_broadcast (&c_in);
    }
  else
    while (t_in < p)
      pthread_cond_wait (&c_in, &m);
  t_out++;


  if (t_out >= p)
    {
      t_in = 0;
      window->emit_calculation_completed ();
      //pthread_cond_broadcast (&c_out);
    }

  while (t_out <= p)
    pthread_cond_wait (&c_out, &m);

  pthread_mutex_unlock (&m);
}
