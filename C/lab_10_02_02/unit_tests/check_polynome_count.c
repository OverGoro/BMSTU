#include "check_polynome_count.h"

// Вычисление значения не пустого полинома
START_TEST(test_polynome_count_several)
{
    node_t *polynome = NULL;
    for (size_t i = 1; i < 5; i++)
    {
        node_t *n = node_create(i);
        polynome = list_add_tail(polynome, n);
    }
    int res = 0;
    int x = 2;
    int rc = polynome_count(polynome, x, &res);
    list_free(&polynome);
    ck_assert_int_eq(rc, 0);
    ck_assert_int_eq(res, 4 + 3 * 2 + 2 * 4 + 1 * 8);

} END_TEST

// Вычисление значения полинома с одним элементов
START_TEST(test_polynome_count_one)
{
    node_t *polynome = NULL;
    for (size_t i = 1; i < 2; i++)
    {
        node_t *n = node_create(i);
        polynome = list_add_tail(polynome, n);
    }
    int x = 163;
    int res = 0;
    int rc = polynome_count(polynome, x, &res);
    list_free(&polynome);
    ck_assert_int_eq(rc, 0);
    ck_assert_int_eq(res, 1);

} END_TEST

// Вычисление значения пустого полинома
START_TEST(test_polynome_count_empty)
{
    node_t *polynome = NULL;
    for (size_t i = 1; i < 1; i++)
    {
        node_t *n = node_create(i);
        polynome = list_add_tail(polynome, n);
    }
    int x = 163;
    int res = 0;
    int rc = polynome_count(polynome, x, &res);
    list_free(&polynome);
    ck_assert_int_eq(rc, ERR_EMPTY_ARR);
    ck_assert_int_eq(res, 0);

} END_TEST
Suite *polynome_count_suite(void)
{
    Suite *s;
    TCase *tc_core;
    s = suite_create("list pop back");
    tc_core = tcase_create("core");

    tcase_add_test(tc_core, test_polynome_count_several);
    tcase_add_test(tc_core, test_polynome_count_one);
    tcase_add_test(tc_core, test_polynome_count_empty);

    suite_add_tcase(s, tc_core);

    return s;
}

