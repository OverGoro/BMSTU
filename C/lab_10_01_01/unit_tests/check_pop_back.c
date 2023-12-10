#include "check_pop_back.h"

// Удаление из списка с несколькими элементами
START_TEST(test_pop_back_several)
{
    node_t *head = NULL;
    node_t *head_ans = NULL;
    void *p = NULL, *p_ans = NULL;
    for (size_t i = 0; i < 4; i++)
    {
        node_t *n = node_create((void *)i);
        head = list_add_tail(head, n);
        if (i != 3)
        {
            node_t *n_1 = node_create((void *)i);
            head_ans = list_add_tail(head_ans, n_1);
        }
    }
    p_ans = (void *)3;
    p = pop_back(&head);
    int rc = cmp_list(head, head_ans);
    list_free(&head);
    list_free(&head_ans);
    ck_assert_int_eq(rc, 0);
    ck_assert_ptr_eq(p, p_ans);

} END_TEST

// Удаление из списка с одним элементом
START_TEST(test_pop_back_one)
{
    node_t *head = NULL;
    node_t *head_ans = NULL;
    void *p = NULL, *p_ans = NULL;
    for (size_t i = 0; i < 1; i++)
    {
        node_t *n = node_create((void *)i);
        head = list_add_tail(head, n);
        if (i != 0)
        {
            node_t *n_1 = node_create((void *)i);
            head_ans = list_add_tail(head_ans, n_1);
        }
    }
    p_ans = head->data;
    p = pop_back(&head);
    int rc = cmp_list(head, head_ans);
    list_free(&head);
    list_free(&head_ans);
    ck_assert_int_eq(rc, 0);
    ck_assert_ptr_eq(p, p_ans);

} END_TEST

// Удаление из пустого списка
START_TEST(test_pop_back_empty)
{
    node_t *head = NULL;
    node_t *head_ans = NULL;
    void *p = NULL, *p_ans = NULL;
    for (size_t i = 0; i < 1; i++)
    {
        node_t *n = node_create((void *)i);
        head = list_add_tail(head, n);
        if (i != 0)
        {
            node_t *n_1 = node_create((void *)i);
            head_ans = list_add_tail(head_ans, n_1);
        }
    }
    p_ans = head->data;
    p = pop_back(&head);
    int rc = cmp_list(head, head_ans);
    list_free(&head);
    list_free(&head_ans);
    ck_assert_int_eq(rc, 0);
    ck_assert_ptr_eq(p, p_ans);

} END_TEST
Suite *pop_back_suite(void)
{
    Suite *s;
    TCase *tc_core;
    s = suite_create("list pop back");
    tc_core = tcase_create("core");

    tcase_add_test(tc_core, test_pop_back_several);
    tcase_add_test(tc_core, test_pop_back_one);
    tcase_add_test(tc_core, test_pop_back_empty);

    suite_add_tcase(s, tc_core);

    return s;
}

