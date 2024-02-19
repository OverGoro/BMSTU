// Городский Юрий ИУ7-22Б
#include <stdio.h>
#include <math.h>

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2

// Расчет элемента ряда
// double x - значение х
// int n - номер элемента в ряду
double count_seq_element(double x, int n)
{
    return sqrt(x / n);
}

int calculate(double *g)
{
    double x_seq, x;
    int n;

    n = 1;
    x_seq = 0;
    
    printf("Enter x or negative value for the end of the input: ");
    if (scanf("%lf", &x) != 1)
    {
        printf("ERROR: IO\n");
        return ERR_IO;
    }
    while (x >= 0)
    {
        x_seq += count_seq_element(x, n);
        n += 1;

        if (scanf("%lf", &x) != 1)
        {
            printf("ERROR: IO\n");
            return ERR_IO;
        }
    }
    if (n <= 1)
    {
        printf("ERROR: empty x sequence\n");
        return ERR_RANGE;
    }

    *g = sin(x_seq);
    return OK;
}

int main(void)
{
    double g;
    int res;
    res = calculate(&g);
    if (res == 0)
    {
        printf("Result: %lf\n", g);
    }

    return res;
}
