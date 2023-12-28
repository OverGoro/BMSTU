#include "check_each.h"
#include <check.h>
#include <stdio.h>
#include "associative_array.h"
#include <stddef.h>

void func(const char *key, int *num, void *p)
{
    int *param = (int *)p;
    (*num) += *param;
    (void)key;
}
// Применение к каждому элементу, массив не пустой
START_TEST(test_each_full)
{
    assoc_array_t arr = assoc_array_create();

    assoc_array_insert(arr, "1", 1);
    assoc_array_insert(arr, "2", 2);
    assoc_array_insert(arr, "3", 3);
    assoc_array_insert(arr, "4", 4);

    int num = 5;
    int rc = assoc_array_each(arr, func, &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    int *find_n = NULL;

    assoc_array_find(arr, "1", &find_n);
    ck_assert_int_eq(6, *find_n);
    assoc_array_find(arr, "2", &find_n);
    ck_assert_int_eq(7, *find_n);
    assoc_array_find(arr, "3", &find_n);
    ck_assert_int_eq(8, *find_n);
    assoc_array_find(arr, "4", &find_n);
    ck_assert_int_eq(9, *find_n);

    assoc_array_destroy(&arr);
} END_TEST

// Применение к каждому элементу, массив пустой
START_TEST(test_each_empty)
{
    assoc_array_t arr = assoc_array_create();

    int *num = NULL;
    int rc = assoc_array_each(arr, func, &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    assoc_array_destroy(&arr);

} END_TEST

// Пустая функция
START_TEST(test_each_empty_func)
{
    assoc_array_t arr = assoc_array_create();

    assoc_array_insert(arr, "1", 1);

    int num = 5;
    int rc = assoc_array_each(arr, NULL, &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&arr);
} END_TEST

Suite *each_suite(void)
{
    Suite *s;
    TCase *tc_core;
    s = suite_create("each suite");
    tc_core = tcase_create("core");

    tcase_add_test(tc_core, test_each_full);
    tcase_add_test(tc_core, test_each_empty);
    tcase_add_test(tc_core, test_each_empty_func);

    suite_add_tcase(s, tc_core);

    return s;
}

