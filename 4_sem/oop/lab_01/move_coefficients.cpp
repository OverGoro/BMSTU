#include "move_coefficients.h"

move_coefficients_t move_coefficients_create(double dx, double dy, double dz)
{
    move_coefficients_t move_coefficients = {
        .dx = dx,
        .dy = dy,
        .dz = dz
    };
    return move_coefficients;
}
