#include "window.h"

//QSize Window::minimumSizeHint () const
//{
//    return QSize (100, 100);
//}

//QSize Window::sizeHint () const
//{
//    return QSize (1000, 1000);
//}
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
    return 0 + x * 0 + y * 0;
    };;
  switch (f_)
    {
    case 0:
      f = [] (double x, double y)
      {
        return 1 + x * 0 + y * 0;
        };
      return f;
    case 1:
      f = [] (double x, double y)
      {
        return x + y * 0;
        };
      return f;
    case 2:
      f = [] (double x, double y)
      {
        return y + x * 0;
        };
      return f;
    case 3:
      f = [] (double x, double y)
      {
        return x + y;
        };
      return f;
    case 4:
      f = [] (double x, double y)
      {
        return sqrt (x * x + y * y);
        };
      return f;
    case 5:
      f = [] (double x, double y)
      {
        return x * x + y * y;
        };
      return f;
    case 6:
      f = [] (double x, double y)
      {
        return exp (x * x - y * y);
        };
      return f;
    case 7:
      f = [] (double x, double y)
      {
        return 1. / (25 * (x * x + y * y) + 1);
        };
      return f;
    }
  return f;
}

QString
Window::state_to_string ()
{
  switch (st)
    {
      case given_function:
        return "Given function";
      case approximation:
        return "Approximation";
      case error:
        return "Residual";
    }
  abort ();
  return "";
}

void
Window::set_gui ()
{
  gr.reset (new grid (pol, n));
  drawer = new painter (gr.get (), f, this);
  drawer->set_Window (this);
  QVBoxLayout *v_layout = new QVBoxLayout (this);

  QHBoxLayout *labels_layout = new QHBoxLayout (this);
  QVBoxLayout *labels_layout1 = new QVBoxLayout (this);
  QVBoxLayout *labels_layout2 = new QVBoxLayout (this);

  QVBoxLayout *drawer_layout = new QVBoxLayout (this);

  number_of_points_label = new QLabel (this);
  change_n_label ();

  function_name_label = new QLabel (this);
  change_func_label ();

  state_label = new QLabel (this);
  change_state_label ();

  fabs_max_label = new QLabel (this);
  change_fabs_max_label ();

  perturbation_label = new QLabel (this);
  change_perturbation_label ();

  s_label = new QLabel (this);
  change_s_label ();

  drawer_layout->addWidget (drawer);

  labels_layout->setAlignment (Qt::AlignLeft);
  labels_layout1->addWidget (number_of_points_label);
  labels_layout1->addWidget (function_name_label);
  labels_layout1->addWidget (fabs_max_label);
  labels_layout1->addWidget (perturbation_label);
  labels_layout2->addWidget (state_label);
  labels_layout1->addWidget (s_label);
  labels_layout2->setAlignment(Qt::AlignTop);

  labels_layout->addLayout (labels_layout1);
  labels_layout->addLayout (labels_layout2);

  v_layout->addLayout (labels_layout);
  v_layout->addLayout (drawer_layout);


  v_layout->setStretchFactor (labels_layout, 0);
  v_layout->setStretchFactor (drawer_layout, 1);
}

void
Window::change_n_label ()
{
  QString s = NUMBER_OF_SPLITS + QString::number (n);
  number_of_points_label->setText (s);
  printf ("n = %d\n", n);
}

void
Window::change_func_label ()
{
  QString s = FUNCTION_NAME + QString::fromStdString (func_name);
  function_name_label->setText (s);
}

void
Window::change_state_label ()
{
  QString s = "Current state: " + state_to_string ();
  state_label->setText (s);
}

void
Window::change_fabs_max_label ()
{
  double ans = drawer->get_fabs_max ();
  QString s = "max |f| = " + QString::number (ans, 'e', 4);
  fabs_max_label->setText (s);
  printf ("max |f| = %e\n", ans);
}

void
Window::change_perturbation_label ()
{
  QString s = "p = " + QString::number (drawer->get_perturbation ());
  perturbation_label->setText (s);
}

void
Window::change_s_label ()
{
  QString s = "s = " + QString::number (drawer->get_s ());
  s_label->setText (s);
}
