#include "check_sort.h"
#include "check_cmp.h"
#include "sort.h"


int cmp_float(const void *l, const void *r)
{
    float lf = *(float*)l;
    float rf = *(float*)r;
    if (lf > rf)
        return 1;
    else if (lf == rf)
        return 0;
    else
        return -1;
}

int cmp_double(const void *l, const void *r)
{
    double lf = *(double*)l;
    double rf = *(double*)r;
    if (lf > rf)
        return 1;
    else if (lf == rf)
        return 0;
    else
        return -1;
}

int cmp_str(const void *l, const void *r)
{
    return strcmp((char *)l, (char *)r);
}

// Массив строк
// Случайный массив
START_TEST(test_mysort_str_random)
{   
    char ta[][8] = {"abcdef", "bagsh", "aaa", "cde", "bfg"}; // Входной массив
    char ta_ans[][8] = {"aaa", "abcdef", "bagsh", "bfg", "cde"}; // Выходной массив

    size_t n_ans = sizeof(ta_ans) / sizeof(ta_ans[0]); // Количество элементов в ожидаемом массиве
    size_t n_arr = sizeof(ta) / sizeof(ta[0]); // Количество элементов в полученном массиве

    mysort(&ta, n_arr, sizeof(ta[0]), cmp_str);
    cmp_arr_str(ta, n_arr, ta_ans, n_ans);
} END_TEST

// Отсортированный в порядке возрастания массив
START_TEST(test_mysort_str_sorted)
{   
    char ta[][8] = {"aaa", "abcdef", "bagsh", "bfg", "cde"}; // Входной массив
    char ta_ans[][8] = {"aaa", "abcdef", "bagsh", "bfg", "cde"}; // Выходной массив

    size_t n_ans = sizeof(ta_ans) / sizeof(ta_ans[0]); // Количество элементов в ожидаемом массиве
    size_t n_arr = sizeof(ta) / sizeof(ta[0]); // Количество элементов в полученном массиве

    mysort(&ta, n_arr, sizeof(ta[0]), cmp_str);
    cmp_arr_str(ta, n_arr, ta_ans, n_ans);
} END_TEST


// Отсортированный в обратном порядке массив
START_TEST(test_mysort_str_reversed)
{   
    char ta[][8] = {"cde", "bfg", "bagsh", "abcdef", "aaa"}; // Входной массив
    char ta_ans[][8] = {"aaa", "abcdef", "bagsh", "bfg", "cde"}; // Выходной массив

    size_t n_ans = sizeof(ta_ans) / sizeof(ta_ans[0]); // Количество элементов в ожидаемом массиве
    size_t n_arr = sizeof(ta) / sizeof(ta[0]); // Количество элементов в полученном массиве

    mysort(&ta, n_arr, sizeof(ta[0]), cmp_str);
    cmp_arr_str(ta, n_arr, ta_ans, n_ans);
} END_TEST


// Массив из двух элементов
START_TEST(test_mysort_str_two)
{   
    char ta[][8] = {"cdfe", "cdef"}; // Входной массив
    char ta_ans[][8] = {"cdef", "cdfe"}; // Выходной массив

    size_t n_ans = sizeof(ta_ans) / sizeof(ta_ans[0]); // Количество элементов в ожидаемом массиве
    size_t n_arr = sizeof(ta) / sizeof(ta[0]); // Количество элементов в полученном массиве

    mysort(&ta, n_arr, sizeof(ta[0]), cmp_str);
    cmp_arr_str(ta, n_arr, ta_ans, n_ans);
} END_TEST

// Массив из одного элемента
START_TEST(test_mysort_str_one)
{   
    char ta[][8] = {"cdefgh"}; // Входной массив
    char ta_ans[][8] = {"cdefgh"}; // Выходной массив

    size_t n_ans = sizeof(ta_ans) / sizeof(ta_ans[0]); // Количество элементов в ожидаемом массиве
    size_t n_arr = sizeof(ta) / sizeof(ta[0]); // Количество элементов в полученном массиве

    mysort(&ta, n_arr, sizeof(ta[0]), cmp_str);
    cmp_arr_str(ta, n_arr, ta_ans, n_ans);
} END_TEST

// Массив из одинаковых элементов элемента
START_TEST(test_mysort_str_same)
{   
    char ta[][8] = {"cdefgh", "cdefgh", "cdefgh", "cdefgh", "cdefgh", "cdefgh"}; // Входной массив
    char ta_ans[][8] = {"cdefgh", "cdefgh", "cdefgh", "cdefgh", "cdefgh", "cdefgh"}; // Выходной массив

    size_t n_ans = sizeof(ta_ans) / sizeof(ta_ans[0]); // Количество элементов в ожидаемом массиве
    size_t n_arr = sizeof(ta) / sizeof(ta[0]); // Количество элементов в полученном массиве

    mysort(&ta, n_arr, sizeof(ta[0]), cmp_str);
    cmp_arr_str(ta, n_arr, ta_ans, n_ans);
} END_TEST




// Массив целых чисел
// Случайный массив
START_TEST(test_mysort_int_random)
{
    int ta[] = {999, -999, 111, 2, 3, 5, 1, 4}; // Входной массив
    int ta_ans[] = {-999, 1, 2, 3, 4, 5, 111, 999}; // Выходной массив

    int n_arr = sizeof(ta) / sizeof(ta[0]); // Количество элементов в полученном массиве
    int n_ans = sizeof(ta_ans) / sizeof(ta_ans[0]); // Количество элементов в ожидаемом массиве

    mysort(ta, n_arr, sizeof(int), cmp_int);
    cmp_arr_int(ta, n_arr, ta_ans, n_ans);
} END_TEST

// Отсортированный в обратном порядке массив
START_TEST(test_mysort_int_reversed)
{
    int ta[] = {999, 111, 5, 4, 3, 2, 1, -999}; // Входной массив
    int ta_ans[] = {-999, 1, 2, 3, 4, 5, 111, 999}; // Выходной массив

    int n_arr = sizeof(ta) / sizeof(ta[0]); // Количество элементов в полученном массиве
    int n_ans = sizeof(ta_ans) / sizeof(ta_ans[0]); // Количество элементов в ожидаемом массиве

    mysort(ta, n_arr, sizeof(int), cmp_int);
    cmp_arr_int(ta, n_arr, ta_ans, n_ans);
} END_TEST

// Отсортированный в порядке возрастания массив
START_TEST(test_mysort_int_sorted)
{
    int ta[] = {-999, 111, 1, 2, 3, 4, 5, 999}; // Входной массив
    int ta_ans[] = {-999, 1, 2, 3, 4, 5, 111, 999}; // Выходной массив

    int n_arr = sizeof(ta) / sizeof(ta[0]); // Количество элементов в полученном массиве
    int n_ans = sizeof(ta_ans) / sizeof(ta_ans[0]); // Количество элементов в ожидаемом массиве

    mysort(ta, n_arr, sizeof(int), cmp_int);
    cmp_arr_int(ta, n_arr, ta_ans, n_ans);
} END_TEST

// Массив из двух элементов
START_TEST(test_mysort_int_two)
{
    int ta[] = {2, 1}; // Входной массив
    int ta_ans[] = {1, 2}; // Выходной массив

    int n_arr = sizeof(ta) / sizeof(ta[0]); // Количество элементов в полученном массиве
    int n_ans = sizeof(ta_ans) / sizeof(ta_ans[0]); // Количество элементов в ожидаемом массиве

    mysort(ta, n_arr, sizeof(int), cmp_int);
    cmp_arr_int(ta, n_arr, ta_ans, n_ans);
} END_TEST

// Массив из одного элемента
START_TEST(test_mysort_int_one)
{
    int ta[] = {1}; // Входной массив
    int ta_ans[] = {1}; // Выходной массив

    int n_arr = sizeof(ta) / sizeof(ta[0]); // Количество элементов в полученном массиве
    int n_ans = sizeof(ta_ans) / sizeof(ta_ans[0]); // Количество элементов в ожидаемом массиве

    mysort(ta, n_arr, sizeof(int), cmp_int);
    cmp_arr_int(ta, n_arr, ta_ans, n_ans);
} END_TEST

// Массив из одинаковых элементов элемента
START_TEST(test_mysort_int_same)
{
    int ta[] = {2, 2, 2, 2}; // Входной массив
    int ta_ans[] = {2, 2, 2, 2}; // Выходной массив

    int n_arr = sizeof(ta) / sizeof(ta[0]); // Количество элементов в полученном массиве
    int n_ans = sizeof(ta_ans) / sizeof(ta_ans[0]); // Количество элементов в ожидаемом массиве

    mysort(ta, n_arr, sizeof(int), cmp_int);
    cmp_arr_int(ta, n_arr, ta_ans, n_ans);
} END_TEST



// Массив float
// Случайный массив
START_TEST(test_mysort_float_random)
{
    float ta[] = {999, -999, 111, 2, 3, 5, 1, 4}; // Входной массив
    float ta_ans[] = {-999, 1, 2, 3, 4, 5, 111, 999}; // Выходной массив

    int n_arr = sizeof(ta) / sizeof(ta[0]); // Количество элементов в полученном массиве
    int n_ans = sizeof(ta_ans) / sizeof(ta_ans[0]); // Количество элементов в ожидаемом массиве

    mysort(ta, n_arr, sizeof(float), cmp_float);
    cmp_arr_float(ta, n_arr, ta_ans, n_ans);
} END_TEST

// Отсортированный в обратном порядке массив
START_TEST(test_mysort_float_reversed)
{
    float ta[] = {999, 111, 5, 4, 3, 2, 1, -999}; // Входной массив
    float ta_ans[] = {-999, 1, 2, 3, 4, 5, 111, 999}; // Выходной массив

    int n_arr = sizeof(ta) / sizeof(ta[0]); // Количество элементов в полученном массиве
    int n_ans = sizeof(ta_ans) / sizeof(ta_ans[0]); // Количество элементов в ожидаемом массиве

    mysort(ta, n_arr, sizeof(float), cmp_float);
    cmp_arr_float(ta, n_arr, ta_ans, n_ans);
} END_TEST

// Отсортированный в порядке возрастания массив
START_TEST(test_mysort_float_sorted)
{
    float ta[] = {-999, 111, 1, 2, 3, 4, 5, 999}; // Входной массив
    float ta_ans[] = {-999, 1, 2, 3, 4, 5, 111, 999}; // Выходной массив

    int n_arr = sizeof(ta) / sizeof(ta[0]); // Количество элементов в полученном массиве
    int n_ans = sizeof(ta_ans) / sizeof(ta_ans[0]); // Количество элементов в ожидаемом массиве

    mysort(ta, n_arr, sizeof(float), cmp_float);
    cmp_arr_float(ta, n_arr, ta_ans, n_ans);
} END_TEST

// Массив из двух элементов
START_TEST(test_mysort_float_two)
{
    float ta[] = {2, 1}; // Входной массив
    float ta_ans[] = {1, 2}; // Выходной массив

    int n_arr = sizeof(ta) / sizeof(ta[0]); // Количество элементов в полученном массиве
    int n_ans = sizeof(ta_ans) / sizeof(ta_ans[0]); // Количество элементов в ожидаемом массиве

    mysort(ta, n_arr, sizeof(float), cmp_float);
    cmp_arr_float(ta, n_arr, ta_ans, n_ans);
} END_TEST

// Массив из одного элемента
START_TEST(test_mysort_float_one)
{
    float ta[] = {1}; // Входной массив
    float ta_ans[] = {1}; // Выходной массив

    int n_arr = sizeof(ta) / sizeof(ta[0]); // Количество элементов в полученном массиве
    int n_ans = sizeof(ta_ans) / sizeof(ta_ans[0]); // Количество элементов в ожидаемом массиве

    mysort(ta, n_arr, sizeof(float), cmp_float);
    cmp_arr_float(ta, n_arr, ta_ans, n_ans);
} END_TEST

// Массив из одинаковых элементов элемента
START_TEST(test_mysort_float_same)
{
    float ta[] = {2, 2, 2, 2}; // Входной массив
    float ta_ans[] = {2, 2, 2, 2}; // Выходной массив

    int n_arr = sizeof(ta) / sizeof(ta[0]); // Количество элементов в полученном массиве
    int n_ans = sizeof(ta_ans) / sizeof(ta_ans[0]); // Количество элементов в ожидаемом массиве

    mysort(ta, n_arr, sizeof(float), cmp_float);
    cmp_arr_float(ta, n_arr, ta_ans, n_ans);
} END_TEST




// Массив double
// Случайный массив
START_TEST(test_mysort_double_random)
{
    double ta[] = {999, -999, 111, 2, 3, 5, 1, 4}; // Входной массив
    double ta_ans[] = {-999, 1, 2, 3, 4, 5, 111, 999}; // Выходной массив

    int n_arr = sizeof(ta) / sizeof(ta[0]); // Количество элементов в полученном массиве
    int n_ans = sizeof(ta_ans) / sizeof(ta_ans[0]); // Количество элементов в ожидаемом массиве

    mysort(ta, n_arr, sizeof(double), cmp_double);
    cmp_arr_double(ta, n_arr, ta_ans, n_ans);
} END_TEST

// Отсортированный в обратном порядке массив
START_TEST(test_mysort_double_reversed)
{
    double ta[] = {999, 111, 5, 4, 3, 2, 1, -999}; // Входной массив
    double ta_ans[] = {-999, 1, 2, 3, 4, 5, 111, 999}; // Выходной массив

    int n_arr = sizeof(ta) / sizeof(ta[0]); // Количество элементов в полученном массиве
    int n_ans = sizeof(ta_ans) / sizeof(ta_ans[0]); // Количество элементов в ожидаемом массиве

    mysort(ta, n_arr, sizeof(double), cmp_double);
    cmp_arr_double(ta, n_arr, ta_ans, n_ans);
} END_TEST

// Отсортированный в порядке возрастания массив
START_TEST(test_mysort_double_sorted)
{
    double ta[] = {-999, 111, 1, 2, 3, 4, 5, 999}; // Входной массив
    double ta_ans[] = {-999, 1, 2, 3, 4, 5, 111, 999}; // Выходной массив

    int n_arr = sizeof(ta) / sizeof(ta[0]); // Количество элементов в полученном массиве
    int n_ans = sizeof(ta_ans) / sizeof(ta_ans[0]); // Количество элементов в ожидаемом массиве

    mysort(ta, n_arr, sizeof(double), cmp_double);
    cmp_arr_double(ta, n_arr, ta_ans, n_ans);
} END_TEST

// Массив из двух элементов
START_TEST(test_mysort_double_two)
{
    double ta[] = {2, 1}; // Входной массив
    double ta_ans[] = {1, 2}; // Выходной массив

    int n_arr = sizeof(ta) / sizeof(ta[0]); // Количество элементов в полученном массиве
    int n_ans = sizeof(ta_ans) / sizeof(ta_ans[0]); // Количество элементов в ожидаемом массиве

    mysort(ta, n_arr, sizeof(double), cmp_double);
    cmp_arr_double(ta, n_arr, ta_ans, n_ans);
} END_TEST

// Массив из одного элемента
START_TEST(test_mysort_double_one)
{
    double ta[] = {1}; // Входной массив
    double ta_ans[] = {1}; // Выходной массив

    int n_arr = sizeof(ta) / sizeof(ta[0]); // Количество элементов в полученном массиве
    int n_ans = sizeof(ta_ans) / sizeof(ta_ans[0]); // Количество элементов в ожидаемом массиве

    mysort(ta, n_arr, sizeof(double), cmp_double);
    cmp_arr_double(ta, n_arr, ta_ans, n_ans);
} END_TEST

// Массив из одинаковых элементов элемента
START_TEST(test_mysort_double_same)
{
    double ta[] = {2, 2, 2, 2}; // Входной массив
    double ta_ans[] = {2, 2, 2, 2}; // Выходной массив

    int n_arr = sizeof(ta) / sizeof(ta[0]); // Количество элементов в полученном массиве
    int n_ans = sizeof(ta_ans) / sizeof(ta_ans[0]); // Количество элементов в ожидаемом массиве

    mysort(ta, n_arr, sizeof(double), cmp_double);
    cmp_arr_double(ta, n_arr, ta_ans, n_ans);
} END_TEST

Suite *sort_suite(void)
{
    Suite *s;
    TCase *tc_core;
    s = suite_create("sort");
    tc_core = tcase_create("core");

    tcase_add_test(tc_core, test_mysort_str_random);
    tcase_add_test(tc_core, test_mysort_str_sorted);
    tcase_add_test(tc_core, test_mysort_str_reversed);
    tcase_add_test(tc_core, test_mysort_str_one);
    tcase_add_test(tc_core, test_mysort_str_two);
    tcase_add_test(tc_core, test_mysort_str_same);

    tcase_add_test(tc_core, test_mysort_int_random);
    tcase_add_test(tc_core, test_mysort_int_sorted);
    tcase_add_test(tc_core, test_mysort_int_reversed);
    tcase_add_test(tc_core, test_mysort_int_one);
    tcase_add_test(tc_core, test_mysort_int_two);
    tcase_add_test(tc_core, test_mysort_int_same);

    tcase_add_test(tc_core, test_mysort_float_random);
    tcase_add_test(tc_core, test_mysort_float_sorted);
    tcase_add_test(tc_core, test_mysort_float_reversed);
    tcase_add_test(tc_core, test_mysort_float_one);
    tcase_add_test(tc_core, test_mysort_float_two);
    tcase_add_test(tc_core, test_mysort_float_same);

    tcase_add_test(tc_core, test_mysort_double_random);
    tcase_add_test(tc_core, test_mysort_double_sorted);
    tcase_add_test(tc_core, test_mysort_double_reversed);
    tcase_add_test(tc_core, test_mysort_double_one);
    tcase_add_test(tc_core, test_mysort_double_two);
    tcase_add_test(tc_core, test_mysort_double_same);


    suite_add_tcase(s, tc_core);

    return s;
}

