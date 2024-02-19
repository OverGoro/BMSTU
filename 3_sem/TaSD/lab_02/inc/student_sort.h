#ifndef STUDENT_SORT_H__
#define STUDENT_SORT_H__
#include <stdlib.h>
#include <stddef.h>
#include "student.h"

/**
* @brief Меняет местами элементы произвольного массива.
*
* @param l[in, out] Указатель на первый элемент
* @param r[in, out] Указатаель на второй элемент
* @param e_size[in] Размер элемента
*/
void swap(void *l, void *r, size_t e_size);

/**
* @brief Сортировка произвольного массива.
*
* Метод сортировки: модифицированная сортировка пузырьком.
*
* @param pdata[in, out] Массив 
* @param n[in] Количество элементов в массиве
* @param e_size[in] Размер элемента
* @param cmp[in] Компоратор
*/
void sa_bubble_sort(void *pdata, size_t n, size_t e_size, cmp_t cmp);

/**
 * @brief Сортировка произвольного массива методом quicksort.
 *
 * @param pdata[in, out] Массив
 * @param n[in] Количество элементов в массиве
 * @param e_size[in] Размер элемента
 * @param cmp[in] Компаратор
 */
void sa_quicksort(void *pdata, size_t n, size_t e_size, cmp_t cmp);

#endif

