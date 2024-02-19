#ifndef FILM_ARRAY_H__
#define FILM_ARRAY_H__

#include "error.h"
#include "film.h"

#include <stddef.h>
#include <string.h>
#include <assert.h>

#define FIELD_TYPE_TITLE "title"
#define FIELD_TYPE_NAME "name"
#define FIELD_TYPE_YEAR "year"

#define MAX_N 15

/**
* @brief Читает массив структур film_t из текстового файла,сортируя их по указанному полю
*
* Возможные значения поля: "title", "year", "name"
*
* @param f[in] Файловый поток
* @param film_array[out] Массив структур film_t
* @param pn[out] Указатель на количество структур в массиве
* @param field[in] Поле по которому ведется сортировка
* @param max_n[in] Максимальное количество структур
*
* @return 
*/
int fa_sorted_read(FILE *f, film_t *film_array, size_t *pn, size_t max_n, comporator_t cmp);


/**
* @brief Вставка структуры film в массив на позицию pos
* Предполагается, что на указанную позицию возможно вставить структуру
*
* @param film_array[in,out] Массив структур
* @param n[in, out] Количество элементов в массиве
* @param film[in] Структура для втсавки
* @param pos[in] Позиция вставки
*/
void fa_paste(film_t *film_array, size_t *n, film_t *film, size_t pos);



/**
* @brief Универсальный поиск места для вставки
*
* @param film_array Массив 
* @param n Количество элементов в массиве
* @param film Элемент для вставки
* @param cmp Компоратор
*
* @return Индекс для вставки
*/
size_t fa_find_place(film_t *film_array, size_t n, const film_t *film, comporator_t cmp);

/**
* @brief Вывод массива структур film_t
*
* @param f[in] Файловый поток
* @param film_array[in] Массив структур
* @param n[in] Количество структур в массиве
*
* @return Код ошибки
*/
int fa_print(FILE *f, film_t *film_array, size_t n);

/**
* @brief Бинарный поиск в массиве фильмов
*
* @param film_array[in] Массив фильмов
* @param n[in] Количество элементов в массиве
* @param prototype[in] Прототип для поиска
* @param cmp[in] Компоратор
*
* @return Указатель на найденную структуру
*/
film_t *fa_bin_search(film_t *film_array, size_t n, film_t *prototype, comporator_t cmp);

#endif

