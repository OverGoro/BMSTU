#include "data.hpp"

Data read_table(const std::string &filename)
{
    Data d;
    std::ifstream f(filename);
    int n, m, k;
    f >> n >> m >> k;
    d.x_arr.resize(n);
    d.y_arr.resize(m);
    d.z_arr.resize(k);

    for (int i = 0; i < n; ++i)
        f >> d.x_arr[i];
    for (int i = 0; i < m; ++i)
        f >> d.y_arr[i];
    for (int i = 0; i < k; ++i)
        f >> d.z_arr[i];

    d.matrix = std::vector<std::vector<std::vector<double>>>(k, std::vector<std::vector<double>>(m, std::vector<double>(n)));

    for (int kk = 0; kk < k; ++kk)
    {
        for (int mm = 0; mm < m; ++mm)
        {
            for (int nn = 0; nn < n; ++nn)
            {
                f >> d.matrix[kk][mm][nn];
            }
        }
    }
    f.close();
    return d;
}

std::ostream &operator<<(std::ostream &os, const Data &d)
{
    for (size_t k = 0; k < d.z_arr.size(); ++k)
    {
        std::cout << "z = " << d.z_arr[k] << "\n";
        std::cout << "+" << std::setw(10) << std::setfill('-') << "+" << "\n";
        std::cout << "| " << std::setw(6) << std::setfill(' ') << "Y / X" << " ";
        for (size_t i = 0; i < d.x_arr.size(); ++i)
        {
            std::cout << "| " << std::setw(6) << std::fixed << std::setprecision(2) << d.x_arr[i] << " ";
        }
        std::cout << "|" << "\n";
        std::cout << "+" << std::setw(10) << std::setfill('-') << "+" << "\n";
        for (size_t i = 0; i < d.matrix[k].size(); ++i)
        {
            std::cout << "| " << std::setfill(' ') << std::setw(6) << std::fixed << std::setprecision(3) << d.y_arr[i] << " ";
            for (size_t j = 0; j < d.matrix[k][i].size(); ++j)
            {
                if (d.matrix[k][i][j] == std::numeric_limits<double>::infinity())
                {
                    std::cout << "| " << std::setw(6) << "inf ";
                }
                else
                {
                    std::cout << "| " << std::setw(6) << std::fixed << std::setprecision(3) << d.matrix[k][i][j] << " ";
                }
            }
            std::cout << "|" << "\n";
        }
        std::cout << "+" << std::setw(10) << std::setfill('-') << "+" << "\n";
    }
    return os;
}

