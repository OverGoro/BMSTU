#include "sparse_matrix_operations.h"
#include <stdio.h>

int sm_multiply(vector_t *vec_1, const sparse_t *mat_2, vector_t *vec_r)
{
    // Неправильные размеры матриц
    if (vec_1->m != mat_2->n || mat_2->m == 0 || mat_2->n == 0 || vec_1->m == 0)
        return ERR_RANGE;

    int rc = v_init_content(vec_r, mat_2->m, 0);
    if (rc)
        return rc;
    
    for (size_t j = 0; j < mat_2->m; j++)
    {
        if (mat_2->column_coords[j] == -1)
            continue;

        bool added = false;
        for (size_t i = 0; i < vec_1->el_num; i++)
        {
            int val;
            if (sm_get_el_by_coords(mat_2, vec_1->columns[i], j, &val) == ERR_OK)
            {
                val *= vec_1->values[i];
                if (!added)
                {
                    added = true;
                    v_push(vec_r, j, val);
                }
                else 
                {
                    vec_r->values[vec_r->el_num - 1] += val;
                }
            }
        }
    }
    return ERR_OK;
}

int sm_mult_normal(vector_t *vec, sparse_t *mat, vector_t *vec_r)
{
    if (vec->m == 0)
        return ERR_RANGE;
    if (mat->m == 0 || mat->n == 0)
        return ERR_RANGE;
    size_t m_1, n_1;
    size_t m_2, n_2;
    size_t m_r, n_r;
    int **mat_1 = NULL, **mat_2 = NULL, **mat_r = NULL;
    int rc = v_convert_to_matrix(vec, &mat_1, &n_1, &m_1);
    if (!rc)
        rc = sm_convert_to_normal(mat, &mat_2, &n_2, &m_2);
    if (!rc)
        rc = matrix_multiply(mat_1, n_1, m_1, mat_2, n_2, m_2, &mat_r, &n_r, &m_r);
    if (!rc)
        rc = v_convert_from_matrix(vec_r, mat_r, n_r, m_r);
    matrix_free(mat_1);
    matrix_free(mat_2);
    matrix_free(mat_r);
    return rc;
}

