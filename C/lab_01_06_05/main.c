// Городский Юрий ИУ7-22Б
// Определение пересечения отрезков
#include <stdio.h>
#include <math.h>
#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2
#define EPSILON 0.00001
#define INTERSECT 1
#define NOT_INTERSECT 0

// Векторное произведение векторов
// x_1, y_1, x_2, y_2, x_3, y_3, x_4, y_4 - координаты начала и конца 2 векторов
double multiply_vectors(double x_1, double y_1, double x_2, double y_2, double x_3, double y_3, double x_4, double y_4)
{
    double vector_product;
    vector_product = (x_2 - x_1) * (y_4 - y_3) - (x_4 - x_3) * (y_2 - y_1);
    return vector_product;
}

// Определение персечения отрезков
// x_p, y_p, x_q, y_q, x_r, y_r, x_s, y_s - координаты точек отрезков pq, vs
unsigned short int intersect(double x_p, double y_p, double x_q, double y_q, double x_r, double y_r, double x_s, double y_s)
{
    double v_p, v_q, v_r, v_s;
    v_p = multiply_vectors(x_r, y_r, x_s, y_s, x_r, y_r, x_p, y_p); // v_p = [rs, rp]
    v_q = multiply_vectors(x_r, y_r, x_s, y_s, x_r, y_r, x_q, y_q); // v_q = [rs, rq]
    v_r = multiply_vectors(x_p, y_p, x_q, y_q, x_p, y_p, x_r, y_r); // v_r = [pq, pr]
    v_s = multiply_vectors(x_p, y_p, x_q, y_q, x_p, y_p, x_s, y_s); // v_s = [pq, ps]
    

    if ((v_p * v_q) < 0 && (v_r * v_s) < 0)
    {
        return INTERSECT;
    }
    return NOT_INTERSECT;
}

int main(void)
{
    double x_p, y_p, x_q, y_q, x_r, y_r, x_s, y_s; // Координаты точек
    short unsigned int result;
    // Ввод
    printf("Input xp, yp, xq, yq, xr, yr, xs, ys: ");
    if (scanf("%lf%lf%lf%lf%lf%lf%lf%lf", &x_p, &y_p, &x_q, &y_q, &x_r, &y_r, &x_s, &y_s) != 8)
    {
        printf("IO Error\n");
        return ERR_IO;
    }

    if ((fabs(x_p - x_q) < EPSILON) && (fabs(y_p - y_q) < EPSILON))
    {
        printf("One of the segments is a point\n");
        return ERR_RANGE;
    }
    else if ((fabs(x_r - x_s) < EPSILON) && (fabs(y_r - y_s) < EPSILON))
    {
        printf("One of the segments is a point\n");
        return ERR_RANGE;
    }

    result = intersect(x_p, y_p, x_q, y_q, x_r, y_r, x_s, y_s);
    printf("%d\n", result);

    return OK;
}
