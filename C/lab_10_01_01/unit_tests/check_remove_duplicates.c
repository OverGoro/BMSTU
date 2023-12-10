#include "check_remove_duplicates.h"
#include "check_cmp.h"
#include <check.h>
#include <stdio.h>

// Дубликаты есть
START_TEST(test_remove_duplicates_yes)
{
    node_t *head = NULL;
    node_t *head_ans = NULL;
    for (size_t i = 0; i < 4; i++)
    {
        node_t *n = node_create((void *)i);
        head = list_add_tail(head, n);
        n = node_create((void *)i);
        head = list_add_tail(head, n);

        node_t *n_1 = node_create((void *)i);
        head_ans = list_add_tail(head_ans, n_1);
    }
    remove_duplicates(&head, cmp_addr);
    int rc = cmp_list(head, head_ans);
    list_free(&head);
    list_free(&head_ans);
    ck_assert_int_eq(rc, 0);

} END_TEST

// Дубликатов нет
START_TEST(test_remove_duplicates_no)
{
    node_t *head = NULL;
    node_t *head_ans = NULL;
    for (size_t i = 0; i < 4; i++)
    {
        node_t *n = node_create((void *)i);
        head = list_add_tail(head, n);
        
        node_t *n_1 = node_create((void *)i);
        head_ans = list_add_tail(head_ans, n_1);
    }
    remove_duplicates(&head, cmp_addr);
    int rc = cmp_list(head, head_ans);
    list_free(&head);
    list_free(&head_ans);
    ck_assert_int_eq(rc, 0);

} END_TEST

Suite *remove_duplicates_suite(void)
{
    Suite *s;
    TCase *tc_core;
    s = suite_create("remove duplicates");
    tc_core = tcase_create("core");

    tcase_add_test(tc_core, test_remove_duplicates_yes);
    tcase_add_test(tc_core, test_remove_duplicates_no);

    suite_add_tcase(s, tc_core);

    return s;
}

