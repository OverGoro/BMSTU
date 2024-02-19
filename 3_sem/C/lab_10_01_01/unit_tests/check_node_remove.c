#include "check_node_remove.h"
#include "check_cmp.h"
#include <check.h>
#include <stdio.h>

// Удаление из начала
START_TEST(test_remove_begin)
{
    node_t *head = NULL;
    node_t *head_ans = NULL;
    node_t *d_node = NULL;
    for (size_t i = 0; i < 4; i++)
    {
        node_t *n = node_create((void *)i);
        head = list_add_tail(head, n);
        if (i != 0)
        {
            node_t *n_1 = node_create((void *)i);
            head_ans = list_add_tail(head_ans, n_1);
        }
        else 
        {
            d_node = n;
        }
    }
    remove_node(&head, d_node);
    int rc = cmp_list(head, head_ans);
    list_free(&head);
    list_free(&head_ans);
    ck_assert_int_eq(rc, 0);

} END_TEST

// Удаление из середины
START_TEST(test_remove_middle)
{
    node_t *head = NULL;
    node_t *head_ans = NULL;
    node_t *d_node = NULL;
    for (size_t i = 0; i < 4; i++)
    {
        node_t *n = node_create((void *)i);
        head = list_add_tail(head, n);
        if (i != 2)
        {
            node_t *n_1 = node_create((void *)i);
            head_ans = list_add_tail(head_ans, n_1);
        }
        else 
        {
            d_node = n;
        }
    }
    remove_node(&head, d_node);
    int rc = cmp_list(head, head_ans);
    list_free(&head);
    list_free(&head_ans);
    ck_assert_int_eq(rc, 0);

} END_TEST

// Удаление из середины
START_TEST(test_remove_end)
{
    node_t *head = NULL;
    node_t *head_ans = NULL;
    node_t *d_node = NULL;
    for (size_t i = 0; i < 4; i++)
    {
        node_t *n = node_create((void *)i);
        head = list_add_tail(head, n);
        if (i != 3)
        {
            node_t *n_1 = node_create((void *)i);
            head_ans = list_add_tail(head_ans, n_1);
        }
        else 
        {
            d_node = n;
        }
    }
    remove_node(&head, d_node);
    int rc = cmp_list(head, head_ans);
    list_free(&head);
    list_free(&head_ans);
    ck_assert_int_eq(rc, 0);

} END_TEST

Suite *node_remove_suite(void)
{
    Suite *s;
    TCase *tc_core;
    s = suite_create("node remve");
    tc_core = tcase_create("core");

    tcase_add_test(tc_core, test_remove_begin);
    tcase_add_test(tc_core, test_remove_middle);
    tcase_add_test(tc_core, test_remove_end);

    suite_add_tcase(s, tc_core);

    return s;
}

