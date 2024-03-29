#ifndef NEWTON_HPP_
#define NEWTON_HPP_

#include "points.hpp"
#include "dif_table.hpp"
#include "error.hpp"
#include <vector>

class NewtonPolynome
{
private:
    std::vector<std::vector<double>> points;
    std::vector<double> coefficients;
public:
    NewtonPolynome();
    int form(std::vector<std::vector<double>> &points, double x, std::size_t n);
    void fill_coefficients(std::vector<std::vector<double>> &dif_table);
    void fill_points(std::vector<std::vector<double>> &func_points, double x, std::size_t n);
    double count(double x);
    void print();
};

#endif
