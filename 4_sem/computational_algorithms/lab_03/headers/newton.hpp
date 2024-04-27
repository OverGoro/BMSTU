#ifndef __NEWTON_H__
#define __NEWTON_H__

#include <numeric>
#include <iostream>
#include <vector>
#include "data.hpp"
#include "point.hpp"

class Newton
{
public:
public:
    Newton();
    ~Newton();
    // нахождение индекса ближайшей точки по значению к искомой
    static size_t prox_index(const std::vector<Point> &points, double x)
    {
        double dif = abs(points[0].getX() - x);
        size_t index = 0;
        for (size_t i = 0; i < points.size(); i++)
        {
            if (abs(points[i].getX() - x) < dif)
            {
                dif = abs(points[i].getX() - x);
                index = i;
            }
        }
        return index;
    }

    // взятие рабочих ближайших точек для расчетов
    static std::vector<Point> get_points(const std::vector<Point> &points, size_t index, size_t n)
    {
        size_t left = index;
        size_t right = index;
        for (size_t i = 0; i + 1 < n; i++)
        {
            if (i % 2 == 0)
            {
                if (left == 0)
                    ++right;
                else
                    --left;
            }
            else
            {
                if (right + 1 == points.size())
                    --left;
                else
                    ++right;
            }
        }

        std::vector<Point> res_points;
        for (size_t i = left; i <= right; i++)
            res_points.push_back(points[i]);
        return res_points;
    }
    // расчет полином Ньютона м результаты в виде таблицы всех данных f(xi .... xn)
    static std::vector<std::vector<double>> newton_table(const std::vector<Point> &table)
    {
        size_t row_count = 2;
        std::vector<std::vector<double>> sub_table;
        sub_table.resize(2);
        for (auto p : table)
        {
            sub_table[0].push_back(p.getX());
            sub_table[1].push_back(p.getY());
        }

        // Добавление столбцов
        for (size_t i = 1; i < sub_table[0].size(); i++)
        {
            sub_table.push_back(std::vector<double>());
            auto &y_row = sub_table[sub_table.size() - row_count];
            // Добавление очередного элемента
            for (size_t j = 0; j + i < sub_table[0].size(); j++)
            {
                double cur = 1;
                if (y_row[j] == std::numeric_limits<double>::infinity() && y_row[j + 1] == std::numeric_limits<double>::infinity())
                    cur = 1;
                else if (y_row[j] == std::numeric_limits<double>::infinity())
                    cur = y_row[j + 1] / (sub_table[0][j] - sub_table[0][j + i]);
                else if (y_row[j + 1] == std::numeric_limits<double>::infinity())
                {
                    // std::cout << 2 << "\n";
                    cur = y_row[j] / (sub_table[0][j] - sub_table[0][j + i]);
                }
                else
                    cur = (y_row[j] - y_row[j + 1]) / (sub_table[0][j] - sub_table[0][j + i]);
                sub_table[i + row_count - 1].push_back(cur);
            }
        }
        return sub_table;
    }

    // скомпликтовал в одну функцию
    static double newton(const std::vector<Point> &point_table, size_t n, double x)
    {
        auto table = get_points(point_table, prox_index(point_table, x), n);
        auto subs = newton_table(table);
        return count_approx(subs, x);
    }

    static double count_approx(const std::vector<std::vector<double>> &table, double x)
    {
        double y_x = 0;
        // const std::vector<double> &x_data = table[0];
        for (size_t i = 1; i < table.size(); i++)
        {
            double member_val = table[i][0];
            for (size_t j = 0; j + 1 < i; j++)
            {
                member_val *= (x - table[0][j]);
            }
            y_x += member_val;
        }
        return y_x;
    }

    // расчет трехметрной интерполяции Полином Ньютона
    static double newton_mult_int(const Data &data,
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
                {
                    x_values.push_back(Point(x_arr[j], matrix[k][i][j]));
                }
                y_values.push_back(Point(y_arr[i], newton(x_values, nx, xp)));
            }
            z_values.push_back(Point(z_arr[k], newton(y_values, ny, yp)));
        }
        return newton(z_values, nz, zp);
    }
};

Newton::Newton(/* args */)
{
}

Newton::~Newton()
{
}

#endif // __NEWTON_H__