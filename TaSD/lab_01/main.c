#include "error.h"
#include "num.h"
#include <stdio.h> 

#define RULER_TEXT "---------1---------2---------3---------4---------5\n"
int main()
{
    float_num_t num_1;
    float_num_t num_2;
    float_num_t num_r;
    
    /*printf("|-------------   \033[92mУмножение чисел\033[39m   --------------|\n");
    printf("|Входные данные:                                 |\n");
    printf("|1) Целое число: макс. длина 40,знак опционален  |\n");
    printf("|2) Вещественное число: [+-]m.n [+-][Ee]k        |\n");
    printf("|   Макс. длина мантиссы m+n = 30                |\n");
    printf("|   Макс. длина порядка k = 5                    |\n");
    printf("|   Порядок, знак порядк и мантиссы  опциональны |\n");
    printf("|Выходные данные: Вещественное число = 1) * 2 )  |\n");
    printf("|------------------------------------------------|\n\n");
    printf("Введите целое число:\n");
    printf(RULER_TEXT);*/
    
    int rc;
    rc = num_read(stdin, &num_1, INTEGER_MODE);
    if (rc != ERR_OK)
    {
        
        switch (rc) 
        {
            case ERR_IO:
                printf("Неправильный формат числа\n");
                break;
            case ERR_ORDER_DIGITS:
                printf("Превышение длины порядка\n");
                break;
            case ERR_DIGITS_NUM:
                printf("Превышение длины числа\n");
                break;
        }
        
        return rc;
    }
    
    /*printf("\nВведите вещественное число:\n");
    printf(RULER_TEXT);*/
    
    rc = num_read(stdin, &num_2, FLOAT_MODE);
    if (rc != ERR_OK)
    {
        
        switch (rc) 
        {
            case ERR_IO:
                printf("Неправильный формат числа\n");
                break;
            case ERR_ORDER_DIGITS:
                printf("Превышение длины порядка\n");
                break;
            case ERR_DIGITS_NUM:
                printf("Превышение длины мантиссы\n");
                break;
        }
        
        return rc;
    }
   
    /*printf("\nРезультат: ");*/
    rc = multiply_nums(&num_1, &num_2, &num_r);
    if (rc == ERR_OK)
        print_num(stdout, &num_r);
    else if (rc == ERR_RANGE)
        printf("Переполнение порядка результата\n");
    return rc;
}

