#include "drawer.h"

void drawer_params_set_lines_color(drawer_params_t &drawer_params, const color_t &color)
{
    drawer_params.lines_color = color;
}

int drawer_draw_line(const color_t &color, const point_t &point_1, const point_t &point_2)
{
    int rc = OK;
    glColor3ub(color.r, color.g, color.b);
    glBegin(GL_LINES);
    glVertex3d(point_1.x, point_1.y, point_1.z);
    glVertex3d(point_2.x, point_2.y, point_2.z);
    glEnd();
    return rc;
}

int drawer_draw_points_array(const drawer_params_t &drawer_params,
                             const points_array_t &points_array,
                             const links_array_t &links_array)
{
    int rc = links_array_validate(links_array, points_array.array_size);
    for (size_t i = 0; !rc && i < links_array.array_size; i++)
    {
        rc = drawer_draw_line(drawer_params.lines_color,
                              points_array.array[links_array.array[i].i_1],
                              points_array.array[links_array.array[i].i_2]);
    }
    return rc;
}

int drawer_draw_figure(const drawer_params_t &drawer_params, const figure_t &figure)
{
    int rc = drawer_draw_points_array(drawer_params, figure.points_array, figure.links_array);
    return rc;
}
