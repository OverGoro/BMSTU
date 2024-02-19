// Городский Юрий ИУ7-22Б Лабораторная работа №4 Задача №1
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "funcs.h"
#include "constants.h"

int main(void)
{
    size_t failed_num = 0;
    size_t tests_input_num = 4;
    size_t tests_output_num = 5;
    char words_1[][WORD_LEN] = { "fabc", "cde", "", "\0" };
    char words_2[][WORD_LEN] = { "cbaf", "fabc", "abs", "" ,"\0" };

    for (size_t i = 0; i < tests_input_num; i++)
    {
        for (size_t j = 0; j < tests_output_num; j++)
        {
            for (size_t k = 0; k < strlen(words_2[i]); k++)
            {
                if (my_strchr(words_1[i], words_2[j][k]) != strchr(words_1[i], words_2[j][k]))
                {
                    failed_num++;
                }
                if (my_strrchr(words_1[i], words_2[j][k]) != strrchr(words_1[i], words_2[j][k]))
                {
                    failed_num++;
                }
            }

            if (my_strcspn(words_1[i], words_2[j]) != strcspn(words_1[i], words_2[j]))
            {
                failed_num++;
            }
            if (my_strpbrk(words_1[i], words_2[j]) != strpbrk(words_1[i], words_2[j]))
            {
                failed_num++;
            }
            if (my_strspn(words_1[i], words_2[j]) != strspn(words_1[i], words_2[j]))
            {
                failed_num++;
            }
        }
    }
    printf("%lu\n", failed_num);
    return (int)failed_num;
}
