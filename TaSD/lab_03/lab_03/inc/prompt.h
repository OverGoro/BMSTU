#ifndef PROMPT_H__
#define PROMPT_H__

#include <stdio.h>

typedef void( *prompt_t)(FILE *f, char *s);
/**
* @brief Не выводит приглашение к вводу
*
* @param s Строка
*/
void empty_prompt(FILE *f, char *s);

/**
* @brief Выводит приглашение к вводу
*
* @param s Строка
*/
void normal_prompt(FILE *f, char *s);

#endif

