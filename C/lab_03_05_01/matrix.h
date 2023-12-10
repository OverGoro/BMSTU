/// Модуль для работы с матрицой
#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "constants.h"
#include "errors.h"

/// @brief Получает массив элементов, сумма цифр которых больше 10
/// @param mat Матрица [in]
/// @param size_t mat_lines_num Количестов строк [in]
/// @param mat_columns_num Количество столбцов [in]
/// @param arr Массив элементов [out]
/// @return Код ошибки
void get_elements(const int mat[][M], size_t mat_lines_num, size_t mat_columns_num, int *arr, size_t *arr_size);

/// @brief Получает сумму цифр числа
/// @param num Число [in]
/// @return Сумма цифр числа
int get_digit_sum(int num);


/// @brief Циклический сдвиг массива влево
/// @param arr Массив [in, out]
/// @param arr_size Размер массива [in]
void cyclic_move(int *arr, size_t arr_size);

/// @brief Циклический сдвиг массива влево на k позиций
/// @param arr Массив [in, out]
/// @param arr_size Размер массива[in, out]
/// @param k Количество позиций
void move_array(int *arr, size_t arr_size, size_t k);


/// @brief Устанавливает на место элементов, сумма цифр которых больше 10 значения из arr
/// @param mat Матрица [in, out]
/// @param size_t mat_lines_num Количестов строк [in]
/// @param mat_columns_num Количество столбцов [in]
/// @param arr Массив элементов [in]
/// @param arr_size Размер массива элементов [in]
void modify_matrix(int mat[][M], size_t mat_lines_num, size_t mat_columns_num, int *arr);
#endif
