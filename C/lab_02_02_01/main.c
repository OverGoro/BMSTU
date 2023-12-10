// Городский Юрий ИУ7-22Б Лабораторная работа №2 задача №1 Вариант №1
// Сформировать и вывести новый массив, в который скопировать элементы
// старого, являющиеся простыми числами
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define N 10 // Максимальное количество элементов в массиве

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2
#define ERR_EMPTY_ARRAY 3

/// @brief Вывод массива
/// @param[in] a Массив 
/// @param[in] a_size Размер массива
void output(const int a[], size_t a_size)
{
    printf("Array: ");
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
    // Ввод размера
    printf("Input array size: ");
    if (scanf("%zu", a_size) != 1)
    {
        return ERR_IO;
    }

    if (*a_size > N || *a_size == 0)
    {
        return ERR_RANGE;
    }
    
    // Ввод элементов
    printf("Input elements: ");
    for (size_t i = 0; i < *a_size; i++)
    {
        if (scanf("%d", &a[i]) != 1)
        {
            return ERR_IO;
        }
    }
        
    return OK;
}

/// @brief Проверка числа на простоту
/// @param[in] num Число
/// @return Простое / не простое
bool is_simple(int num)
{
    if (num < 2)
    {
        return false;
    }
    int int_sqrt_num = (int)sqrt(num);
    for (int i = 2; i <= int_sqrt_num; i++)
    {
        if (num % i == 0)
        {
            return false;
        }
    }
    return true;
}
/// @brief Формирование массива из простых чисел другого массива
/// @param[in] a Старый массив
/// @param[in] a_size Размер старого массива
/// @param[out] b Новый массив
/// @param[out] b_size Размер нового массива
void form_array(const int a[], size_t a_size, int b[], size_t *b_size)
{
    size_t j = 0;
    for (size_t i = 0; i < a_size; i++)
    {
        if (is_simple(a[i]))
        {
            b[j] = a[i];
            j++;
        }
    }
    *b_size = j;
}

int main(void)
{
    int a[N], b[N]; // Старый и новый массивы
    size_t a_size = N, b_size = N; // Размеры старого и нового массива
    int input_exit_code = 0; // Код завершения функции ввода
    
    input_exit_code = input(a, &a_size);
    if (input_exit_code != OK)
    {
        printf("Input ERROR\n");
        return input_exit_code;
    }

    form_array(a, a_size, b, &b_size);
    if (b_size == 0)
    {
        return ERR_EMPTY_ARRAY;
    }
    output(b, b_size);
    printf("\n");
    return OK;
}
