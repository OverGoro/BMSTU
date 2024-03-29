#include "scale_coefficients.h"

scale_coefficients_t scale_coefficients_init(double kx, double ky, double kz)
{
    scale_coefficients_t scale_coefficients = {
        .kx = kx,
        .ky = ky,
        .kz = kz
    };
    return scale_coefficients;
}
