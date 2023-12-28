#include "check_find.h"
#include <check.h>

// Поиск элемента, массив не пустой
START_TEST(test_find_full)
{
    assoc_array_t arr = assoc_array_create();

    assoc_array_insert(arr, "1", 1);
    assoc_array_insert(arr, "2", 2);
    assoc_array_insert(arr, "3", 3);
    assoc_array_insert(arr, "4", 4);

    int rc = assoc_array_insert(arr, "5", 5);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    int *find_n = NULL;

    assoc_array_find(arr, "1", &find_n);
    ck_assert_int_eq(1, *find_n);
    assoc_array_find(arr, "2", &find_n);
    ck_assert_int_eq(2, *find_n);
    assoc_array_find(arr, "3", &find_n);
    ck_assert_int_eq(3, *find_n);
    assoc_array_find(arr, "4", &find_n);
    ck_assert_int_eq(4, *find_n);
    assoc_array_find(arr, "5", &find_n);
    ck_assert_int_eq(5, *find_n);
    assoc_array_destroy(&arr);

} END_TEST

// Поиск элемента массив пустой
START_TEST(test_find_empty)
{
    assoc_array_t arr = assoc_array_create();

    int *num = NULL;
    int rc = assoc_array_find(arr, "1", &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);
    assoc_array_destroy(&arr);

} END_TEST

// Поиск элемента элемента не существует
START_TEST(test_find_not_exist)
{
    assoc_array_t arr = assoc_array_create();

    assoc_array_insert(arr, "1", 1);


    int *find_n = NULL;

    int rc = assoc_array_find(arr, "1", &find_n);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(1, *find_n);

    rc = assoc_array_find(arr, "2", &find_n);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);
   
    assoc_array_destroy(&arr);
} END_TEST
Suite *find_suite(void)
{
    Suite *s;
    TCase *tc_core;
    s = suite_create("find suite");
    tc_core = tcase_create("core");

    tcase_add_test(tc_core, test_find_full);
    tcase_add_test(tc_core, test_find_empty);
    tcase_add_test(tc_core, test_find_not_exist);

    suite_add_tcase(s, tc_core);

    return s;
}

