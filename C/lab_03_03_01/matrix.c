#include "matrix.h"

int get_max_line_value(const int *mat, size_t mat_columns_num)
{
    int max_val = mat[0];
    for (size_t j = 0; j < mat_columns_num; j++)
    {
        if (max_val < mat[j])
        {
            max_val = mat[j];
        }
    }
    return max_val;
}

void replace_lines(int *line_1, int *line_2, size_t columns_num)
{
    for (size_t i = 0; i < columns_num; i++)
    {
        replace_elements(&line_1[i], &line_2[i]);
    }
}

void replace_elements(int *e_1, int *e_2)
{
    int replaced = *e_1;
    *e_1 = *e_2;
    *e_2 = replaced;
}

void sort_matrix(int mat[][M], size_t mat_lines_num, size_t mat_columns_num)
{
    int max_values[N];
    for (size_t i = 0; i < mat_lines_num; i++)
    {
        max_values[i] = get_max_line_value(mat[i], mat_columns_num);
    }
    
    for (size_t i = 0; i < mat_lines_num; i++)
    {
        size_t max_j = i;
        for (size_t j = i; j < mat_lines_num; j++)
        {
            if (max_values[max_j] < max_values[j])
            {
                max_j = j;
            }
        }
        replace_lines(mat[i], mat[max_j], mat_columns_num);
        replace_elements(&max_values[i], &max_values[max_j]);
    }
}
