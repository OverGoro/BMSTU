#include "matrix.h"

int get_digit_sum(int num)
{
    int summ = 0;
    num = abs(num);
    while (num > 0)
    {
        summ += num % 10;
        num /= 10;
    }
    return summ;
}
void cyclic_move(int *arr, size_t arr_size)
{
    int first_element = arr[0];
    for (size_t j = 1; j < arr_size; j++)
    {
        arr[j - 1] = arr[j];
    }
    arr[arr_size - 1] = first_element;
}
void move_array(int *arr, size_t arr_size, size_t k)
{
    if (arr_size == 0)
    {
        return;
    }
    
    for (size_t i = 0; i < k; i++)
    {
        cyclic_move(arr, arr_size);
    }
}

void get_elements(const int mat[][M], size_t mat_lines_num, size_t mat_columns_num, int *arr, size_t *arr_size)
{
    *arr_size = 0;
    for (size_t i = 0; i < mat_lines_num; i++)
    {
        for (size_t j = 0; j < mat_columns_num; j++)
        {
            if (get_digit_sum(mat[i][j]) > MAX_DIGIT_SUMM)
            {
                arr[*arr_size] = mat[i][j];
                (*arr_size)++;
            }
        }
    }
}


void modify_matrix(int mat[][M], size_t mat_lines_num, size_t mat_columns_num, int *arr)
{
    size_t arr_i = 0;
    for (size_t i = 0; i < mat_lines_num; i++)
    {
        for (size_t j = 0; j < mat_columns_num; j++)
        {    
            if (get_digit_sum(mat[i][j]) > MAX_DIGIT_SUMM)
            {
                mat[i][j] = arr[arr_i];
                arr_i++;
            }
        }
    }
}
