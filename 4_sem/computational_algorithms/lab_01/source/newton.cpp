#include "../headers/newton.hpp"
#include "newton.hpp"

NewtonPolynome::NewtonPolynome()
{

}

int NewtonPolynome::form(std::vector<std::vector<double>> &func_points, double x, std::size_t n)
{
    if (n == 0)
        return ERR_RANGE;
    fill_points(func_points, x, n);

    std::vector<std::vector<double>> dif_table = dif_table_form(points);
    
    if (dif_table.size() == 0)
        return ERR_RANGE;

    fill_coefficients(dif_table);

    return OK;
}

void NewtonPolynome::fill_coefficients(std::vector<std::vector<double>> &dif_table)
{
    coefficients.resize(dif_table.size() - 1);
    for (size_t i = 1; i < dif_table.size(); i++)
    {
        coefficients[i - 1] = dif_table[i][0];
    }
}

void NewtonPolynome::fill_points(std::vector<std::vector<double>> &func_points, double x, std::size_t n)
{
    points.clear();
    points = points_get_closest_x(func_points, x, n);
    std::sort(points.begin(), points.end(), [](std::vector<double> a, std::vector<double> b){return a[0] < b[0];});
    for (auto &p : points)
        p.resize(2);
}
double NewtonPolynome::count(double x)
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

void NewtonPolynome::print()
{
    std::cout << "Точки:\n";
    points_print(points);

    std::cout << "Таблица разностей:\n";
    std::vector<std::vector<double>> dif_table = dif_table_form(points);
    dif_table_print(dif_table);
    
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

