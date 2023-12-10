#ifndef SPARSE_MATRIX_GENERATOR_H__
#define SPARSE_MATRIX_GENERATOR_H__
#include "sparse_matrix.h"
#include <stdlib.h>
#include "vec.h"
/**
* @brief Генерация матрицы с случайными элементами с зданным процентом заполнения
*
* @param mat[out] Матрица
* @param m[in] Кол-во столбцов
* @param n[in] Кол-во строк
* @param fill_percent[in] Процент заполнения
*
* @return Код ошибки
*/
int matrix_generate(int ***mat, sparse_t *mat_sparse, size_t m, size_t n, size_t fill_percent);

int vector_generate(int ***mat, vector_t *vec, size_t m, size_t fill_percent);

#endif // !SPARSE_MATRIX_GENERATOR_H__
