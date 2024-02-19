// Городский Юрий ИУ7-22Б Лабораторная работа №2 Задача №3 Вариант №1
#include <stdio.h>
#include <stdbool.h>
#include "matrix.h"
#include "matrixio.h"
#include "constants.h"
#include "errors.h"



int main(void)
{
    int mat[N][M];
    int arr[N * M];

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

    get_elements((const int (*)[M]) mat, mat_lines_num, mat_columns_num, arr, &arr_size);
    if(arr_size == 0)
    {
        printf("No required elements\n");
        return ERROR_NO_ELEMENTS;
    }
    move_array(arr, arr_size, MOVE_K);
    modify_matrix(mat, mat_lines_num, mat_columns_num, arr);
    print_matrix((const int (*)[M]) mat, mat_lines_num, mat_columns_num);
    
    return OK;
}
