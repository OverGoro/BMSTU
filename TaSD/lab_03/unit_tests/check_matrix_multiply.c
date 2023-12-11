#include "check_matrix_multiply.h"
#include <check.h>
START_TEST(test_multiply_square)
{
    size_t n = 3, m = 3;

    double mat_1[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    double *pmat_1[3] = {mat_1[0], mat_1[1], mat_1[2]};

    double mat_2[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    double *pmat_2[3] = {mat_2[0], mat_2[1], mat_2[2]};

    double **mat_r;
    size_t n_r = 0, m_r = 0;
    double mat_ans[3][3] =  {{30, 36, 42}, {66, 81, 96}, {102, 126, 150}};

    int rc = matrix_multiply(pmat_1, n, m, pmat_2, n, m, &mat_r, &n_r, &m_r);

    ck_assert_uint_eq(rc, ERR_OK);
    ck_assert_uint_eq(n, n_r);
    ck_assert_uint_eq(m, m_r);

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            ck_assert_double_eq(mat_r[i][j], mat_ans[i][j]);
        }
    }

    matrix_free(mat_r);
} END_TEST

START_TEST(test_multiply_not_square)
{
    size_t n = 2, m = 3;

    double mat_1[2][3] = {{1, 2, 3}, {4, 5, 6}};
    double *pmat_1[2] = {mat_1[0], mat_1[1]};

    double mat_2[3][2] = {{1, 2}, {3, 4}, {5, 6}};
    double *pmat_2[3] = {mat_2[0], mat_2[1], mat_2[2]};

    double **mat_r;
    size_t n_r = 0, m_r = 0;
    double mat_ans[2][2] =  {{22, 28}, {49, 64}};

    int rc = matrix_multiply(pmat_1, n, m, pmat_2, m, n, &mat_r, &n_r, &m_r);

    ck_assert_uint_eq(rc, ERR_OK);
    ck_assert_uint_eq(2, n_r);
    ck_assert_uint_eq(2, m_r);

    for (size_t i = 0; i < 2; i++)
    {
        for (size_t j = 0; j < 2; j++)
        {
            ck_assert_double_eq(mat_r[i][j], mat_ans[i][j]);
        }
    }

    matrix_free(mat_r);
} END_TEST

START_TEST(test_multiply_one)
{
    size_t n = 1, m = 1;

    double mat_1[1][1] = {{2}};
    double *pmat_1[1] = {mat_1[0]};

    double mat_2[1][1] = {{1}};
    double *pmat_2[1] = {mat_2[0]};

    double **mat_r;
    size_t n_r = 0, m_r = 0;
    double mat_ans[1][1] =  {{2}};

    int rc = matrix_multiply(pmat_1, n, m, pmat_2, n, m, &mat_r, &n_r, &m_r);

    ck_assert_uint_eq(rc, ERR_OK);
    ck_assert_uint_eq(n, n_r);
    ck_assert_uint_eq(m, m_r);

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            ck_assert_double_eq(mat_r[i][j], mat_ans[i][j]);
        }
    }

    matrix_free(mat_r);
} END_TEST

START_TEST(test_multiply_wrong_n)
{
    double mat_1[2][3] = {{1, 2, 3}, {4, 5, 6}};
    double *pmat_1[2] = {mat_1[0], mat_1[1]};

    double mat_2[2][3] = {{1}};
    double *pmat_2[2] = {mat_2[0], mat_2[1]};

    double **mat_r;
    size_t n_r = 0, m_r = 0;

    int rc = matrix_multiply(pmat_1, 2, 3, pmat_2, 2, 3, &mat_r, &n_r, &m_r);

    if (rc == ERR_OK)
        matrix_free(mat_r);

    ck_assert_uint_ne(rc, ERR_OK);
} END_TEST

START_TEST(test_multiply_wrong_m)
{
    double mat_1[3][2] = {{2}};
    double *pmat_1[3] = {mat_1[0], mat_1[1], mat_1[2]};

    double mat_2[3][2] = {{1}};
    double *pmat_2[3] = {mat_2[0], mat_2[1], mat_2[2]};

    double **mat_r;
    size_t n_r = 0, m_r = 0;

    int rc = matrix_multiply(pmat_1, 3, 2, pmat_2, 3, 2, &mat_r, &n_r, &m_r);

    if (rc == ERR_OK)
        matrix_free(mat_r);

    ck_assert_uint_ne(rc, ERR_OK);
} END_TEST


Suite *multiply_suite(void)
{
    Suite *s;
    TCase *tc_core;
    s = suite_create("multiply");
    tc_core = tcase_create("core");

    tcase_add_test(tc_core, test_multiply_square);
    tcase_add_test(tc_core, test_multiply_not_square);
    tcase_add_test(tc_core, test_multiply_one);
    tcase_add_test(tc_core, test_multiply_wrong_n);
    tcase_add_test(tc_core, test_multiply_wrong_m);
    suite_add_tcase(s, tc_core);

    return s;
}

