#include "check_shift.h"
#include <check.h>
#include "../inc/array.h"
#include "check_cmp.h"

START_TEST(test_shift_one_el_one_mv)
{
    int arr[1] = {1};
    int arr_ans[1] = {1};
    size_t n = 1;
    array_cycle_shift(arr, n, 1);
    ck_assert_int_eq(cmp_arr_int(arr, n, arr_ans, n), 0);
}

START_TEST(test_shift_one_el_several_mv)
{
    int arr[1] = {1};
    int arr_ans[1] = {1};
    size_t n = 1;
    array_cycle_shift(arr, n, 12);
    ck_assert_int_eq(cmp_arr_int(arr, n, arr_ans, n), 0);
}

START_TEST(test_shift_several_el_one_mv)
{
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int arr_ans[10] = {10, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    size_t n = 10;
    array_cycle_shift(arr, n, 1);
    ck_assert_int_eq(cmp_arr_int(arr, n, arr_ans, n), 0);
}

START_TEST(test_shift_several_el_several_mv)
{
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int arr_ans[10] = {8, 9, 10, 1, 2, 3, 4, 5, 6, 7};
    size_t n = 10;
    array_cycle_shift(arr, n, 3);
    ck_assert_int_eq(cmp_arr_int(arr, n, arr_ans, n), 0);
}



Suite *shift_suite(void)
{
    Suite *s;
    TCase *tc_core;
    s = suite_create("shift");
    tc_core = tcase_create("core");
    tcase_add_test(tc_core, test_shift_one_el_one_mv); 
    tcase_add_test(tc_core, test_shift_one_el_several_mv); 
    tcase_add_test(tc_core, test_shift_several_el_one_mv); 
    tcase_add_test(tc_core, test_shift_several_el_several_mv); 

    suite_add_tcase(s, tc_core);

    return s;
}

