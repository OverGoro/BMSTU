#ifndef STR_IO_H__
#define STR_IO_H__
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "error.h"

/**
* @brief Ввод строки
*
* @param f[in, out] Файловый поток
* @param n[in] Количество символов в массивк
* @param str[in] Массив символов
*
* @return Код ошибки
*/
int input_str(FILE *f, size_t n, char *str);

#endif

