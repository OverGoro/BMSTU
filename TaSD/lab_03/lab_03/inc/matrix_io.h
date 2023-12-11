#ifndef MATRIX_IO_H__
#define MATRIX_IO_H__

#include "matrix.h"
#include "error.h"
#include "prompt.h"
#include <stdio.h>

/**
* @brief Ввод матрицы, записанной в координатном формате из файлового потока
*
* @param f_in[in, out] Файловый поток для чтения данных
* @param f_out[in, out] Файловый поток для вывода приглашений ввода
* @param ptrs[out] Указатель на матрицу
* @param n[out] Количество строк
* @param m[out] Количество столбцов
* @param el_num[out] Количество ненулевых элементов 
* @param prompt[in] Функция для вывода приглашений ввода
*
* @return Код ошибки
*/
int matrix_coord_input(FILE *f_in, FILE*f_out, int ***ptrs, size_t *n, size_t *m, size_t *el_num, prompt_t prompt);

/**
* @brief Ввод односрочной матрицы, записанной в координатном формате из файлового потока
*
* @param f_in[in, out] Файловый поток для чтения данных
* @param f_out[in, out] Файловый поток для вывода приглашений ввода
* @param ptrs[out] Указатель на матрицу
* @param n[out] Количество строк
* @param m[out] Количество столбцов
* @param el_num[out] Количество ненулевых элементов 
* @param prompt[in] Функция для вывода приглашений ввода
*
* @return Код ошибки
*/
int matrix_vec_coord_input(FILE *f_in, FILE*f_out, int ***ptrs, size_t *n, size_t *m, size_t *el_num, prompt_t prompt);

/**
* @brief Подсчет ненулевых элементов матрицы
*
* @param ptrs[in] Матрица 
* @param n[in] Количество строк
* @param m[in] Количество столбцов
*
* @return Количество ненулевых элементов
*/
size_t matrix_count_no_zero(int **ptrs, size_t n, size_t m);

/**
* @brief Вывод матрицы в нормальном виде
*
* @param f[in, out] Файловый поток
* @param ptrs[in] Матрица
* @param n[in] Количество строк
* @param m[in] Количество столбцов
*
* @return Код ошибки
*/
int matrix_normal_print(FILE *f, int **ptrs, size_t n, size_t m);

#endif

