#ifndef MOVE_COEFFICIENTS_H
#define MOVE_COEFFICIENTS_H

typedef struct
{
    double dx;
    double dy;
    double dz;
} move_coefficients_t;

move_coefficients_t move_coefficients_create(double dx, double dy, double dz);

#endif // MOVE_COEFFICIENTS_H
