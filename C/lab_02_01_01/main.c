// Городский Юрий ИУ7-22Б Лабораторная работа №2 задача №1 Вариант №1
// Подсчет произведение нечетных элементов в массиве
#include <stdio.h>
#include <stdbool.h>

#define N 10 // Максимальное количество элементов в массиве

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2

/// @brief Ввод массива
/// @param[out] a Массив
/// @param[out] a_size Размер массива
/// @return Код ошибки
int input(int a[], size_t *a_size)
{
    // Ввод размера
    printf("Input array size: ");
    if (scanf("%zu", a_size) != 1)
    {
        return ERR_IO;
    }
    printf("Input elements: ");
    if (*a_size > N || *a_size == 0)
    {
        return ERR_RANGE;
    }
    
    // Ввод элементов
    for (size_t i = 0; i < *a_size; i++)
    {
        if (scanf("%d", &a[i]) != 1)
        {
            return ERR_IO;
        }
    }
        
    return OK;
}

/// @brief Проверка числа на четность
/// @param[in] num Число
/// @return Четность
bool is_odd(int num)
{
    return (num % 2);
}

/// @brief Подсчет произведения нечетных элемент
/// @param[in] a Массив
/// @param[in] a_size Размер массивы
/// @param[out] result Произведения нечетных элементов
/// @return 
int multiply_odd(const int a[], size_t a_size, int *result)
{
    int res = 1; // Результат произведения
    int odd_num = 0; // Количество нечетных элементов в массиве
    for (size_t i = 0; i < a_size; i++)
    {
        if (is_odd(a[i]))
        {
            res *= a[i];
            odd_num++;
        }
    }
    if (odd_num > 0)
    {
        *result = res;
        return OK;
    }
    return ERR_RANGE;
}

int main(void)
{
    int a[N]; // Массив
    size_t a_size = N; // Размер массива
    int product = 0; // Значение
    int input_exit_code = 0; // Код завершения функции ввода
    int multiply_exit_code = 0; // Код завершения функции поиска произведения
    
    input_exit_code = input(a, &a_size);
    if (input_exit_code != OK)
    {
        printf("Input ERROR\n");
        return input_exit_code;
    }

    multiply_exit_code = multiply_odd(a, a_size, &product);
    if (multiply_exit_code != OK)
    {
        printf("No odd elements\n");
        return multiply_exit_code;
    }
    printf("Multiply of odd elemets: %d\n", product);
    return OK;
}
