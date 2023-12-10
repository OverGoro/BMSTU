#include "vec.h"
#include <stdlib.h>

void v_free_content(vector_t *vector)
{
    if (vector->values != NULL)
        free(vector->values);
    vector->values = NULL;

    if (vector->columns != NULL)
        free(vector->columns);
    vector->columns = NULL;
}

int v_init_content(vector_t *vector, size_t m, size_t el_num)
{
    v_free_content(vector);
    vector->el_num = 0;
    vector->m = 0;
    
    if (el_num == 0)
        vector->values = calloc(1, sizeof(int)); // Выделение одного элемента, для realloc
    else
        vector->values = calloc(el_num, sizeof(int));
    if (vector->values == NULL)
    {
        v_free_content(vector);
        return ERR_MEM;
    }

    if (el_num > 0)
        vector->columns = calloc(el_num, sizeof(size_t));
    else
        vector->columns = calloc(1, sizeof(size_t));
    if (vector->columns == NULL)
    {
        v_free_content(vector);
        return ERR_MEM;
    }

    vector->m = m;
    vector->el_num = el_num;
    return ERR_OK;
}

int v_convert_from_matrix(vector_t *vector, int **mat, size_t n, size_t m)
{
    if (n != 1 || m == 0)
        return ERR_RANGE;
    size_t el_num = matrix_count_no_zero(mat, n, m);
    int rc = v_init_content(vector, m, el_num);
    if (rc)
        return rc;
    size_t cur_el_i = 0;
    for (size_t i = 0; i < m; i++)
    {
        if (mat[0][i] != 0)
        {
            vector->values[cur_el_i] = mat[0][i];
            vector->columns[cur_el_i] = i;
            cur_el_i++;
        }
    }
    return rc;
}

int v_convert_to_matrix(vector_t *vector, int ***mat, size_t *n, size_t *m)
{
    *mat = matrix_allocate(1, vector->m);
    if (*mat == NULL)
        return ERR_MEM;
    for (size_t i = 0; i < vector->m; i++)
    {
        (*mat)[0][i] = 0;
    }
    for (size_t i = 0; i < vector->el_num; i++)
    {
         (*mat)[0][vector->columns[i]] = vector->values[i];
    }
    *n = 1;
    *m = vector->m;
    return ERR_OK;
}

int v_push(vector_t *vector, size_t m, int value)
{
    int *tmp_val = realloc(vector->values, sizeof(int) * (vector->el_num + 1));
    if (tmp_val == NULL)
        return ERR_MEM;
    vector->values = tmp_val;

    size_t *tmp_columns = realloc(vector->columns, sizeof(size_t) * (vector->el_num + 1));
    if (tmp_columns == NULL)
        return ERR_MEM;
    vector->columns = tmp_columns;
    
    vector->el_num++;
    vector->values[vector->el_num - 1] = value;
    vector->columns[vector->el_num - 1] = m;
    return ERR_OK;
}

