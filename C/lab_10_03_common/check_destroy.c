#include "check_destroy.h"
#include <check.h>

// Уничтожение не пустого массива
START_TEST(test_destroy_full)
{
    assoc_array_t arr = assoc_array_create();

    assoc_array_insert(arr, "1", 1);
    assoc_array_insert(arr, "2", 2);
    assoc_array_insert(arr, "3", 3);
    assoc_array_insert(arr, "4", 4);

    assoc_array_destroy(&arr);
    ck_assert_ptr_null(arr);
} END_TEST

// Уничтожение пустого массива
START_TEST(test_destroy_empty)
{
    assoc_array_t arr = assoc_array_create();

    assoc_array_destroy(&arr);
    ck_assert_ptr_null(arr);
} END_TEST

Suite *destroy_suite(void)
{
    Suite *s;
    TCase *tc_core;
    s = suite_create("destroy suite");
    tc_core = tcase_create("core");

    tcase_add_test(tc_core, test_destroy_empty);
    tcase_add_test(tc_core, test_destroy_full);

    suite_add_tcase(s, tc_core);

    return s;
}
