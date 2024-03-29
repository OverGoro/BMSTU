#include "spline.hpp"
int main(int argc, char const *argv[])
{
    auto splines = Spline::read_splines("datat.txt");
    Spline::print_splines(splines);
    Spline::print_values_splines(splines, 0, 7, 0.1, "graph.txt");
    return 0;
}
