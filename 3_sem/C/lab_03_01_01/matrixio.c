#include "matrixio.h"

/// @brief Ввод матрицы
/// @param mat Матрица
/// @param lines_num Количество строк
/// @param columns_num Количество столбцов
/// @return Код ошибки
int input_matrix(int mat[][M], size_t *mat_lines_num, size_t *mat_columns_num)
{
    printf("Lines number: ");
    if (scanf("%zu", mat_lines_num) != 1)
    {
        return ERROR_IO;
    }
    else if (*mat_lines_num > N || *mat_lines_num <= 0)
    {
        return ERROR_RANGE;
    }
    printf("Columns number: ");
    if (scanf("%zu", mat_columns_num) != 1)
    {
        return ERROR_IO;
    }
    else if (*mat_columns_num > M || *mat_columns_num <= 0)
    {
        return ERROR_RANGE;
    }
    printf("Matrix elements: ");
    size_t entered_elements = 0;
    for (size_t i = 0; i < *mat_lines_num; i++)
    {
        for (size_t j = 0; j < *mat_columns_num; j++)
        {
            if (scanf("%d", &mat[i][j]) != 1)
            {
                return ERROR_IO;
            }
            entered_elements++;
        }
    }
    if (entered_elements != (*mat_lines_num) * (*mat_columns_num))
    {
        printf("Few elements\n");
        return ERROR_RANGE;
    }
    return OK;
}

/// @brief Вывод массива
/// @param arr Массив
/// @param arr_size Размер массива
void print_array(const int *arr, size_t arr_size)
{
    for (size_t i = 0; i < arr_size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
