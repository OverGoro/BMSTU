// Городский Юрий ИУ7-22Б Лабораторная работа №2 Задача №5 Вариант №0
// Вычислить max(a[0] + a[n-1], ... , a[(n-1)/2] + a[n/2])
#include <stdio.h>
#define N 10 // Максимальное количество элементов в массиве

#define OK 0
#define ERROR_IO 1
#define ERROR_RANGE 2


/// @brief Поиск максимальной суммы элементов, равноудаленнных от концов массива
/// @param[in] pa_s Указатель на начало массива
/// @param[in] pa_e Указатель на конец массива
/// @param[in] max Максимальная сумма
void find_max(const int *pa_s, const int *pa_e, int *max)
{
    const int *pa_j = pa_e - 1;
    const int *pa_i = pa_s;
    *max = *pa_i + *pa_j;
    pa_i++;
    pa_j--;
    while (pa_i <= pa_j)
    {
        if (*pa_i + *pa_j > *max)
        {
            *max = *pa_i + *pa_j;
        }
        pa_i++;
        pa_j--;
    }    
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
    int max = 0; // Максимальная сумма элементов
    
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
    
    find_max(pa_s, pa_e, &max);
    printf("Max: %d\n", max);

    return OK;
}
