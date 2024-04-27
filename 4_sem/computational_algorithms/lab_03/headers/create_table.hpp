#ifndef __CREATE_TABLE_H__
#define __CREATE_TABLE_H__

#include <cmath>
#include <fstream>
#include <vector>
#include <iostream>

std::vector<double> linspace(double start_in, double end_in, int num_in)
{

    std::vector<double> linspaced;

    double start = static_cast<double>(start_in);
    double end = static_cast<double>(end_in);
    double num = static_cast<double>(num_in);

    if (num == 0)
    {
        return linspaced;
    }
    if (num == 1)
    {
        linspaced.push_back(start);
        return linspaced;
    }

    double delta = (end - start) / (num - 1);

    for (int i = 0; i < num - 1; ++i)
    {
        linspaced.push_back(start + delta * i);
    }
    linspaced.push_back(end); // I want to ensure that start and end
                              // are exactly the same as the input
    return linspaced;
}

double func(double x, double y, double z)
{
    return exp(2 * x - y) * z * z;
}

// double func(double x, double y, double z)
// {
//     if (fabs(x + y) < 1e-8)
//     {
//         return 1e+8 - z;
//     }
//     else
//     {
//         return 1 / (x + y) - z;
//     }
// }

void print_func()
{
    std::ofstream os("out.txt");

    size_t step = 10;

    double x_min = -5;
    double x_max = 5;
    size_t x_count = (x_max - x_min) * step;

    double y_min = -3;
    double y_max = 4;
    size_t y_count = (y_max - y_min) * step;

    double z_min = -1;
    double z_max = 2;
    size_t z_count = (z_max - z_min) * step;

    os << x_count << " " << y_count << " " << z_count << "\n";

    std::vector<double> x = linspace(x_min, x_max, x_count);
    std::vector<double> y = linspace(y_min, y_max, y_count);
    std::vector<double> z = linspace(z_min, z_max, z_count);

    // for (auto e : x)
    // {
    //     std::cout << e << " ";
    // }
    // std::cout << "\n";

    // double c = x_min;
    // for (size_t i = 0; i < x_count; i++)
    // {
    //     x[i] = c;
    //     c += (x_max - x_min) / (x_count - 1);
    // }

    // c = y_min;
    // for (size_t i = 0; i <= y_count; i++)
    // {
    //     y[i] = c;
    //     c += (y_max - y_min) / (y_count - 1);
    // }

    // c = z_min;
    // for (size_t i = 0; i <= z_count; i++)
    // {
    //     z[i] = c;
    //     c += (z_max - z_min) / (z_count - 1);
    // }

    for (auto e : x)
        os << e << " ";
    os << "\n";
    for (auto e : y)
        os << e << " ";
    os << "\n";
    for (auto e : z)
        os << e << " ";
    os << "\n";

    for (auto zz : z)
    {
        for (auto yy : y)
        {
            for (auto xx : x)
            {
                os << func(xx, yy, zz) << " ";
            }
            os << "\n";
        }
    }
}

#endif // __CREATE_TABLE_H__