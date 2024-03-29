#include "dif_table.hpp"

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

std::vector<std::vector<double>> dif_table_form(const std::vector<std::vector<double>>& points)
{
    std::vector<std::vector<double>> table;

    dif_table_set_size(table, points);

    dif_table_fill(points, table);

    return table;
}



void dif_table_print(const std::vector<std::vector<double>> &table)
{
    for (const auto &l : table)
    {
        for (const auto &p : l)
            std::cout << p << " ";
        std::cout << "\n";
    }
}
