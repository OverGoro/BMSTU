// Городский Юрий ИУ7-22Б Лабораторная работа №4 Задача №3 Вариант №1

#include <stddef.h>
#include <stdio.h>
#include "constants.h"
#include "strio.h"
#include "errors.h"
#include "funcs.h"

int main(void)
{
    char str[STR_LEN + 1];

    char new_str[STR_LEN + 1];
    size_t new_str_len = 0;

    char words[MAX_WORDS_NUM][WORD_LEN + 1];
    size_t words_num = 0;
    int rc = 0;
    
    rc = input_string(str, STR_LEN + 1);
    if (rc != OK)
    {
        return rc;
    }
    
    rc = split_to_words(str, words, &words_num);
    if (rc != OK)
    {
        return rc;
    }
    rc = make_new_str(new_str, &new_str_len, words, words_num);
    if (rc != OK)
    {
        return rc;
    }
    printf("Result: %s\n", new_str);

    return OK;
}
