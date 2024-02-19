#ifndef HASH_FUNC_H_
#define HASH_FUNC_H_

#include <stddef.h>

/**
* @brief Хэш функция деления
*
* @param s[in] Строка
* @param m[in] Размерность массива
*
* @return Результат хэш функции
*/
size_t hash_func(char *s, size_t m);

#endif

