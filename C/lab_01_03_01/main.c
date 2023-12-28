// Городский Юрий ИУ7-22Б
// Определение объема и температуры новой смеси
#include <stdio.h>

#define OK 0
#define ERR_IO 1
int main(void)
{
    double v1, t1, v2, t2; // v - объем, t - температура
    double v, t; // объем и температура новой смеси
    
    // Ввод
    printf("Input first V, first T, second V, second T: ");
    scanf("%lf%lf%lf%lf", &v1, &t1, &v2, &t2);

    v = v1 + v2;
    t = (v1 * t1 + v2 * t2) / v;

    printf("Volume: %f\nTemperature: %f\n", v, t);
    
    return OK;
}

