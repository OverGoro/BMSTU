/// Модуль для работы с матрицой
#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stdio.h>
#include <stdbool.h>
#include "constants.h"
#include "errors.h"

/// @brief Заполняет квадратную матрицу по спирали по часовой стрелке
/// @param mat Матрица [in, out]
/// @param mat_lines_num Количество строк [in]
/// @param mat_colums_num Количество столбцов [in]
void fill_matrix(int mat[][M], size_t mat_lines_num, size_t mat_colums_num);
#endif
