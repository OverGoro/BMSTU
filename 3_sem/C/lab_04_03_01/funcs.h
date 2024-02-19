#ifndef __FUNS_H__
#define __FUNS_H__
#include <string.h>
#include "constants.h"
#include "errors.h"


/// @brief Оставляет только первые вхождения каждого символа слова
/// @param[in, out] word Слово
/// @return Код ошибки
int delete_repeated_chars(char *word);

/// @brief Формирование новой строки, из слов отличных от последнего в массиве слов
/// @param[out] new_line Новыя строка
/// @param[out] new_line_len Длина новой строки
/// @param[in] words Массив слов
/// @param[in] words_num Количество слов в массиве
/// @return Код ошибки
int make_new_str(char *new_line, size_t *new_line_len, char words[][WORD_LEN + 1], size_t words_num);

#endif
