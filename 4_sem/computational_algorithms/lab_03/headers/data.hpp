#ifndef __DATA_H__
#define __DATA_H__

#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <limits>
#include <numeric>

class Data
{
public:
    std::vector<double> x_arr;
    std::vector<double> y_arr;
    std::vector<double> z_arr;
    std::vector<std::vector<std::vector<double>>> matrix;

public:
    Data() = default;
    ~Data() = default;
};

Data read_table(const std::string &filename);

std::ostream &operator<<(std::ostream &os, const Data &d);

#endif // __DATA_H__