// Городский Юрий ИУ7-22Б
// Определение площади трапеции с помощью длины оснований и угла при большем основании

#define PI 3.14159265358979323846
#define CIRCLE_ANGLE 360
#include <stdio.h>
#include <math.h>
int main(void)
{
    double a, b, phi;
    double s, h;
    printf("Enter lower base, upper base, angle(in degrees): ");
    scanf("%lf%lf%lf", &a, &b, &phi);
    
    phi = 2 * PI * phi / CIRCLE_ANGLE; // Перевод из градусов в радианы
    
    h = tan(phi) * (fabs(a - b) / 2); // Высота трапеции
    
    s = (a + b) / 2 * h; // Площадь трапеции
    printf("%lf\n", s);

    return 0;
}

