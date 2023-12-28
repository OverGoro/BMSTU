/// Модуль для работы с матрицой
#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stdio.h>
#include <stdbool.h>
#include "constants.h"
#include "errors.h"

/// @brief Проверка к-ой строки матрицы на симмеричность
/// @param[in] mat_line Cтрока матрицы
/// @param[in] columns_num Количество столбцов
/// @return Симметричность
bool check_matrix_line(const int *mat_line, size_t mat_columns_num);

/// @brief Получение списка симметричных строк
/// @param[in] mat Матрица
/// @param[in] k Число К
/// @param[out] arr Массив симметричности строк
void get_array(const int mat[][M], size_t mat_lines_num, size_t mat_columns_num, int arr[]);
#endif
