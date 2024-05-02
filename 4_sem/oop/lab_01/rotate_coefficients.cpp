#include "rotate_coefficients.h"

rotate_coefficients_t rotate_coefficients_init(double x_angle, double y_angle, double z_angle)
{
    rotate_coefficients_t rotate_coefficients = {
        .x_angle = x_angle,
        .y_angle = y_angle,
        .z_angle = z_angle // Z
    };
    return rotate_coefficients;
}
