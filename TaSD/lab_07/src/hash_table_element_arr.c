#include "../inc/hash_table_element_arr.h"
#include <stdlib.h>

int element_arr_add(element_arr_t *arr, char *name, char *manual)
{
    arr->n++;
    int rc = ERR_OK;

    element_t *tmp = NULL;
    if (!rc && arr->values)
        tmp = realloc(arr->values, sizeof(element_t) * arr->n);
    else if (!rc)
        tmp = malloc(sizeof(element_t) * arr->n);

    if (!rc && tmp != NULL)
    {
        arr->values = tmp;
        element_set_content(&arr->values[arr->n - 1], name, manual);
    }
    else if (!rc)
        rc = ERR_MEM;

    return rc;
}

void element_arr_free_content(element_arr_t *arr)
{
    free(arr->values);
    arr->values = NULL;
    arr->n = 0;
}

int element_arr_read(FILE *f, element_arr_t *arr)
{
    int rc = ERR_OK;
    while (!rc)
    {
        element_t e;
        rc = element_read(f, &e);
        if (!rc) rc = element_arr_add(arr, e.name, e.manual);
    }
    if (!rc && !feof(f))
        rc = ERR_FILE;
    return rc;
}

size_t element_arr_get_size(element_arr_t *arr) 
{
    if (arr == NULL)
        return 0;
    size_t s = sizeof(element_arr_t) + sizeof(element_t *) * arr->n;
    for (size_t i = 0; i < arr->n; i++)
        s += element_get_size(&arr->values[i]);
    return s;
}

