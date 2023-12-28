#ifndef __FUNS_H__
#define __FUNS_H__
#include <string.h>
#include "constants.h"

/// @brief Удаление повторяющихся слов
/// @param[in, out] words Массив слов
/// @param[in, out] words_num Количество слов
void delete_repeated_words(char words[][WORD_LEN + 1], size_t *words_num);

/// @brief Сортировка слов в алфавитном порядке
/// @param[in, out] words Массив слов
/// @param[in] words_num Количество слов
void sort_words(char words[][WORD_LEN + 1], size_t words_num);

#endif
