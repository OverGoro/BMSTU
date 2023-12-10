// Городский Юрий ИУ7-22Б
#include <stdio.h>
#include <math.h>

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2
// Определение порядка числа
// num - число
int count_num_order(int num)
{
    int number_order = 0;
    while (num > 0)
    {
        number_order += 1;
        num /= 10;
    }
    return number_order;
}

// Вывод числа по символам
// num - число
// number_order - порядок числа
void print_by_digits(int num, int number_order)
{    
    int digit;
    int k = 1;
    for (int i = 0; i < number_order - 1; i++)
    {
        k *= 10;
    }
    
    for (int i = 0; i < number_order; i++)
    {   
        digit = num / k % 10;
        k /= 10;
        printf("%d", digit);
    }
    printf("\n");
}

int main(void)
{
    int num;
    int number_order;
    
    // Ввод
    printf("Input num: ");
    if (scanf("%d", &num) != 1)
    {
        printf("IO Error\n");
        return ERR_IO;
    }

    if (num < 1)
    {
        printf("The number is not natural\n");
        return ERR_RANGE;   
    }   

    // Определение порядка числа
    number_order = count_num_order(num);

    // Вывод числа
    print_by_digits(num, number_order);
    
    return OK;
}

