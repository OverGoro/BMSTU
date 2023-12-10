#ifndef SPARSE_MATRIX_H__
#define SPARSE_MATRIX_H__
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

#include "matrix.h"
#include "matrix_io.h"
#include "error.h"

// Разреженная матрицы
typedef struct
{
    size_t n; // Количество строк
    size_t m; // Количество столбцов
    size_t el_num; // Количество ненулевых элементов
    int *values; // Значения ненулевых элементов
    size_t *rows; // Строки ненулевых элементов
    ssize_t *column_coords; // Индексы начала столбцов в values
} sparse_t;

/**
* @brief Выделение памяти под содержимое параметров разреженной матрицы
*
* @param matrix Матрица
* @param n Количество строк
* @param m Количество столбцов
* @param el_nem Количество ненулевых элементов
*
* @return Код ошибки
*/
int sm_init_content(sparse_t *matrix, size_t n, size_t m, size_t el_nem);

/**
* @brief Освобождает память, выделенную под поля разреженной матрицы
*
* @param matrix Разреженная матрица
*/
void sm_free_content(sparse_t *matrix);

/**
* @brief Конвертирует нормальную матрицу в разреженную
*
* @param spare_matrix[out] Разреженная матрица
* @param normal_matrix[in] Нормальная матрица
* @param n[in] Количество строк в матрице
* @param m[in] Количество столбцов в матрице
*
* @return Код ошибки
*/
int sm_convert_from_normal(sparse_t *spare_matrix, int **normal_matrix, size_t n, size_t m);

/**
* @brief Конвертирует разреженную матрицу в нормальную
*
* @param spare_matrix[in] Разреженная матрица
* @param normal_matrix[out] Нормальная матрица
* @param n[out] Количество строк в матрице
* @param m[out] Количество столбцов в матрице
*
* @return Код ошибки
*/
int sm_convert_to_normal(sparse_t *sparse_matrix, int ***normal_matrix, size_t *n, size_t *m);

/**
* @brief Получает координаты ненулевого элмента разреженной матрицы
*
* @param matrix[in] Разреженная матрица
* @param n_el[out] Строка элемента
* @param m_el[out] Столбец элемента
* @param i[in] Номер элемента
*/
void sm_get_el_coords(const sparse_t *matrix, size_t *n_el, size_t *m_el, size_t i);

/**
* @brief Получает значение ненулевого элемента по заданным координатам, 
* если элемент не найден - возвращаяет ошибку
*
* @param matrix[in] Разреженная матрица
* @param n_el[in] Строк элемента
* @param m_el[in] Стобец элемента
* @param val_el[out] Значение элемента
*
* @return Код ошибки
*/
int sm_get_el_by_coords(const sparse_t *matrix, size_t n_el, size_t m_el, int *val_el);

/**
* @brief Добавляет ненулевой элемент в конец
*
* @param matrix[in, out] Разреженная матрица
* @param n_el[in] Строка элемента
* @param val_el[in] Значение элемента
*
* @return Код ошибки
*/
int sm_push_element(sparse_t *matrix, size_t n_el, int val_el);

#endif // !SPARSE_MATRIX_H__
