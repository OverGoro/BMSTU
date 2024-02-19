#include "check_key.h"
#include <check.h>
#include <stdlib.h>
START_TEST(test_key_random)
{
    int tai[] = {999, -999, 111, 2, 3, 5, 1, 4}; // Случайный массив
    int tai_ans[] = {999, 111};
    int tai_temp[2];
    
    double av = get_average(tai, tai + sizeof(tai) / sizeof(int));
    size_t n = count_greater(tai, tai + sizeof(tai) / sizeof(int), av);

    ck_assert_uint_eq(n, sizeof(tai_ans) / sizeof(int));
    
    int rc = key(tai, tai + sizeof(tai) / sizeof(int), tai_temp, tai_temp + sizeof(tai_temp) / sizeof(int)); 

    size_t n_ans = sizeof(tai_ans) / sizeof(tai_ans[0]);

    ck_assert_uint_eq(rc, ERR_OK);
    cmp_arr_int(tai_temp, n, tai_ans, n_ans);

} END_TEST

START_TEST(test_key_reversed)
{
    int tai[] = {999, 111, 5, 4, 3, 2, 1, -999}; // Упорядоченный по убыванию массив
    int tai_ans[] = {999, 111};
    int tai_temp[2];
    
    double av = get_average(tai, tai + sizeof(tai) / sizeof(int));
    size_t n = count_greater(tai, tai + sizeof(tai) / sizeof(int), av);

    ck_assert_uint_eq(n, sizeof(tai_ans) / sizeof(int));
    
    int rc = key(tai, tai + sizeof(tai) / sizeof(int), tai_temp, tai_temp + sizeof(tai_temp) / sizeof(int)); 

    size_t n_ans = sizeof(tai_ans) / sizeof(tai_ans[0]);

    ck_assert_uint_eq(rc, ERR_OK);
    cmp_arr_int(tai_temp, n, tai_ans, n_ans);
}END_TEST

START_TEST(test_key_sorted)
{
    int tai[] = {-999, 1, 2, 3, 4, 5, 111, 999}; // Упорядоченный по возрастанию массив
    int tai_ans[] = {111, 999};
    int tai_temp[2];
    
    double av = get_average(tai, tai + sizeof(tai) / sizeof(int));
    size_t n = count_greater(tai, tai + sizeof(tai) / sizeof(int), av);

    ck_assert_uint_eq(n, sizeof(tai_ans) / sizeof(int));
    
    int rc = key(tai, tai + sizeof(tai) / sizeof(int), tai_temp, tai_temp + sizeof(tai_temp) / sizeof(int)); 

    size_t n_ans = sizeof(tai_ans) / sizeof(tai_ans[0]);

    ck_assert_uint_eq(rc, ERR_OK);
    cmp_arr_int(tai_temp, n, tai_ans, n_ans);
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

