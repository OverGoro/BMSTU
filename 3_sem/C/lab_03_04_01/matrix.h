/// Модуль для работы с матрицой
#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stdio.h>
#include <stdbool.h>
#include "constants.h"
#include "errors.h"

#define N 10
/// @brief Упорядочивание строк матрицы по убыванию наибольших элементов строк
/// @param mat Матрица [in, out]
/// @param mat_size Количество строк и столбцов[in]
void sort_matrix(int mat[][M], size_t mat_size);

/// @brief перемена местами элементов 2 массивов с start_i по end_i
/// @param line_1 1-й массив [in, out]
/// @param line_2 2-й массив [in, out]
/// @param start_i начальный индекс [in]
/// @param end_i конечный индекс [in]
void replace_array_elements(int *line_1, int *line_2, size_t start_i, size_t end_i);

/// @brief Перемена элементов местами
/// @param e_1 Адрес первого элемента [in, out]
/// @param e_2 Адрес второго элемента [in, out]
void replace_elements(int *e_1, int *e_2);
#endif
