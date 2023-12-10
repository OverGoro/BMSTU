#include "menu.h"
#include "vec_io.h"
#include "sparse_matrix_operations.h"
#include "sparse_matrix_io.h"
#include <stdio.h>
#include <stddef.h>
#include "prompt.h"

void handle_err(int err)
{
    switch (err) 
    {
    case ERR_OK:
        printf("\033[92mОперация завершена\033[0m\n");
        break;
    case ERR_IO:
        printf("\033[91mОшибка ввода\033[0m\n");
        break;
    case ERR_RANGE:
        printf("\033[91mОшибка диапазона данных\033[0m\n");
        break;
    case ERR_MEM:
        printf("\033[91mОшибка работы с динамической памятью\033[0m\n");
        break;
    case ERR_EL_OVERWRITE:
        printf("\033[91mОшибка: перезапись элемента\033[0m\n");
        break;
    default:
        printf("\033[91mНеизвестная ошибка\033[0m\n");
        break;
    }
}

void menu_commands_print(void)
{
    printf(MENU_TEXT);
}


int menu_input_matrix(int ***mat, sparse_t *sparse_mat)
{
    size_t n, m, el_num;
    int rc = matrix_coord_input(stdin, stdout, mat, &n, &m, &el_num, normal_prompt);
    if (!rc)
        rc = sm_convert_from_normal(sparse_mat, *mat, n, m);
    handle_err(rc);
    return rc;
}

int menu_input_vector(int ***mat, vector_t *vec)
{
    size_t n, m, el_num;
    int rc = matrix_vec_coord_input(stdin, stdout, mat, &n, &m, &el_num, normal_prompt);
    if (!rc)
        rc = v_convert_from_matrix(vec, *mat, n, m);
    handle_err(rc);
    return rc;
}

int menu_print_matrix(sparse_t *mat)  
{
    if (mat->m > 10 || mat->n > 10)
    {
        printf("В разреженном виде:\n");
        sm_print(stdout, mat);
    }
    else
    {
        printf("В нормальном виде:\n");
        sm_normal_print(stdout, mat);
    }
    handle_err(ERR_OK);
    return ERR_OK;
}

int menu_print_vector(vector_t *vec)
{
    if (vec->m > 10)
    {
        printf("В разреженном виде:\n");
        vec_print(stdout, vec);
    }
    else
    {
        printf("В нормальном виде:\n");
        vec_normal_print(stdout, vec);
    }
    handle_err(ERR_OK);
    return ERR_OK;
}

int menu_mult(vector_t *vec, sparse_t *mat, vector_t *vec_r)
{
    int rc = sm_multiply(vec, mat, vec_r);
    if (!rc)
    {
        if (vec_r->m > 10)
            vec_print(stdout, vec_r);
        else
            vec_normal_print(stdout, vec_r);
    }
    handle_err(rc);
    return rc;
}

int menu_mult_normal(vector_t *vec, sparse_t *mat, vector_t *vec_r)
{
    int rc = sm_mult_normal(vec, mat, vec_r);
    if (!rc)
    {
        if (vec_r->m > 10)
            vec_print(stdout, vec_r);
        else
            vec_normal_print(stdout, vec_r);
    }
    handle_err(rc);
    return rc;
}

int menu_measure(FILE *f, FILE *f_normal, FILE *f_sparse)
{
    int rc = make_measure(f, f_normal, f_sparse);
    handle_err(rc);
    return rc;
}

