#include "check_slae.h"
#include <check.h>
START_TEST(test_slae_eq_n)
{
    double mat_1[3][4] = {{1, 6, 7, 10}, {2, 5, 14, 13}, {3, 4, 9, 21}};
    double *pmat_1[3] = {mat_1[0], mat_1[1], mat_1[2]};


    double **mat_r;
    size_t n_r = 0, m_r = 0;
    double mat_ans[3][1] =  {{(double)83/12}, {1}, {(double)-5/12}};

    int rc = slae_solve(pmat_1, 3, 4, &mat_r, &n_r, &m_r);

    ck_assert_uint_eq(rc, ERR_OK);
    ck_assert_uint_eq(3, n_r);
    ck_assert_uint_eq(1, m_r);

    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 1; j++)
        {
            ck_assert_double_eq_tol(mat_r[i][j], mat_ans[i][j], EPSILON);
        }
    }

    matrix_free(mat_r);
} END_TEST

START_TEST(test_slae_gt_n) 
{
    double mat_1[4][4] = {{1, 6, 7, 10}, {2, 5, 14, 13}, {3, 4, 9, 21}, {6, 8, 18, 42}};
    double *pmat_1[4] = {mat_1[0], mat_1[1], mat_1[2], mat_1[3]};


    double **mat_r;
    size_t n_r = 0, m_r = 0;
    double mat_ans[3][1] =  {{(double)83/12}, {1}, {(double)-5/12}};

    int rc = slae_solve(pmat_1, 3, 4, &mat_r, &n_r, &m_r);

    ck_assert_uint_eq(rc, ERR_OK);
    ck_assert_uint_eq(3, n_r);
    ck_assert_uint_eq(1, m_r);

    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 1; j++)
        {
            ck_assert_double_eq_tol(mat_r[i][j], mat_ans[i][j], EPSILON);
        }
    }

    matrix_free(mat_r);
} END_TEST

START_TEST(test_slae_lt_n) 
{
    double mat_1[2][4] = {{1, 6, 7, 10}, {2, 5, 14, 13}};
    double *pmat_1[2] = {mat_1[0], mat_1[1]};


    double **mat_r = NULL;
    size_t n_r = 0, m_r = 0;

    int rc = slae_solve(pmat_1, 2, 4, &mat_r, &n_r, &m_r);

    ck_assert_uint_ne(rc, ERR_OK);
    ck_assert_uint_eq(0, n_r);
    ck_assert_uint_eq(0, m_r);
    if (mat_r == NULL)
        matrix_free(mat_r);
} END_TEST

Suite *slae_suite(void)
{
    Suite *s;
    TCase *tc_core;
    s = suite_create("slae");
    tc_core = tcase_create("core");

    tcase_add_test(tc_core, test_slae_eq_n);
    tcase_add_test(tc_core, test_slae_gt_n);
    tcase_add_test(tc_core, test_slae_lt_n);
    suite_add_tcase(s, tc_core);

    return s;
}

