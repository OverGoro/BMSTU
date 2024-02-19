#include "check_remove_duplicates.h"
#include "check_cmp.h"
#include <check.h>
#include <stdio.h>

// Четное число элементоа
START_TEST(test_split_odd)
{
    node_t *head_l = NULL, *head_r = NULL;
    node_t *head_ans_l = NULL, *head_ans_r = NULL;
    for (size_t i = 0; i < 8; i++)
    {
        node_t *n = node_create((void *)i);
        head_l = list_add_tail(head_l, n);
        
        node_t *n_1 = node_create((void *)i);
        if (i < 4)
            head_ans_l = list_add_tail(head_ans_l, n_1);
        else
            head_ans_r = list_add_tail(head_ans_r, n_1);
    }
    front_back_split(head_l, &head_r);

    int rc_l = cmp_list(head_l, head_ans_l);
    int rc_r = cmp_list(head_r, head_ans_r);
    list_free(&head_l);
    list_free(&head_r);
    list_free(&head_ans_l);
    list_free(&head_ans_r);

    ck_assert_int_eq(rc_l, 0);
    ck_assert_int_eq(rc_r, 0);

} END_TEST
// Нечетное число элементоа
START_TEST(test_split)
{
    node_t *head_l = NULL, *head_r = NULL;
    node_t *head_ans_l = NULL, *head_ans_r = NULL;
    for (size_t i = 0; i < 9; i++)
    {
        node_t *n = node_create((void *)i);
        head_l = list_add_tail(head_l, n);
        
        node_t *n_1 = node_create((void *)i);
        if (i < 5)
            head_ans_l = list_add_tail(head_ans_l, n_1);
        else
            head_ans_r = list_add_tail(head_ans_r, n_1);
    }
    front_back_split(head_l, &head_r);

    int rc_l = cmp_list(head_l, head_ans_l);
    int rc_r = cmp_list(head_r, head_ans_r);
    list_free(&head_l);
    list_free(&head_r);
    list_free(&head_ans_l);
    list_free(&head_ans_r);

    ck_assert_int_eq(rc_l, 0);
    ck_assert_int_eq(rc_r, 0);

} END_TEST
Suite *split_suite(void)
{
    Suite *s;
    TCase *tc_core;
    s = suite_create("split");
    tc_core = tcase_create("core");

    tcase_add_test(tc_core, test_split_odd);
    tcase_add_test(tc_core, test_split);

    suite_add_tcase(s, tc_core);

    return s;
}

