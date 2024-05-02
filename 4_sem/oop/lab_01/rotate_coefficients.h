#ifndef ROTATE_COEFFICIENTS_H
#define ROTATE_COEFFICIENTS_H

typedef struct
{
    double x_angle;
    double y_angle;
    double z_angle;
} rotate_coefficients_t;

rotate_coefficients_t rotate_coefficients_init(double x_angle, double y_angle, double z_angle);

#endif // ROTATE_COEFFICIENTS_H
