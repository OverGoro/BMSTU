#include "check_sort.h"
#include "check_cmp.h"

// Список в обратном порядке
START_TEST(test_sort_backward)
{
    node_t *head = NULL;
    node_t *head_ans = NULL;
    for (size_t i = 0; i < 8; i++)
    {
        node_t *n = node_create((void *)(7 - i));
        head = list_add_tail(head, n);
        
        node_t *n_1 = node_create((void *)i);
        head_ans = list_add_tail(head_ans, n_1);
    }
    head = sort(head, cmp_addr);

    int rc = cmp_list(head, head_ans);
    list_free(&head);
    list_free(&head_ans);

    ck_assert_int_eq(rc, 0);

} END_TEST

// Список в порядке возрастания
START_TEST(test_sort_forward)
{
    node_t *head = NULL;
    node_t *head_ans = NULL;
    for (size_t i = 0; i < 8; i++)
    {
        node_t *n = node_create((void *)(i));
        head = list_add_tail(head, n);
        
        node_t *n_1 = node_create((void *)i);
        head_ans = list_add_tail(head_ans, n_1);
    }
    head = sort(head, cmp_addr);

    int rc = cmp_list(head, head_ans);
    list_free(&head);
    list_free(&head_ans);

    ck_assert_int_eq(rc, 0);

} END_TEST
// Список из 1 элемента
START_TEST(test_sort_one)
{
    node_t *head = NULL;
    node_t *head_ans = NULL;
    for (size_t i = 0; i < 1; i++)
    {
        node_t *n = node_create((void *)(i));
        head = list_add_tail(head, n);
        
        node_t *n_1 = node_create((void *)i);
        head_ans = list_add_tail(head_ans, n_1);
    }
    head = sort(head, cmp_addr);

    int rc = cmp_list(head, head_ans);
    list_free(&head);
    list_free(&head_ans);

    ck_assert_int_eq(rc, 0);

} END_TEST

// Список из случайных элементов
START_TEST(test_sort_random)
{
    node_t arr[5] = { {(void *)15, NULL}, 
                    {(void *)10, NULL}, 
                    {(void *)92, NULL}, 
                    {(void *)14, NULL}, 
                    {(void *)5, NULL} };
    node_t arr_ans[5] = { {(void *)5, NULL}, 
                    {(void *)10, NULL}, 
                    {(void *)14, NULL}, 
                    {(void *)15, NULL}, 
                    {(void *)92, NULL} };
    for (size_t i = 0; i < 4; i++)
    {
        arr[i].next = &arr[i + 1];
        arr_ans[i].next = &arr[i + 1];
    }

    node_t *head = &arr[0];
    node_t *head_ans = &arr_ans[0];

    head = sort(head, cmp_addr);

    int rc = cmp_list(head, head_ans);

    ck_assert_int_eq(rc, 0);

} END_TEST

Suite *sort_suite(void)
{
    Suite *s;
    TCase *tc_core;
    s = suite_create("sort");
    tc_core = tcase_create("core");

    tcase_add_test(tc_core, test_sort_backward);
    tcase_add_test(tc_core, test_sort_forward);
    tcase_add_test(tc_core, test_sort_one);
    tcase_add_test(tc_core, test_sort_random);

    suite_add_tcase(s, tc_core);

    return s;
}


