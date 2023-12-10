#include "sparse_matrix_io.h"
#include <stdio.h>

int sm_coord_input(FILE *f_in, FILE *f_out, sparse_t *matrix, prompt_t prompt)
{
    // Считывание размеров матрицы и количество ненулевых элементов 
    size_t n = 0;
    size_t m = 0;
    size_t el_num = 0;
    int rc = sm_init_content(matrix, 1, 1, 1);
    if (rc != ERR_OK)
        return rc;
    
    int **ptmp = NULL;
    rc = matrix_coord_input(f_in, f_out, &ptmp, &n, &m, &el_num, prompt);
    if (rc != ERR_OK)
        return rc;
    matrix_normal_print(f_out, ptmp, n, m );

    // Выделение памяти под содержимое полей матрицы
    rc = sm_convert_from_normal(matrix, ptmp, n, m);

    return rc;
}

void sm_print(FILE *f, sparse_t *matrix)
{
    if (matrix->m == 0 || matrix->n == 0)
    {
        fprintf(f, "\033[92mПустая матрица\033[0m\n");
        return;
    }
    fprintf(f, " A: ");
    for (size_t i = 0; i < matrix->el_num; i++)
        fprintf(f, "%d ", matrix->values[i]);
    fprintf(f, "\n");
    fprintf(f, "IA: ");
    for (size_t i = 0; i < matrix->el_num; i++)
        fprintf(f, "%lu ", matrix->rows[i]);
    fprintf(f, "\n");
    fprintf(f, "JA: ");
    for (size_t i = 0; i < matrix->m; i++)
    {
        if (matrix->column_coords[i] == -1)
            fprintf(f, "- ");
        else
            fprintf(f, "%lu ", matrix->column_coords[i]);
    }
    fprintf(f, "\n");
}

int sm_normal_print(FILE *f, sparse_t *matrix)
{
    if (matrix->m == 0 || matrix->n == 0)
    {
        fprintf(f, "\033[92mПустая матрица\033[0m\n");
        return ERR_OK;
    }

    int **normal_mat = NULL; // Нормальная матрица
    size_t n, m; // Размеры нормальной матрицы
    
    int rc = sm_convert_to_normal(matrix, &normal_mat, &n, &m);
    if (rc != ERR_OK)
        return rc;
    rc = matrix_normal_print(f, normal_mat, n, m);
    return rc;
}

