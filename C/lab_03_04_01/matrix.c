#include "matrix.h"

void replace_elements(int *e_1, int *e_2)
{
    int replaced = *e_1;
    *e_1 = *e_2;
    *e_2 = replaced;
}

void replace_array_elements(int *line_1, int *line_2, size_t start_i, size_t end_i)
{
    for (size_t i = start_i; i < end_i; i++)
    {
        replace_elements(&line_1[i], &line_2[i]);
    }
    printf("\n");
}

void sort_matrix(int mat[][M], size_t mat_size)
{
    size_t i = 0;
    while (i <= mat_size - i)
    {
        replace_array_elements(mat[i], mat[mat_size - i - 1], i, mat_size - i);
        i++;
    }
}
