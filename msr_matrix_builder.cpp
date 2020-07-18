#include "msr_matrix_builder.h"

msr_matrix_builder::msr_matrix_builder()
{

}

msr_matrix_builder::~msr_matrix_builder()
{
  delete [] matrix;
  delete [] I;
}

msr_matrix_builder::msr_matrix_builder(int n_, polygon *p_)
{
  n = n_;
  pol = p_;

  int alloc_size = allocation_size ();

  matrix = new double[alloc_size];
  I = new int[alloc_size];

  carcass();

  fill_us();
}
int
msr_matrix_builder::allocation_size ()
{
    int size = 4 * (n * n - n);
    int al_size = 0;
    for (int i = 0; i < size; i++)
        al_size += get_num_of_diag (i);
    return size + al_size + 1;
}

int
msr_matrix_builder::get_num_of_diag (int k)
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
msr_matrix_builder::fill_us ()
{
    Js j;
    fill_js (j, pol, n);

    u.BbC = ultimate_scalar_counter (j.BbC, 1, 0, 0, 1, 0, 0);
    u.AaB = ultimate_scalar_counter (j.AaB, 1, 0, 0, 1, 0, 0);
    u.Bab = ultimate_scalar_counter (j.Bab, 1, 0, 0, 1, 0, 0);
    u.Cbc = ultimate_scalar_counter (j.Cbc, 1, 0, 0, 1, 0, 0);
    u.CcD = ultimate_scalar_counter (j.CcD, 1, 0, 0, 1, 0, 0);
    u.Dcd = ultimate_scalar_counter (j.Dcd, 1, 0, 0, 1, 0, 0);
    u.DdA = ultimate_scalar_counter (j.DdA, 1, 0, 0, 1, 0, 0);
    u.Ada = ultimate_scalar_counter (j.Ada, 1, 0, 0, 1, 0, 0);
}

void
msr_matrix_builder::carcass ()
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
msr_matrix_builder::fill_MSR_matrix (int p, int k)
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
  assert (N + 1 +  sum == I[N]);
}

