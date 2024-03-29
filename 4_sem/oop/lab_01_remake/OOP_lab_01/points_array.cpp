#include "points_array.h"

points_array_t points_array_init_empty()
{
    points_array_t points_array = {
        .array = NULL,
        .array_size = 0
    };
    return points_array;
}

static int points_allocate(point_t * &points, size_t array_size)
{
    points = (point_t *)malloc(array_size * sizeof(point_t));
    if (points == NULL)
        return ERR_MEM;
    return OK;
}

int points_array_allocate(points_array_t &points_array, size_t array_size)
{
    int rc = points_allocate(points_array.array, array_size);
    if (!rc)
        points_array.array_size = array_size;
    return rc;
}

static void points_free(point_t *points)
{
    if (points != NULL)
        free(points);
}

void points_array_free(points_array_t &points_array)
{
    points_free(points_array.array);
}

static int points_array_read_array_size(size_t &size, FILE *f)
{
    if (fscanf(f, "%lu", &size) != 1)
        return ERR_IO;
    return OK;
}

static int points_array_read_array(point_t *points, FILE *f, size_t size)
{
    if (points == NULL)
        return ERR_NULL_PTR;

    // Чтение точек
    int rc = OK;
    for (size_t i = 0; !rc && i < size; i++)
        rc = point_read(f, points[i]);

    return rc;
}


int points_array_read(points_array_t &points_array, FILE *f)
{
    int rc = points_array_read_array_size(points_array.array_size, f);

    // Выделение памяти
    if (!rc)
    {
        rc = points_allocate(points_array.array, points_array.array_size);
        // Чтение точек
        if (!rc)
        {
            rc = points_array_read_array(points_array.array, f, points_array.array_size);
            if (rc)
                points_free(points_array.array);
        }
    }

    return rc;
}

static int points_array_print_array_size(FILE *f, size_t array_size)
{
    fprintf(f, "%lu\n", array_size);
    return OK;
}

static int points_array_print_array(FILE *f, const point_t *array, size_t array_size)
{
    int rc = OK;
    for (size_t i = 0; !rc && i < array_size; i++)
    {
        rc = point_print(f, array[i]);
    }
    return rc;
}


int points_array_print(FILE *f, const points_array_t &points_array)
{
    int rc = OK;
    rc = points_array_print_array_size(f, points_array.array_size);
    if (!rc)
        rc = points_array_print_array(f, points_array.array, points_array.array_size);
    return rc;
}

int points_array_rotate(points_array_t &points_array, const point_t &center, const rotate_coefficients_t &angle)
{
    int rc = OK;
    for (size_t i = 0; !rc && i < points_array.array_size; i++)
    {
        rc = point_rotate(points_array.array[i], center, angle);
    }
    return rc;
}

int points_array_move(points_array_t &points_array, const move_coefficients_t &move)
{
    int rc = OK;
    for (size_t i = 0; !rc && i < points_array.array_size; i++)
    {
        rc = point_move(points_array.array[i], move);
    }
    return rc;
}

int points_array_scale(points_array_t &points_array, const point_t &center, const scale_coefficients_t &scale)
{
    int rc = OK;
    for (size_t i = 0; !rc && i < points_array.array_size; i++)
    {
        rc = point_scale(points_array.array[i], center, scale);
    }
    return rc;
}
