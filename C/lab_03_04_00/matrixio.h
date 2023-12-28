#ifndef __MATRIXIO_H__
#define __MATRIXIO_H__
#include "constants.h"
#include "errors.h"
#include <stdio.h>

/// @brief Ввод матрицы
/// @param mat Матрица
/// @param[out] lines_num Количество строк
/// @param[out] columns_num Количество столбцов
/// @return Код ошибки
int input_matrix(int mat[][M], size_t *mat_lines_num, size_t *mat_columns_num);
#endif
