/// Модуль для работы с матрицой
#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stddef.h>
#include <stdbool.h>
#include "constants.h"
#include "errors.h"

/// @brief Поиск минимального элемеента под главной диагональю квадратной матрицы
/// @param[in] mat Матрица
/// @param[in] mat_size Размер матрицы
/// @param[out] min_el имальный элемент
/// @return Код ошибки
int find_min_element(int mat[][M], size_t mat_size, int *min_el);
#endif
