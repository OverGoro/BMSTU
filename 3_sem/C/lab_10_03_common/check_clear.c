#include "check_clear.h"
#include <check.h>

// Очистка не пустого массива
START_TEST(test_clear_full)
{
    assoc_array_t arr = assoc_array_create();

    assoc_array_insert(arr, "1", 1);
    assoc_array_insert(arr, "2", 2);
    assoc_array_insert(arr, "3", 3);
    assoc_array_insert(arr, "4", 4);

    assoc_array_clear(arr);
    int *find_n = NULL;

    int rc = assoc_array_find(arr, "1", &find_n);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);
    rc = assoc_array_find(arr, "2", &find_n);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);
    rc = assoc_array_find(arr, "3", &find_n);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);
    rc = assoc_array_find(arr, "4", &find_n);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);
 
    assoc_array_destroy(&arr);
} END_TEST

// Очистка массива с 1 элементом 
START_TEST(test_clear_one)
{
    assoc_array_t arr = assoc_array_create();

    assoc_array_insert(arr, "1", 1);

    assoc_array_clear(arr);
    int *find_n = NULL;

    int rc = assoc_array_find(arr, "1", &find_n);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);
 
    assoc_array_destroy(&arr);
} END_TEST

// Очистка пустого массива
START_TEST(test_clear_empty)
{
    assoc_array_t arr = assoc_array_create();

    assoc_array_clear(arr);

    assoc_array_destroy(&arr);
} END_TEST

Suite *clear_suite(void)
{
    Suite *s;
    TCase *tc_core;
    s = suite_create("clear suite");
    tc_core = tcase_create("core");

    tcase_add_test(tc_core, test_clear_empty);
    tcase_add_test(tc_core, test_clear_one);
    tcase_add_test(tc_core, test_clear_full);

    suite_add_tcase(s, tc_core);

    return s;
}
