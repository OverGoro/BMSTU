#ifndef STUDENT_ARRAY_H__
#define STUDENT_ARRAY_H__
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "error.h"
#include "student.h"
#include "student_io.h"



/**
* @brief Ввод массива студентов из файла
*
* @param f[in, out] Файловый поток
* @param arr_beg[out] Указатель на начало массива
* @param arr_end[out] Указатель на конец массива
* @param prompt[in] Функция приглашения к выводу
*
* @return Код ошибки
*/
int sa_input(FILE *f, student_t **arr_beg, student_t **arr_end, prompt_t prompt);

/**
* @brief Добавляет запись в конец массива
*
* @param arr_beg[in, out] Начало массива
* @param arr_end[in, out] Конец массива
* @param s[in] Запись для добавления
*
* @return Код ошибки
*/
int sa_append(student_t **arr_beg, student_t **arr_end, student_t *s);

/**
* @brief Удаление записи по индексу
*
* @param arr_beg[in, out] Начало массива
* @param arr_end[in, out] Конец массива
* @param i[in] Инекс
*
* @return Код ошибки
*/
int sa_delete(student_t **arr_beg, student_t **arr_end, size_t i);

/**
* @brief Вывод массива студентов
*
* @param f[in, out] Файловый поток
* @param arr_beg[in] Указатель на начало массива
* @param arr_end[in] Указатель на конец массива
* @param is_table[in] Красивый вывод
*/
void sa_output(FILE *f, const student_t *arr_beg, const student_t *arr_end, bool is_table);

/**
* @brief Добавление элементов в таблицу ручным вводом
*
* @param arr_beg[in, out] Начало массива
* @param arr_end[in, out] Конец массива
*
* @return Код ошибки
*/
int sa_keyboard_append(student_t **arr_beg, student_t **arr_end);


int sa_copy(const student_t *arr_beg, const student_t *arr_end, 
            student_t **tmp_beg, student_t **tmp_end);

#endif

