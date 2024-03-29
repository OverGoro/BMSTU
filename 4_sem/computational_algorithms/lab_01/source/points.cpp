#include "points.hpp"

std::size_t get_closest_x_index(const std::vector<std::vector<double>> &points, double x)
{
    std::size_t closest_i = 0;
    for (std::size_t i = 1; i < points.size(); i++)
    {
        if (std::abs(points[i][0] - x) <  std::abs(points[closest_i][0] - x))
            closest_i = i;
    }
    return closest_i;
}

std::vector<std::vector<double>> points_get_closest_x(const std::vector<std::vector<double>> &points, double x, std::size_t n)
{
    std::vector<std::vector<double>> closest_points = {};
    
    std::size_t closest_i = get_closest_x_index(points, x);
    std::size_t start_i = closest_i, end_i = closest_i;
    for (size_t i = 1; i < n && (start_i > 0 || end_i + 1 < points.size()); i++)
    {
        if (start_i > 0 && end_i + 1 < points.size())
        {
            if (std::abs(points[start_i - 1][0] - x) <  std::abs(points[end_i + 1][0] - x))
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

std::vector<std::vector<double>> points_duplicate_derivatives(const std::vector<std::vector<double>> &points)
{
    std::vector<std::vector<double>> duplicated_points;
    for (const auto &p : points)
    {
        for (size_t i = 1; i < p.size(); i++)
        {
            duplicated_points.push_back(p);
        }
    }
    return duplicated_points;
}


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
    std::sort(points.begin(), points.end(), [](std::vector<double> &a, std::vector<double>&b){return a[0] < b[0];});
}

void points_print(const std::vector<std::vector<double>> &points)
{
    for (const auto &l : points)
    {
        for (const auto &p : l)
            std::cout << p << " ";
        std::cout << "\n";
    }
}

int points_read(std::vector<std::vector<double>> &points, const char *filename)
{
    int rc = OK;
    std::ifstream file(filename);
    if (!file.is_open())
    {
        rc = ERR_FILE;
    }

    // Чтение заголовка
    std::string header_line;
    std::getline(file, header_line);

    // Чтение данных точек
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        double num;
        std::vector<double> numbers;
        while (iss >> num)
        {
            numbers.push_back(num);
        }
        if (numbers.size() > 1)
            points.push_back(numbers);
    }

    if (rc == ERR_IO && file.eof() != 0) rc = OK;
    file.close();
    return rc;
}
