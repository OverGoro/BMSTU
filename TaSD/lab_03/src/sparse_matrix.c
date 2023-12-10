#include "sparse_matrix.h"
#include <bits/types/struct_tm.h>
#include <stdio.h>
#include <stdlib.h>

int sm_init_content(sparse_t *matrix, size_t n, size_t m, size_t el_num)
{
    int rc = ERR_OK;
    sm_free_content(matrix); // Очистка старого содержимого перед новой инициализацией
    
    matrix->n = n;
    matrix->m = m;
    matrix->el_num = el_num;

    // Выделение памяти под значения ненулевых элементов
    if (rc == ERR_OK)
    {
        matrix->values = calloc(el_num, sizeof(int));
        if (matrix->values == NULL)
            rc = ERR_MEM;
    }
    // Выделение памяти под строки ненулевых элементов
    if (rc == ERR_OK)
    {
        matrix->rows = calloc(el_num, sizeof(size_t));
        if (matrix->rows == NULL)
            rc = ERR_MEM;
    }
    // Выделение памяти под индексы начала столбцов в values
    if (rc == ERR_OK)
    {
        matrix->column_coords = malloc(sizeof(ssize_t) * m);
        if (matrix->column_coords == NULL)
            rc = ERR_MEM;
        else
        {
            for (size_t i = 0; i < m; i++)
            {
                matrix->column_coords[i] = -1;
            }
        }
    }

    // В случае ошикби очистить мартрицу
    if (rc != ERR_OK)
        sm_free_content(matrix);
    return rc;
}

void sm_free_content(sparse_t *matrix)
{
    if (matrix->values != NULL)
    {
        free(matrix->values);
        matrix->values = NULL;
    }
    if (matrix->rows != NULL)
    {
        free(matrix->rows);
        matrix->rows = NULL;
    }
    if (matrix->column_coords != NULL)
    {
        free(matrix->column_coords);
        matrix->column_coords = NULL;
    }
    matrix->n = 0;
    matrix->n = 0;
    matrix->el_num = 0;
}

int sm_convert_from_normal(sparse_t *spare_matrix, int **normal_matrix, size_t n, size_t m)
{
    size_t el_num = matrix_count_no_zero(normal_matrix, n, m);
    int rc = sm_init_content(spare_matrix, n, m, el_num);
    if (rc != ERR_OK)
        return rc;
    size_t cur_i = 0;
    for (size_t j = 0; j < m; j++)
    {
        for (size_t i = 0; i < n; i++)
        {
            if (normal_matrix[i][j] != 0)
            {
                spare_matrix->values[cur_i] = normal_matrix[i][j];
                spare_matrix->rows[cur_i] = i;
                if (spare_matrix->column_coords[j] == -1)
                {
                    spare_matrix->column_coords[j] = cur_i;
                }
                cur_i++;
            }
        }
    }
    return rc;
}

int sm_convert_to_normal(sparse_t *sparse_matrix, int ***normal_matrix, size_t *n, size_t *m)
{
    *n = 0;
    *m = 0;
    // Выделение памяти под нормальную матрицу
    *normal_matrix = matrix_allocate(sparse_matrix->n, sparse_matrix->m);
    if (*normal_matrix == NULL)
        return ERR_MEM;
    
    *n = sparse_matrix->n;
    *m = sparse_matrix->m;
    
    // Заполнение нулями
    for (size_t i = 0; i < *n; i++)
    {
        for (size_t j = 0; j < *m; j++)
            (*normal_matrix)[i][j] = 0;
    }

    // Заполнение ненулевых значений
    for (size_t i = 0; i < sparse_matrix->el_num; i++)
    {
        size_t n_el, m_el;
        sm_get_el_coords(sparse_matrix, &n_el, &m_el, i);
        (*normal_matrix)[n_el][m_el] = sparse_matrix->values[i];
    }
    return ERR_OK;
}

void sm_get_el_coords(const sparse_t *matrix, size_t *n_el, size_t *m_el, size_t i_el)
{
    *n_el = matrix->rows[i_el];
    *m_el = 0;
    for(size_t i = 0; i < matrix->m; i++)
    {
        if (matrix->column_coords[i] != -1)
        {
            if (matrix->column_coords[i] <= (ssize_t)i_el)
                *m_el = i;
            else
                break;
        }
    }
}

int sm_get_el_by_coords(const sparse_t *matrix, size_t n_el, size_t m_el, int *val_el)
{
    // Координаты элемента выходят за границы массива
    if (n_el >= matrix->n || m_el >= matrix->m)
        return ERR_RANGE;
    ssize_t i_start = matrix->column_coords[m_el];
    // Стобца элемента нет в матрице
    if (i_start == -1)
        return ERR_RANGE;

    ssize_t i_end = matrix->el_num;
    for (size_t i = m_el + 1; i < matrix->m; i++)
    {
        if (matrix->column_coords[i] != -1)
        {
            i_end = matrix->column_coords[i];
            break;
        }
    }

    for (size_t i = i_start; i < (size_t)i_end; i++)
    {
        // Найден элемент с заданными координатами
        if (matrix->rows[i] == n_el)
        {
            *val_el = matrix->values[i];
            return ERR_OK;
        }
    }
    // Элемент оказался нулевым
    return ERR_RANGE;

}

int sm_push_element(sparse_t *matrix, size_t n_el, int val_el)
{
    int *tmp_values = realloc(matrix->values, (matrix->el_num + 1) * sizeof(int));
    if (tmp_values == NULL)
        return ERR_MEM;
    matrix->values = tmp_values;

    size_t *tmp_rows = realloc(matrix->values, (matrix->el_num + 1) * sizeof(size_t));
    if (tmp_rows == NULL)
        return ERR_MEM;
    matrix->rows = tmp_rows;
    
    matrix->values[matrix->el_num - 1] = val_el;
    matrix->rows[matrix->el_num - 1] = n_el;
    return ERR_OK;
}


