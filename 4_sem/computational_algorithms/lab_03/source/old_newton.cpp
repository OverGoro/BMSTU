#include "old_newton.hpp"

#pragma region Help functions
static std::size_t get_closest_x_index(const std::vector<std::vector<double>> &points, double x)
{
    std::size_t closest_i = 0;
    for (std::size_t i = 1; i < points.size(); i++)
    {
        if (std::abs(points[i][0] - x) < std::abs(points[closest_i][0] - x))
            closest_i = i;
    }
    return closest_i;
}

static std::vector<std::vector<double>> points_get_closest_x(const std::vector<std::vector<double>> &points, double x, std::size_t n)
{
    std::vector<std::vector<double>> closest_points = {};

    std::size_t closest_i = get_closest_x_index(points, x);
    std::size_t start_i = closest_i, end_i = closest_i;
    for (size_t i = 1; i < n && (start_i > 0 || end_i + 1 < points.size()); i++)
    {
        if (start_i > 0 && end_i + 1 < points.size())
        {
            if (std::abs(points[start_i - 1][0] - x) < std::abs(points[end_i + 1][0] - x))
                start_i--;
            else
                end_i++;
        }
        else if (start_i > 0)
        {
            start_i--;
        }
        else if (end_i + 1 < points.size())
        {
            end_i++;
        }
    }

    for (std::size_t i = start_i; i <= end_i; ++i)
    {
        closest_points.push_back(points[i]);
    }

    return closest_points;
}

// static std::vector<std::vector<double>> points_duplicate_derivatives(const std::vector<std::vector<double>> &points)
// {
//     std::vector<std::vector<double>> duplicated_points;
//     for (const auto &p : points)
//     {
//         for (size_t i = 1; i < p.size(); i++)
//         {
//             duplicated_points.push_back(p);
//         }
//     }
//     return duplicated_points;
// }

void points_inverse(std::vector<std::vector<double>> &points)
{
    for (auto &l : points)
    {
        if (l.size() > 4)
            l.resize(4);
        std::swap(l[0], l[1]);
        if (l.size() > 2 && l[3] == 0)
            l.resize(2);
        if (l.size() > 3)
            l[3] = l[3] / l[2] / l[2] / l[2];
        if (l.size() > 2)
            l[2] = 1 / l[2];
    }
}

void points_sort_by_x(std::vector<std::vector<double>> &points)
{
    std::sort(points.begin(), points.end(), [](std::vector<double> &a, std::vector<double> &b)
              { return a[0] < b[0]; });
}

static void dif_table_set_size(std::vector<std::vector<double>> &table, const std::vector<std::vector<double>> &points)
{
    table.resize(points.size() + 1);

    // Set sizes of the table
    table[0].resize(points.size());
    table[1].resize(points.size());

    for (std::size_t i = 2; i < table.size() && table[i - 1].size() > 1; i++)
    {
        table[i].resize(table[i - 1].size() - 1);
    }
}

static void dif_table_fill(const std::vector<std::vector<double>> &points, std::vector<std::vector<double>> &table)
{
    for (std::size_t i = 0; i < points.size(); i++)
    {
        table[0][i] = points[i][0];
        table[1][i] = points[i][1];
    }

    // Fill divided differences
    int k = 1;
    for (std::size_t i = 2; i < table.size(); i++)
    {
        k *= (i - 1);
        for (std::size_t j = 0; j < table[i].size(); j++)
        {
            if (points[j + i - 1][0] != points[j][0] || points[j].size() < i + 1)
                table[i][j] = (table[i - 1][j + 1] - table[i - 1][j]) / (table[0][j + i - 1] - table[0][j]);
            else
                table[i][j] = points[j][i] / k;
        }
    }
}

static std::vector<std::vector<double>> dif_table_form(const std::vector<std::vector<double>> &points)
{
    std::vector<std::vector<double>> table;

    dif_table_set_size(table, points);

    dif_table_fill(points, table);

    return table;
}
#pragma endregion

#pragma region NewtonPolynome
NewtonPolynome::NewtonPolynome()
{
}

int NewtonPolynome::form(const std::vector<std::vector<double>> &func_points, double x, std::size_t n)
{
    if (n == 0)
        return 1;
    fill_points(func_points, x, n);

    std::vector<std::vector<double>> dif_table = dif_table_form(points);

    if (dif_table.size() == 0)
        return 1;

    fill_coefficients(dif_table);

    return 0;
}

int NewtonPolynome::form(const std::vector<Point> &points, double x, std::size_t n)
{
    if (n == 0)
        return 1;
    std::vector<std::vector<double>> tmp_vec;
    for (auto p : points)
    {
        tmp_vec.push_back({p.getX(), p.getY()});
    }
    return form(tmp_vec, x, n);
}

void NewtonPolynome::fill_coefficients(const std::vector<std::vector<double>> &dif_table)
{
    coefficients.resize(dif_table.size() - 1);
    for (size_t i = 1; i < dif_table.size(); i++)
    {
        coefficients[i - 1] = dif_table[i][0];
    }
}

void NewtonPolynome::fill_points(const std::vector<std::vector<double>> &func_points, double x, std::size_t n)
{
    points.clear();
    points = points_get_closest_x(func_points, x, n);
    std::sort(points.begin(), points.end(), [](std::vector<double> a, std::vector<double> b)
              { return a[0] < b[0]; });
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

double NewtonPolynome::newton(const std::vector<Point> &points, std::size_t n, double x)
{
    NewtonPolynome tmp_polynome;
    tmp_polynome.form(points, x, n);
    return tmp_polynome.count(x);
}

double NewtonPolynome::mult_int(const Data &data, size_t nx, size_t ny, size_t nz, double xp, double yp, double zp)
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
            {
                x_values.push_back(Point(x_arr[j], matrix[k][i][j]));
            }
            y_values.push_back(Point(y_arr[i], newton(x_values, nx, xp)));
        }
        z_values.push_back(Point(z_arr[k], newton(y_values, ny, yp)));
    }
    return newton(z_values, nz, zp);
}

#pragma endregion
