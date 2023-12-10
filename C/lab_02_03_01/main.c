// Городский Юрий ИУ7-22Б Лабораторная работа №2 Задача №3 Вариант №1
// Вставка очередного числа фиббоначи после каждого элемента массива кратного 3
#include <stdio.h>
#include <stdbool.h>

#define N_F 20 // Максимальное количество элементов в новом массиве
#define N 10 // Максимальное количество элементов в введенном массиве

#define MULTICIPLITY_FACTOR 3 // Коэффициент кратности
#define OK 0
#define ERROR_IO 1
#define ERROR_RANGE 2

/// @brief Определение кратности числа n числу k
/// @param[in] n Число 
/// @param[in] k Коэффициент кратности
/// @return Кратность
bool is_multiple(int n, int k)
{
    if (n % k == 0)
    {
        return true;
    }
    return false;
}

/// @brief Вычисление n-ого элемента последовательности Фибоначчи
/// @param fib_0 Первый элемент последовательности
/// @param fib_1 Второй элемент последовательности
/// @param n Номер элемента последовательности
/// @return 
int fib(int fib_0, int fib_1, size_t n)
{
    for (size_t i = 1; i < n; i++)
    {
        int temp = fib_1;
        fib_1 = fib_0 + fib_1;
        fib_0 = temp;
    }
    return fib_0;   
}

/// @brief Вывод массива
/// @param[in] a Массив
/// @param[in] a_size Размер массива
void output(const int a[], size_t a_size)
{
    for (size_t i = 0; i < a_size; i++)
    {
        printf("%d ", a[i]);
    }
}
/// @brief Ввод массива
/// @param[out] a Массив
/// @param[out] a_size Размер массива
/// @return Код ошибки
int input(int a[], size_t *a_size)
{
    printf("Array size: ");
    if (scanf("%zu", a_size) != 1)
    {
        return ERROR_IO;
    }
    if (*a_size <= 0 || *a_size > N)
    {
        return ERROR_RANGE;
    }
    printf("Enter elements: ");
    for (size_t i = 0; i < *a_size; i++)
    {
        if (scanf("%d", &a[i]) != 1)
        {
            return ERROR_IO;
        }
    }
    return OK;
}
/// @brief Вставка элемента е на позицию i
/// @param[in, out] a Массив
/// @param[in] a_size Размер массива
/// @param[in] i Позиция элемента
/// @param[in] e Значение элемента
void insert(int a[], size_t *a_size, size_t i, int e)
{
    for (size_t j = *a_size; j > i; j--)
    {
        a[j] = a[j - 1];
    }
    a[i] = e;
    (*a_size)++;
}
/// @brief  Формирование нового массива
/// @param[in] a Старый массив
/// @param[in] a_size Размер массива
/// @param[in] fib_0 Первый элемент последовательности Фибоначчи
/// @param[in] fib_1 Второй элемент последовательности Фибоначчи
void form_array(int a[], size_t *a_size, int fib_0, int fib_1)
{
    size_t i = 0;
    int fib_num = 1; // Число вставленных чисел
    while (i < *a_size)
    {
        if (is_multiple(a[i], MULTICIPLITY_FACTOR) == true)
        {
            insert(a, a_size, i + 1, fib(fib_0, fib_1, fib_num));
            i++;
            fib_num++;
        }
        i++;
    }
}
int main(void)
{
    int fib_0 = 0, fib_1 = 1; // Значения последних 2 элементов последовательности Фибоначчи
    int input_exit_code; // Код завершения функции ввода
    int a[N_F]; // Массив
    size_t a_size; // Размер массива
    
    input_exit_code = input(a, &a_size);
    if (input_exit_code != OK)
    {
        printf("Input error\n");
        return input_exit_code;
    }
    
    form_array(a, &a_size, fib_0, fib_1);

    printf("New array: ");
    output(a, a_size);
    printf("\n");
    return OK;
}
