#include "funcs.h"

int delete_repeated_chars(char *word)
{
    char temp_word[WORD_LEN + 1];
    size_t temp_word_len = 0;
    size_t word_len = strlen(word);
    if (word_len > WORD_LEN)
    {
        return ERR_TOO_LONG_WORDS;
    }
    
    temp_word[0] = '\0';

    for (size_t i = 0; i < word_len; i++)
    {
        if (strchr(temp_word, word[i]) == NULL)
        {
            temp_word[temp_word_len] = word[i];
            temp_word[temp_word_len + 1] = '\0';
            temp_word_len++;
        }
    }
    strcpy(word, temp_word);
    return OK;
}

int make_new_str(char *new_line, size_t *new_line_len, char words[][WORD_LEN + 1], size_t words_num)
{
    new_line[0] = '\0';
    *new_line_len = 0;
    if (words_num == 0)
    {
        return ERR_NO_WORDS;
    }
    for (int i = words_num - 1; i >= 0; i--)
    {
        if (strcmp(words[i], words[words_num - 1]) != 0)
        {
            delete_repeated_chars(words[i]);
            size_t word_len = strlen(words[i]);
            if (*new_line_len + word_len + 1 > STR_LEN)
            {
                return ERR_TOO_LONG_STRING;
            }
            strcat(new_line, words[i]);
            strcat(new_line, " ");
            *new_line_len += strlen(words[i]) + 1;
        }
    }
    if (*new_line_len != 0)
    {
        new_line[*new_line_len - 1] = '\0';
        (*new_line_len)--;
    }
    else
    {
        return ERR_EMPTY_STR;
    }
    return OK;
}
