#include "helper_functions.h"
int
read_polygon_from_file (char *file_name,
                        polygon *Polygon)
{
    double a1, a2, b1, b2, c1, c2, d1, d2, k;
    FILE *fp = fopen (file_name, "r");
    if (!fp)
      {
        printf ("Couldn't open file %s\n", file_name);
        return -1;
      }
    if (fscanf (fp, "%lf %lf %lf %lf %lf %lf %lf %lf %lf",
                &a1, &a2, &b1, &b2, &c1, &c2, &d1, &d2, &k) != 9)
      {
        printf ("usage of %s: a1, a2, b1, b2, "
               "c1, c2, d1, d2, k\n", file_name);
        fclose (fp);
        return -2;
      }
    Polygon->A.x = a1;
    Polygon->A.y = a2;
    Polygon->B.x = b1;
    Polygon->B.y = b2;
    Polygon->C.x = c1;
    Polygon->C.y = c2;
    Polygon->D.x = d1;
    Polygon->D.y = d2;
    Polygon->k = k;
    fclose (fp);
    return 0;
}
void
print_polygon (polygon P)
{
    printf ("A = (%lf, %lf)\n", P.A.x, P.A.y);
    printf ("B = (%lf, %lf)\n", P.B.x, P.B.y);
    printf ("C = (%lf, %lf)\n", P.C.x, P.C.y);
    printf ("D = (%lf, %lf)\n", P.D.x, P.D.y);
    printf ("a = (%lf, %lf)\n", P.a.x, P.a.y);
    printf ("b = (%lf, %lf)\n", P.b.x, P.b.y);
    printf ("c = (%lf, %lf)\n", P.c.x, P.c.y);
    printf ("d = (%lf, %lf)\n", P.d.x, P.d.y);
//    printf ("A1 = (%lf, %lf)\n", P.A1.x, P.A1.y);
//    printf ("B1 = (%lf, %lf)\n", P.B1.x, P.B1.y);
//    printf ("C1 = (%lf, %lf)\n", P.C1.x, P.C1.y);
//    printf ("D1 = (%lf, %lf)\n", P.D1.x, P.D1.y);
    printf ("k = %lf\n", P.k);
}
int
find_inside_points (polygon *p)
{
  point middle;
  if (find_middle (p, &middle))
    {
      return -1;
    }
  auto find_point = [p](double x1, double y1,
                   double x2, double y2,
                   point middle) -> point
  {
    point desired;
    if (fabs (x2 - x1) < 1e-16)
      {
         desired.x = x1;
         desired.y = y1 + (y2 - y1) / p->k;
         return desired;
      }
    x2 -= x1;
    y2 -= y1;
    middle.x -= x1;
    middle.y -= y1;
    double coeff = (y2) / (x2);
    desired.x = (1 - 1. / (p->k));

    desired.x *= sqrt ((middle.x * middle.x
                + middle.y * middle.y) / (1 + coeff * coeff));
    desired.x *= (middle.x > 0 ? 1 : -1);
    desired.y = coeff * desired.x;
    desired.x += x1;
    desired.y += y1;
    return desired;
  };
  p->a = find_point (p->A.x, p->A.y, p->C.x, p->C.y, middle);
  p->b = find_point (p->B.x, p->B.y, p->D.x, p->D.y, middle);
  p->c = find_point (p->C.x, p->C.y, p->A.x, p->A.y, middle);
  p->d = find_point (p->D.x, p->D.y, p->B.x, p->B.y, middle);
  return 0;
}
int
find_middle (polygon *p, point *middle)
{
    double k1 = 0, b1 = 0, k2 = 0, b2 = 0;
    bool m1 = false, m2 = false;
    if (fabs(p->C.x - p->A.x) < 1e-16)
        m1 = true;
    if (fabs(p->B.x - p->D.x) < 1e-16)
        m2 = true;
    if (!m1)
      {
        k1 = (p->C.y - p->A.y)/(p->C.x - p->A.x);
        b1 = p->C.y - k1 * p->C.x;
      }
    if (!m2)
      {
        k2 = (p->B.y - p->D.y)/(p->B.x - p->D.x);
        b2 = p->B.y - k2 * p->B.x;
      }
    if (m1 && m2)
      {
        printf ("Something realy wrong with figure"
                "(both diagonals are vertical lines)\n");
        return -1;
      }
    if (m1)
      {
        //function x = const connects A and C
        middle->x = p->A.x;
        middle->y = k2 * middle->x + b2;
      }
    else if (m2)
      {
        //function x = const connects B and D
        middle->x = p->B.x;
        middle->y = k1 * middle->x + b1;
      }
    else
      {
        if (fabs (k1 - k2) < 1e-16)
          {
            printf ("Something is seriosly wrong "
                    "with the figure(diagonals are parallel)\n");
            return -1;
          }
        middle->x = (b1 - b2) / (k2 - k1);
        middle->y = k1 * middle->x + b1;
      }
    return 0;
}
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
