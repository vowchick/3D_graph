#ifndef WINDOW_H
#define WINDOW_H
#include "helper_functions.h"
#include <QWidget>

class Window : public QWidget
{
  Q_OBJECT
public:
  Window (polygon *pol_, int n_,
          int p, double eps,
          std::function<double (double, double)> f_,
          QWidget *parent);

private:
void
initialize (polygon *pol_, int n_,
            int p_, double eps_,
            std::function<double (double, double)> f_);
void
allocate_memory ();
void
erase ();

private:
  int n = 0;
  int threads_num = 0;
  double eps = 0.;
  polygon *pol;
  std::function<double (double, double)> f;
  builder_solver_data data;



signals:

};

#endif // WINDOW_H
