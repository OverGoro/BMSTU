#include "elements_link_array.h"


links_array_t links_array_create_empty()
{
    links_array_t links_array = {
        .array = NULL,
        .array_size = 0
    };
    return links_array;
}

int links_array_allocate(links_array_t &links_array, size_t array_size)
{
    int rc = OK;

    links_array.array = (link_t *)malloc(array_size * sizeof(link_t));
    if (links_array.array == NULL)
        rc = ERR_MEM;
    if (!rc)
        links_array.array_size = array_size;

    return rc;
}

void links_array_clear(links_array_t &links_array)
{
    if (!links_array.array)
        free(links_array.array);

    links_array.array = NULL;
    links_array.array_size = 0;
}

static int links_array_read_array_size(size_t &array_size, FILE *f)
{
    int rc = OK;

    // Чтение размеров
    if (!rc && fscanf(f, "%lu", &array_size) != 1)
        rc = ERR_IO;

    return rc;
}

static int links_array_read_array(link_t *array, FILE *f, size_t array_size)
{
    int rc = OK;
    for (size_t i = 0; !rc && i < array_size; i++)
        rc = link_read(array[i], f);
    return rc;
}

int links_array_read(links_array_t &links_array, FILE *f)
{
    int rc = OK;
    size_t array_size;

    // Чтение размеров
    if (!rc)
        rc = links_array_read_array_size(array_size, f);

    // Выделение памяти
    if (!rc)
        rc = links_array_allocate(links_array, array_size);

    // Чтение связей
    if (!rc)
        rc = links_array_read_array(links_array.array, f, links_array.array_size);

    if (rc)
        links_array_clear(links_array);

    return rc;
}

static int links_array_print_array(FILE *f, const link_t *array, size_t array_size)
{
    int rc = OK;
    for (size_t i = 0; !rc && i < array_size; i++)
    {
        rc = link_print(f, array[i]);
    }
    return rc;
}

static int links_array_print_array_size(FILE *f, size_t array_size)
{
    fprintf(f, "%lu\n", array_size);
    return OK;
}

int links_array_print(FILE *f, const links_array_t &links_array)
{
    int rc = OK;
    rc = links_array_print_array_size(f, links_array.array_size);
    if (!rc)
        rc = links_array_print_array(f, links_array.array, links_array.array_size);
    return rc;
}

int links_array_validate(const links_array_t &links_array, size_t target_array_size)
{
    int rc = OK;
    for (size_t i = 0; !rc && i < links_array.array_size; i++)
    {
        rc = link_validate(links_array.array[i], target_array_size);
    }
    return rc;
}
