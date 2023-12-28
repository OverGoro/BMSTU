#include "strio.h"
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

int get_words(const char *str, char words[][WORD_LEN + 1], size_t *words_num)
{
    *words_num = 0;

    size_t i = 0;
    const char *cur_char = str;
    while (*cur_char != '\0')
    {   
        if (strchr(WORD_SEPARATORS, *cur_char) == NULL)
        {
            if (i >= WORD_LEN)
            {
                return ERR_TOO_LONG_WORDS;
                if (*words_num > MAX_WORDS_NUM)
                {
                    return ERR_TOO_MANY_WORDS;
                }
            }
            
            if (i == 0)
            {
                (*words_num)++;
            }            
            words[(*words_num) - 1][i] = *cur_char;
            words[(*words_num) - 1][i + 1] = '\0';
            i++;
        }
        else if (i != 0)
        {
            i = 0;
        }
        cur_char++;
    }
    if (*words_num == 0)
    {
        return ERR_NO_WORDS;
    }
    return OK;   
}

void print_words(char words[][WORD_LEN + 1], size_t words_num)
{ 
    if (words_num > 0)
    {
        for (size_t i = 0; i < words_num - 1; i++)
        {
            printf("%s ", words[i]);
        }
        if (words_num > 0)
        {
            printf("%s", words[words_num - 1]);
        }
    }
}

