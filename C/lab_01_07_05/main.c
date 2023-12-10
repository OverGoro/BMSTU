// Городский Юрий ИУ7-22Б
#include <stdio.h>
#include <math.h>

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2

// Расчет значения ряда
// х - значение х
// epsilon - точность
double count_row(double x, double epsilon)
{   
    int member_num = 1;
    double s, member;

    s = 1;
    member = x * x / 2;
    while (fabs(member) > epsilon)
    {
        s += member;
        member_num += 1;
        member = member * x * x * (2 * member_num - 1) / (2 * member_num);
    }

    return s;
}
int main(void)
{
    double x, epsilon;
    double f, s;
    double rel_delta, abs_delta;
    // Ввод
    printf("Input x, epsilon: ");
    if (scanf("%lf%lf", &x, &epsilon) != 2)
    {
        printf("IO Error\n");
        return ERR_IO;
    }

    if (epsilon <= 0 || epsilon > 1)
    {
        printf("Range error: wrong epsilon\n");
        return ERR_RANGE;
    }
    if (fabs(x) >= 1)
    {
        printf("Range error: wrong x\n");
        return ERR_RANGE;
    }

    f = 1 / sqrt(1 - x * x); // Значение функции

    s = count_row(x, epsilon); // Значение ряда

    abs_delta = fabs(f - s); // Абсолютная погрешность
    rel_delta = abs_delta / fabs(f); // Относительная погрешность
    
    printf("%.6lf\n%.6lf\n%.6lf\n%.6lf\n", s, f, abs_delta, rel_delta);

    return OK;
}
