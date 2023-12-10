#include "check_create.h"
#include <check.h>

// Создание массива
START_TEST(test_create)
{
    assoc_array_t arr = assoc_array_create();

    ck_assert_ptr_nonnull(arr);

    assoc_array_destroy(&arr);
    ck_assert_ptr_null(arr);
} END_TEST


Suite *create_suite(void)
{
    Suite *s;
    TCase *tc_core;
    s = suite_create("create suite");
    tc_core = tcase_create("core");

    tcase_add_test(tc_core, test_create);

    suite_add_tcase(s, tc_core);

    return s;
}
