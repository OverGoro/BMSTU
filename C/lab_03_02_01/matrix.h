/// Модуль для работы с матрицой
#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stdio.h>
#include <stdbool.h>
#include "constants.h"
#include "errors.h"

/// @brief Удаление строки из матрицы
/// @param mat Матрица [in, out]
/// @param mat_lines_num Количество строк в матрице [in, out]
/// @param mat_columns_num Количество столбцов в маьтице [in]
/// @param line_num Номер строки для удаление [in]
void delete_line(int mat[][M], size_t *mat_lines_num, size_t mat_columns_num, size_t line_num);

/// @brief Удаление столбца из матрицы
/// @param mat Матрица [in, out]
/// @param mat_lines_num Количество строк в матрице [out]
/// @param mat_columns_num Количество столбцов в маьтице [in, out]
/// @param line_num Номер столбца для удаление [in]
void delete_column(int mat[][M], size_t mat_lines_num, size_t *mat_columns_num, size_t column_num);

/// @brief Получить сумму цифр числа
/// @param num Число [in]
/// @return Сумма цифр числа
int get_digit_summ(int num);

/// @brief Получение индекса элемента матрицы с минимальной суммой цифр
/// @param mat Матрица [in]
/// @param mat_lines_num Количсетво строк в матрице [in]
/// @param mat_lines_num Количсетво столбцов в матрице [in]
/// @param min_i Строка искомого элемента [out]
/// @param min_j Столбец искомого элемента [out]
void get_min_digit_summ_index(const int mat[][M], size_t mat_lines_num, size_t mat_columns_num, size_t *min_i, size_t *min_j);
#endif
