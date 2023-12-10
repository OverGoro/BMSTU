#ifndef __STRIO_H__
#define __STRIO_H__
#include "errors.h"
#include "constants.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/// @brief Разбивает строку на слова
/// @param[in] str Строка
/// @param[out] words Массив слов
/// @param[out] words_num Длина слов
/// @return Код ошибки
int split_to_words(char *str, char words[][WORD_LEN + 1], size_t *words_num);

/// @brief Считывание сроки
/// @param buff Буффер 
/// @param buff_size Размер буффера
/// @return Код ошибки
int input_string(char *buff, size_t buff_size);
#endif
