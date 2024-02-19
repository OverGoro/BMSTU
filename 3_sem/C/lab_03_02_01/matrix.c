#include "matrix.h"

/// @brief Удаление элемента массива по индексу
/// @param[in, out] arr массив
/// @param[in, out] arr_size размер массива
/// @param[in] index индекс элемента для удаления
void delete_by_index(int *arr, size_t *arr_size, size_t index)
{
    for (size_t i = index; i < *arr_size - 1; i++)
    {
        arr[i] = arr[i + 1];
    }
    (*arr_size)--;
}

/// @brief Копирование массива 1 в массив 2
/// @param arr_1 Массив 1
/// @param arr_2 Массив 2
/// @param arr_size Размер массивов
void copy_array(const int *arr_1, int *arr_2, size_t arr_size)
{
    for (size_t i = 0; i < arr_size; i++)
    {
        arr_2[i] = arr_1[i];
    }
}
void delete_line(int mat[][M], size_t *mat_lines_num, size_t mat_columns_num, size_t line_num)
{
    for (size_t i = line_num; i < *mat_lines_num - 1; i++)
    {
        copy_array(mat[i + 1], mat[i], mat_columns_num);
    }
    (*mat_lines_num)--;
}

void delete_column(int mat[][M], size_t mat_lines_num, size_t *mat_columns_num, size_t column_num)
{
    size_t new_columns_num = *mat_columns_num;
    for (size_t i = 0; i < mat_lines_num; i++)
    {   
        new_columns_num = *mat_columns_num;
        delete_by_index(mat[i], &new_columns_num, column_num);
    }
    *mat_columns_num = new_columns_num;
}


int get_digit_summ(int num)
{
    int res = 0;
    if (num < 0)
    {
        num = -num;
    }
    while (num > 0)
    {
        res += num % 10;
        num /= 10;
    }
    return res;
}

void get_min_digit_summ_index(const int mat[][M], size_t mat_lines_num, size_t mat_columns_num, size_t *min_i, size_t *min_j)
{   
    *min_i = 0, *min_j = 0;
    int min_digit_summ = get_digit_summ(mat[*min_i][*min_j]);
    for (size_t i = 0; i < mat_lines_num; i++)
    {
        for (size_t j = 0; j < mat_columns_num; j++)
        {
            int current_digit_summ = get_digit_summ(mat[i][j]);
            if (current_digit_summ < min_digit_summ)
            {
                *min_i = i;
                *min_j = j;
                min_digit_summ = current_digit_summ;
            }
        }
    }
}
