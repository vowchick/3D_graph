#ifndef WINDOW_H
#define WINDOW_H
#include "helper_functions.h"
#include "grid.h"
#include <QWidget>
#include "thread_info.h"

class Window : public QWidget
{
  Q_OBJECT
public:
  Window (polygon *pol_, int n_,
          int p, double eps,
          std::function<double (double, double)> f_,
          QWidget *parent);
  ~Window ();

private:
void
initialize (polygon *pol_, int n_,
            int p_, double eps_,
            std::function<double (double, double)> f_);
void
initialize_info ();
void
initialize_barrier ();
void
allocate_memory ();
void
initialize_vectors ();
void
erase ();
void
start_threads ();

private:
  int n = 0;
  int threads_num = 0;
  double eps = 0.;
  polygon *pol;
  grid *gr;
  std::function<double (double, double)> f;
  builder_solver_data data;
  thread_info *info;
  pthread_barrier_t *barrier;



signals:

};

#endif // WINDOW_H
