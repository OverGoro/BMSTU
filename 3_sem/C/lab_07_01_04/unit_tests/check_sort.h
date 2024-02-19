#ifndef CHECK_SORT_H__
#define CHECK_SORT_H__
#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include "check_cmp.h"
#include "sort.h"

// Дополнительные компораторы
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
int cmp_float(const void *l, const void *r);

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
int cmp_double(const void *l, const void *r);

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
int cmp_str(const void *l, const void *r);

Suite *sort_suite(void);

#endif

