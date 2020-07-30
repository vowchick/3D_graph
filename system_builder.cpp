#include "system_builder.h"

system_builder::~system_builder()
{

}

system_builder::system_builder(grid *gr_, std::function<double (double, double)> f_,
                               double *matrix_, double *rhs_, int *I_)
{
  n = gr_->get_n ();
  f = f_;
  gr = gr_;

  set_all (matrix_, I_, rhs_);

  carcass();

}
int
system_builder::allocation_size ()
{
    int size = 4 * (n * n - n);
    int al_size = 0;
    for (int i = 0; i < size; i++)
        al_size += get_num_of_diag (i);
    return size + al_size + 1;
}

int
system_builder::get_num_of_diag (int k)
{
  int i, j, trapeze_num;
  get_ijtrapeze (&i, &j, &trapeze_num, k, n);
  if (j > 0 && j < n - 1)
      return 6;
  else if (j == 0 || j == n - 1)
      return 4;
  abort ();
}


void
system_builder::carcass ()
{
    int len = allocation_size();
    int N = 4 * (n * n - n);
    int nz = len - N - 1;
    int l = 0, s = 0;
    I[0] = N + 1;
    for (int k = 1; k <= N; k++)
      {
        l = get_num_of_diag(k - 1);
        I[k] = I[k - 1] + l;
        s += l;
      }
    assert (s == nz);
    assert (I[N] == len);
    printf ("Here!: %d %d\n", s, nz);
    printf ("%d %d\n", I[N], len);
}

void
system_builder::fill_MSR_matrix (int p, int k)
{
  int k1, k2, l, s;
  int N = 4 * (n * n - n);
  int sum = 0;
  k1 = k * N; k1 /= p;
  k2 = (k + 1) * N; k2 = k2 / p - 1;
  for (l = k1; l <= k2; l++)
    {
      s = get_off_diag (l,
                        matrix + l,
                        matrix + I[l],
                        I + I[l]);
      sum += s;
    }
  reduce_sum (p, &sum, 1);
  printf ("%d %d\n", N + 1 + sum, I[N]);
  assert (N + 1 + sum == I[N]);
}

void
system_builder::fill_rhs(int p, int idx)
{
  int N = 4 * (n * n - n), k1, k2;
  k1 = idx * N; k1 /= p;
  k2 = (idx + 1) * N; k2 = k2 / p - 1;
  for (int k = k1; k <= k2; k++)
    {
      rhs[k] = fill_rhs_at (k);
    }
}
