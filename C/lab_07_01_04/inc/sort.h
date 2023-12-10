#ifndef SORT_H__
#define SORT_H__

#include <malloc.h>
#include <stddef.h>
#include <string.h>

#include "error.h"

typedef int (*cmp_t)(const void *l, const void *r);


/**
* @brief Сравнивает 2 целых числа типа int
*
* @param l[in] Указательна левое число
* @param r[in] Указатель на правое чило
*
* @return 
* Число > 0 - Левое число больше правого
* 0 - Левое число = правому
* Число < 1 - Левое число меньше правого
*/
int cmp_int(const void *l, const void *r);


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
void mysort(void *pdata, size_t n, size_t e_size, cmp_t cmp);

/**
* @brief Вычисление среднего значения целочисленного массива
*
* @param pbeg[in] Указатель на начало массива
* @param pend[in] Указатель на конец массива
*
* @return Среднее значение
*/
double get_average(const int *pbeg, const int *pend);

/**
* @brief Определение количества элементов в целочисленном массиве, 
* значение которых > val
*
* @param pbeg[in] Начало массива
* @param pend[in] Конец массива
* @param val[in] Значение для сравнения
*
* @return Количество найденных элементов
*/
size_t count_greater(const int *pbeg, const int *pend, double val);

/**
* @brief Заполняет массив элементами исходного, значение которых > val
*
* @param pb_src[in] Начало исходного массива
* @param pe_src[in] Конец исхднего массива
* @param pb_dst[out] Начало новго массива
* @param pe_dst[out] Конец нового массива
* @param val[in] Значение для сравнения
*
* @return Код ошибки 
*/
int fill_greater(const int *pb_src, const int *pe_src, int *pb_dst, double val);

/**
* @brief Фильтр элементов массива и запись их в новый массив.
*
* В массиве остаются элементы, которые больше среднего арифметического
* всех элементов массива.
*
* @param pb_src Указатель на начало исходного массива
* @param pe_src Указатель на конец исходного массива
* @param pb_dst Указатель на начало нового массива
* @param pe_dst Указатель на конец нового массива
*
* @return код ошибки
*/
int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);


#endif

