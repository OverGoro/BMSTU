#include <iostream>
#include <chrono>
#include <iomanip>

#define NUM 3e7

double mult_double(double a, double b)
{
    auto start = std::chrono::high_resolution_clock::now();
    double res;
    res = a * b;
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    return (double)duration.count();
}

double mult_double_asm(double a, double b)
{
    auto start = std::chrono::high_resolution_clock::now();
    double res;
    __asm__(
        "fld %1\n\t"
        "fld %2\n\t"
        "fmulp\n\t"
        "fstp %0\n\t"
        : "=m"(res)
        : "m"(a), "m"(b)
        :);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    return (double)duration.count();
}

float mult_float(float a, float b)
{
    auto start = std::chrono::high_resolution_clock::now();
    float res = a * b;
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    return (double)duration.count();
}

float mult_float_asm(float a, float b)
{
    auto start = std::chrono::high_resolution_clock::now();

    float res;
    __asm__(
        "fld %1\n\t"
        "fld %2\n\t"
        "fmulp\n\t"
        "fstp %0\n\t"
        : "=m"(res)
        : "m"(a), "m"(b)
        :);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    return (double)duration.count();
}

double add_float(double a, double b)
{
    auto start = std::chrono::high_resolution_clock::now();
    double res = a + b;
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    return (double)duration.count();
}

float add_float_asm(float a, float b)
{
    auto start = std::chrono::high_resolution_clock::now();
    float res;
    __asm__(
        "fld %1\n\t"
        "fld %2\n\t"
        "faddp\n\t"
        "fstp %0\n\t"
        : "=m"(res)
        : "m"(a), "m"(b)
        :);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    return (double)duration.count();
}

double add_double(double a, double b)
{
    auto start = std::chrono::high_resolution_clock::now();
    double res = a + b;
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    return (double)duration.count();
}

double add_double_asm(double a, double b)
{
    auto start = std::chrono::high_resolution_clock::now();
    double res;
    __asm__(
        "fld %1\n\t"
        "fld %2\n\t"
        "faddp\n\t"
        "fstp %0\n\t"
        : "=m"(res)
        : "m"(a), "m"(b)
        :);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    return (double)duration.count();
}

int main(int argc, char const *argv[])
{

    double time = 0;
    for (int i = 0; i < NUM; ++i)
    {
        time += mult_double(0.5, 0.6);
    }
    std::cout << "double *: " << time / NUM << " микросекунд" << std::endl;

    time = 0;
    for (int i = 0; i < NUM; ++i)
    {
        time += mult_double_asm(0.5, 0.6);
    }
    std::cout << "asm double *: " << time / NUM << " микросекунд" << std::endl;

    time = 0;
    for (int i = 0; i < NUM; ++i)
    {
        time += mult_float(0.5, 0.6);
    }
    std::cout << "float *: " << time / NUM << " микросекунд" << std::endl;

    time = 0;
    for (int i = 0; i < NUM; ++i)
    {
        time += mult_float_asm(0.5, 0.6);
    }
    std::cout << "asm float *: " << time / NUM << " микросекунд" << std::endl;

    time = 0;
    for (int i = 0; i < NUM; ++i)
    {
        time += add_double(0.5, 0.6);
    }
    std::cout << "double +: " << time / NUM << " микросекунд" << std::endl;

    time = 0;
    for (int i = 0; i < NUM; ++i)
    {
        time += add_double_asm(0.5, 0.6);
    }
    std::cout << "asm double +: " << time / NUM << " микросекунд" << std::endl;

    time = 0;
    for (int i = 0; i < NUM; ++i)
    {
        time += add_float(0.5, 0.6);
    }
    std::cout << "float +: " << time / NUM << " микросекунд" << std::endl;

    time = 0;
    for (int i = 0; i < NUM; ++i)
    {
        time += add_float_asm(0.5, 0.6);
    }
    std::cout << "asm float +: " << time / NUM << " микросекунд" << std::endl;
    return 0;
}
