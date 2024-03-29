#include "canvas.h"

static point_t size_project_point(const screen_size_t &screen_size, const count_size_t &count_size, const point_t &point)
{
    double x = (point.x + count_size.width / 2) / count_size.width * screen_size.width;
    double y = (point.y + count_size.height / 2) / count_size.height * screen_size.height;
    double z = point.z;
    return point_init(x, y, z);
}

static point_t canvas_project_point(const canvas_t &canvas_parameters, const point_t &point)
{
    return size_project_point(canvas_parameters.screen_size, canvas_parameters.count_size, point);
}

static int qpainter_set_pen(QPainter *painter, const QPen &pen)
{
    if (painter == NULL)
        return ERR_NULL_PTR;

    painter->setPen(pen);
    return OK;
}

static int qpainter_draw_line(QPainter *painter, const point_t &point_1, const point_t &point_2)
{
    if (painter == NULL)
        return ERR_NULL_PTR;

    painter->drawLine(point_1.x, point_1.y, point_2.x, point_2.y);
    return OK;
}

int canvas_draw_line(const canvas_t &canvas_parameters, const point_t &point_1, const point_t &point_2)
{
    int rc = qpainter_set_pen(canvas_parameters.painter, canvas_parameters.lines_pen);
    if (!rc)
        rc = qpainter_draw_line(canvas_parameters.painter, point_1, point_2);
    return rc;
}

int canvas_draw_3d_line(const canvas_t &canvas_parameters, const point_t &point_1, const point_t &point_2)
{
    point_t screen_point_1 = canvas_project_point(canvas_parameters, point_1);
    point_t screen_point_2 = canvas_project_point(canvas_parameters, point_2);

    return canvas_draw_line(canvas_parameters, screen_point_1, screen_point_2);
}

int canvas_draw_linked_points(const canvas_t &canvas_parameters, const point_t *points, const link_t &link)
{
    return canvas_draw_3d_line(canvas_parameters, points[link.i_1], points[link.i_2]);
}

int canvas_draw_linked_points_array(const canvas_t &canvas_parameters, const points_array_t &points_array, const links_array_t &links_array)
{
    int rc = links_validate(links_array.array, links_array.array_size, points_array.array_size);
    for (size_t i = 0; !rc && i < links_array.array_size; i++)
    {
        rc = canvas_draw_linked_points(canvas_parameters, points_array.array, links_array.array[i]);
    }
    return rc;
}

int canvas_draw_figure(const canvas_t &canvas_parameters, const figure_t &figure)
{
    return canvas_draw_linked_points_array(canvas_parameters, figure.points_array, figure.links_array);
}





void canvas_set_painter(canvas_t &canvas, QPainter *painter)
{
    canvas.painter = painter;
}

void canvas_set_lines_pen(canvas_t &canvas, QPen &lines_pen)
{
    canvas.lines_pen = lines_pen;
}

static screen_size_t screen_size_init(size_t width, size_t height)
{
    return screen_size_t{.width = width,
                         .height = height};
}
static screen_size_t screen_size_init_null()
{
    return screen_size_t{.width = 0,
                         .height = 0};
}

void canvas_set_screen_size(canvas_t &canvas, size_t width, size_t height)
{
    canvas.screen_size = screen_size_init(width, height);
}

static count_size_t count_size_init(double width, double height)
{
    return count_size_t {.width = width,
                         .height = height};
}
static count_size_t count_size_init_null()
{
    return count_size_t {.width = 0,
                         .height = 0};
}

void canvas_set_count_size(canvas_t &canvas, double width, double height)
{
    canvas.count_size = count_size_init(width, height);
}

canvas_t canvas_init_empty()
{
    canvas_t canvas = {
        .painter = NULL,
        .lines_pen = QPen(),
        .screen_size = screen_size_init_null(),
        .count_size = count_size_init_null()
    };
    return canvas;
}
