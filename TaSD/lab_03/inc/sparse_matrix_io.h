#ifndef SPARSE_MATRIX_IO_H__
#define SPARSE_MATRIX_IO_H__

#include <stddef.h>
#include <stdio.h>
#include "sparse_matrix.h"
#include "matrix_io.h"
#include "matrix_operations.h"
#include "error.h"
#include "prompt.h"

/**
* @brief Координатный ввод разреженной матрицы
*
* @param f_in[in, out] Файловый поток для чтения данных
* @param f_out[in, out] Файловый поток для вывода приглашений ввода
* @param matrix[out] Матрица
* @param prompt[in] Функция для вывода приглашений ввода
*
* @return Код ошибки
*/
int sm_coord_input(FILE *f_in, FILE *f_out, sparse_t *matrix, prompt_t prompt);

/**
* @brief Ввод разреженной матрицы в обычном виде
*
* @param f_in[in, out] Файловый поток для чтения данных
* @param f_out[in, out] Файловый поток для вывода приглашений ввода
* @param matrix[out] Матрица
* @param prompt[in] Функция для вывода приглашений ввода
*
* @return Код ошибки
*/
int sm_normal_input(FILE *f_in, FILE *f_out, sparse_t *matrix, prompt_t prompt);

/**
* @brief Вывод параметров разреженной матрицы
*
* @param f[in] Файловый поток 
* @param matrix[out] Матрица
*
* @return Код ошибки
*/
void sm_print(FILE *f, sparse_t *matrix);

/**
* @brief Вывод разреженной матрицы ввиде обычной матрицы
*
* @param f[in] Файловый поток 
* @param matrix[out] Матрица
*
* @return Код ошибки
*/
int sm_normal_print(FILE *f, sparse_t *matrix);

#endif // !SPARSE_MATRIX_IO_H__
