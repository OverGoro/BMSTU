#ifndef MENU_H__
#define MENU_H__
#include "sparse_matrix.h"
#include "measure.h"
#include "vec.h"
#define MENU_TEXT "\
Разреженные матрицы\n\
1) Ввести разреженную матрицу\n\
2) Ввести вектор\n\
3) Вывести разреженную матрицу\n\
4) Вывести вектор\n\
5) Умножить вектор на разреженную матрицу\n\
6) Умножить вектор на разреженную матрицу в обычном виде\n\
7) Замерный эксперимент\n\
\n0) Выйти\n"

enum Commands 
{
    EXIT,
    INPUT_MAT,
    INPUT_VEC,
    PRINT_MAT,
    PRINT_VEC,
    MULT,
    MULT_NORM,
    MEASURE
};

/**
* @brief Обработка кода ошибки
*
* @param err[in] Код ошибки
*/
void handle_err(int err);

/**
* @brief Выводит список команд
*/
void menu_commands_print(void);

/**
* @brief Ввод разреженной матрицы
*
* @param mat[out] Матрица в обычном виде
* @param sparse_mat[out] Разреженная матрица
*
* @return Код ошибки
*/
int menu_input_matrix(int ***mat, sparse_t *sparse_mat);

/**
* @brief Ввод вектора
*
* @oaram mat[out] Вектор ввиде обычной матрицы
* @param vec[out] Вектор
*
* @return Код ошибки
*/
int menu_input_vector(int ***mat, vector_t *vec);

/**
* @brief Выводит разреженную матрицу
*
* @param mat[in] Разреженная матрица
*
* @return Код ошибки 
*/
int menu_print_matrix(sparse_t *mat);

/**
* @brief Выводит вектор
*
* @param mat[in] Вектор
*
* @return Код ошибки 
*/
int menu_print_vector(vector_t *vec);

/**
* @brief Умножение вектора на разряженную матрицу
*
* @param vec[in] Вектор
* @param mat[in] Разреженная матрица
* @param vec_r[in] Результат
*
* @return Код ошибки
*/
int menu_mult(vector_t *vec, sparse_t *mat, vector_t *vec_r);

/**
* @brief Умножение вектора на разряженную матрицу обычным методом
*
* @param vec[in] Вектор
* @param mat[in] Разреженная матрица
* @param vec_r[in] Результат
*
* @return Код ошибки
*/
int menu_mult_normal(vector_t *vec, sparse_t *mat, vector_t *vec_r);

/**
* @brief Замерный эксперимент 
*
* @param f[in,out] Выходной файловый поток с текстовой информацией
* @param f_normal[in,out] Выходной файловый поток графика нормального умножения
* @param f_sparse[in,out] Выходной файловый поток графика разреженного умножения
*
* @return Код ошикбки
*/
int menu_measure(FILE *f, FILE *f_normal, FILE *f_sparse);
#endif

