#include "sparse_matrix_generator.h"
#include "sparse_matrix_io.h"

int matrix_generate(int ***mat, sparse_t *mat_sparse, size_t m, size_t n, size_t fill_percent)
{
    matrix_free(*mat);

    if (m == 0 || n == 0)
        return ERR_OK;

    srand(0);

    size_t el_num = (size_t)(m * n * fill_percent / 100); // Количество случайных элементов
    size_t enterend_el_num = 0; // Количество заполненных элементов

    *mat = NULL;
    *mat = matrix_allocate(m, n);

    if (*mat == NULL)
        return ERR_MEM;

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            if (enterend_el_num < el_num)
                (*mat)[i][j] = rand() % (m);
            else
                (*mat)[i][j] = 0;
            enterend_el_num++;
        }            
    }

    int rc = sm_convert_from_normal(mat_sparse, *mat, n, m);
    return rc;
}

int vector_generate(int ***mat, vector_t *vec, size_t m, size_t fill_percent)
{
    matrix_free(*mat);
    if (m == 0)
        return ERR_OK;
    srand(0);
    size_t n = 1;
    size_t el_num = (size_t)(m * n * fill_percent / 100);
    size_t enterend_el_num = 0;

    *mat = NULL;
    *mat = matrix_allocate(m, n);

    if (*mat == NULL)
        return ERR_MEM;

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            if (enterend_el_num < el_num)
                (*mat)[i][j] = rand() % (m);
            else
                (*mat)[i][j] = 0;
            enterend_el_num++;
        }            
    }


    int rc = v_convert_from_matrix(vec, *mat, n, m);
    return rc;
}

