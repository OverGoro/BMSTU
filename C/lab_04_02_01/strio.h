#ifndef __STRIO_H__
#define __STRIO_H__
#include "errors.h"
#include "constants.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/// @brief Считывание сроки
/// @param buff Буффер 
/// @param buff_size Размер буффера
/// @return Код ошибки
int input_string(char *buff, size_t buff_size);

/// @brief Разбиение строки на массив слов
/// @param[in] str Строка
/// @param[out] words Массив слов
/// @param[out] words_num Количество слов
/// @return Код ошибки
int get_words(const char *str, char words[][WORD_LEN + 1], size_t *words_num);

/// @brief Вывод массива слов
/// @param words Массив слов
/// @param words_num Количество слов
void print_words(char words[][WORD_LEN + 1], size_t words_num);


#endif
