#include "matrixio.h"
int input_matrix_size(size_t *mat_lines_num, size_t *mat_columns_num)
{
    printf("Lines number: ");
    if (scanf("%zu", mat_lines_num) != 1)
    {
        return ERROR_IO;
    }
    else if (*mat_lines_num > N || *mat_lines_num == 0)
    {
        return ERROR_RANGE;
    }
    printf("Columns number: ");
    if (scanf("%zu", mat_columns_num) != 1)
    {
        return ERROR_IO;
    }
    else if (*mat_columns_num > M || *mat_columns_num == 0)
    {
        return ERROR_RANGE;
    }
    if (*mat_columns_num != *mat_lines_num)
    {
        printf("Matrix is not square\n");
        return ERROR_RANGE;
    }
    return OK;
}

void print_matrix(const int mat[][M], size_t mat_lines_num, size_t mat_columns_num)
{
    printf("Matrix: \n");
    for (size_t i = 0; i < mat_lines_num; i++)
    {
        for (size_t j = 0; j < mat_columns_num; j++)
        {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}
