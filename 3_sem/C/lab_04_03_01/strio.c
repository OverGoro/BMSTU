#include "strio.h"

int split_to_words(char *str, char words[][WORD_LEN + 1], size_t *words_num)
{
    *words_num = 0;
    char *cur_word = strtok(str, WORD_SEPARATORS);
    while (cur_word != NULL)
    {
        if (strlen(cur_word) > WORD_LEN)
        {
            return ERR_TOO_LONG_WORDS;
        }
        if (*words_num == MAX_WORDS_NUM)
        {
            return ERR_TOO_MANY_WORDS;
        }
        strcpy(words[*words_num], cur_word);
        (*words_num)++;
        cur_word = strtok(NULL, WORD_SEPARATORS);
    }
    
    return OK;   
}

int input_string(char *buff, size_t buff_size)
{
    if (fgets(buff, buff_size, stdin) != buff)
    {
        return ERR_IO;
    }
    char *p = strrchr(buff, '\n');
    if (p != NULL)
    {
        *p = 0;
        return OK;
    }
    return ERR_TOO_LONG_INPUT;
}

