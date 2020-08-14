#ifndef GRID_H
#define GRID_H

#include "structs_and_stuff.h"
#include "helper_functions.h"

class grid
{
public:
    grid();
    grid (polygon *p_, int n_);

    polygon* get_polygon () const {return p;}
    int get_n () const {return n;}
    void set_n (int n_) {n = n_;}
    us get_u () const {return u;}
    Js get_J () const {return J;}
    void fill_us ();
    void fill_u2s ();

    void fill_js (polygon *p, int n);
//    double get_f_value_by_ijtr (std::function<double (double, double)> f, int i, int j, int trapeze);
    double get_f_value_by_ijtr (std::function<double (double, double)> f, int i, int j, int trapeze, int n);
    double get_value (std::vector<double> f, double x, double y, int trapeze_num, int odd);
    void fill_points (point &A, point &B, point &C, point &D, int trapeze);

    double get_width () const { return width; }
    double get_height () const { return height; }

private:
  void find_width ();
  void find_height ();
  int find_index (point a, point b, point moveac, point movebc, point xy, point second_point_for_line);
  triangle which_triangle (point xy, triangle one, triangle two);
  void fill_triangles (triangle &one, triangle &two, int i, int j);
  double interpolate (std::vector<double> f, triangle tri, point xy);

private:
    polygon *p;
    int n;
    us u;
    Js J;
    double width = 0;
    double height = 0;
};

#endif // GRID_H
