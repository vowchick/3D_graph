#include "window.h"

Window::Window(polygon *pol_, int n_,
               int p_, double eps_,
               std::function<double (double, double)> f_,
               QWidget *parent) : QWidget(parent)
{
  initialize (pol_, n_, p_, eps_, f_);
  allocate_memory ();
  auto x = data.matrix;
  FIX_UNUSED (x);
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

  data.rhs = data.matrix + alloc_size;
  data.x = data.rhs + diag_length;
  data.u = data.x + diag_length;
  data.r = data.u + diag_length;
  data.v = data.r + diag_length;
  data.buf = data.v + diag_length;

}

void
Window::erase ()
{
  delete []data.matrix;
  delete []data.I;
}
