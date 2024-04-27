#include "splines.hpp"
#include "newton.hpp"
#include "newton_splines.hpp"
#include "create_table.hpp"
#include "old_newton.hpp"
#include <iostream>


#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 60

static void printProgress(double percentage) {
    int val = (int) (percentage * 100);
    int lpad = (int) (percentage * PBWIDTH);
    int rpad = PBWIDTH - lpad;
    printf("\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
    fflush(stdout);
}

int main(/*int argc, char const *argv[]*/)
{
    print_func();
    Data d = read_table("out.txt");
    // std::cout << d;
    double x,y,z;
    // std::cout << "x: ";
    // std::cin >> x;
    // std::cout << "y: ";
    // std::cin >> y;
    // std::cout << "z: ";
    // std::cin >> z;

    x = -1.152;
    y = 1.141;
    z = 1.43;
    // 2,3,5

    size_t nx, ny, nz;
    std::cout << "степень аппроксимации nx: ";
    std::cin >> nx;
    std::cout << "степень аппроксимации ny: ";
    std::cin >> ny;
    std::cout << "степень аппроксимации nz: ";
    std::cin >> nz;

    std::cout << "Real: ";
    std::cout << func(x,y,z) << "\n";
    std::cout << "Newton:";
    std::cout << "u = f(x, y, z) = " << NewtonPolynome::mult_int(d, nx, ny, nz, x, y, z) << "\n";

    std::cout << "Spline:";
    std::cout << "u = f(x, y, z) = " << Spline::splines_mult_int(d, x, y, z) << "\n";

    std::cout << "Spline + newton result:";
    std::cout << "u = f(x, y, z) = " << spline_newton_mult_int(d, nx, ny, nz, x, y, z) << "\n";

    double min_x = -5, max_x = 5;
    double min_y = -5, max_y = 5;
    double min_z = -5, max_z = 5;

    size_t num = 10;

    double step_x = (max_x - min_x) / num;
    double step_y = (max_y - min_y) / num;
    double step_z = (max_z - min_z) / num;

    std::ofstream os_n("out_newton.txt");
    std::ofstream os_s("out_spline.txt");
    std::ofstream os_sn("out_newton_spline.txt");

    double percent = 0;
    double percent_step = 1.0 / num / num / num;
    for (double cur_x = min_x; max_x - cur_x > 1e-6; cur_x += step_x)
    {
        for (double cur_y = min_y; max_y - cur_y > 1e-6; cur_y += step_y)
        {
            for (double cur_z = min_z; max_z - cur_z > 1e-6; cur_z += step_z)
            {
                os_n << cur_x << " " << cur_y << " " << cur_z << " " << NewtonPolynome::mult_int(d, nx, ny, nz, cur_x, cur_y, cur_z) << "\n";
                os_s << cur_x << " " << cur_y << " " << cur_z << " " << Spline::splines_mult_int(d, cur_x, cur_y, cur_z) << "\n";
                os_sn << cur_x << " " << cur_y << " " << cur_z << " " << spline_newton_mult_int(d, nx, ny, nz, cur_x, cur_y, cur_z) << "\n";
                printProgress(percent);
                percent += percent_step;
            }
        }
    }
    std::cout << "\n";
    os_n.close();
    os_s.close();
    os_sn.close();

    return 0;
}
