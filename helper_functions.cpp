#include "helper_functions.h"
/*int
find_ABCD1_points (polygon *p)
{
    auto find__1 = [](point Z,point z, point Q,
            point q, point *desired)->int
    {
      double k1, k2, b1, b2;
      // k = (y2 - y1) / (x2 - x1)
      bool is_vertical_1 = false, is_vertical_2 = false;
      if (fabs (Z.x - Q.x) < 1e-16)
          is_vertical_1 = true;
      if (fabs (Q.x - q.x) < 1e-16)
          is_vertical_2 = true;
      if (is_vertical_1 && is_vertical_2)
        {
            printf ("something is wron with the input figure\n");
            return 0;
        }
      if (is_vertical_1)
        {
          desired->x = Z.x;
          k2 = (Q.y - q.y) / (Q.x - q.x);
          b2 = z.y - k2 * z.x;
          desired->y = k2 * desired->x + b2;
        }
      else if (is_vertical_2)
        {
          desired->x = Q.x;
          k1 = (Q.y - Z.y) / (Q.x - Z.x);
          b1 = Z.y - k1 * Z.x;
          desired->y = k1 * desired->x + b1;
        }
      else
        {
          k1 = (Q.y - Z.y) / (Q.x - Z.x);
          b1 = Z.y - k1 * Z.x;
          k2 = (Q.y - q.y) / (Q.x - q.x);
          b2 = z.y - k2 * z.x;
          if (fabs (k1 - k2) < 1e-16)
            {
               printf ("Literally isn't supposed to happen\n");
               return -1;
            }
          desired->x = (b2 - b1) / (k1 - k2);
          desired->y = k1 * desired->x + b1;
        }
      return 0;
    };
    if (find__1 (p->A, p->a, p->B, p->b, &p->A1))
      {
        return -1;
      }
    if (find__1 (p->B, p->b, p->C, p->c, &p->B1))
      {
        return -1;
      }
    if (find__1 (p->C, p->c, p->D, p->d, &p->C1))
      {
        return -1;
      }
    if (find__1 (p->D, p->d, p->A, p->a, &p->D1))
      {
        return -1;
      }
    return 0;
}*/
