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
    us get_u () const {return u;}
    void fill_us ();
    double get_f_value_by_ijtr (std::function<double (double, double)> f, int i, int j, int trapeze);
    void fill_points (point &A, point &B, point &C, point &D, int trapeze);


private:
    polygon *p;
    int n;
    us u;
};

#endif // GRID_H
