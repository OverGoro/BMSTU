#include "check_remove.h"

// Удаление 1 элемента из середины
START_TEST(check_remove_full)
{
    assoc_array_t arr = assoc_array_create();

    assoc_array_insert(arr, "1", 1);
    assoc_array_insert(arr, "2", 2);
    assoc_array_insert(arr, "3", 3);
    assoc_array_insert(arr, "4", 4);

    int rc = assoc_array_remove(arr, "1");
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_remove(arr, "2");
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_remove(arr, "3");
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_remove(arr, "4");
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    int *find_n = NULL;

    rc = assoc_array_find(arr, "1", &find_n);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);
    rc = assoc_array_find(arr, "2", &find_n);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);
    rc = assoc_array_find(arr, "3", &find_n);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);
    rc = assoc_array_find(arr, "4", &find_n);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&arr);
} END_TEST
// Удаление 1 элемента из середины
START_TEST(check_remove_middle)
{
    assoc_array_t arr = assoc_array_create();

    assoc_array_insert(arr, "1", 1);
    assoc_array_insert(arr, "2", 2);
    assoc_array_insert(arr, "3", 3);
    assoc_array_insert(arr, "4", 4);

    int rc = assoc_array_remove(arr, "3");
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    int *find_n = NULL;

    rc = assoc_array_find(arr, "1", &find_n);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(1, *find_n);
    rc = assoc_array_find(arr, "2", &find_n);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(2, *find_n);
    rc = assoc_array_find(arr, "3", &find_n);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);
    rc = assoc_array_find(arr, "4", &find_n);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(4, *find_n);

    assoc_array_destroy(&arr);
} END_TEST

// Удаление 1 элемента из начала
START_TEST(check_remove_begin)
{
    assoc_array_t arr = assoc_array_create();

    assoc_array_insert(arr, "1", 1);
    assoc_array_insert(arr, "2", 2);
    assoc_array_insert(arr, "3", 3);
    assoc_array_insert(arr, "4", 4);

    int rc = assoc_array_remove(arr, "1");
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    int *find_n = NULL;

    rc = assoc_array_find(arr, "1", &find_n);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);

    rc = assoc_array_find(arr, "2", &find_n);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(2, *find_n);
    rc = assoc_array_find(arr, "3", &find_n);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(3, *find_n);
    rc = assoc_array_find(arr, "4", &find_n);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(4, *find_n);

    assoc_array_destroy(&arr);

} END_TEST

// Удаление 1 элемента из конца
START_TEST(check_remove_end)
{
    assoc_array_t arr = assoc_array_create();

    assoc_array_insert(arr, "1", 1);
    assoc_array_insert(arr, "2", 2);
    assoc_array_insert(arr, "3", 3);
    assoc_array_insert(arr, "4", 4);

    int rc = assoc_array_remove(arr, "4");
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    int *find_n = NULL;

    rc = assoc_array_find(arr, "4", &find_n);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);

    rc = assoc_array_find(arr, "1", &find_n);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(1, *find_n);
    rc = assoc_array_find(arr, "2", &find_n);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(2, *find_n);
    rc = assoc_array_find(arr, "3", &find_n);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(3, *find_n);

    assoc_array_destroy(&arr);
} END_TEST

// Удаление из массива с 1 элементом
START_TEST(check_remove_one)
{
    assoc_array_t arr = assoc_array_create();

    assoc_array_insert(arr, "1", 1);

    int rc = assoc_array_remove(arr, "1");
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    int *find_n = NULL;

    rc = assoc_array_find(arr, "q", &find_n);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&arr);
} END_TEST


// Удаление из путсого массива
START_TEST(check_remove_empty)
{
    assoc_array_t arr = assoc_array_create();

    int rc = assoc_array_remove(arr, "1");
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&arr);
} END_TEST

Suite *remove_suite(void)
{
    Suite *s;
    TCase *tc_core;
    s = suite_create("remove suite");
    tc_core = tcase_create("core");

    tcase_add_test(tc_core, check_remove_begin);
    tcase_add_test(tc_core, check_remove_middle);
    tcase_add_test(tc_core, check_remove_end);
    tcase_add_test(tc_core, check_remove_one);
    tcase_add_test(tc_core, check_remove_empty);
    tcase_add_test(tc_core, check_remove_full);

    suite_add_tcase(s, tc_core);

    return s;
}
