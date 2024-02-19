#include "array.h"
#include <stdbool.h>
#include <math.h>
/**
* @brief Циклический сдвиг массива на 1 позицию
*
* @param arr[in, out] Массив
* @param n[in] Количество элементов в массиве
*/
static void array_shift_one(int *arr, size_t n)
{
    if (n == 0)
        return;
    int last = arr[n - 1];
    for (size_t i = n - 1; i > 0; i--)
    {
        arr[i] = arr[i - 1];
    }
    arr[0] = last;
}

void array_cycle_shift(int *arr, size_t n, size_t k)
{
    for (size_t i = 0; i < k; i++)
        array_shift_one(arr, n);
}

/**
* @brief Проверка, является ли число полным квадратом
*
* @param n[in] Число
*
* @return true/false
*/
static bool is_full_sqr(int n)
{
    int i;
    for (i = 0; i * i < n; i++);
    if (i * i == n)
        return true;
    return false;
}

int array_form_sqr(const int *arr, size_t n, int *arr_sqr, size_t *n_sqr)
{
    size_t tmp_n = 0;
    for (size_t i = 0; i < n; i++)
    {
        if (is_full_sqr(arr[i]))
        {
            tmp_n++;
        }
    }
    if (tmp_n > *n_sqr)
    {
        *n_sqr = tmp_n;
        return FORM_MODE_COUNT;
    }
    
    tmp_n = 0;
    for (size_t i = 0; i < n; i++)
    {
        if (is_full_sqr(arr[i]))
        {
            arr_sqr[tmp_n] = arr[i];
            tmp_n++;
        }
    }
    *n_sqr = tmp_n;
    return FORM_MODE_CREATE;
}

