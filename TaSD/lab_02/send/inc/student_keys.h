#ifndef STUDENT_KEYS_H__
#define STUDENT_KEYS_H__
#include "student.h"
#include <stdlib.h>
#include "error.h"
#include "student_io.h"
#include <stdbool.h>

typedef struct
{
    size_t n;             // Индекс в таблице
    double average_mark;  // Значение средней оценки
} student_key_t;

/**
* @brief Сравнение элементов массива ключей по оценке
*
* @param p_l[in] Указатель на первый элемент
* @param p_r[in] Указатель на второй элмент
*
* @return Результат сравнения
*/
int ka_cmp_marks(const void *p_l, const void *p_r);

/**
* @brief Создание массива ключей по таблице
*
* @param ka_beg[out] Указатель на начало массива ключей
* @param ka_end[out] Указатель на конец массива ключей
* @param arr_beg[in] Указатель на начало таблицы
* @param arr_end[in] Указатель на конец таблицы
*
* @return Код ошибки
*/
int ka_create(student_key_t **ka_beg, student_key_t **ka_end,
              const student_t *arr_beg, const student_t *arr_end);

/**
* @brief Вывод массива ключей
*
* @param f Файловый поток
* @param arr_beg[in] Начало массива ключей
* @param arr_end[in] Конец массива ключей
*/
void ka_print(FILE *f, const student_key_t *arr_beg, const student_key_t *arr_end, bool is_table);

int ka_print_table(FILE *f, 
                   const student_t *arr_beg,
                   const student_key_t *key_beg, const student_key_t *key_end);

#endif // !STUDENT_KEYS_H__

