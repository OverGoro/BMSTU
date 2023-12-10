#include "check_key.h"
#include <check.h>
START_TEST(test_key_random)
{
    int tai[] = {999, -999, 111, 2, 3, 5, 1, 4}; // Случайный массив
    int tai_ans[] = {999, 111};
    int *tai_temp;
    int *tai_temp_end;
    
    int rc = key(tai, tai + sizeof(tai) / sizeof(int), &tai_temp, &tai_temp_end); 

    size_t n_arr = tai_temp_end - tai_temp;
    size_t n_ans = sizeof(tai_ans) / sizeof(tai_ans[0]);

    ck_assert_uint_eq(rc, ERR_OK);
    cmp_arr_int(tai_temp, n_arr, tai_ans, n_ans);

    free(tai_temp);
} END_TEST

START_TEST(test_key_reversed)
{
    int tai[] = {999, 111, 5, 4, 3, 2, 1, -999}; // Упорядоченный по убыванию массив
    int tai_ans[] = {999, 111};
    int *tai_temp;
    int *tai_temp_end;
    int rc = key(tai, tai + sizeof(tai) / sizeof(int), &tai_temp, &tai_temp_end); 

    size_t n_arr = tai_temp_end - tai_temp;
    size_t n_ans = sizeof(tai_ans) / sizeof(tai_ans[0]);

    ck_assert_uint_eq(rc, ERR_OK);
    cmp_arr_int(tai_temp, n_arr, tai_ans, n_ans);

    free(tai_temp);
}END_TEST

START_TEST(test_key_sorted)
{
    int tai[] = {-999, 1, 2, 3, 4, 5, 111, 999}; // Упорядоченный по возрастанию массив
    int tai_ans[] = {111, 999};
    int *tai_temp;
    int *tai_temp_end;
    int rc = key(tai, tai + sizeof(tai) / sizeof(int), &tai_temp, &tai_temp_end); 

    size_t n_arr = tai_temp_end - tai_temp;
    size_t n_ans = sizeof(tai_ans) / sizeof(tai_ans[0]);

    ck_assert_uint_eq(rc, ERR_OK);
    cmp_arr_int(tai_temp, n_arr, tai_ans, n_ans);

    free(tai_temp);
} END_TEST

Suite *key_suite(void)
{
    Suite *s;
    TCase *tc_core;
    s = suite_create("key");
    tc_core = tcase_create("core");

    tcase_add_test(tc_core, test_key_random);
    tcase_add_test(tc_core, test_key_reversed);
    tcase_add_test(tc_core, test_key_sorted);
    suite_add_tcase(s, tc_core);

    return s;
}

