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


/**
* @brief Выделение памяти под массив указателей на film_t
*
* @param n[in] Количество элементов
*
* @return Масив
*/
film_t *fa_allocate(size_t n);

/**
* @brief Освобождение памяти 
*
* @param film_array[in, out]
* @param n[in] Количество элементов в массивк
*/
void fa_free(film_t **film_array, size_t n);

/**
* @brief Подсчет количества структуру в файле
*
* @param f[in, out] Файловый поток
* @param n[out] Количество структур
*
* @return Код ошибки
*/
int fa_count(FILE *f, size_t *n);

/**
* @brief Создание отсортированного массива фильмов по файлу и компортору
*
* @param f[in, out] Файловый поток
* @param pfilms[out] Массив фильмов
* @param n_films[out] Количество фильмов
* @param cmp[in] Компоратор
*
* @return Код ошибки
*/
int fa_sorted_create(FILE *f, film_t **pfilms, size_t *n_films, comporator_t cmp);

/**
* @brief Чтение массива структур film_t из текстового файла с сортировкой их по указанному компаратору
*
* Возможные значения поля: "title", "year", "name"
*
* @param f[in] Файловый поток
* @param film_array[out] Массив структур film_t
* @param pn[out] Указатель на количество структур в массиве
* @param max_n[in] Максимальное количество структур
* @param cmp[in] Компоратор
*
* @return Код ошибки
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

