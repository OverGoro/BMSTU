// Городский Юрий ИУ7-22Б Лабораторная работа №2 Задача №5 Вариант №2 (Защита)
#include <stdio.h>
#define N 10 // Максимальное количество элементов в массиве

#define OK 0
#define ERROR_IO 1
#define ERROR_RANGE 2

/// @brief Поиск укзателя первого отрицательного элемента
/// @param arr Массив 
/// @param arr_size Размер массива
/// @return Указатель первого отрицательного элемента
int *find_first_negative(int *p_s, int *p_e)
{
    while (p_s < p_e)
    {
        if (*p_s < 0)
        {
            return p_s;
        }
        p_s++;
    }
    return p_e - 1;
}

/// @brief Поиск суммы
/// @param arr Массив
/// @param arr_size Размер массива
/// @return Сумма
int find_summ(int *p_s, int *p_e)
{
    int *first_neg_p_i = find_first_negative(p_s, p_e);
    int curr_summ = 1;
    int full_summ = 0;
    while (p_s <= first_neg_p_i)
    {
        curr_summ *= (*p_s);
        full_summ += curr_summ;
        p_s ++;
    }
    return full_summ;
}
/// @brief Ввод массива
/// @param[in] pa_s Указатель на начало массива
/// @param[out] pa_e Указатель на конец массива
/// @return Код ошибки
int input(int **const pa_s, int **pa_e)
{
    size_t a_size; // Размер массива
    printf("Array size: ");
    if (scanf("%zu", &a_size) != 1)
    {
        return ERROR_IO;
    }
    if (a_size <= 0 || a_size > N)
    {
        return ERROR_RANGE;
    }
    *pa_e += a_size;
    printf("Enter elements: ");
    for (int *pa_i = *pa_s; pa_i < *pa_e; pa_i++)
    {
        if (scanf("%d", pa_i) != 1)
        {
            return ERROR_IO;
        }
    }
    return OK;
}
int main(void)
{
    int a[N]; // Массив чисел
    int *pa_s, *pa_e; // Указатели на начало и конец массива
    int input_exit_code = 0; // Код завершения функции ввода
    int res = 0; // Максимальная сумма элементов
    
    pa_s = a;
    pa_e = a;
    input_exit_code = input(&pa_s, &pa_e);
    if (input_exit_code == ERROR_RANGE)
    {
        printf("Error: range\n");
        return input_exit_code;
    }
    else if (input_exit_code == ERROR_IO)
    {
        printf("Error: IO\n");
        return input_exit_code;
    }
    
    res = find_summ(pa_s, pa_e);
    printf("Summ: %d\n", res);

    return OK;
}
