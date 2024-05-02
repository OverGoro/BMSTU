#ifndef SCALE_COEFFICIENTS_H
#define SCALE_COEFFICIENTS_H

typedef struct
{
    double kx;
    double ky;
    double kz;
} scale_coefficients_t;

scale_coefficients_t scale_coefficients_init(double kx, double ky, double kz);

#endif // SCALE_COEFFICIENTS_H
