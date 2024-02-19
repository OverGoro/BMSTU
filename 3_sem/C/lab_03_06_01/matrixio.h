#ifndef __MATRIXIO_H__
#define __MATRIXIO_H__
#include <stdio.h>
#include "constants.h"
#include "errors.h"

/// @brief Ввод размеров матрицы
/// @param lines_num Количество строк [out]
/// @param columns_num Количество столбцов [out]
/// @return Код ошибки
int input_matrix_size(size_t *mat_lines_num, size_t *mat_columns_num);

/// @brief Вывод матрицы
/// @param[in] mat Матрица
/// @param[in] mat_lines_num Количество строк в матрице
/// @param[in] mat_columns_num Количество столбцов в матрице
void print_matrix(const int mat[][M], size_t mat_lines_num, size_t mat_columns_num);
#endif
