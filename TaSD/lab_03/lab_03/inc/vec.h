#ifndef VEC_H___
#define VEC_H___

#include "matrix_io.h"
#include "error.h"

#include <stddef.h>
#include <stdlib.h>

// Вектор
typedef struct
{
    int *values; // Значения ненулевых элементов
    size_t *columns; // Стоблцы ненулевых элементов
    size_t m; // Количество  столбцов
    size_t el_num; // Количество ненулевых элементов
} vector_t;

/**
* @brief Выделяет память под поля вектора
*
* @param vector[in, out] Вектор
* @param m[in] Количество столбцов
* @param el_num[in] Количество ненулевых элементов
*
* @return Код ошибки
*/
int v_init_content(vector_t *vector, size_t m, size_t el_num);

/**
* @brief Обнуляет вектор
*
* @param vector[in. out] Вектор
*/
void v_free_content(vector_t *vector);

/**
* @brief Конвертирует обычную матрицу в вектор
*
* @param vector[out] Вектор
* @param mat[in] Матрица
* @param n[in] Количество строк в матрице
* @param m[in] Количество столбцов в матрице
*/
int v_convert_from_matrix(vector_t *vector, int **mat, size_t n, size_t m);

int v_convert_to_matrix(vector_t *vector, int ***mat, size_t *n, size_t *m);

/**
* @brief Добавляет ненулевой элмент в вектор
*
* @param vector_t[in, out] Вектор
* @param m[in] столбец элемента
* @param value[in] Знаечние элемента
*
* @return Код ошибки
*/
int v_push(vector_t *vector_t, size_t m, int value);

#endif

