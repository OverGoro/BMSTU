#include "funcs.h"

void replace_words(char *word_1, char *word_2)
{
    char replaced_str[WORD_LEN + 1];
    strcpy(replaced_str, word_1);
    strcpy(word_1, word_2);
    strcpy(word_2, replaced_str);
}


void delete_word(char words[][WORD_LEN + 1], size_t *words_num, size_t word_i)
{
    for (size_t i = word_i + 1; i < *words_num; i++)
    {
        strcpy(words[i - 1], words[i]);
    }
    (*words_num)--;
}

void delete_repeated_words(char words[][WORD_LEN + 1], size_t *words_num)
{
    size_t i = 0;
    while (i < *words_num)
    {        
        for (size_t j = 0; j < i; j++)
        {
            if (strcmp(words[i], words[j]) == 0)
            {
                delete_word(words, words_num, i);
                i--;
                break;
            }
        }
        i++;
    }
}

void sort_words(char words[][WORD_LEN + 1], size_t words_num)
{
    for (size_t i = 0; i < words_num - 1; i++)
    {
        for (size_t j = i + 1; j < words_num; j++)
        {
            if (strcmp(words[j], words[i]) < 0)
            {
                replace_words(words[i], words[j]);
            }
        }
    }
}
