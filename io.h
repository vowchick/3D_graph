#ifndef IO_H
#define IO_H
#include <strings.h>
#include <fstream>
#include<string>
#include "helper_functions.h"

template <typename func>
void split (std::vector<std::string> &, std::string &, func f);
int read_polygon_from_file (char *file_name,
                        polygon &Polygon);
void print_polygon (polygon P);
int find_inside_points (polygon &p);
int find_middle (polygon &p, point *middle);

int process_input (char *argv[], input &in, polygon &pol);
#endif // IO_H
