#include "vec_io.h"
#include <stdio.h>

int vec_input(FILE *f_in, FILE *f_out, vector_t *vec, prompt_t prompt)
{ 
    // Считывание размеров матрицы и количество ненулевых элементов 
    size_t n = 0;
    size_t m = 0;
    size_t el_num = 0;
    int rc = v_init_content(vec, 0, 0);
    if (rc != ERR_OK)
        return rc;
    
    int **ptmp = NULL;
    rc = matrix_coord_input(f_in, f_out, &ptmp, &n, &m, &el_num, prompt);
    if (rc != ERR_OK)
        return rc;
    // matrix_normal_print(f_out, ptmp, n, m);
    if (n != 1)
    {
        free(ptmp);
        return ERR_RANGE;
    }

    // Выделение памяти под содержимое полей матрицы
    rc = v_convert_from_matrix(vec, ptmp, n, m);
    free(ptmp);
    return rc;
}

void vec_print(FILE *f, vector_t *vec)
{
    if (vec->m == 0)
    {
        fprintf(f, "\033[92mПустой вектор\033[0m\n");
        return;
    }
    fprintf(f, " A: ");
    for(size_t i = 0; i < vec->el_num; i++)
    {
        fprintf(f, "%d ", vec->values[i]);
    }
    fprintf(f, "\n");
    fprintf(f, "JA: ");
    for(size_t i = 0; i < vec->el_num; i++)
    {
        fprintf(f, "%lu ", vec->columns[i]);
    }
    fprintf(f, "\n");
}

void vec_normal_print(FILE *f, vector_t *vec)
{
    if (vec->m == 0)
    {
        fprintf(f, "\033[92mПустой вектор\033[0m\n");
        return;
    }
    size_t cur_el = 0;
    for (size_t i = 0; i < vec->m; i++)
    {
        if (cur_el < vec->el_num && vec->columns[cur_el] == i)
        {
            fprintf(f, "%d ", vec->values[cur_el]);
            cur_el++;
        }
        else 
        {
            fprintf(f, "0 ");
        }
    }
    fprintf(f, "\n");
}

