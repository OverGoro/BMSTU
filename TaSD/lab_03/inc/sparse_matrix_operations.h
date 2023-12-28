#ifndef SPARSE_MATRIX_OPERATIONS_H__
#define SPARSE_MATRIX_OPERATIONS_H__

#include <stdbool.h>
#include "vec.h"
#include "sparse_matrix.h"
#include "matrix_operations.h"
#include "error.h"

/**
* @brief Произведение вектора на разреженную матрицу
*
* @param vec_1[in] Вектор 1
* @param mat_2[in] Матрица 2
* @param vec_r[out] Вектор результат произведения
*
* @return Код ошибки
*/
int sm_multiply(vector_t *vec_1, const sparse_t *mat_2, vector_t *vec_r);

/**
* @brief Произведение вектора на разреженную матрицу в нормальном виде
*
* @param vec_1[in] Вектор 1
* @param mat_2[in] Матрица 2
* @param vec_r[out] Вектор результат произведения
*
* @return Код ошибки
*/
int sm_mult_normal(vector_t *vec, sparse_t *mat, vector_t *vec_r);
#endif // !SPARSE_MATRIX_OPERATIONS_H__
