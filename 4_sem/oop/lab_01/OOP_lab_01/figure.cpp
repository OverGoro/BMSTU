#include "figure.h"

figure_t figure_init_empty()
{
    figure_t figure = {
        .points_array = points_array_init_empty(),
        .links_array = links_array_create_empty()
    };
    return figure;
}

int figure_allocate(figure_t &figure, size_t array_size, size_t links_size)
{
    int rc = OK;

    // Выделение памяти
    rc = points_array_allocate(figure.points_array, array_size);
    if (!rc)
        rc = links_array_allocate(figure.links_array, links_size);

    // Освобождение памяти
    if (rc)
    {
        figure_clear(figure);
    }

    return rc;
}


void figure_clear(figure_t &figure)
{
    points_array_clear(figure.points_array);
    links_array_clear(figure.links_array);
}

int figure_rotate(figure_t &figure, const point_t &center, const rotate_coefficients_t &angle)
{
    int rc = points_array_rotate(figure.points_array, center, angle);
    return rc;
}

int figure_move(figure_t &figure, const move_coefficients_t &move)
{
    int rc = points_array_move(figure.points_array, move);
    return rc;
}

int figure_scale(figure_t &figure, const point_t &center, const scale_coefficients_t &scale)
{
    int rc = points_array_scale(figure.points_array, center, scale);
    return rc;
}

//static int figure_read_points_array(points_array_t &points_array, FILE *f)
//{
//    return points_array_read(points_array, f);
//}

//static int figure_read_links_array(links_array_t &links_array, FILE *f)
//{
//    return links_array_read(links_array, f);
//}

int figure_read(figure_t &figure, FILE *f)
{
    int rc = OK;
    rc = points_array_read(figure.points_array, f);
    if (!rc)
        rc = links_array_read(figure.links_array, f);
    if (rc)
        figure_clear(figure);
    return rc;
}

int figure_read_file(figure_t &figure, const char *filename)
{
    int rc = OK;

    figure_t tmp_figure = figure_init_empty();
    FILE *f = NULL;

    if (!rc) f = fopen(filename, "r");

    if (!rc && f == NULL)
        rc = error_get_file_error();

    if (!rc)
        rc = figure_read(tmp_figure, f);

    // Закрытие файла
    if (f)
        fclose(f);

    if (!rc)
    {
        figure_clear(figure);
        figure = tmp_figure;
    }
    else
        figure_clear(tmp_figure);

    return rc;
}

int figure_print(FILE *f, const figure_t &figure)
{
    int rc = points_array_print(f, figure.points_array);
    if (!rc)
        rc = links_array_print(f, figure.links_array);
    return rc;
}

int figure_save_file(const figure_t &figure, const char *filename)
{
    int rc = OK;
    FILE *f = fopen(filename, "w");

    if (f == NULL)
        rc = error_get_file_error();

    if (!rc)
        rc = figure_print(f, figure);

    if (f)
        fclose(f);

    return rc;
}
