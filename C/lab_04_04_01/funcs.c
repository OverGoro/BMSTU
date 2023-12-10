#include "funcs.h"
bool is_num(const char *str)
{
    const char *cur_char = str;
    size_t integer_digits = 0;
    size_t fractional_digits = 0;
    size_t exp_digits = 0;
    // Чтение до начала числа
    while (isspace(*cur_char))
    {
        cur_char++;
    }
    // Проверка на +-
    if (strchr("+-", *cur_char) != NULL && *cur_char != '\0')
    {
        cur_char++;
    }
    // Проверка части до точки или e
    while (strchr(DIGITS, *cur_char) != NULL && *cur_char != '\0')
    {
        integer_digits++;
        cur_char++;
    }
    if (*cur_char == '.')
    {
        cur_char++;
    }
    // Проверка части после точки
    while (strchr(DIGITS, *cur_char) != NULL && *cur_char != '\0')
    {
        fractional_digits++;
        cur_char++;
    }
    if (fractional_digits + integer_digits == 0)
    {
        return false;
    }
    // Проверка e
    if (strchr("eE", *cur_char) != NULL && *cur_char != '\0')
    {
        cur_char++;
        // Проверка на +-
        if (strchr("+-", *cur_char) != NULL && *cur_char != '\0')
        {
            cur_char++;
        }
        // Проверка части после e
        while (strchr(DIGITS, *cur_char) != NULL && *cur_char != '\0')
        {
            exp_digits++;
            cur_char++;
        }
        if (exp_digits == 0)
        {
            return false;
        }
    }
    // Чтение до конца строки
    while (isspace(*cur_char))
    {
        cur_char++;
    }
    if (*cur_char == '\0')
    {
        return true;
    }
    return false;
}
