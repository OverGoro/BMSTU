#ifndef __MY_NEWTON_H__
#define __MY_NEWTON_H__

#include "point.hpp"
#include "data.hpp"
#include <vector>
#include <algorithm>

class NewtonPolynome
{
private:
    std::vector<std::vector<double>> points;
    std::vector<double> coefficients;
public:
    NewtonPolynome();
    int form(const std::vector<Point> &points, double x, std::size_t n);
    int form(const std::vector<std::vector<double>> &points, double x, std::size_t n);
    void fill_coefficients(const std::vector<std::vector<double>> &dif_table);
    void fill_points(const std::vector<std::vector<double>> &func_points, double x, std::size_t n);
    double count(double x);
    static double newton(const std::vector<Point> &points, std::size_t n, double x);
    static double mult_int(const Data &data,
                           size_t nx, size_t ny, size_t nz,
                           double xp, double yp, double zp);
    void print();
};

#endif // __MY_NEWTON_H__