#ifndef CHECK_CMP_H__
#define CHECK_CMP_H__
#include "film.h"

/**
* @brief Сравнение 2 массивов фильмов, 
*
* @param arr_1[in] Массив 1
* @param arr_2[in] Массив 2
* @param n_1[in] Кол-во элементов в массиве 1
* @param n_2[in] Кол-во элементов в массиве 2
*
* @return 0 - равны, 1 - не равны
*/
int cmp_film_t_arr(film_t *arr_1, film_t *arr_2, size_t n_1, size_t n_2);

#endif // !CHECK_CMP_H__
