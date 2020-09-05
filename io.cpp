#include "io.h"
int process_input (char *argv[], input &in, polygon &pol)
{
  in.file_name = argv[1];
  in.nx = atoi (argv[2]);
  in.ny = atoi (argv[3]);
  in.k = atoi (argv[4]);
  in.eps = atof (argv[5]);
  in.p = atoi (argv[6]);
  if (in.nx <= 0 || in.ny <= 0. || in.k <= 0 || in.p <= 0 || in.eps <= 0)
    {
      printf ("nx, ny, k, p and eps should be greater than zero\n");
      return -1;
    }

  if (in.nx != in.ny)
    {
      printf ("I will assume that nx == ny\n");
      return -2;
    }

  int res = read_polygon_from_file (in.file_name, pol);
  if (res < 0)
    return res;

  res = find_inside_points (pol);
  return res;
}
int
read_polygon_from_file (char *file_name,
                        polygon &Polygon)
{
    double inp [10];
    int it = 0;

    std::ifstream fp (file_name);
    if (!fp)
      {
        printf ("Couldn't open file %s\n", file_name);
        return -1;
      }

    std::string buf;
    while (std::getline (fp, buf) && it < 9)
      {
        std::vector<std::string> res;
        split (res, buf, [] (char x)
        {
            if (x == ' ' || x == '\t')
              return 0;
            return 1;
        });
        for (auto x : res)
          {
            if (it >= 9)
              break;
            inp[it++] = std::stod (x);
          }
      }
    for (int i = 0; i < 8; i++)
      {
        if (fabs (inp[i]) > 2)
          {
            printf ("Input is too big\n");
            return -1;
          }
      }
    Polygon.A.x = inp[0];
    Polygon.A.y = inp[1];
    Polygon.B.x = inp[2];
    Polygon.B.y = inp[3];
    Polygon.C.x = inp[4];
    Polygon.C.y = inp[5];
    Polygon.D.x = inp[6];
    Polygon.D.y = inp[7];
    Polygon.k = inp[8];
    return 0;
}
template <typename func>
void split (std::vector<std::string> &res, std::string &buf, func f)
{
  std::string word;
  word.clear ();
  for (auto x : buf)
    {
      if (x == '#')
        {
          res.clear ();
          return;
        }
      if (f (x))
        {
          word += x;
        }
      else
        {
          if (word.size ())
            {
              res.push_back (word);
              word.clear ();
            }
        }
    }
  if (word.size ())
    {
      res.push_back (word);
      word.clear ();
    }
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
    printf ("k = %lf\n", P.k);
}
int
find_inside_points (polygon &p)
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
         desired.y = y1 + (y2 - y1) / p.k;
         return desired;
      }
    x2 -= x1;
    y2 -= y1;
    middle.x -= x1;
    middle.y -= y1;
    double coeff = (y2) / (x2);
    desired.x = (1 - 1. / (p.k));

    desired.x *= sqrt ((middle.x * middle.x
                + middle.y * middle.y) / (1 + coeff * coeff));
    desired.x *= (middle.x > 0 ? 1 : -1);
    desired.y = coeff * desired.x;
    desired.x += x1;
    desired.y += y1;
    return desired;
  };
  p.a = find_point (p.A.x, p.A.y, p.C.x, p.C.y, middle);
  p.b = find_point (p.B.x, p.B.y, p.D.x, p.D.y, middle);
  p.c = find_point (p.C.x, p.C.y, p.A.x, p.A.y, middle);
  p.d = find_point (p.D.x, p.D.y, p.B.x, p.B.y, middle);
  return 0;
}
int
find_middle (polygon &p, point *middle)
{
    double k1 = 0, b1 = 0, k2 = 0, b2 = 0;
    bool m1 = false, m2 = false;
    if (fabs(p.C.x - p.A.x) < 1e-16)
        m1 = true;
    if (fabs(p.B.x - p.D.x) < 1e-16)
        m2 = true;
    if (!m1)
      {
        k1 = (p.C.y - p.A.y)/(p.C.x - p.A.x);
        b1 = p.C.y - k1 * p.C.x;
      }
    if (!m2)
      {
        k2 = (p.B.y - p.D.y)/(p.B.x - p.D.x);
        b2 = p.B.y - k2 * p.B.x;
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
        middle->x = p.A.x;
        middle->y = k2 * middle->x + b2;
      }
    else if (m2)
      {
        //function x = const connects B and D
        middle->x = p.B.x;
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
