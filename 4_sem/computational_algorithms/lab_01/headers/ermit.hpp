#ifndef ERMITPOLYNOME_H
#define ERMITPOLYNOME_H

#include "points.hpp"
#include "dif_table.hpp"
#include "error.hpp"
#include <vector>

class ErmitPolynome
{
private:
    std::vector<std::vector<double>> points;
    std::vector<std::vector<double>> dif_table;
    std::vector<double> coefficients;
    
    void fill_coefficients(std::vector<std::vector<double>> &dif_table);
public:
    ErmitPolynome();
    int form(const std::vector<std::vector<double>> &points, double x, std::size_t n);
    void fill_points(const std::vector<std::vector<double>> &func_points, double x, std::size_t n);
    double count(double x);
    void print();
    void print_equation();
};

#endif // ERMITPOLYNOME_H
