// Городский Юрий ИУ7-22Б Лабораторная работа №3 Задача №1 Вариант №1
#include <stdio.h>
#include <stdbool.h>
#include "matrix.h"
#include "matrixio.h"
#include "constants.h"
#include "errors.h"

int main(void)
{
    int mat[N][M];
    int arr[N];
    
    size_t mat_lines_num, mat_columns_num;
    size_t arr_size;
    
    int input_mat_code = 0;
    
    input_mat_code = input_matrix(mat, &mat_lines_num, &mat_columns_num);
    if (input_mat_code != 0)
    {
        switch (input_mat_code)
        {
            case ERROR_IO:
                printf("Input error\n");
                break;
            case ERROR_RANGE:
                printf("Range error\n");
                break;
            default:
                printf("Unexpected error\n");            
                break;
        }
        return input_mat_code;
    }
    get_array((const int (*)[M])mat, mat_lines_num, mat_columns_num, arr);

    arr_size = mat_lines_num;
    print_array(arr, arr_size);

    return OK;
}
