#include "matrix.h"

void fill_matrix(int mat[][M], size_t mat_lines_num, size_t mat_columns_num)
{
    int value = 1; // Текущее значение
    int row = 0; // Текущая строка
    int col = 0; // Текущий столбец
    int row_end = mat_lines_num - 1; // Граничный столбец
    int col_end = mat_columns_num - 1; // Граничная строка
    
    while (row <= row_end && col <= col_end) 
    {
        // Заполнение верхней строки слева направо
        for (int i = col; i <= col_end; i++) 
        {
            mat[row][i] = value;
            value++;
        }
        row++;

        // Заполнение правого столбца сверху вниз
        for (int i = row; i <= row_end; i++) 
        {
            mat[i][col_end] = value;
            value++;
        }
        col_end--;

        // Заполнение нижней строки справа налево
        if (row <= row_end) 
        {
            for (int i = col_end; i >= col; i--) 
            {
                mat[row_end][i] = value;
                value++;
            }
            row_end--;
        }

        // Заполнение левого столбца снизу вверх
        if (col <= col_end) 
        {
            for (int i = row_end; i >= row; i--) 
            {
                mat[i][col] = value;
                value++;
            }
            col++;
        }
    }
}
