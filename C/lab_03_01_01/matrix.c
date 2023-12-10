#include "matrix.h"

bool check_matrix_line(const int *mat_line, size_t mat_columns_num)
{
    const int *p_start = mat_line;
    const int *p_end = mat_line + mat_columns_num - 1;
    while (p_start < p_end)
    {
        if ((*p_start) != (*p_end))
        {
            return false;
        }
        p_start++;
        p_end--;
    }  
    return true;
}

void get_array(const int mat[][M], size_t mat_lines_num, size_t mat_columns_num, int arr[])
{
    for (size_t i = 0; i < mat_lines_num; i++)
    {
        if (check_matrix_line(mat[i], mat_columns_num) == true)
        {
            arr[i] = 1;
        }
        else
        {
            arr[i] = 0;
        }
    }
}
