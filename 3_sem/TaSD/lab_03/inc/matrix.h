#ifndef MATRIX_H__
#define MATRIX_H__
#include <stddef.h>
#include <stdlib.h>

/**
* @brief Выделение памяти под матрицу
*
* @param n[in] Количество строк
* @param m[in] Количестов столбцов
*
* @return Указатель на матрицу.
* В случае неуспеха - NULL
*/
int **matrix_allocate(size_t n, size_t m);


/**
* @brief Освобождение матрицы
*
* @param ptrs[in] Матрица
*/
void matrix_free(int **ptrs);

#endif

