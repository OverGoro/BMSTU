#include "check_pop_front.h"

// Удаление из списка с несколькими элементами
START_TEST(test_pop_front_several)
{
    node_t *head = NULL;
    node_t *head_ans = NULL;
    int p = 0, p_ans = 0;
    for (size_t i = 0; i < 4; i++)
    {
        node_t *n = node_create(i);
        head = list_add_tail(head, n);
        if (i != 0)
        {
            node_t *n_1 = node_create(i);
            head_ans = list_add_tail(head_ans, n_1);
        }
    }
    p_ans = head->data;
    p = pop_front(&head);
    int rc = cmp_list(head, head_ans);
    list_free(&head);
    list_free(&head_ans);
    ck_assert_int_eq(rc, 0);
    ck_assert_int_eq(p, p_ans);

} END_TEST

// Удаление из списка с одним элементом
START_TEST(test_pop_front_one)
{
    node_t *head = NULL;
    node_t *head_ans = NULL;
    int p = 0, p_ans = 0;
    for (size_t i = 0; i < 1; i++)
    {
        node_t *n = node_create(i);
        head = list_add_tail(head, n);
        if (i != 0)
        {
            node_t *n_1 = node_create(i);
            head_ans = list_add_tail(head_ans, n_1);
        }
    }
    p_ans = head->data;
    p = pop_front(&head);
    int rc = cmp_list(head, head_ans);
    list_free(&head);
    list_free(&head_ans);
    ck_assert_int_eq(rc, 0);
    ck_assert_int_eq(p, p_ans);

} END_TEST

Suite *pop_front_suite(void)
{
    Suite *s;
    TCase *tc_core;
    s = suite_create("list pop front");
    tc_core = tcase_create("core");

    tcase_add_test(tc_core, test_pop_front_several);
    tcase_add_test(tc_core, test_pop_front_one);

    suite_add_tcase(s, tc_core);

    return s;
}

