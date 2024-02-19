#ifndef FILM_H__
#define FILM_H__

#include <stdio.h>
#include <string.h>

#include "error.h"

#define TITLE_LEN 25
#define NAME_LEN 25

typedef struct
{
    char title[TITLE_LEN + 1];
    char name[NAME_LEN + 1];
    int year;
} film_t;

typedef int (*comporator_t)(const film_t *l, const film_t *r);
/**
* @brief Сравнение фильмов по заголовку
*
* @param film_1[in] Фильм 1
* @param film_2[in] Фильм 2
*
* @return
* 1 - film_1 больше film_2
* 0 - film_1 равен film_2
* -1 - film_1 меньше film_2
*/
int film_cmp_by_title(const film_t *film_1, const film_t *film_2);

/**
* @brief Сравнение фильмов по автору
*
* @param film_1[in] Фильм 1
* @param film_2[in] Фильм 2
*
* @return
* 1 - film_1 больше film_2
* 0 - film_1 равен film_2
* -1 - film_1 меньше film_2
*/
int film_cmp_by_name(const film_t *film_1, const film_t *film_2);

/**
* @brief Сравнение фильмов по году выпуска
*
* @param film_1[in] Фильм 1
* @param film_2[in] Фильм 2
*
* @return
* 1 - film_1 больше film_2
* 0 - film_1 равен film_2
* -1 - film_1 меньше film_2
*/
int film_cmp_by_year(const film_t *film_1, const film_t *film_2);


/**
* @brief Чтение фильма из файла
*
* @param f[in] Файловый поток
* @param pf[out] Указатель на структуру film_t
*
* @return Код ошибки
*/
int film_read(FILE *f, film_t *pf);


/**
* @brief Вывод структуры film_t в поток
*
* @param f[in] Файловый поток
* @param pf[in] Указатель на структуру film_t
*
* @return Код ошибки
*/
int film_print(FILE *f, film_t *pf);


#endif

