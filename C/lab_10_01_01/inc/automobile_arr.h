#ifndef AUTOMOBILE_ARR_H__ 
#define AUTOMOBILE_ARR_H__

#include <stdlib.h>
#include <stddef.h>
#include "automobile.h"

/**
* @brief Подсчет количества структур в файле
*
* @param f[in, out] Файловый поток
* @param n[out] Количество автомобилей
*
* @return Код ошибки
*/
int a_arr_count(FILE *f, size_t *n);

/**
* @brief Чтение массива автомобилей из файлового потока
*
* @param f[in, out] Файловый поток
* @param a_arr[out] Массив автомобилей
* @param n[out] Количество элементов в массиве
*
* @return Код ошибки
*/
int a_arr_read(FILE *f, automobile_t **a_arr, size_t *n);

/**
* @brief Освобождение памяти под массив автомобилей
*
* @param a_arr[in, out] Массив
* @param n[in, out] Количество элементов в массиве
*/
void a_arr_free(automobile_t **a_arr, size_t *n);

#endif // !AUTOMOBILE_ARR_H__ 

