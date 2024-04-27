#include <iostream>
#include <iomanip>
double sin_asm(double pi)
{
    double res;
    __asm__(
        "fld %1\n\t"
        "fsin\n\t"
        "fstp %0\n\t"
        : "=m"(res)
        : "m"(pi)
        : );
    return res;
}
double sin_asm_div_2(double pi)
{
    double res;
    const int d = 2;
    __asm__(
        "fld %1\n\t"
        "fild %2\n\t"
        "fdivp\n\t"
        "fsin\n\t"
        "fstp %0\n\t"
        : "=m"(res)
        : "m"(pi), "m"(d)
        : );
    return res;
}


double sin_asm_fldpi()
{
    double res;
    __asm__(
        "fldpi\n\t"
        "fsin\n\t"
        "fstp %0\n\t"
        : "=m"(res)
        : 
        : );
    return res;
}

double sin_asm_fldpi_div_2()
{
    double res;
    const int d = 2;
    __asm__(
        "fldpi\n\t"
        "fild %1\n\t"
        "fdivp\n\t"
        "fsin\n\t"
        "fstp %0\n\t"
        : "=m"(res)
        : "m"(d)
        : );
    return res;
}

int main(int argc, char const *argv[])
{
    double pi_1 = 3.14;
    double pi_2 = 3.141596;
    std::cout << std::setprecision(30) << "sin " << pi_1 << "\t" << sin_asm(pi_1) << "\n";
    std::cout << std::setprecision(30) << "sin " << pi_2  << "\t" << sin_asm(pi_2) << "\n";
    std::cout << std::setprecision(30) << "sin " << "def "  << "\t\t\t" << sin_asm_fldpi() << "\n";
    std::cout << std::setprecision(30) << "sin " << pi_1  << "\t" << sin_asm_div_2(pi_1) << "\n";
    std::cout << std::setprecision(30) << "sin " << pi_2  << "\t" << sin_asm_div_2(pi_2) << "\n";
    std::cout << std::setprecision(30) << "sin " << "def "  << "\t\t\t" << sin_asm_fldpi_div_2() << "\n";

    return 0;
}
