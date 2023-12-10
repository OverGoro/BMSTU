#ifndef MATRIX_OPERATIONS_H__
#define MATRIX_OPERATIONS_H__

#include <stddef.h>
#include <math.h>

#include "matrix.h"
#include "error.h"

#define EPSILON 0.00001 // Точность сравнения элементов

// Элементарные преобразования матриц
/**
* @brief Перемена столбцов местами
*
* @param ptrs[out] Матрица
* @param n[in] Количество строк
* @param m_1[in] Столбец 1
* @param m_1[in] Столбец 2
*/
void matrix_swap_column(int **ptrs, size_t n, size_t m_1, size_t m_2);

/**
* @brief Перестановка строк местами
*
* @param ptrs[out] Матрица
* @param n_1[in] Строка 1
* @param n_2[in] Строка 2
*/
void matrix_swap_row(int **ptrs, size_t n_1, size_t n_2);

/**
* @brief Умножение элементов строки на k
*
* @param ptrs[out] Матрица
* @param n[in] Строка
* @param m[in] Количество столбцов
* @param k[in] Коэффициент
*/
void matrix_multiply_row(int **ptrs, size_t n, size_t m, int k);

/**
* @brief Сумма 2 строк
*
* @param ptrs[out] Матрица
* @param n_dst[in] Строка, куда записывается сложение
* @param n_src[in] Строка, с которой складывается n_dst
* @param m[in] Количество столбцов во всей матрице
*/
void matrix_summ_row(int **ptrs, size_t n_dst, size_t n_src, size_t m);


// Преобразования матрицы

/**
* @brief Приводит область матрицы от 0 до n_t строки  и от 0 до m_t столбца
* к верхне треугольному вилу с помощью элементарных преобразований
*
* @param ptrs[in, out] Матрица
* @param n_t[in] Граница области по строкам
* @param m_t[in] Граница области по столбцам
* @param m[in] Количество столбцов во всей матрице
*/
void matrix_up_triangle(int **ptrs, size_t n_t, size_t m_t, size_t m);

/**
* @brief Приводит область матрицы от 0 до n_t строки  и от 0 до m_t столбца
* к нижне треугольному вилу с помощью элементарных преобразований
*
* @param ptrs[in, out] Матрица
* @param n_t[in] Граница области по строкам
* @param m_t[in] Граница области по столбцам
* @param m[in] Количество столбцов
*/
void matrix_bottom_triangle(int **ptrs, size_t n_t, size_t m_t, size_t m);

/**
* @brief Умножение матриц
*
* @param mat_1[in] Матрица 1
* @param n_1[in] Количество строк матрицы 1
* @param m_1[in] Количество столбцов матрицы 1
* @param mat_2[in] Матрица 2
* @param n_2[in] Количество строк матрицы 2
* @param m_2[in] Количество столбцов матрицы 2
* @param mat_res[in] Результат умножения
* @param n_res[in] Количество строк результата
* @param m_res[in] Количество столбцов результата
*
* @return Код ошибки
*/
int matrix_multiply(int **mat_1, size_t n_1, size_t m_1,
int **mat_2, size_t n_2, size_t m_2,
int ***mat_res, size_t *n_res, size_t *m_res);

/**
* @brief Сложение матриц
*
* @param mat_1[in] Матрица 1
* @param n_1[in] Количество строк матрицы 1
* @param m_1[in] Количество столбцов матрицы 1
* @param mat_2[in] Матрица 2
* @param n_2[in] Количество строк матрицы 2
* @param m_2[in] Количество столбцов матрицы 2
* @param mat_res[in] Результат сложения
* @param n_res[in] Количество строк результата
* @param m_res[in] Количество столбцов результата
*
* @return Код ошибки
*/
int matrix_summ(int **mat_1, size_t n_1, size_t m_1,
int **mat_2, size_t n_2, size_t m_2,
int ***mat_res, size_t *n_res, size_t *m_res);

#endif // !MATRIX_OPERATIONS_H__

