#include "check_min.h"
#include "associative_array.h"
#include <check.h>

// Минимальный элемент, массив не пустой
START_TEST(test_min_full)
{
    assoc_array_t arr = assoc_array_create();

    assoc_array_insert(arr, "1", 1);
    assoc_array_insert(arr, "2", 2);
    assoc_array_insert(arr, "3", 3);
    assoc_array_insert(arr, "4", 4);

    int *find_num;
    int rc = assoc_array_min(arr, &find_num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(1, *find_num);
    assoc_array_destroy(&arr);
} END_TEST

// Минимальный элемент, массив пустой
START_TEST(test_min_empty)
{
    assoc_array_t arr = assoc_array_create();

    int *num;
    int rc = assoc_array_min(arr, &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);
    assoc_array_destroy(&arr);
} END_TEST

Suite *min_suite(void)
{
    Suite *s;
    TCase *tc_core;
    s = suite_create("min suite");
    tc_core = tcase_create("core");

    tcase_add_test(tc_core, test_min_full);
    tcase_add_test(tc_core, test_min_empty);

    suite_add_tcase(s, tc_core);

    return s;
}
