#ifndef __SPLINES_H__
#define __SPLINES_H__

#include "newton.hpp"
#include "data.hpp"

class SplineTuple
{
public:
    double a, b, c, d, x;

public:
    SplineTuple() = default;
    SplineTuple(double a, double b, double c, double d, double x)
        : a(a), b(b), c(c), d(d), x(x) {}
    ~SplineTuple() = default;
};

class Spline
{
public:
    Spline() = default;
    ~Spline() = default;
    static std::vector<SplineTuple> build_spline(const std::vector<Point> &values, size_t n)
    {
        std::vector<SplineTuple> splines;
        splines.resize(n - 1);
        std::fill(splines.begin(), splines.end(), SplineTuple(0, 0, 0, 0, 0));

        for (size_t i = 0; i < splines.size(); i++)
        {
            splines[i].x = values[i].getX();
            splines[i].a = values[i].getY();
        }

        splines[0].c = 0;
        splines[n - 2].c = 0;

        std::vector<double> alpha;
        alpha.resize(n - 1);
        std::fill(alpha.begin(), alpha.end(), 0);

        std::vector<double> beta;
        beta.resize(n - 1);
        std::fill(beta.begin(), beta.end(), 0);

        for (size_t i = 1; i + 1 < n; i++)
        {
            double hi = values[i].getX() - values[i - 1].getX();
            double hi1 = values[i + 1].getX() - values[i].getX();
            double delta = (values[i].getY() - values[i - 1].getY()) / hi;
            double delta1 = (values[i + 1].getY() - values[i].getY()) / hi1;
            double a = hi;
            double c = 2.0 * (hi + hi1);
            double b = hi1;
            double f = 6.0 * (delta1 - delta);
            double z = (a * alpha[i - 1] + c);
            alpha[i] = -b / z;
            beta[i] = (f - a * beta[i - 1]) / z;
        }

        for (int i = n - 3; i >= 0; i--)
        {
            splines[i].c = alpha[i] * splines[i + 1].c + beta[i];
        }

        for (int i = n - 2; i > 0; i--)
        {
            double hi = values[i].getX() - values[i - 1].getX();
            splines[i].d = (splines[i].c - splines[i - 1].c) / hi;
            splines[i].b = hi * (2.0 * splines[i].c + splines[i - 1].c) / 6.0 + (values[i].getY() - values[i - 1].getY()) / hi;
        }
        return splines;
    }

    static double spline_interpolate(const std::vector<Point> &values, size_t n, double x)
    {
        auto splines = build_spline(values, n);

        if (splines.size() == 0)
        {
            std::cout << "Splines size 0\n";
            return 0;
        }

        n = splines.size();
        SplineTuple s(0, 0, 0, 0, 0);

        if (x <= splines[0].x)
            s = splines[0];
        else if (x >= splines[n - 1].x)
            s = splines[n - 1];
        else
        {
            size_t i = 0;
            size_t j = n - 1;
            while (i + 1 < j)
            {
                int k = i + (j - i) / 2;
                if (x <= splines[k].x)
                    j = k;
                else
                    i = k;
            }
            s = splines[j];
        }

        double dx = x - s.x;
        return s.a + (s.b + (s.c / 2.0 + s.d * dx / 6.0) * dx) * dx;
    }

    static double splines_mult_int(const Data &data,
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

                y_values.push_back(Point(y_arr[i], spline_interpolate(x_values, x_values.size(), xp)));
            }
            z_values.push_back(Point(z_arr[k], spline_interpolate(y_values, y_values.size(), yp)));
        }

        return spline_interpolate(z_values, z_values.size(), zp);
    }
};

#endif // __SPLINES_H__