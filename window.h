#ifndef WINDOW_H
#define WINDOW_H
#include "helper_functions.h"
#include "grid.h"
#include <QWidget>
#include "thread_info.h"
#include "painter.h"
#include <QHBoxLayout>
#include <QtWidgets/QtWidgets>
class Window : public QWidget
{
  Q_OBJECT
public:
  Window (polygon *pol_, int n_,
          int p, double eps,
          int func_ind,
          QWidget *parent);
  ~Window ();
  void emit_calculation_completed ();
  void set_approx (double *approx);
  void update_surface ();
//  QSize minimumSizeHint () const;
//  QSize sizeHint () const;

private:
void
initialize (polygon *pol_, int n_,
            int p_, double eps_,
            int func_ind);

void update_surface_coeffs ();
void
set_f ();
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
void closeEvent(QCloseEvent *event) override;
std::string
int_to_str (int f);

private:
  int n = 0;
  int threads_num = 0;
  double eps = 0.;
  polygon *pol;
  std::unique_ptr<grid> gr;
  std::function<double (double, double)> f;
  int func_ind;
  std::string func_name;
  builder_solver_data data;
  std::unique_ptr<thread_info []> info_ptr;
  thread_info *info;
  pthread_barrier_t barrier;
  pthread_cond_t cond;
  int p_out;
  painter *drawer;
  state st = given_function;



public slots:
  void double_n ();
  void undouble_n () ;
  void change_function ();
  void after_calculation ();
  void change_state ();
signals:
  void calculation_completed ();
};

#endif // WINDOW_H
