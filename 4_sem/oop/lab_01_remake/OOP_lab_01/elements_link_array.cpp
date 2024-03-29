#include "elements_link_array.h"


links_array_t links_array_create_empty()
{
    links_array_t links_array = {
        .array = NULL,
        .array_size = 0
    };
    return links_array;
}

static int links_allocate(link_t * &links, size_t array_size)
{
    links = (link_t *)malloc(array_size * sizeof(link_t));
    if (links == NULL)
        return ERR_MEM;
    return OK;
}

int links_array_allocate(links_array_t &links_array, size_t array_size)
{
    int rc = links_allocate(links_array.array, array_size);
    if (!rc)
        links_array.array_size = array_size;
    return rc;
}

static void links_free(link_t *links)
{
    if (links != NULL)
        free(links);
}

void links_array_free(links_array_t &links_array)
{
    links_free(links_array.array);
}

static int links_array_read_array_size(size_t &array_size, FILE *f)
{
    if (fscanf(f, "%lu", &array_size) != 1)
        return ERR_IO;
    return OK;
}

static int links_array_read_array(link_t *array, FILE *f, size_t array_size)
{
    if (array == NULL)
        return ERR_NULL_PTR;

    int rc = OK;
    for (size_t i = 0; !rc && i < array_size; i++)
        rc = link_read(array[i], f);
    return rc;
}

int links_array_read(links_array_t &links_array, FILE *f)
{

    // Чтение размеров
    int rc = links_array_read_array_size(links_array.array_size, f);

    // Выделение памяти
    if (!rc)
    {
        rc = links_allocate(links_array.array, links_array.array_size);
        // Чтение связей
        if (!rc)
        {
            rc = links_array_read_array(links_array.array, f, links_array.array_size);
            if (rc)
                links_free(links_array.array);
        }
    }

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
    int rc = links_array_print_array_size(f, links_array.array_size);
    if (!rc)
        rc = links_array_print_array(f, links_array.array, links_array.array_size);
    return rc;
}

int links_validate(const link_t *links, size_t links_size, size_t target_array_size)
{
    int rc = OK;
    for (size_t i = 0; !rc && i < links_size; i++)
    {
        rc = link_validate(links[i], target_array_size);
    }
    return rc;
}

int links_array_validate(const links_array_t &links_array, size_t target_array_size)
{
    return links_validate(links_array.array, links_array.array_size, target_array_size);
}
