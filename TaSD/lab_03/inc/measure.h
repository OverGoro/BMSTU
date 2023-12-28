#ifndef MEASURE_H__
#define MEASURE_H__
#include <math.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stddef.h>
#include <stdio.h>
#include "sparse_matrix_operations.h"
#include "sparse_matrix_generator.h"
#include "vec.h"
#include "error.h"

typedef struct
{
    size_t fill_percent; // Процент заполнения матриц
    size_t m, n; // Количество строк, столбцов
    
    size_t sparse_size; // Память при разреженном умножении
    size_t normal_size; // Память при нормальном умножении 

    size_t sparse_repeats; // Количество повторов при замере разреженного умнодения
    size_t normal_repeats; // Количество повторов при замере нормального умножения
    
    double sparse_time; // Время разреженного умножения
    double normal_time; // Время нормального умножения

    double sparse_rse; // rse разреженного умножения
    double normal_rse; // rse нормального умножения
    
    double *sparse_measures; // Массив результатов замеров времени разреженного умножения
    double *normal_measures; // Массив результатов замеров времени нормального умножения
} measure_t;


/**
* @brief Получение одного замера
*
* @param m[in] Количество строк в матрице
* @param n[in] Количество столбцов в матрице
* @param fill_percent[in] Процент заполнения матрицы
* @param measure[out] Результат замера
*
* @return Код ошибки
*/
int measure_get(size_t m, size_t n, size_t fill_percent, measure_t *measure);

/**
* @brief Вывод результатов измерения в виде текста
*
* @param f[in] Файловый поток вывода
* @param measure[in] Результат измерений
*/
void measure_print(FILE *f, measure_t *measure);

/**
* @brief Вывод данных для построния графиков
*
* @param f_sparse[in, out] Файловый поток для разреженной матрицы
* @param f_normal[in, out] Файловый поток для нормальной матрицы
* @param measure[in] Результат замеров
*/
void measure_graph_print(FILE *f_sparse, FILE *f_normal, measure_t *measure);

/**
* @brief Проведние замеров
*
* @param f_out[in] Выходной файл результатов в виде текста
* @param f_normal[in] Файловый поток для графика нормального умножения
* @param f_sparse[in] Файловый поток для графика разреженного умножения
*
* @return Код ошибки
*/
int make_measure(FILE *f_out, FILE *f_normal, FILE *f_sparse);

/**
* @brief расчета среднего времени
*
* @param pbeg[in] Указатель на начало массива с замерами
* @param pend[in] Указателб на конец массив с замерами
*
* @return Среднее значение замеров
*/
double get_average_time(const double *pbeg, const double *pend);

/**
* @brief Расчет ошибки среднего
*
* @param arr[in] Массив
* @param n[in] Количество элементов в массиве
*
* @return Ошибка среднего
*/
double get_rce(const double *arr, size_t n);

#endif // !MEASURE_H__

