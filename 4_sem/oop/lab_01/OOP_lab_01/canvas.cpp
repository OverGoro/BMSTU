#include "canvas.h"

static point_t canvas_convert_point(const canvas_t &canvas_parameters, const point_t &point)
{
    double x = (point.x + canvas_parameters.count_width / 2) / canvas_parameters.count_width * canvas_parameters.canvas_width;
    double y = (point.y + canvas_parameters.count_height / 2) / canvas_parameters.count_height * canvas_parameters.canvas_height;
    double z = point.z;
    point_t screen_point = point_init(x, y, z);
    return screen_point;
}

int canvas_draw_line(const canvas_t &canvas_parameters, const point_t &point_1, const point_t &point_2)
{
    canvas_parameters.painter.setPen(canvas_parameters.lines_pen);
    point_t screen_point_1 = canvas_convert_point(canvas_parameters, point_1);
    point_t screen_point_2 = canvas_convert_point(canvas_parameters, point_2);

    QPointF p_1 = QPointF(screen_point_1.x, screen_point_1.y);
    QPointF p_2 = QPointF(screen_point_2.x, screen_point_2.y);

    canvas_parameters.painter.drawLine(p_1, p_2);
    return OK;
}

int canvas_draw_points_array(const canvas_t &canvas_parameters, const point_t *points, const link_t &link)
{
    canvas_draw_line(canvas_parameters, points[link.i_1], points[link.i_2]);
}
int canvas_draw_points(const canvas_t &canvas_parameters, const points_array_t &points_array, const links_array_t &links_array)
{
    int rc = links_array_validate(links_array, points_array.array_size);
    for (size_t i = 0; !rc && i < links_array.array_size; i++)
    {
        rc = canvas_draw_points_array(canvas_parameters, points_array.array, links_array.array[i]);
    }
    return rc;
}

int canvas_draw_figure(const canvas_t &canvas_parameters, const figure_t &figure)
{
    int rc = canvas_draw_points(canvas_parameters, figure.points_array, figure.links_array);
    return rc;
}
