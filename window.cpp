#include "window.h"
std::atomic <bool> calculating (true);
Window::Window(polygon *pol_, int n_,
               int p_, double eps_,
               int func_ind,
               QWidget *parent) : QWidget(parent)
{
  connect(this, SIGNAL (calculation_completed ()), this, SLOT (after_calculation ()));

  initialize (pol_, n_, p_, eps_, func_ind);
  allocate_memory ();
  initialize_vectors ();
  initialize_barrier_and_cond ();
  allocate_info ();
  initialize_info ();
  start_threads ();


}

void
Window::allocate_info ()
{
  info_ptr.reset (new thread_info[threads_num]);
  info = info_ptr.get ();
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
      if (n > 1)
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
Window::change_function ()
{
  if (!calculating)
    {
      func_ind++;
      func_ind %= 8;
      f = int_to_f (func_ind);
      func_name = int_to_str (func_ind);
      calculating = true;
      before_calculation ();
      p_out++;
      pthread_cond_broadcast (&cond);
    }

}

void
Window::initialize_info ()
{
  for (int i = 0; i < threads_num; i++)
    {
      info[i].f = f;
      info[i].n = n;
      info[i].p = threads_num;
      info[i].eps = eps;
      info[i].idx = i;
      info[i].barrier = &barrier;
      info[i].gr = gr.get ();
      info[i].proceed = true;
      info[i].data = &data;
      info[i].window = this;
      info[i].cond = &cond;
      info[i].p_out = &p_out;
    }
}
void
Window::initialize (polygon *pol_, int n_,
                    int p_, double eps_,
                    int func_ind_)
{
    pol = pol_;
    n = n_;
    func_ind = func_ind_;
    f = int_to_f (func_ind);
    func_name = int_to_str (func_ind);
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
  data.matrix.reset (new double [alloc_size]);
  data.I.reset (new int [alloc_size]);

  data.rhs.reset (new double[diag_length]);
  data.x.reset (new double[diag_length]);

  gr.reset (new grid (pol, n));

  data.u.reset (new double[diag_length]);
  data.r.reset (new double[diag_length]);
  data.v.reset (new double[diag_length]);
  data.buf.reset (new double[threads_num]);

}

void
Window::after_calculation ()
{
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

}
void Window::emit_calculation_completed ()
{
  emit calculation_completed ();
}

