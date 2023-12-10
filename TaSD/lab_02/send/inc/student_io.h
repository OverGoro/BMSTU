#ifndef STUDENT_IO_H__
#define STUDENT_IO_H__
#include <stdbool.h>
#include <stdio.h>
#include "student.h"
#include "error.h"

#include "str_io.h"

#define TABLE_TITLE "                            Студент                                                     |      Свой дом              |   Общежитие   |            Съемное жилье                |\n\
   n  |   Жилье   |   Фамилия  |    Имя     |  Группа    | Пол | Возраст |Оценка|  Год  |   Улица    |  Дом  |  Кв.  |№ Общ. |№ ком. |   Улица    |  Дом  |  Кв.  |    Цена    |\n\
------|-----------|------------|------------|------------|-----|---------|------|-------|------------|-------|-------|-------|-------|------------|-------|-------|------------|\n"

#define N_WIDTH 5
#define HOUSING_WIDTH 9
#define SEX_WIDTH 3
#define AGE_WIDTH 7
#define MARK_WIDTH 2
#define DATE_WIDTH 5
#define HOUSE_WIDTH 5
#define FLAT_WIDTH 5
#define DORMITORY_NUM_WITH 5
#define ROOM_NUM_WIDTH 5
#define COST_WIDTH 10

#define STR(x) #x

typedef void( *prompt_t)(FILE *f, char *s);
/**
* @brief Не выводит приглашение к вводу
*
* @param s Строка
*/
void empty_prompt(FILE *f, char *s);

/**
* @brief Выводит приглашение к вводу
*
* @param s Строка
*/
void normal_prompt(FILE *f, char *s);

/**
* @brief Ввод структуры house_t
*
* @param f[in] Файловый поток
* @param house[out] Дом
*
* @return Код ошибки
*/
int house_input(FILE *f, house_t *house);

/**
* @brief Вывод структуры house_t
*
* @param f[in] Файловый поток
* @param house[out] Дом
* @param is_table[in] Красивый вывод
*/
void house_print(FILE *f, const house_t *house, bool is_table);

/**
* @brief Ввод структуры dormitory_t
*
* @param f[in] Файловый поток
* @param dormitory[out] Общежитие
*
* @return Код ошибки
*/
int dormitory_input(FILE *f, dormitory_t *dormitory);

/**
* @brief Вывод структуры dormitory_t
*
* @param f[in] Файловый поток
* @param dormitory[out] Общежитие
* @param is_table[in] Красивый вывод
*/
void dormitory_print(FILE *f, const dormitory_t *dormitory, bool is_table);

/**
* @brief Ввод структуры rental_t
*
* @param f[in] Файловый поток
* @param rental[out] Съемное жилье
*
* @return Код ошибки
*/
int rental_input(FILE *f, rental_t *rental);

/**
* @brief Ввод структуры rental_t
*
* @param f[in] Файловый поток
* @param rental[in] Съемное жилье
* @param is_table[in] Красивый вывод
*
* @return Код ошибки
*/
void rental_print(FILE *f, const rental_t *rental, bool is_table);

/**
* @brief Чтение структуры студента из файлового потока
*
* @param[in] f Файловый поток
* @param[in] student Студент
* @param[in] prompt Функция вывода приглашений и ошибок
* 
* @renturn Код ошибки
*/
int student_input(FILE *f, student_t *student, prompt_t prompt);

/**
* @brief Вывод student_t в файловый поток
*
* @param f[in] Файловый поток
* @param student_t[in] Студент
* @param is_table[in] Красивый вывод
*/
void student_print(FILE *f, const student_t *student, bool is_table);

#endif

