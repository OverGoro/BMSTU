#ifndef TIME_TEST_H__
#define TIME_TEST_H__

#include "sort.h"
#include "error.h"
#include <stddef.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#define START_N 500
#define END_N 5000
#define TESTS_NUM 10
#define DELTA_N 500

typedef struct
{
    size_t mysort_repeats;
    size_t qsort_repeats;
    double mysort_time;
    double qsort_time;
    double **mysort_measures;
    double **qsort_measures;
} measure_t;

typedef void(*set_el_t)(int *prev_e, int *cur_e);

void set_sorted_el(int *prev_e, int *cur_e);
void set_reversed_el(int *prev_e, int *cur_e);
void set_random_el(int *cur_e, int *temp);
void set_equal_el(int *prev_e, int *cur_e);

/**
* @brief Измерение времени сортировки qsort и mysort
*
* @param pdata[in] Массив для сортировки
* @param n[in] Количество элементов в массиве
* @param e_size[in] Размер элемента массива
* @param cmp[in] Компоратор
* @param measure[out] Результат измерения
*
* @return Код ошибки
*/
int measure_get(const void *pdata, size_t n, size_t e_size, cmp_t cmp, measure_t *measure);

/**
* @brief Вывод результатов измерения
*
* @param f_m[in] Файловый поток mysort
* @param f_q[in] Файловый поток qsort
* @param measure[in] Результат измерения
* @param n[in] Количество элементов при измерении
*
* @return Код ошибки
*/
void measure_print(FILE *f_m, FILE *f_q, const measure_t *measure, size_t n);


/**
* @brief Заполняет массив на основе функции set_el
*
* @param pbeg[out] Начало массива
* @param pend[out] Конец массива
* @param n[in] Количество элементов массива
* @param set_el[in] Функция получения очередного элемента
*
* @return Код ошибки
*/
int fill_arr(int **pbeg, int **pend, size_t n, set_el_t set_el);

/**
* @brief Заполняет массив случайными элементами
*
* @param pbeg[out] Начало массива
* @param pend[out] Конец массива
* @param n[in] Количество элементов массива
*
* @return Код ошибки
*/
int fill_arr_random(int **pbeg, int **pend, size_t n);

/**
* @brief Провести замер
*
* @param in_file_name[in] Имя входного файла
* @param out_file_name[in] Имя выходного файла
* @param set_el_func[in] Функция заполнения элементов массива
*
* @return Код ошибки
*/
int make_measure(const char *in_file_name, const char *out_file_name, set_el_t set_el_func);

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

#endif
