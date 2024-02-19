#include "funcs.h"
void find_char(const char **searched_char, const char *cur_char)
{
    while (**searched_char != '\0' && **searched_char != *cur_char)
    {
        (*searched_char)++;
    }
}
void find_last_char(const char **searched_char, const char *cur_char)
{
    const char *found_char = NULL;
    while (**searched_char != '\0')
    {
        if (**searched_char == *cur_char)
        {
            found_char = *searched_char;
        }
        (*searched_char)++;
    }
    if (found_char != NULL)
    {
        (*searched_char) = found_char;
    }
}
char *my_strpbrk(const char *string1, const char *string2)
{
    const char *cur_char = string1;
    const char *found_char = NULL;
    const char *searched_char = string2;
    while (*cur_char != '\0')
    {
        searched_char = string2;
        find_char(&searched_char, cur_char);
        if (*searched_char != '\0')
        {
            return (char *)cur_char;
        }
        cur_char++;
    }
    return (char *)found_char;
}

size_t my_strspn(const char *string1, const char *string2)
{
    size_t found_char_num = 0;
    const char *cur_char = string1;
    const char *searched_char = string2;
    while (*cur_char != '\0')
    {
        searched_char = string2;
        find_char(&searched_char, cur_char);
        if (*searched_char == 0)
        {
            return found_char_num;
        }
        else
        {
            found_char_num++;
        }
        cur_char++;
    }
    return found_char_num;
}

size_t my_strcspn(const char *string1, const char *string2)
{
    size_t char_before_num = 0;
    const char *cur_char = string1;
    const char *searched_char = string2;
    while (*cur_char != '\0')
    {
        searched_char = string2;
       
        find_char(&searched_char, cur_char);
        if (*searched_char == 0)
        {
            char_before_num++;
        }
        else
        {
            return char_before_num;
        }
        cur_char++;
    }
    return char_before_num;
}

char *my_strchr(const char *string, const int symbol)
{
    const char *cur_char = string;
    const char *found_char = NULL;
    const char s = (char)symbol;
    find_char(&cur_char, &s);

    if (*cur_char == s)
    {
        found_char = cur_char;
    }
    return (char *)found_char;
}

char *my_strrchr(const char *string, const int symbol)
{
    const char *cur_char = string;
    const char *found_char = NULL;  
    find_last_char(&cur_char, (const char*)&symbol);
    if (*cur_char == symbol)
    {
        found_char = cur_char;
    }
    return (char *)found_char;
}
