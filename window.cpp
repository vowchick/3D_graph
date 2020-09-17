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
  set_gui ();
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
Window::increase ()
{
  drawer->increase ();
  change_s_label ();
}

void
Window::decrease ()
{
  change_s_label ();
  drawer->decrease ();
}

void
Window::clockwise ()
{
  drawer->clockwise ();
}

void
Window::unclockwise ()
{
  drawer->unclockwise ();
}

void
Window::perturb ()
{
  drawer->perturb ();
  change_perturbation_label ();
}
void
Window::unperturb ()
{
  drawer->unperturb ();
  change_perturbation_label ();
}
void
Window::double_n ()
{
  if (!calculating)
    {
      Time = get_time();
      n *= 2;
      change_n_label ();
      if (static_cast<state> (st) == given_function)
        {
          given_func_case ();
          return;
        }
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
      if (n > 6)
        {
          n /= 2;
          change_n_label ();
          if (static_cast<state> (st) == given_function)
            {
              given_func_case ();
              return;
            }
          calculating = true;
          before_calculation ();
          p_out++;
          pthread_cond_broadcast (&cond);
        }
    }

}
void
Window::given_func_case ()
{
  working_gr.reset (new grid (pol, n));
  after_calculation ();
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
      change_func_label ();
      set_f ();
      if (static_cast<state> (st) == given_function)
        {
          given_func_case ();
          return;
        }
      calculating = true;
      before_calculation ();
      p_out++;
      pthread_cond_broadcast (&cond);
    }

}

void
Window::change_state ()
{
  if (!calculating)
    {
      st = static_cast<state> ((st + 1) % 3);
      switch (st)
        {
        case given_function:
        case error:
          drawer->change_state ();
          break;
        case approximation:
          state_changed_flag = true;
          if (!calculating)
            {
              calculating = true;
              before_calculation ();
              p_out++;
              pthread_cond_broadcast (&cond);
            }
          break;
        }
      change_fabs_max_label ();
      change_state_label ();
      update_surface_coeffs ();
      drawer->updateGL ();
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
      info[i].gr = working_gr.get ();
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

  working_gr.reset (new grid (pol, n));

  data.u.reset (new double[diag_length]);
  data.r.reset (new double[diag_length]);
  data.v.reset (new double[diag_length]);
  data.buf.reset (new double[threads_num]);

}

void
Window::after_calculation ()
{
  Time = (get_time () - Time);
  calculating = false;
  if (state_changed_flag)
    {
      state_changed_flag = false;
      drawer->change_state ();
    }
  update_surface ();
  drawer->set_approx (appro);
  update_surface_coeffs ();
  change_fabs_max_label ();
  drawer->updateGL();
}


void
Window::closeEvent(QCloseEvent *event)
{
  if (calculating)
    event->ignore ();
  else
    {
      for (int i = 0; i < threads_num; i++)
        {
          info[i].proceed = false;
        }
      p_out++;
      pthread_cond_broadcast (&cond);
      event->accept ();
    }

}

void
Window::set_approx (double *approx)
{
  int diag_length = 4 * n * (n - 1);
  appro.resize (diag_length);

  for (int i = 0; i < diag_length; i++)
    appro[i] = approx[i];
}

void
Window::ultimate_update (double *x)
{
  update_surface ();
  set_approx (x);
}
void
Window::update_surface ()
{
  drawer->update_surface (working_gr);
}

void
Window::update_surface_coeffs ()
{
  drawer->update_surface_coeffs ();
}
void
Window::before_calculation ()
{
  allocate_memory ();
  initialize_vectors ();
  initialize_info ();
}
void
Window::set_f ()
{
  drawer->set_f (f);
}
void
Window::erase ()
{

}
void Window::emit_calculation_completed ()
{
  emit calculation_completed ();
}

