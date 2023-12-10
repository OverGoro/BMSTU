// Городский Юрий ИУ7-22Б Лабораторная работа №2 Задача №3 Вариант №1
// Вставка очередного числа фиббоначи после каждого элемента массива кратного 3
#include <stdio.h>
#include <stdbool.h>
#include "matrix.h"
#include "matrixio.h"
#include "constants.h"
#include "errors.h"

int main(void)
{
    int mat[N][M];
    
    size_t mat_lines_num;
    size_t mat_columns_num;

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
    if (mat_columns_num != mat_lines_num)
    {
        printf("Not square matrix\n");
        return ERROR_NOT_SQUARE;
    }
    sort_matrix(mat, mat_lines_num);
    print_matrix((const int (*)[M]) mat, mat_lines_num, mat_columns_num);
    return OK;
}
