#include "../headers/ermit.hpp"
#include "ermit.hpp"

ErmitPolynome::ErmitPolynome()
{
}

int ErmitPolynome::form(const std::vector<std::vector<double>> &func_points, double x, std::size_t n)
{
    if (n == 0)
        return ERR_RANGE;
    fill_points(func_points, x, n);

    dif_table = dif_table_form(points);

    if (dif_table.size() == 0)
        return ERR_RANGE;

    fill_coefficients(dif_table);

    return OK;
}

void ErmitPolynome::fill_points(const std::vector<std::vector<double>> &func_points, double x, std::size_t n)
{
    std::vector<std::vector<double>> tmp_points = points_get_closest_x(func_points, x, n);
    std::sort(tmp_points.begin(), tmp_points.end(), [](std::vector<double> a, std::vector<double> b){return a[0] > b[0];});
    points.clear();
    points = points_duplicate_derivatives(tmp_points);
}

void ErmitPolynome::fill_coefficients(std::vector<std::vector<double>> &dif_table)
{
    coefficients.resize(dif_table.size() - 1);
    for (size_t i = 1; i < dif_table.size(); i++)
    {
        coefficients[i - 1] = dif_table[i][0];
    }
}

double ErmitPolynome::count(double x)
{
    double cur_x = 1;
    double res = 0;
    for (size_t i = 0; i < coefficients.size(); i++)
    {
        res += cur_x * coefficients[i];
        cur_x *= (x - points[i][0]);
    }
    return res;
}

void ErmitPolynome::print()
{
    std::cout << "Points:\n";
    points_print(points);

    std::cout << "Dif table:\n";
    dif_table_print(dif_table);

    print_equation();
}

void ErmitPolynome::print_equation()
{
    std::cout << "P(x) = " << coefficients[0] << " + \n";
    for (std::size_t i = 1; i < coefficients.size(); i++)
    {
        if (coefficients[i] > 0)
            std::cout << "+";
        std::cout << coefficients[i];
        for (size_t j = 0; j < i; j++)
        {
            if (points[j][0] < 0)
                std::cout << "(x + " << std::abs(points[j][0]) << ")";
            else
                std::cout << "(x - " << points[j][0] << ")";
        }
        std::cout << "\n";
    }
}
