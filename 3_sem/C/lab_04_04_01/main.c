// Городский Юрий ИУ7-22Б Лабораторная работа №2 Задача №4 Вариант №1
// Проверка строки по выражению [+-]?(\d+([.]\d+)?([eE][+-]?\d+)?|[.]\d+([eE][+-]?\d+)?)
#include <stddef.h>
#include <stdio.h>
#include "constants.h"
#include "strio.h"
#include "errors.h"
#include "funcs.h"

int main(void)
{
    char str[STR_LEN + 1] = "";
    int input_string_code;

    input_string_code = input_string(str, STR_LEN + 1);
    if (input_string_code != OK)
    {
        switch (input_string_code)
        {
            case ERR_IO:
                return ERR_IO;
            case ERR_TOO_LONG_INPUT:
                return ERR_TOO_LONG_INPUT;
            default:
                return ERR_UNDEFINED;
        }   
    }
    if (is_num(str))
    {
        printf("YES");
    }
    else
    {
        printf("NO");
    }   
    return OK;
}
