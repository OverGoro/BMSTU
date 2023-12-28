#include "check_cmp.h"

void cmp_arr_str(char parr[][8], size_t n_arr, char ans[][8], size_t n_ans)
{
    ck_assert_uint_eq(n_arr, n_ans);
    for (size_t i = 0; i < n_arr; i++)
    {
        ck_assert_str_eq(parr[i], ans[i]);
    }
}

void cmp_arr_int(int *parr, size_t n_arr, int *ans, size_t n_ans)
{
    ck_assert_uint_eq(n_arr, n_ans);
    for (size_t i = 0; i < n_arr; i++)
    {
        ck_assert_int_eq(parr[i], ans[i]);
    }
}

void cmp_arr_float(float *parr, size_t n_arr, float *ans, size_t n_ans)
{
    ck_assert_uint_eq(n_arr, n_ans);
    for (size_t i = 0; i < n_arr; i++)
    {
        ck_assert_float_eq(parr[i], ans[i]);
    }
}

void cmp_arr_double(double *parr, size_t n_arr, double *ans, size_t n_ans)
{
    ck_assert_uint_eq(n_arr, n_ans);
    for (size_t i = 0; i < n_arr; i++)
    {
        ck_assert_double_eq(parr[i], ans[i]);
    }
}



