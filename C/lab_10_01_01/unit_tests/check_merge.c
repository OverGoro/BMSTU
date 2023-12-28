#include "check_merge.h"
#include "check_cmp.h"

// Слияние 2 списков, каждый элемент второго больше элемента первого
START_TEST(test_merge_greater)
{
    node_t arr_1[3] = { {(void *)1, NULL}, 
                    {(void *)2, NULL}, 
                    {(void *)3, NULL} };
    node_t arr_2[3] = { {(void *)5, NULL}, 
                    {(void *)10, NULL}, 
                    {(void *)14, NULL} };
    node_t arr_ans[6] = { {(void *)1, NULL}, 
                    {(void *)2, NULL}, 
                    {(void *)3, NULL},
                    {(void *)5, NULL}, 
                    {(void *)10, NULL}, 
                    {(void *)14, NULL} };   
    for (size_t i = 0; i < 2; i++)
    {
        arr_1[i].next = &arr_1[i + 1];
        arr_2[i].next = &arr_2[i + 1];
    }
    for (size_t i = 0; i < 5; i++)
        arr_ans[i].next = &arr_ans[i + 1];

    node_t *head_1 = &arr_1[0];
    node_t *head_2 = &arr_2[0];
    node_t *head_ans = &arr_ans[0];
    
    node_t *head = sorted_merge(&head_1, &head_2, cmp_addr);

    int rc = cmp_list(head, head_ans);

    ck_assert_int_eq(rc, 0);
    ck_assert_ptr_null(head_1);
    ck_assert_ptr_null(head_2);

} END_TEST


// Слияние 2 списков, каждый элемент второго меньше элемента первого
START_TEST(test_merge_lower)
{
    node_t arr_2[3] = { {(void *)1, NULL}, 
                    {(void *)2, NULL}, 
                    {(void *)3, NULL} };
    node_t arr_1[3] = { {(void *)5, NULL}, 
                    {(void *)10, NULL}, 
                    {(void *)14, NULL} };
    node_t arr_ans[6] = { {(void *)1, NULL}, 
                    {(void *)2, NULL}, 
                    {(void *)3, NULL},
                    {(void *)5, NULL}, 
                    {(void *)10, NULL}, 
                    {(void *)14, NULL} };   
    for (size_t i = 0; i < 2; i++)
    {
        arr_1[i].next = &arr_1[i + 1];
        arr_2[i].next = &arr_2[i + 1];
    }
    for (size_t i = 0; i < 5; i++)
        arr_ans[i].next = &arr_ans[i + 1];

    node_t *head_1 = &arr_1[0];
    node_t *head_2 = &arr_2[0];
    node_t *head_ans = &arr_ans[0];
    
    node_t *head = sorted_merge(&head_1, &head_2, cmp_addr);

    int rc = cmp_list(head, head_ans);

    ck_assert_int_eq(rc, 0);
    ck_assert_ptr_null(head_1);
    ck_assert_ptr_null(head_2);

} END_TEST


// Слияние 2 списков
START_TEST(test_merge)
{
    node_t arr_1[3] = { {(void *)1, NULL}, 
                    {(void *)4, NULL}, 
                    {(void *)5, NULL} };
    node_t arr_2[3] = { {(void *)2, NULL}, 
                    {(void *)3, NULL}, 
                    {(void *)6, NULL} };
    node_t arr_ans[6] = { {(void *)1, NULL}, 
                    {(void *)2, NULL}, 
                    {(void *)3, NULL},
                    {(void *)4, NULL}, 
                    {(void *)5, NULL}, 
                    {(void *)6, NULL} };   
    for (size_t i = 0; i < 2; i++)
    {
        arr_1[i].next = &arr_1[i + 1];
        arr_2[i].next = &arr_2[i + 1];
    }
    for (size_t i = 0; i < 5; i++)
        arr_ans[i].next = &arr_ans[i + 1];

    node_t *head_1 = &arr_1[0];
    node_t *head_2 = &arr_2[0];
    node_t *head_ans = &arr_ans[0];
    
    node_t *head = sorted_merge(&head_1, &head_2, cmp_addr);

    int rc = cmp_list(head, head_ans);

    ck_assert_int_eq(rc, 0);
    ck_assert_ptr_null(head_1);
    ck_assert_ptr_null(head_2);
} END_TEST

// Слияние пустого и не пустого
START_TEST(test_merge_empty_1)
{
    node_t *arr_1 = NULL;
    node_t arr_2[3] = { {(void *)2, NULL}, 
                    {(void *)3, NULL}, 
                    {(void *)6, NULL} };
    node_t arr_ans[3] = { {(void *)2, NULL}, 
                    {(void *)3, NULL},
                    {(void *)6, NULL} };   
    for (size_t i = 0; i < 2; i++)
    {
        arr_2[i].next = &arr_2[i + 1];
        arr_ans[i].next = &arr_ans[i + 1];
    }

    node_t *head_1 = arr_1;
    node_t *head_2 = &arr_2[0];
    node_t *head_ans = &arr_ans[0];
    
    node_t *head = sorted_merge(&head_1, &head_2, cmp_addr);

    int rc = cmp_list(head, head_ans);

    ck_assert_int_eq(rc, 0);
    ck_assert_ptr_null(head_1);
    ck_assert_ptr_null(head_2);
} END_TEST

// Слияние не пустого и пустого
START_TEST(test_merge_empty_2)
{
    node_t *arr_2 = NULL;
    node_t arr_1[3] = { {(void *)2, NULL}, 
                    {(void *)3, NULL}, 
                    {(void *)6, NULL} };
    node_t arr_ans[3] = { {(void *)2, NULL}, 
                    {(void *)3, NULL},
                    {(void *)6, NULL} };   
    for (size_t i = 0; i < 2; i++)
    {
        arr_1[i].next = &arr_1[i + 1];
        arr_ans[i].next = &arr_ans[i + 1];
    }

    node_t *head_2 = arr_2;
    node_t *head_1 = &arr_1[0];
    node_t *head_ans = &arr_ans[0];
    
    node_t *head = sorted_merge(&head_1, &head_2, cmp_addr);

    int rc = cmp_list(head, head_ans);

    ck_assert_int_eq(rc, 0);
    ck_assert_ptr_null(head_1);
    ck_assert_ptr_null(head_2);
} END_TEST

// Слияние 2 пустых
START_TEST(test_merge_empty_all)
{
    node_t *arr_1 = NULL;
    node_t *arr_2 = NULL;
    node_t *arr_ans = NULL;

    node_t *head_1 = arr_1;
    node_t *head_2 = arr_2;
    node_t *head_ans = arr_ans;
    
    node_t *head = sorted_merge(&head_1, &head_2, cmp_addr);

    int rc = cmp_list(head, head_ans);

    ck_assert_int_eq(rc, 0);
    ck_assert_ptr_null(head_1);
    ck_assert_ptr_null(head_2);
} END_TEST

Suite *merge_suite(void)
{
    Suite *s;
    TCase *tc_core;
    s = suite_create("merge");
    tc_core = tcase_create("core");

    tcase_add_test(tc_core, test_merge_lower);
    tcase_add_test(tc_core, test_merge_greater);
    tcase_add_test(tc_core, test_merge);
    tcase_add_test(tc_core, test_merge_empty_1);
    tcase_add_test(tc_core, test_merge_empty_2);
    tcase_add_test(tc_core, test_merge_empty_all);

    suite_add_tcase(s, tc_core);

    return s;
}


