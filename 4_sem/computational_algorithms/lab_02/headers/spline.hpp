#ifndef SPLINE_HPP__
#define SPLINE_HPP__
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "newton.hpp"

class Spline
{
private:
    double a, b, c, d;
    double x_0, y_0, x_1, y_1;

    double h;

    double Xi, Nu; // Вспомогательные значения при расчете C

    // Вспомгательное значение при расчете Nu
    double fi(const Spline &prev_spline) const;

    void set_Xi(const Spline &prev_prev_spline, const Spline &prev_spline);
    void set_Xi(double xi);

    void set_Nu(const Spline &prev_prev_spline, const Spline &prev_spline);
    void set_Nu(double nu);

    void set_b();   // Для последнего
    void set_b(const Spline &next_spline);// Для остальных

    void set_c(const Spline &next_spline);
    void set_c(double c);

    void set_d(); // Для последнего
    void set_d(const Spline &next_spline); // Для остальных

public:
    Spline();
    ~Spline();
    Spline(double x_0, double y_0, double x_1, double y_1);
    void print() const;
    double operator ()(double x) const;
    bool contain_x(double x) const;
    

    static void print_splines(const std::vector<Spline> &splines);
    static std::vector<Spline> generate_splines(std::vector<double> &x, std::vector<double> &y);
    static std::vector<Spline> generate_splines_1(std::vector<double> &x, std::vector<double> &y);
    static std::vector<Spline> generate_splines_2(std::vector<double> &x, std::vector<double> &y);
    static std::vector<Spline> read_splines(std::string filename);
    static void print_values_splines(const std::vector<Spline> &splines, double x_0, double x_1, double step, std::string filename);
};

#endif