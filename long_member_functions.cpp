#include "system_builder.h"

int
system_builder::get_off_diag (int k, double *a_diag, double *a,
                  int *I)
{
    int i, j, trapeze_num;
    us u = gr->get_u();

    get_ijtrapeze (&i, &j, &trapeze_num, k, n);
    //расписываем случаи
    //полностью внутри
    if (j > 0 && j < n - 1 && i > 0 && i < n - 1)
      {
        double tr1, tr2, tr21, tr22;
        if (i + j < n)
          {
            tr1 = tr2 = u.get_u (0, trapeze_num);
            tr21 = u.get_u2 (0, trapeze_num);

            for (int i = 0; i < 6; i++)
              a[i] = 2 * tr21;
          }
        else if (i + j == n)
          {
            tr1 = u.get_u (0, trapeze_num);
            tr2 = u.get_u (1, trapeze_num);

            tr21 = u.get_u2 (0, trapeze_num);
            tr22 = u.get_u2 (1, trapeze_num);
            a[0] = 2 * tr22;
            a[1] = tr21 + tr22;
            a[2] = 2 * tr21;
            a[3] = 2 * tr21;
            a[4] = tr21 + tr22;
            a[5] = 2 * tr22;
          }
        else
          {
            tr1 = tr2 = u.get_u (1, trapeze_num);
            tr22 = u.get_u2 (1, trapeze_num);
            for (int i = 0; i < 6; i++)
              a[i] = 2 * tr22;
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

            int next_trapeze = (trapeze_num + 1) % 4;

            I[4] = get_k (0, j - 1, next_trapeze, n);
            I[5] = get_k (0, j, next_trapeze, n);
          }

         return 6;
      }
    //правая сторона трапеции
    else if (i == 0 && j > 0 && j < n - 1)
      {
        int prev_trapeze = (trapeze_num == 0 ? 3 : trapeze_num - 1);
        double tr1 = u.get_u (0, trapeze_num),
               tr2 = u.get_u (1, prev_trapeze);
        double tr21 = u.get_u2 (0, trapeze_num),
               tr22 = u.get_u2 (1, prev_trapeze);

        *a_diag = 3 * (tr1 + tr2);

        a[0] = tr21 + tr22;
        a[1] = 2 * tr22;
        a[2] = 2 * tr22;
        a[3] = tr21 + tr22;
        a[4] = 2 * tr21;
        a[5] = 2 * tr21;

        I[0] = get_k (i, j + 1, trapeze_num, n);
        I[1] = get_k (n - 2, j + 1, prev_trapeze, n);
        I[2] = get_k (n - 2, j, prev_trapeze, n);
        I[3] = get_k (i, j - 1, trapeze_num, n);
        I[4] = get_k (i + 1, j - 1, trapeze_num, n);
        I[5] = get_k (i + 1, j, trapeze_num, n);

        return 6;
      }
    //нижняя сторона трапеции
    else if (j == 0 && i > 0 && i < n - 1)
      {
        double tr = u.get_u (0, trapeze_num);
        double tr2 = u.get_u2 (0, trapeze_num);
        *a_diag = 3 * tr;

        a[0] = 2 * tr2;
        a[1] = 2 * tr2;
        a[2] = tr2;
        a[3] = tr2;

        I[0] = get_k (i, j + 1, trapeze_num, n);
        I[1] = get_k (i - 1, j + 1, trapeze_num, n);
        I[2] = get_k (i - 1, j, trapeze_num, n);

        if (i < n - 2)
          I[3] = get_k (i + 1, j, trapeze_num, n);
        else
          {
            int next_trapeze = (trapeze_num + 1) % 4;
            I[3] = get_k (0, j, next_trapeze, n);
          }
        return 4;
      }
    //верхняя сторона трапеции
    else if (j == n - 1 && i > 0 && i < n - 1)
      {
        double tr = u.get_u (1, trapeze_num);
        double tr2 = u.get_u2 (1, trapeze_num);
        *a_diag = 3 * tr;

        a[0] = tr2;
        a[1] = 2 * tr2;
        a[2] = 2 * tr2;
        a[3] = tr2;

        I[0] = get_k (i - 1, j, trapeze_num, n);
        I[1] = get_k (i, j - 1, trapeze_num, n);

        if (i < n - 2)
          {
            I[2] = get_k (i + 1, j - 1, trapeze_num, n);
            I[3] = get_k (i + 1, j, trapeze_num, n);
          }
        else
          {
            int next_trapeze = (trapeze_num + 1) % 4;
            I[2] = get_k (0, j - 1, next_trapeze, n);
            I[3] = get_k (0, j, next_trapeze, n);
          }

        return 4;
      }
    //правый нижний угол
    else if (j == 0 && i == 0)
      {
        int prev_trapeze = (trapeze_num == 0 ? 3 : trapeze_num - 1);
        double tr1 = u.get_u (0, trapeze_num),
               tr2 = u.get_u (1, prev_trapeze),
               tr3 = u.get_u (0, prev_trapeze);
        double tr21 = u.get_u2 (0, trapeze_num),
               tr22 = u.get_u2 (1, prev_trapeze),
               tr23 = u.get_u2 (0, prev_trapeze);

        *a_diag = tr1 + tr2 + tr3;

        a[0] = tr21 + tr22;
        a[1] =        tr22 + tr23;
        a[2] =               tr23;
        a[3] = tr21;

        I[0] = get_k (0, 1, trapeze_num, n);
        I[1] = get_k (n - 2, 1, prev_trapeze, n);
        I[2] = get_k (n - 2, 0, prev_trapeze, n);
        I[3] = get_k (1, 0, trapeze_num, n);

        return 4;
      }
    //правый верхний угол
    else if (j == n - 1 && i == 0)
      {
        int prev_trapeze = (trapeze_num == 0 ? 3 : trapeze_num - 1);
        double tr1 = u.get_u (1, trapeze_num),
               tr2 = u.get_u (0, trapeze_num),
               tr3 = u.get_u (1, prev_trapeze);
        double tr21 = u.get_u2 (1, trapeze_num),
               tr22 = u.get_u2 (0, trapeze_num),
               tr23 = u.get_u2 (1, prev_trapeze);

        *a_diag = tr1 + tr2 + tr3;

        a[0] =               tr23;
        a[1] =        tr22 + tr23;
        a[2] = tr21 + tr22;
        a[3] = tr21;

        I[0] = get_k (n - 2, n - 1, prev_trapeze, n);
        I[1] = get_k (0, n - 2, trapeze_num, n);
        I[2] = get_k (1, n - 2, trapeze_num, n);
        I[3] = get_k (1,  n - 1, trapeze_num, n);

        return 4;
      }
    abort ();
    return -1000;
}
double
system_builder::fill_rhs_at (int k)
{
  int i, j, trapeze_num;
  Js J = gr->get_J ();

  get_ijtrapeze (&i, &j, &trapeze_num, k, n);
  //расписываем случаи
  //полностью внутри
  if (j > 0 && j < n - 1 && i > 0 && i < n - 1)
    {
      double tr1, tr2;
      if (i + j < n)
        {
          tr1 = tr2 = J.get_J (0, trapeze_num);

        }
      else if (i + j == n)
        {
          tr1 = J.get_J (0, trapeze_num);
          tr2 = J.get_J (1, trapeze_num);
        }
      else
        {
          tr1 = tr2 = J.get_J (1, trapeze_num);
        }
      double ans = 0;
      ans = tr1 *
              (
                2
              );
      ans += tr2 *
              (
                 2
               );
      ans += ((tr1 + tr2) / 2.) *
              (
                8
              );

      return ans / 12.;
    }
  //правая сторона трапеции
  else if (i == 0 && j > 0 && j < n - 1)
    {
      int trapeze_prev = (trapeze_num == 0 ? 3 : trapeze_num - 1);
      double tr1 = J.get_J (0, trapeze_num),
             tr2 = J.get_J (1, trapeze_prev);

      double ans = 0;

      ans = tr1 *
             (
               2
             );
      ans += tr2 *
              (
                 2
              );
      ans += ((tr1 + tr2) / 2) *
              (
                  8
              );

      return ans / 12.;
    }
  //нижняя сторона трапеции
  else if (j == 0 && i > 0 && i < n - 1)
    {
      double tr = J.get_J (0, trapeze_num);

      double ans = 0;

      ans = tr *
             (
               10
             );
      return ans / 12.;
    }
  //верхняя сторона трапеции
  else if (j == n - 1 && i > 0 && i < n - 1)
    {
      double tr = J.get_J (1, trapeze_num);
      double ans = 0;

      ans = tr *
              (
                10
              );
      return ans / 12.;
    }
  //правый нижний угол
  else if (j == 0 && i == 0)
    {
      int trapeze_prev = (trapeze_num == 0 ? 3 : trapeze_num - 1);
      double tr1 = J.get_J (0, trapeze_num),
             tr2 = J.get_J (1, trapeze_prev),
             tr3 = J.get_J (0, trapeze_prev);
      double ans = 0;

      ans = tr1 *
             (
               1
             );
      ans += ((tr1 + tr2) / 2) *
              (
                1
              );
      ans += ((tr2 + tr3) / 2) *
              (
                1
              );
      ans += tr3 *
              (
                1
              );
      ans += ((tr1 + tr2 + tr3) / 3.) *
              (
                6
              );
      return ans / 12.;
    }
  //правый верхний угол
  else if (j == n - 1 && i == 0)
    {
      int trapeze_prev = (trapeze_num == 0 ? 3 : trapeze_num - 1);
      double tr1 = J.get_J (1, trapeze_num),
             tr2 = J.get_J (0, trapeze_num),
             tr3 = J.get_J (1, trapeze_prev);
      double ans = 0;

      ans = tr1 *
             (
               1
             );
      ans += ((tr1 + tr2) / 2) *
              (
                1
              );
      ans += ((tr2 + tr3) / 2) *
              (
                 1
              );
      ans += tr3 *
              (
                1
              );
      ans += ((tr1 + tr2 + tr3) / 3.) *
              (
                6
              );
      return ans / 12.;
    }
  abort ();
}
/*double
system_builder::fill_rhs_at (int k)
{
    int i, j, trapeze_num, n2 = 2 * n - 1;
    Js J = gr->get_J ();

    get_ijtrapeze (&i, &j, &trapeze_num, k, n);
    //расписываем случаи
    //полностью внутри
    if (j > 0 && j < n - 1 && i > 0 && i < n - 1)
      {
        double tr1, tr2;
        if (i + j < n)
          {
            tr1 = tr2 = J.get_J (0, trapeze_num);

          }
        else if (i + j == n)
          {
            tr1 = J.get_J (0, trapeze_num);
            tr2 = J.get_J (1, trapeze_num);
          }
        else
          {
            tr1 = tr2 = J.get_J (1, trapeze_num);
          }
        double ans = 0;
        ans = tr1 *
                (
                  4  * gr->get_f_value_by_ijtr (f, 2 * i - 2, 2 * j + 1, trapeze_num, n2) +
                  2  * gr->get_f_value_by_ijtr (f, 2 * i - 2, 2 * j + 0, trapeze_num, n2) +
                  20 * gr->get_f_value_by_ijtr (f, 2 * i - 1, 2 * j + 0, trapeze_num, n2) +

                  4  * gr->get_f_value_by_ijtr (f, 2 * i - 1, 2 * j - 1, trapeze_num, n2) +
                  2  * gr->get_f_value_by_ijtr (f, 2 * i + 0, 2 * j - 2, trapeze_num, n2) +
                  20 * gr->get_f_value_by_ijtr (f, 2 * i + 0, 2 * j - 1, trapeze_num, n2) +

                  4  * gr->get_f_value_by_ijtr (f, 2 * i + 1, 2 * j - 2, trapeze_num, n2)
                );
        ans += tr2 *
                (
                   4  * gr->get_f_value_by_ijtr (f, 2 * i + 2, 2 * j - 1, trapeze_num, n2) +
                   2  * gr->get_f_value_by_ijtr (f, 2 * i + 2, 2 * j + 0, trapeze_num, n2) +
                   20 * gr->get_f_value_by_ijtr (f, 2 * i + 1, 2 * j + 0, trapeze_num, n2) +

                   4  * gr->get_f_value_by_ijtr (f, 2 * i + 1, 2 * j + 1, trapeze_num, n2) +
                   2  * gr->get_f_value_by_ijtr (f, 2 * i + 0, 2 * j + 2, trapeze_num, n2) +
                   20 * gr->get_f_value_by_ijtr (f, 2 * i + 0, 2 * j + 1, trapeze_num, n2) +

                   4  * gr->get_f_value_by_ijtr (f, 2 * i - 1, 2 * j + 2, trapeze_num, n2)
                 );
        ans += ((tr1 + tr2) / 2.) *
                (
                  2  * gr->get_f_value_by_ijtr (f, 2 * i - 2, 2 * j + 2, trapeze_num, n2) +
                  20 * gr->get_f_value_by_ijtr (f, 2 * i - 1, 2 * j + 1, trapeze_num, n2) +

                  20 * gr->get_f_value_by_ijtr (f, 2 * i + 1, 2 * j - 1, trapeze_num, n2) +
                  2  * gr->get_f_value_by_ijtr (f, 2 * i + 2, 2 * j - 2, trapeze_num, n2) +

                  36 * gr->get_f_value_by_ijtr (f, 2 * i + 0, 2 * j + 0, trapeze_num, n2)
                );

        return ans / 192.;
      }
    //правая сторона трапеции
    else if (i == 0 && j > 0 && j < n - 1)
      {
        int trapeze_prev = (trapeze_num == 0 ? 3 : trapeze_num - 1);
        double tr1 = J.get_J (0, trapeze_num),
               tr2 = J.get_J (1, trapeze_prev);

        double ans = 0;

        ans = tr1 *
               (
                 4  * gr->get_f_value_by_ijtr (f, 2 * i + 1, 2 * j - 2, trapeze_num, n2) +
                 2  * gr->get_f_value_by_ijtr (f, 2 * i + 2, 2 * j - 2, trapeze_num, n2) +
                 20 * gr->get_f_value_by_ijtr (f, 2 * i + 1, 2 * j - 1, trapeze_num, n2) +

                 4  * gr->get_f_value_by_ijtr (f, 2 * i + 2, 2 * j - 1, trapeze_num, n2) +
                 2  * gr->get_f_value_by_ijtr (f, 2 * i + 2, 2 * j + 0, trapeze_num, n2) +
                 20 * gr->get_f_value_by_ijtr (f, 2 * i + 1, 2 * j + 0, trapeze_num, n2) +

                 4  * gr->get_f_value_by_ijtr (f, 2 * i + 1, 2 * j + 1, trapeze_num, n2)
               );
        ans += tr2 *
                (
                   4  * gr->get_f_value_by_ijtr (f, n2 - 2, 2 * j + 2, trapeze_prev, n2) +
                   2  * gr->get_f_value_by_ijtr (f, n2 - 3, 2 * j + 2, trapeze_prev, n2) +
                   20 * gr->get_f_value_by_ijtr (f, n2 - 2, 2 * j + 1, trapeze_prev, n2) +

                   4  * gr->get_f_value_by_ijtr (f, n2 - 3, 2 * j + 1, trapeze_prev, n2) +
                   2  * gr->get_f_value_by_ijtr (f, n2 - 3, 2 * j + 0, trapeze_prev, n2) +
                   20 * gr->get_f_value_by_ijtr (f, n2 - 2, 2 * j + 0, trapeze_prev, n2) +

                   4  * gr->get_f_value_by_ijtr (f, n2 - 2, 2 * j - 1, trapeze_prev, n2)
                );
        ans += ((tr1 + tr2) / 2) *
                (
                    //если вдруг не работает, то здесь я считал, что эти точки "принадлежат"
                    //обоим треугольникам, хотя можно считать, что только одному, мб попробовать

                  2  * gr->get_f_value_by_ijtr (f, 2 * i + 0, 2 * j + 2, trapeze_num, n2) +
                  20 * gr->get_f_value_by_ijtr (f, 2 * i + 0, 2 * j + 1, trapeze_num, n2) +

                  20 * gr->get_f_value_by_ijtr (f, 2 * i + 0, 2 * j - 1, trapeze_num, n2) +
                  2  * gr->get_f_value_by_ijtr (f, 2 * i + 0, 2 * j - 2, trapeze_num, n2) +

                  36 * gr->get_f_value_by_ijtr (f, 2 * i + 0, 2 * j + 0, trapeze_num, n2)
                );

        return ans / 192.;
      }
    //нижняя сторона трапеции
    else if (j == 0 && i > 0 && i < n - 1)
      {
        double tr = J.get_J (0, trapeze_num);

        double ans = 0;

        ans = tr *
               (
                 20 * gr->get_f_value_by_ijtr (f, 2 * i + 1, 2 * j + 0, trapeze_num, n2) +
                 2  * gr->get_f_value_by_ijtr (f, 2 * i + 2, 2 * j + 0, trapeze_num, n2) +
                 4 * gr->get_f_value_by_ijtr (f, 2 * i + 1, 2 * j + 1, trapeze_num, n2) +

                 20 * gr->get_f_value_by_ijtr (f, 2 * i + 0, 2 * j + 1, trapeze_num, n2) +
                 2  * gr->get_f_value_by_ijtr (f, 2 * i + 0, 2 * j + 2, trapeze_num, n2) +
                 4 * gr->get_f_value_by_ijtr (f, 2 * i - 1, 2 * j + 2, trapeze_num, n2) +

                 20 * gr->get_f_value_by_ijtr (f, 2 * i - 1, 2 * j + 1, trapeze_num, n2) +
                 2  * gr->get_f_value_by_ijtr (f, 2 * i - 2, 2 * j + 2, trapeze_num, n2) +
                 4 * gr->get_f_value_by_ijtr (f, 2 * i - 2, 2 * j + 1, trapeze_num, n2) +

                 20 * gr->get_f_value_by_ijtr (f, 2 * i - 1, 2 * j + 0, trapeze_num, n2) +
                 2  * gr->get_f_value_by_ijtr (f, 2 * i - 2, 2 * j + 0, trapeze_num, n2) +

                 36 * gr->get_f_value_by_ijtr (f, 2 * i + 0, 2 * j + 0, trapeze_num, n2)
               );
        return ans / 192.;
      }
    //верхняя сторона трапеции
    else if (j == n - 1 && i > 0 && i < n - 1)
      {
        double tr = J.get_J (1, trapeze_num);
        double ans = 0;

        ans = tr *
                (
                  20 * gr->get_f_value_by_ijtr (f, 2 * i + 1, 2 * j + 0, trapeze_num, n2) +
                  2  * gr->get_f_value_by_ijtr (f, 2 * i + 2, 2 * j + 0, trapeze_num, n2) +
                  4  * gr->get_f_value_by_ijtr (f, 2 * i + 2, 2 * j - 1, trapeze_num, n2) +

                  20 * gr->get_f_value_by_ijtr (f, 2 * i + 1, 2 * j - 1, trapeze_num, n2) +
                  2  * gr->get_f_value_by_ijtr (f, 2 * i + 2, 2 * j - 2, trapeze_num, n2) +
                  4  * gr->get_f_value_by_ijtr (f, 2 * i + 1, 2 * j - 2, trapeze_num, n2) +

                  20 * gr->get_f_value_by_ijtr (f, 2 * i + 0, 2 * j - 1, trapeze_num, n2) +
                  2  * gr->get_f_value_by_ijtr (f, 2 * i + 0, 2 * j - 2, trapeze_num, n2) +
                  4  * gr->get_f_value_by_ijtr (f, 2 * i - 1, 2 * j - 1, trapeze_num, n2) +

                  20 * gr->get_f_value_by_ijtr (f, 2 * i - 1, 2 * j + 0, trapeze_num, n2) +
                  2  * gr->get_f_value_by_ijtr (f, 2 * i - 2, 2 * j + 0, trapeze_num, n2) +

                  36 * gr->get_f_value_by_ijtr (f, 2 * i + 0, 2 * j + 0, trapeze_num, n2)
                );
        return ans / 192.;
      }
    //правый нижний угол
    else if (j == 0 && i == 0)
      {
        int trapeze_prev = (trapeze_num == 0 ? 3 : trapeze_num - 1);
        double tr1 = J.get_J (0, trapeze_num),
               tr2 = J.get_J (1, trapeze_prev),
               tr3 = J.get_J (0, trapeze_prev);
        double ans = 0;

        ans = tr1 *
               (
                 20 * gr->get_f_value_by_ijtr (f, 2 * i + 1, 2 * j + 0, trapeze_num, n2) +
                 2  * gr->get_f_value_by_ijtr (f, 2 * i + 2, 2 * j + 0, trapeze_num, n2) +
                 4  * gr->get_f_value_by_ijtr (f, 2 * i + 1, 2 * j + 1, trapeze_num, n2)
               );
        ans += ((tr1 + tr2) / 2) *
                (
                  20 * gr->get_f_value_by_ijtr (f, 2 * i + 0, 2 * j + 1, trapeze_num, n2) +
                  2  * gr->get_f_value_by_ijtr (f, 2 * i + 0, 2 * j + 2, trapeze_num, n2)
                );
        ans += tr2 *
                (
                  4 * gr->get_f_value_by_ijtr (f, n2 - 2, 2 * j + 2, trapeze_prev, n2)
                );
        ans += ((tr2 + tr3) / 2) *
                (
                  20 * gr->get_f_value_by_ijtr (f, n2 - 2, 2 * j + 1, trapeze_prev, n2) +
                  2  * gr->get_f_value_by_ijtr (f, n2 - 3, 2 * j + 2, trapeze_prev, n2)
                );
        ans += tr3 *
                (
                  20 * gr->get_f_value_by_ijtr (f, n2 - 3, 2 * j + 1, trapeze_prev, n2) +
                  2  * gr->get_f_value_by_ijtr (f, n2 - 3, 2 * j + 0, trapeze_prev, n2) +
                  4  * gr->get_f_value_by_ijtr (f, n2 - 2, 2 * j + 0, trapeze_prev, n2)
                );
        ans += ((tr1 + tr2 + tr3) / 3) *
                (
                  36 * gr->get_f_value_by_ijtr (f, 0, 0, trapeze_num, n2)
                );
        return ans / 192.;
      }
    //правый верхний угол
    else if (j == n - 1 && i == 0)
      {
        int trapeze_prev = (trapeze_num == 0 ? 3 : trapeze_num - 1);
        double tr1 = J.get_J (1, trapeze_num),
               tr2 = J.get_J (0, trapeze_num),
               tr3 = J.get_J (1, trapeze_prev);
        double ans = 0;

        ans = tr1 *
               (
                 20 * gr->get_f_value_by_ijtr (f, 2 * i + 1, 2 * j + 0, trapeze_num, n2) +
                 2 * gr->get_f_value_by_ijtr (f, 2 * i + 2, 2 * j + 0, trapeze_num, n2) +
                 4 * gr->get_f_value_by_ijtr (f, 2 * i + 2, 2 * j - 1, trapeze_num, n2)
               );
        ans += ((tr1 + tr2) / 2) *
                (
                  20 * gr->get_f_value_by_ijtr (f, 2 * i + 1, 2 * j - 1, trapeze_num, n2) +
                  2 * gr->get_f_value_by_ijtr (f, 2 * i + 2, 2 * j - 2, trapeze_num, n2)
                );
        ans += tr2 *
                (
                  4 * gr->get_f_value_by_ijtr (f, 2 * i + 1, 2 * j - 2, trapeze_num, n2)
                );
        ans += ((tr2 + tr3) / 2) *
                (
                    20 * gr->get_f_value_by_ijtr (f, 2 * i + 0, 2 * j - 1, trapeze_num, n2) +
                    2 * gr->get_f_value_by_ijtr (f, 2 * i + 0, 2 * j - 2, trapeze_num, n2)
                );
        ans += tr3 *
                (
                  20 * gr->get_f_value_by_ijtr (f, n2 - 2, 2 * j - 1, trapeze_prev, n2) +
                  2 *  gr->get_f_value_by_ijtr (f, n2 - 3, 2 * j + 0, trapeze_prev, n2) +
                  4 *  gr->get_f_value_by_ijtr (f, n2 - 2, 2 * j + 0, trapeze_prev, n2)
                );
        ans += ((tr1 + tr2 + tr3) / 2) *
                (
                  36 * gr->get_f_value_by_ijtr (f, 2 * i + 0, 2 * j + 0, trapeze_num, n2)
                );

        return ans / 192.;
      }
    abort ();
}
*/
