#ifndef WINDOW_H
#define WINDOW_H
#include "helper_functions.h"
#include "grid.h"
#include <QWidget>
#include "thread_info.h"
#include "painter.h"
#include <QHBoxLayout>
#include <QtWidgets/QtWidgets>
#include <string>
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
  void closeEvent(QCloseEvent *event) override;
//  QSize minimumSizeHint () const;
//  QSize sizeHint () const;

private:
void
initialize (polygon *pol_, int n_,
            int p_, double eps_,
            int func_ind);

void change_n_label ();
void change_func_label ();
void change_state_label ();
void change_fabs_max_label ();
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
std::string
int_to_str (int f);
void
set_gui ();
QString
state_to_string ();

private:
  int n = 0;
  int threads_num = 0;
  double eps = 0.;
  polygon *pol;
  std::unique_ptr<grid> gr;
  std::unique_ptr<grid> working_gr;
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

//labels
private:
  QLabel *number_of_points_label;
  QLabel *state_label;
  QLabel *function_name_label;
  QLabel *fabs_max_label;



public slots:
  void double_n ();
  void undouble_n () ;
  void change_function ();
  void after_calculation ();
  void change_state ();
  void increase ();
  void decrease ();
signals:
  void calculation_completed ();
};

#endif // WINDOW_H
