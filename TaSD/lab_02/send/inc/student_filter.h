#ifndef STUDENT_FILTER__
#define STUDENT_FILTER__

#include "student.h"
#include "error.h"
#include <stdlib.h>

/**
* @brief Подсчет количества студентов равных прототипу по массиву
* компараторов
*
* @param arr_beg[in] Начало массива
* @param arr_end[in] Конец массива
* @param cmp_arr[in] Массив компараторов
* @param cmp_n[in] Количество компараторов в массиве
*
* @return Количество студентов
*/
size_t sa_count_filtered(const student_t *arr_beg, const student_t *arr_end,
                         const student_t *prototype,
                         cmp_t *cmp_arr, size_t cmp_n);

/**
* @brief Заполнение массива элементами, равными прототипу по массиву компараторов
*
* @param arr_beg[in] Начало исходного массива
* @param arr_end[in] Конец исходного массива
* @param dst_beg[out] Начало нового массива
* @param dst_end[out] Конец нового массива
* @param prototype[in] Прототип
* @param n_stb[in] Количество подходящих струтктур
* @param cmp_arr[in] Массив компараторов
* @param cmp_n[in] Количество компараторов
*
* @return Код ошибки
*/
int sa_create_filtered(const student_t *arr_beg, const student_t *arr_end,
                         student_t **dst_beg, student_t **dst_end,
                         const student_t *prototype, size_t n_stb,
                         cmp_t *cmp_arr, size_t cmp_n);



/**
* @brief Фильтрация элементов по прототипу и массиву компараторов
*
* Все элемента массива сравниваются с прототипом по массиву компараторов
* и добавляются в новый массив в случае равенства
*
* @param arr_beg[in] Указатель на начала исходного массива
* @param arr_end[in] Указатель на конец исходного массива
* @param res_beg[out] Указатель на начало фильтрованного массива
* @param res_end[out] Указатель на конец фильтрованного массива
* @param cmp_arr[in] Массив компараторов
* @param cmp_n[in] Количество компараторов в массиве
*
* @return Код ошибки
*/
int sa_filter(const student_t *prototype,
               const student_t *arr_beg, const student_t *arr_end,
               student_t **res_beg, student_t **res_end,
               cmp_t *cmp_arr, size_t cmp_n);

#endif
