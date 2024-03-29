#ifndef POINTS_HPP_
#define POINTS_HPP_

#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "error.hpp"

std::vector<std::vector<double>> points_get_closest_x(const std::vector<std::vector<double>> &points, double x, std::size_t n);

std::vector<std::vector<double>> points_duplicate_derivatives(const std::vector<std::vector<double>> &points);

void points_print(const std::vector<std::vector<double>> &points);

void points_inverse(std::vector<std::vector<double>> &points);

void points_sort_by_x(std::vector<std::vector<double>> &points);

int points_read(std::vector<std::vector<double>> &points, const char *filename);

#endif
