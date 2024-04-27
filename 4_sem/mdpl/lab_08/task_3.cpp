#include <cmath>
#include <iostream>

extern "C"
{
    double get_root(double x_start, double x_end, double eps);
}

double f(double x) {
    return sin(x * x + 5 * x); // Заменить функцией, корни которой мы ищем
}

// a, b - пределы хорды, epsilon — необходимая погрешность
double findRoot(double a, double b, double epsilon) {
    while(fabs(b - a) > epsilon) {
        a = a - (b - a) * f(a) / (f(b) - f(a));
        b = b - (a - b) * f(b) / (f(a) - f(b));
    }
    // a, b — (i - 1)-й и i-й члены

    return b;
}

int main(int argc, char const *argv[])
{
    double start_x = 0.3;
    double end_x =0.5;
    double eps = 0.001;

    std::cout << "Start x: ";
    std::cin >> start_x;

    std::cout << "End x: ";
    std::cin >> end_x;

    std::cout << "Eps: ";
    std::cin >> eps;


    double res = 0;

    res = findRoot(start_x, end_x, eps);

    std::cout << "C++ answer: " << res << "\n";

    res = get_root(start_x, end_x, eps);

    std::cout <<"asm answer: " << res << "\n";

    return 0;
}
