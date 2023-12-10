#include "check_max.h"
#include "associative_array.h"
#include <check.h>

// Максимальный элемент, массив не пустой
START_TEST(test_max_full)
{
    assoc_array_t arr = assoc_array_create();

    assoc_array_insert(arr, "1", 1);
    assoc_array_insert(arr, "2", 2);
    assoc_array_insert(arr, "3", 3);
    assoc_array_insert(arr, "4", 4);

    int *find_num;
    int rc = assoc_array_max(arr, &find_num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(4, *find_num);
    assoc_array_destroy(&arr);
} END_TEST

// Максимальный элемент, массив пустой
START_TEST(test_max_empty)
{
    assoc_array_t arr = assoc_array_create();

    int *num;
    int rc = assoc_array_max(arr, &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);
    assoc_array_destroy(&arr);
} END_TEST

Suite *max_suite(void)
{
    Suite *s;
    TCase *tc_core;
    s = suite_create("max suite");
    tc_core = tcase_create("core");

    tcase_add_test(tc_core, test_max_full);
    tcase_add_test(tc_core, test_max_empty);

    suite_add_tcase(s, tc_core);

    return s;
}
