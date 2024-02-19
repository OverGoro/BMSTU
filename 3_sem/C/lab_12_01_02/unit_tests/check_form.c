#include "check_form.h"
#include <check.h>
#include "../inc/array.h"
#include "check_cmp.h"

// Формирование массива полных квадратов из массива с множеством элементов и 1 полным квадратом
// Выделение необходмой памяти
START_TEST(test_form_sqr_count_size_one)
{
    int arr[10] = {1, 2, 3, 6, 7, 8, 10, 11, 12, 13};
    int ans_arr[1] = {1};
    int res_arr[1];
    size_t n = 0;
    array_form_sqr(arr, sizeof(arr) / sizeof(int), res_arr, &n);
    ck_assert_uint_eq(n, sizeof(ans_arr) / sizeof(int));
    array_form_sqr(arr, sizeof(arr) / sizeof(int), res_arr, &n);
    int rc = cmp_arr_int(ans_arr, sizeof(ans_arr) / sizeof(int), res_arr, n);
    ck_assert_int_eq(rc, 0);
}

// Формирование массива полных квадратов из массива с множеством элементов и множеством полных квадратов
// Выделение необходмой памяти
START_TEST(test_form_sqr_count_size_several)
{
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int ans_arr[3] = {1, 4, 9};
    int res_arr[3];
    size_t n = 0;
    array_form_sqr(arr, sizeof(arr) / sizeof(int), res_arr, &n);
    ck_assert_uint_eq(n, sizeof(ans_arr) / sizeof(int));
    array_form_sqr(arr, sizeof(arr) / sizeof(int), res_arr, &n);
    int rc = cmp_arr_int(ans_arr, sizeof(ans_arr) / sizeof(int), res_arr, n);
    ck_assert_int_eq(rc, 0);
}

// Формирование массива полных квадратов из массива с множеством элементов и 0 полных квадратов
// Выделение необходмой памяти
START_TEST(test_form_sqr_count_size_null)
{
    int arr[10] = {2, 2, 3, 2, 5, 6, 7, 8, 2, 10};
    int res_arr[1];
    size_t n = 0;
    array_form_sqr(arr, sizeof(arr) / sizeof(int), res_arr, &n);
    ck_assert_uint_eq(n, 0);
}

// Формирование массива полных квадратов из массива с множеством элементов и 1 полным квадратом
// Выделение памяти равной исходному массиву
START_TEST(test_form_sqr_max_size_one)
{
    int arr[10] = {1, 2, 3, 6, 7, 8, 10, 11, 12, 13};
    int ans_arr[1] = {1};
    int res_arr[sizeof(arr) / sizeof(int)];
    size_t n = sizeof(arr) / sizeof(int);

    array_form_sqr(arr, sizeof(arr) / sizeof(int), res_arr, &n);

    ck_assert_uint_eq(n, sizeof(ans_arr) / sizeof(int));
    int rc = cmp_arr_int(ans_arr, sizeof(ans_arr) / sizeof(int), res_arr, n);
    ck_assert_int_eq(rc, 0);
}
// Формирование массива полных квадратов из массива с множеством элементов и 1 полным квадратом
// Выделение памяти равной исходному массиву
START_TEST(test_form_sqr_max_size_several)
{
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int ans_arr[3] = {1, 4, 9};
    int res_arr[sizeof(arr) / sizeof(int)];
    size_t n = sizeof(arr) / sizeof(int);

    array_form_sqr(arr, sizeof(arr) / sizeof(int), res_arr, &n);

    ck_assert_uint_eq(n, sizeof(ans_arr) / sizeof(int));
    int rc = cmp_arr_int(ans_arr, sizeof(ans_arr) / sizeof(int), res_arr, n);
    ck_assert_int_eq(rc, 0);
}

// Формирование массива полных квадратов из массива с множеством элементов и 0 полных квадратов
// Выделение памяти равной исходному массиву
START_TEST(test_form_sqr_max_size_null)
{
    int arr[10] = {2, 2, 3, 2, 5, 6, 7, 8, 2, 10};
    int res_arr[1];
    size_t n = sizeof(arr) / sizeof(int);

    array_form_sqr(arr, sizeof(arr) / sizeof(int), res_arr, &n);

    ck_assert_uint_eq(n, 0);
}


Suite *form_suite(void)
{
    Suite *s;
    TCase *tc_core;
    s = suite_create("form");
    tc_core = tcase_create("core");

    tcase_add_test(tc_core, test_form_sqr_max_size_null);
    tcase_add_test(tc_core, test_form_sqr_max_size_one);
    tcase_add_test(tc_core, test_form_sqr_max_size_several);

    tcase_add_test(tc_core, test_form_sqr_count_size_null);
    tcase_add_test(tc_core, test_form_sqr_count_size_one);
    tcase_add_test(tc_core, test_form_sqr_count_size_several);
    
    suite_add_tcase(s, tc_core);

    return s;
}

