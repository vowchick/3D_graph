#include "window.h"

QSize Window::minimumSizeHint () const
{
    return QSize (100, 100);
}

QSize Window::sizeHint () const
{
    return QSize (1000, 1000);
}
std::string
Window::int_to_str (int f)
{
  switch (f)
    {
    case 0:
      return "1";
    case 1:
      return "x";
    case 2:
      return "y";
    case 3:
      return "x + y";
    case 4:
      return "sqrt (x^2 + y^2)";
    case 5:
      return "x^2 + y^2";
    case 6:
      return "exp (x^2 - y^2)";
    case 7:
      return "(25 * (x^2 + y^2) + 1)^(-1)";
    }
  return "0";
}
std::function<double (double, double)>
get_f (int f_)
{
  std::function<double (double, double)> f =
      [] (double x, double y)
  {
    FIX_UNUSED (x, y);
    return 0;
    };;
  switch (f_)
    {
    case 0:
      f = [] (double x, double y)
      {
        FIX_UNUSED (x, y);
        return 1;
        };
      return f;
    case 1:
      f = [] (double x, double y)
      {
        FIX_UNUSED (x, y);
        return x;
        };
      return f;
    case 2:
      f = [] (double x, double y)
      {
        FIX_UNUSED (x, y);
        return y;
        };
      return f;
    case 3:
      f = [] (double x, double y)
      {
        FIX_UNUSED (x, y);
        return x + y;
        };
      return f;;
    case 4:
      f = [] (double x, double y)
      {
        FIX_UNUSED (x, y);
        return sqrt (x * x + y * y);
        };
      return f;
    case 5:
      f = [] (double x, double y)
      {
        FIX_UNUSED (x, y);
        return x * x + y * y;
        };
      return f;
    case 6:
      f = [] (double x, double y)
      {
        FIX_UNUSED (x, y);
        return exp (x * x - y * y);
        };
      return f;
    case 7:
      f = [] (double x, double y)
      {
        FIX_UNUSED (x, y);
        return 1. / (25 * (x * x + y * y) + 1);
        };
      return f;
    }
  return f;
}
