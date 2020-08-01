#include "window.h"
std::atomic <bool> calculating (true);
Window::Window(polygon *pol_, int n_,
               int p_, double eps_,
               std::function<double (double, double)> f_,
               QWidget *parent) : QWidget(parent)
{
  initialize (pol_, n_, p_, eps_, f_);
  allocate_memory ();
  initialize_vectors ();
  initialize_barrier_and_cond ();
  allocate_info ();
  initialize_info ();
  start_threads ();

  connect(this, SIGNAL (calculation_completed ()), this, SLOT (after_calculation ()));

}

void
Window::allocate_info ()
{
  info = new thread_info[threads_num];
  if (!info)
    {
      printf ("Not enough memory!\n");
      erase ();
      abort ();
    }
}
Window::~Window ()
{
  pthread_barrier_destroy (&barrier);
}
void
Window::start_threads ()
{
  pthread_t tid;
  for (int i = 0; i < threads_num; i++)
    {
      if (pthread_create (&tid, 0, pthread_func, info + i))
        {
          fprintf (stderr, "cannot create thread #%d!\n", i);
          abort ();
        }
    }
}

void
Window::initialize_vectors ()
{
  int diag_size = 4 * n * (n - 1);

  for (int i = 0; i < diag_size; i++)
    {
      data.u[i] = 0.;
      data.r[i] = 0.;
      data.v[i] = 0.;
      data.x[i] = 0.;
    }
}

void
Window::double_n ()
{
  if (!calculating)
    {
      n *= 2;
      calculating = true;
      before_calculation ();
      p_out++;
      pthread_cond_broadcast (&cond);
    }

}

void
Window::undouble_n ()
{
  if (!calculating)
    {
      if (n >= 1)
        {
          n /= 2;
          calculating = true;
          before_calculation ();
          p_out++;
          pthread_cond_broadcast (&cond);
        }
    }

}
void
Window::initialize_info ()
{
  for (int i = 0; i < threads_num; i++)
    {
      info->f = f;
      info->n = n;
      info->p = threads_num;
      info->eps = eps;
      info->idx = i;
      info->barrier = &barrier;
      info->gr = gr;
      info->proceed = true;
      info->data = &data;
      info->window = this;
      info->cond = &cond;
      info->p_out = &p_out;
    }
}
void
Window::initialize (polygon *pol_, int n_,
                    int p_, double eps_,
                    std::function<double (double, double)> f_)
{
    pol = pol_;
    n = n_;
    f = f_;
    threads_num = p_;
    eps = eps_;
}

void
Window::initialize_barrier_and_cond ()
{
  if (pthread_barrier_init (&barrier, NULL, threads_num))
    {
      delete []info;
      erase ();
      abort ();
    }
  cond = PTHREAD_COND_INITIALIZER;
}

void
Window::allocate_memory ()
{
  int alloc_size = allocation_size (n);
  int diag_length = 4 * n * (n - 1);
  data.matrix = new double [alloc_size +
                            5 * diag_length +
                            threads_num];
  if (!data.matrix)
    {
      printf ("Not enough memory!\n");
      abort ();
    }

  data.I = new int [alloc_size];
  if (!data.I)
    {
      delete []data.matrix;
      printf ("Not enough memory!\n");
      abort ();
    }
  gr = new grid (pol, n);
  if (!gr)
    {
      delete []data.matrix;
      delete []data.I;
      printf ("Not enough memory!\n");
      abort ();
    }
  data.rhs = data.matrix + alloc_size;
  data.x = data.rhs + diag_length;
  data.u = data.x + diag_length;
  data.r = data.u + diag_length;
  data.v = data.r + diag_length;
  data.buf = data.v + diag_length;

}

void
Window::after_calculation ()
{
  erase ();
  calculating = false;
}

void
Window::before_calculation ()
{
  allocate_memory ();
  initialize_vectors ();
  initialize_info ();
}
void
Window::erase ()
{
  delete []data.matrix;
  delete []data.I;
  delete gr;
}
void Window::emit_calculation_completed ()
{
  emit calculation_completed ();
}
