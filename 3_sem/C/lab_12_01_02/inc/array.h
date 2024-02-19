#ifndef ARRAY_H__
#define ARRAY_H__

#include <stddef.h>

enum form_modes
{
    FORM_MODE_CREATE,
    FORM_MODE_COUNT
};

/**
* @brief Циклический сдвиг массива на k позиций
*
* @param arr[in, out] Массив
* @param n[in] Количество элементов в массиве
* @param k[in] Сдвиг
*/
void array_cycle_shift(int *arr, size_t n, size_t k);

/**
* @brief Формирует новый массив из полных квадратов другого массива
*
* @param arr[in] Исходный массив
* @param n[in] Колчиество элементов в первом массиве
* @param arr_sqr[out] Массив полных квадратов
* @param n_sqr[out] Количество элементов в массиве полных квадратов
*
* @param Код ошибки
*/
int array_form_sqr(const int *arr, size_t n, int *arr_sqr, size_t *n_sqr);

#endif // !ARRAY_H__
