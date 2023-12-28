/// Модуль для работы с матрицой
#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stdio.h>
#include <stdbool.h>
#include "constants.h"
#include "errors.h"

#define N 10

/// @brief Получение максимального значения строки
/// @param mat Строка матрицы [in]
/// @param mat_columns_num Количество столбцов [in]
/// @return Максимальный элмент строки
int get_max_line_value(const int *mat, size_t mat_columns_num);

/// @brief Сортировка строк матрицы по убыванию наибольших элементов строк
/// @param mat Матрица [in, out]
/// @param mat_lines_num Количество строк [in]
/// @param mat_columns_num Количество столбцов [in]
void sort_matrix(int mat[][M], size_t mat_lines_num, size_t mat_columns_num);

/// @brief перемена строк матрицы местами
/// @param[in, out] line_1 Строка 1 матрицы
/// @param[in, out] line_2 Строка 2 матрицы
/// @param[in] columns_num Количество столбцов
void replace_lines(int *line_1, int *line_2, size_t columns_num);

/// @brief Перемена элементов местами
/// @param e_1 Адрес первого элемента [in, out]
/// @param e_2 Адрес второго элемента [in, out]
void replace_elements(int *e_1, int *e_2);
#endif
