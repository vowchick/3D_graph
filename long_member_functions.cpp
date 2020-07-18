#include "msr_matrix_builder.h"

int
msr_matrix_builder::get_off_diag (int k, double *a_diag, double *a,
                  int *I)
{
    int i, j, trapeze_num;
    get_ijtrapeze (&i, &j, &trapeze_num, k, n);
    //расписываем случаи
    //полностью внутри
    if (j > 0 && j < n - 1 && i > 0 && i < n - 1)
      {
        double tr1, tr2;
        if (i + j < n)
          {
            tr1 = tr2 = get_u (0, trapeze_num, u);
            for (int i = 0; i < 6; i++)
              a[i] = 2 * tr1;
          }
        else if (i + j == n)
          {
            tr1 = get_u (0, trapeze_num, u);
            tr2 = get_u (1, trapeze_num, u);
            a[0] = 2 * tr2;
            a[1] = tr1 + tr2;
            a[2] = 2 * tr1;
            a[3] = 2 * tr1;
            a[4] = tr1 + tr2;
            a[5] = 2 * tr2;
          }
        else
          {
            tr1 = tr2 = get_u (1, trapeze_num, u);
            for (int i = 0; i < 6; i++)
              a[i] = 2 * tr2;
          }
        *a_diag  = 3 * (tr1 + tr2);

        if (i < n - 2)
          {
            I[0] = get_k (i, j + 1, trapeze_num, n);
            I[1] = get_k (i - 1, j + 1, trapeze_num, n);
            I[2] = get_k (i - 1, j, trapeze_num, n);
            I[3] = get_k (i, j - 1, trapeze_num, n);
            I[4] = get_k (i + 1, j - 1, trapeze_num, n);
            I[5] = get_k (i + 1, j, trapeze_num, n);
          }
        else
          {
            I[0] = get_k (i, j + 1, trapeze_num, n);
            I[1] = get_k (i - 1, j + 1, trapeze_num, n);
            I[2] = get_k (i - 1, j, trapeze_num, n);
            I[3] = get_k (i, j - 1, trapeze_num, n);

            int next_trapeze = (trapeze_num + 1) % 8;

            I[4] = get_k (0, j - 1, next_trapeze, n);
            I[5] = get_k (0, j, next_trapeze, n);
          }

        return 6;
      }
    //правая сторона трапеции
    else if (i == 0 && j > 0 && j < n - 1)
      {
        int prev_trapeze = (trapeze_num == 0 ? 3 : trapeze_num - 1);
        double tr1 = get_u (0, trapeze_num, u),
               tr2 = get_u (1, prev_trapeze, u);

        *a_diag = 3 * (tr1 + tr2);

        a[0] = tr1 + tr2;
        a[1] = 2 * tr2;
        a[2] = 2 * tr2;
        a[3] = tr1 + tr2;;
        a[4] = 2 * tr1;
        a[5] = 2 * tr1;

        I[0] = get_k (i, j + 1, trapeze_num, n);
        I[1] = get_k (n - 2, j, prev_trapeze, n);
        I[2] = get_k (n - 2, j - 1, prev_trapeze, n);
        I[3] = get_k (i, j - 1, trapeze_num, n);
        I[4] = get_k (i + 1, j - 1, trapeze_num, n);
        I[5] = get_k (i + 1, j, trapeze_num, n);

        return 6;
      }
    //нижняя сторона трапеции
    else if (j == 0 && i > 0 && i < n - 1)
      {
        double tr = get_u (0, trapeze_num, u);
        *a_diag = 3 * tr;

        a[0] = 2 * tr;
        a[1] = 2 * tr;
        a[2] = tr;
        a[3] = tr;

        I[0] = get_k (i, j + 1, trapeze_num, n);
        I[1] = get_k (i - 1, j + 1, trapeze_num, n);
        I[2] = get_k (i - 1, j, trapeze_num, n);
        I[3] = get_k (i + 1, j, trapeze_num, n);

        return 4;
      }
    //верхняя сторона трапеции
    else if (j == n - 1 && i > 0 && i < n - 1)
      {
        double tr = get_u (1, trapeze_num, u);
        *a_diag = 3 * tr;

        a[0] = tr;
        a[1] = 2 * tr;
        a[2] = 2 * tr;
        a[3] = tr;

        I[0] = get_k (i - 1, j, trapeze_num, n);
        I[1] = get_k (i - 1, j - 1, trapeze_num, n);
        I[2] = get_k (i + 1, j - 1, trapeze_num, n);
        I[3] = get_k (i + 1, j, trapeze_num, n);

        return 4;
      }
    //правый нижний угол
    else if (j == 0 && i == 0)
      {
        int prev_trapeze = (trapeze_num == 0 ? 3 : trapeze_num - 1);
        double tr1 = get_u (0, trapeze_num, u),
               tr2 = get_u (1, prev_trapeze, u),
               tr3 = get_u (0, prev_trapeze, u);

        *a_diag  = tr1 + tr3 + tr3;

        a[0] = tr1 + tr2;
        a[1] =       tr2 + tr3;
        a[2] =             tr3;
        a[3] = tr1;

        I[0] = get_k (i, j + 1, trapeze_num, n);
        I[1] = get_k (n - 2, j + 1, prev_trapeze, n);
        I[2] = get_k (n - 2, j, prev_trapeze, n);
        I[3] = get_k (i + 1, j, trapeze_num, n);

        return 4;
      }
    //правый верхний угол
    else if (j == n - 1 && i == 0)
      {
        int prev_trapeze = (trapeze_num == 0 ? 3 : trapeze_num - 1);
        double tr1 = get_u (1, trapeze_num, u),
               tr2 = get_u (0, trapeze_num, u),
               tr3 = get_u (1, prev_trapeze, u);

        *a_diag  = tr1 + tr3 + tr3;

        a[0] =             tr3;
        a[1] =       tr2 + tr3;
        a[2] = tr1 + tr2;
        a[3] = tr1;

        I[0] = get_k (n - 2, j, prev_trapeze, n);
        I[1] = get_k (i, j - 1, trapeze_num, n);
        I[2] = get_k (i + 1, j - 1, trapeze_num, n);
        I[3] = get_k (i + 1, j, trapeze_num, n);

        return 4;
      }
    abort ();
    return -1000;
}
