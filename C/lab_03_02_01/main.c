// Городский Юрий ИУ7-22Б Лабораторная работа №3 Задача №2 Вариант №1
#include <stdio.h>
#include <stdbool.h>
#include "matrix.h"
#include "matrixio.h"
#include "constants.h"
#include "errors.h"

int main(void)
{
    int mat[N][M];
    
    size_t mat_lines_num, mat_columns_num;

    size_t min_i = 0, min_j = 0;
    
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

    get_min_digit_summ_index((const int (*)[M]) mat, mat_lines_num, mat_columns_num, &min_i, &min_j);
    delete_line(mat, &mat_lines_num, mat_columns_num, min_i);
    if (mat_lines_num == 0)
    {
        printf("Empty matrix\n");
        return ERROR_EMPTY_MATRIX;
    }

    delete_column(mat, mat_lines_num, &mat_columns_num, min_j);
    if (mat_columns_num == 0)
    {
        printf("Empty matrix\n");
        return ERROR_EMPTY_MATRIX;
    }


    print_matrix((const int (*)[M]) mat, mat_lines_num, mat_columns_num);
    return OK;
}
