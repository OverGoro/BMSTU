// Городский Юрий ИУ7-22Б Лабораторная работа №2 Задача №3 Вариант №1
// Вставка очередного числа фиббоначи после каждого элемента массива кратного 3
#include <stddef.h>
#include <stdio.h>
#include "constants.h"
#include "strio.h"
#include "errors.h"
#include "funcs.h"

int main(void)
{
    char str[STR_LEN + 1];
    char words[MAX_WORDS_NUM][WORD_LEN + 1];
    size_t words_num = 0;
    int get_words_code;

    int input_error = input_string(str, STR_LEN + 1);
    if (input_error != OK)
    {
        return input_error;
    }
    
    get_words_code = get_words(str, words, &words_num);
    if (get_words_code != OK)
    {
        switch (get_words_code)
        {
            case ERR_TOO_LONG_WORDS:
                printf("ERR: String has too long words\n");
                return ERR_TOO_LONG_WORDS;
                break;
            case ERR_TOO_LONG_INPUT:
                printf("ERR: Sring is too long\n");
                return ERR_TOO_LONG_INPUT;
                break;
            case ERR_NO_WORDS:
                printf("ERR: No words\n");
                return ERR_NO_WORDS;
            default:
                printf("Undefined error");
                return ERR_UNDEFINED;
        }
    }

    
    delete_repeated_words(words, &words_num);
    sort_words(words, words_num);
    printf("Result: ");
    print_words(words, words_num);
    return OK;
}
