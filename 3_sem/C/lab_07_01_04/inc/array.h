#ifndef ARRAY_H__
#define ARRAY_H__

#include <stdio.h>
#include <malloc.h>

#include "error.h"
#include "sort.h"

/**
* @brief Подсчет количества элементов в файле, являющихся
* целыми числами
*
* @param f[in, out] файл
* @param pn[out] Количество элементов
*
* @return Код ошибки
*/
size_t arr_cnt_file(FILE *f, size_t *pn);

/**
* @brief Считывает данные в массив из файла
*
* @param f[in, out] Файловый поток
* @param pbeg[out] Указатель на начало массива
* @param pend[out] Указтель на конец массива
*
* @return 
*/
int arr_read(FILE *f, int *pbeg, int *pend);

/**
* @brief Создание целочисленного массива из файла.
*
* @param f[in, out] Файловый поток
* @param pbeg[out] Указатель на начало массива
* @param pn[out] Указатель на конец массива
*
* @return Код ошибки
*/
int arr_create(FILE *f, int **pbeg, int **pend);

/**
* @brief Выводит массив в файловый поток
*
* @param f[in ,out] Файловый поток
* @param pbeg[in] Указатель на начало массива
* @param pend[in] Указатель на конец массива
*
* @return Код ошибки
*/
int arr_print(FILE *f, const int *pbeg, const int *pend);

#endif
