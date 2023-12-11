#include "matrix_operations.h"

void matrix_swap_column(int **ptrs, size_t n, size_t m_1, size_t m_2)
{
    for (size_t i = 0; i < n; i++)
    {
        int tmp = ptrs[i][m_1];
        ptrs[i][m_1] = ptrs[i][m_2];
        ptrs[i][m_2] = tmp;
    }
}

void matrix_swap_row(int **ptrs, size_t n_1, size_t n_2)
{
    int *tmp = ptrs[n_1];
    ptrs[n_1] = ptrs[n_2];
    ptrs[n_2] = tmp;
}

void matrix_multiply_row(int **ptrs, size_t n, size_t m, int k)
{
    for (size_t i = 0; i < m; i++)
        ptrs[n][i] *= k;
}

void matrix_summ_row(int **ptrs, size_t n_dst, size_t n_src, size_t m)
{
    for (size_t i = 0; i < m; i++)
        ptrs[n_dst][i] += ptrs[n_src][i];
}

void matrix_up_triangle(int **ptrs, size_t n_t, size_t m_t, size_t m)
{
    size_t cur_i = 0, cur_j = 0;
    while (cur_i < n_t && cur_j < m_t)
    {
        for (size_t i = cur_i + 1; i < n_t; i++)
        {
            if (abs(ptrs[i][cur_j]) > EPSILON && abs(ptrs[cur_i][cur_j]) > EPSILON)
            {
                matrix_multiply_row(ptrs, i, m, -ptrs[cur_i][cur_j] / ptrs[i][cur_j]);
                matrix_summ_row(ptrs, i, cur_i, m);
            }
        }
        cur_i++;
        cur_j++;
    }
}

void matrix_bottom_triangle(int **ptrs, size_t n_t, size_t m_t, size_t m)
{
    size_t cur_i = 1, cur_j = 1;
    while (cur_i < n_t && cur_j < m_t)
    {
        for (int i = cur_i - 1; i >= 0; i--)
        {
            if (abs(ptrs[i][cur_j]) > EPSILON && abs(ptrs[cur_i][cur_j]) > EPSILON)
            {
                matrix_multiply_row(ptrs, i, m, -ptrs[cur_i][cur_j] / ptrs[i][cur_j]);
                matrix_summ_row(ptrs, i, cur_i, m);
            }
        }
        cur_i++;
        cur_j++;
    }
}

int matrix_multiply(int **mat_1, size_t n_1, size_t m_1,
int **mat_2, size_t n_2, size_t m_2,
int ***mat_res, size_t *n_res, size_t *m_res)
{
    // Проверка входных матриц
    if (mat_1 == NULL || mat_2 == NULL)
    {
        return ERR_RANGE;
    }
    
    // Проверка совместимости размерностей матриц
    if (m_1 != n_2) 
    {
        return ERR_RANGE;
    }
    
    // Выделение памяти для результирующей матрицы
    *n_res = n_1;
    *m_res = m_2;
    *mat_res = matrix_allocate(*n_res, *m_res);
    if (*mat_res == NULL)
    {
        return ERR_MEM;
    }
    
    // Умножение матриц
    for (size_t i = 0; i < *n_res; i++) 
    {
        for (size_t j = 0; j < *m_res; j++) 
        {
            (*mat_res)[i][j] = 0;
            for (size_t k = 0; k < m_1; k++) 
            {
                (*mat_res)[i][j] += mat_1[i][k] * mat_2[k][j];
            }
        }
    }
    
    return ERR_OK;
}

int matrix_summ(int **mat_1, size_t n_1, size_t m_1,
int **mat_2, size_t n_2, size_t m_2,
int ***mat_res, size_t *n_res, size_t *m_res) 
{
    // Проверка входных матриц
    if (mat_1 == NULL || mat_2 == NULL)
    {
        return ERR_RANGE;
    }
    
    // Проверка совместимости размерностей матриц
    if (m_1 != m_2 || n_1 != n_2) 
    {
        return ERR_RANGE;
    }
    
    // Выделение памяти для результирующей матрицы
    *n_res = n_1;
    *m_res = m_1;
    *mat_res = matrix_allocate(*n_res, *m_res);
    if (*mat_res == NULL)
    {
        return ERR_MEM;
    }
    
    // Сложение матриц
    for (size_t i = 0; i < *n_res; i++) 
    {
        for (size_t j = 0; j < *m_res; j++) 
        {
            (*mat_res)[i][j] = mat_1[i][j] + mat_2[i][j];
        }
    }
    
    return ERR_OK;
}


