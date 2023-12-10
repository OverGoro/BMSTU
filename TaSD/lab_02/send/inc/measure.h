#ifndef MEASURE_H__
#define MEASURE_H__

#include <sys/time.h>
#include "student.h"
#include "student_keys.h"
#include <bits/types/FILE.h>

typedef struct
{
    size_t n; 
    double time;
    unsigned long memory;
} measure_t;


/**
* @brief Проведение замера
*
* @param arr_beg[in] Начало таблицы
* @param arr_end[in] Конец таблицы
* @param qsort_table_res[out] Результат qsort для таблицы
* @param bsort_table_res[out] Результат bubble sort для таблицы
* @param qsort_key_res[out] Результат qsort для массива ключей 
* @param bsort_key_res[out] Результат bubble sort для массива ключей
*
* @return Код ошибки
*/
int take_measure(const student_t *arr_beg, const student_t *arr_end,
                 measure_t *qsort_table_res, measure_t *bsort_table_res,
                 measure_t *qsort_key_res, measure_t *bsort_key_res);

/**
* @brief Создает массив student_t с случайными оценками
*
* @param[out] arr_beg
* @param[out] tmp_arr_end
* @param[in] n
*
* @return Код ошибки
*/
int generate_random_marks_arr(student_t **arr_beg, student_t **tmp_arr_end, size_t n);

/**
* @brief Проводит все замеры и записывает в файлы
*
* @param start_n Начальное количество элментво в массиве
* @param end_n Конечное число элементов в массиве
* @param step_n Изменение количества за шаг
*
* @return Код ошибки
*/
int conduct_experiment(size_t start_n, size_t end_n, size_t step_n);

/**
* @brief Вывод результата замеров 
*
* @param f[in, out] Файловый поток
* @param m[in] Результат
*/
void print_measure(FILE *f, measure_t *m);

#endif

