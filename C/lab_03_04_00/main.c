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

    int min_el = 0;
    int find_min_el_code = 0;

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
            case ERROR_FEW_ELEMENTS:
                printf("Entered few elements\n");
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
    
    find_min_el_code = find_min_element(mat, mat_lines_num, &min_el);
    if (find_min_el_code == ERROR_ONLY_EVEN)
    {
        printf("Only even elemets under main diagonal\n");
    }
    else if (find_min_el_code == ERROR_NO_UNDER_DIAG_ELEMENTS)
    {
        printf("No elemets under main diagonal\n");
    }
    else if (find_min_el_code == OK)
    {
        printf("%d\n", min_el);
    }
    
    
    return find_min_el_code;
}
