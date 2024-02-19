#include "matrix_io.h"
#include <stdio.h>

int matrix_coord_input(FILE *f_in, FILE*f_out, int ***ptrs, size_t *n, size_t *m, size_t *el_num, prompt_t prompt)
{
    // Считывание размеров матрицы и количество ненулевых элементов
    prompt(f_out, "Строки и стобцы начинаются с 1\n");
    prompt(f_out, "Введите через пробел: кол-во строк, кол-во столбцов, кол-во ненулевых элементов\n");
    if (fscanf(f_in, "%lu%lu%lu", n, m, el_num) != 3)
        return ERR_IO;

    // Количество ненулевых элементов в матрице больше числа элементов матрицы
    if (*el_num > (*m) * (*n))
        return ERR_RANGE;

    // Количество строк или стобцов = 0
    if (*m == 0 || *n == 0)
        return ERR_RANGE;

    // Выделение памяти под матрицу
    *ptrs = matrix_allocate(*n, *m);
    if (*ptrs == NULL)
        return ERR_MEM;

    // Заполнение матрицы 0-ми
    for (size_t i = 0; i < *n; i++)
    {
        for (size_t j = 0; j < *m; j++) 
        {
            (*ptrs)[i][j] = 0;
        }
    }
    
    int rc = ERR_OK;
    if (*el_num > 0)
    {
        prompt(f_out, "Значения ненулевых элементов\n");
    }
    // Считывание ненулевых элементов
    for (size_t i = 0; i < *el_num; i++)
    {
        size_t x, y;
        int val;
        prompt(f_out, "Введите через пробел: номер строки, номер столбца, значение элмента\n");
        if (fscanf(f_in, "%lu%lu%d", &y, &x, &val) != 3)
        {
            rc = ERR_IO;
            break;
        }
        if (x > *m || y > *n || x == 0 || y == 0)
        {
            rc = ERR_IO;
            break;
        }
        if ((*ptrs)[y - 1][x - 1] != 0)
        {
            rc = ERR_EL_OVERWRITE;
            break;
        }
        (*ptrs)[y - 1][x - 1] = val;
    }

    // Если произошла ошибка при считывании 
    if (rc != ERR_OK)
    {
        matrix_free(*ptrs);
        *ptrs = NULL;
    }
    return rc;
}

int matrix_vec_coord_input(FILE *f_in, FILE*f_out, int ***ptrs, size_t *n, size_t *m, size_t *el_num, prompt_t prompt)
{
    *n = 1;
    // Считывание размеров матрицы и количество ненулевых элементов
    prompt(f_out, "Строки и стобцы начинаются с 1\n");
    prompt(f_out, "Введите через пробел: кол-во столбцов, кол-во ненулевых элементов\n");
    if (fscanf(f_in, "%lu%lu", m, el_num) != 2)
        return ERR_IO;

    // Количество ненулевых элементов в матрице больше числа элементов матрицы
    if (*el_num > (*m) * (*n))
        return ERR_RANGE;

    // Количество строк или стобцов = 0
    if (*m == 0 || *n == 0)
        return ERR_RANGE;

    // Выделение памяти под матрицу
    *ptrs = matrix_allocate(*n, *m);
    if (*ptrs == NULL)
        return ERR_MEM;

    // Заполнение матрицы 0-ми
    for (size_t i = 0; i < *n; i++)
    {
        for (size_t j = 0; j < *m; j++) 
        {
            (*ptrs)[i][j] = 0;
        }
    }
    
    int rc = ERR_OK;
    if (*el_num > 0)
    {
        prompt(f_out, "Значения ненулевых элементов\n");
    }
    // Считывание ненулевых элементов
    for (size_t i = 0; i < *el_num; i++)
    {
        size_t x, y = 1;
        int val;
        prompt(f_out, "Введите через пробел: номер столбца, значение элeмента\n");
        if (fscanf(f_in, "%lu%d", &x, &val) != 2)
        {
            rc = ERR_IO;
            break;
        }
        if (x > *m || y > *n || x == 0 || y == 0)
        {
            rc = ERR_IO;
            break;
        }
        if ((*ptrs)[y - 1][x - 1] != 0)
        {
            rc = ERR_EL_OVERWRITE;
            break;
        }
        (*ptrs)[y - 1][x - 1] = val;
    }

    // Если произошла ошибка при считывании 
    if (rc != ERR_OK)
    {
        matrix_free(*ptrs);
        *ptrs = NULL;
    }
    return rc;
}

size_t matrix_count_no_zero(int **ptrs, size_t n, size_t m)
{
    size_t el_num = 0; // Количество ненулевых элементов матрицы

    for (size_t i = 0; i < n; i ++)
    {
        for (size_t j = 0; j < m; j++)
        {
            if (abs(ptrs[i][j]) > 0) 
                el_num++;
        }
    }
    
    return el_num;
}

int matrix_normal_print(FILE *f, int **ptrs, size_t n, size_t m)
{
    fprintf(f, "%lu %lu\n", n, m);
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            fprintf(f, "%d ", ptrs[i][j]);
        }
        fprintf(f, "\n");
    }

    return ERR_OK;
}

