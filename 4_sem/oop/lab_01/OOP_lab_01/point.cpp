#include "point.h"

point_t point_init(double x, double y, double z)
{
    point_t point = {
        .x = x,
        .y = y,
        .z = z
    };
    return point;
}

int point_move(point_t &point, const move_coefficients_t &move)
{
    point.x += move.dx;
    point.y += move.dy;
    point.z += move.dz;
    return OK;
}

static int point_rotate_axis_x(point_t &point, double angle)
{
    double cos_angle = cos(angle);
    double sin_angle = sin(angle);
    double y = point.y * cos_angle - point.z * sin_angle;
    double z = point.y * sin_angle + point.z * cos_angle;
    point.y = y;
    point.z = z;
    return OK;
}

static int point_rotate_axis_y(point_t &point, double angle)
{
    double cos_angle = cos(angle);
    double sin_angle = sin(angle);
    double x = point.x * cos_angle + point.z * sin_angle;
    double z = -point.x * sin_angle + point.z * cos_angle;
    point.x = x;
    point.z = z;
    return OK;
}

static int point_rotate_axis_z(point_t &point, double angle)
{
    double cos_angle = cos(angle);
    double sin_angle = sin(angle);
    double x = point.x * cos_angle - point.y * sin_angle;
    double y = point.x * sin_angle + point.y * cos_angle;
    point.x = x;
    point.y = y;
    return OK;
}


int point_rotate(point_t &point, const point_t &center, const rotate_coefficients_t &angle)
{
    move_coefficients_t movement = move_coefficients_create(-center.x, -center.y, -center.z);

    move_coefficients_t back_movement = move_coefficients_create(center.x, center.y, center.z);

    int rc = point_move(point, movement);
    if (!rc)
        rc = point_rotate_axis_x(point, angle.x_angle);
    if (!rc)
        rc = point_rotate_axis_y(point, angle.y_angle);
    if (!rc)
        rc = point_rotate_axis_z(point, angle.z_angle);
    if (!rc)
        rc = point_move(point, back_movement);


    return rc;
}

int point_scale(point_t &point, const point_t &center, const scale_coefficients_t &scale)
{
    point.x = center.x + (point.x - center.x) * scale.kx;
    point.y = center.y + (point.y - center.y) * scale.ky;
    point.z = center.z + (point.z - center.z) * scale.kz;
    return OK;
}

int point_read(FILE *file, point_t &point)
{
    int rc = OK;
    if (fscanf(file, "%lf%lf%lf", &point.x, &point.y, &point.z) != 3)
    {
        rc = ERR_IO;
    }
    return rc;
}

int point_print(FILE *file, const point_t &point)
{
    fprintf(file, "%lf %lf %lf\n", point.x, point.y, point.z);
    return OK;
}
