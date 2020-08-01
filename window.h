#ifndef WINDOW_H
#define WINDOW_H
#include "helper_functions.h"
#include "grid.h"
#include <QWidget>
#include "thread_info.h"
enum func
{
  one,
  x,
  y,
  x_plus_y,
  x_2_plus_y_2__2,
  x_2_plus_y_2,
  exp_x_2_minus_y_2,
  one_div_tw_five
};

class Window : public QWidget
{
  Q_OBJECT
public:
  Window (polygon *pol_, int n_,
          int p, double eps,
          std::function<double (double, double)> f_,
          QWidget *parent);
  ~Window ();
  void emit_calculation_completed ();
  QSize minimumSizeHint () const;
  QSize sizeHint () const;

private:
void
initialize (polygon *pol_, int n_,
            int p_, double eps_,
            std::function<double (double, double)> f_);
void
erase ();
void
before_calculation ();
void
initialize_info ();
void
initialize_barrier_and_cond ();
void
allocate_memory ();
void
allocate_info ();
void
initialize_vectors ();
void
start_threads ();
std::string
enum_to_str (func f);
std::function<double (double, double)>
enum_to_f (func f);

private:
  int n = 0;
  int threads_num = 0;
  double eps = 0.;
  polygon *pol;
  grid *gr;
  std::function<double (double, double)> f;
  builder_solver_data data;
  thread_info *info;
  pthread_barrier_t barrier;
  pthread_cond_t cond;
  int p_out;


public slots:
  void double_n ();
  void undouble_n () ;
  void after_calculation ();
signals:
  void calculation_completed ();
};

#endif // WINDOW_H
