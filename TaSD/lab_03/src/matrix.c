#include "matrix.h"

int **matrix_allocate(size_t n, size_t m)
{
    int **ptrs, *data;
    ptrs = malloc(n * sizeof(int*));
    if (!ptrs)
        return NULL;
    data = malloc(n * m * sizeof(int));
    if (!data)
    {
        free(ptrs);
        return NULL;
    }
    for (size_t i = 0; i < n; i++)
        ptrs[i] = data + i * m;
    return ptrs;
}

void matrix_free(int **ptrs)
{
    if (ptrs != NULL)
    {
        free(ptrs[0]);
        free(ptrs);
    }
}

