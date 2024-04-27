#ifndef __NEWTON_SPLINES_H__
#define __NEWTON_SPLINES_H__

#include "old_newton.hpp"
#include "splines.hpp"

double spline_newton_mult_int(const Data &data,
                              size_t nx, size_t ny, size_t nz,
                              double xp, double yp, double zp)
{
    const auto &matrix = data.matrix;
    const auto &x_arr = data.x_arr;
    const auto &y_arr = data.y_arr;
    const auto &z_arr = data.z_arr;

    std::vector<Point> z_values;
    for (size_t k = 0; k < z_arr.size(); k++)
    {
        std::vector<Point> y_values;

        for (size_t i = 0; i < y_arr.size(); i++)
        {
            std::vector<Point> x_values;
            for (size_t j = 0; j < x_arr.size(); j++)
                x_values.push_back(Point(x_arr[j], matrix[k][i][j]));
            y_values.push_back(Point(y_arr[i], NewtonPolynome::newton(x_values, nx, xp)));
        }
        z_values.push_back(Point(z_arr[k], Spline::spline_interpolate(y_values, y_values.size(), yp)));

    }
    return NewtonPolynome::newton(z_values, nz, zp);
}

#endif // __NEWTON_SPLINES_H__