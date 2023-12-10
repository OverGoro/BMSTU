// Городский Юрий ИУ7-22Б Лабораторная работа №2 Задача №4 Вариант №2
// Упорядочить массив с помощью сортировки выбором
#include <stdio.h>

#define N 10 // Максимальное количество элементов в массиве

#define OK 0
#define OK_OVERFLOW 100
#define ERROR_IO 1
#define ERROR_RANGE 2

/// @brief Вывод массива
/// @param[in] a массив
/// @param[in] a_size размер массива
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
    *a_size = 0;
    int e = 0; // Очередной элемент
    printf("Enter elements: ");
    while (scanf("%d", &e) == 1)
    {
        if (*a_size >= N)
        {
            return OK_OVERFLOW;
        }
        a[*a_size] = e;
        (*a_size)++;
    }
    if (*a_size == 0)
    {
        return ERROR_RANGE;
    }
    return OK;
}

// /// @brief Поиск индекса минимального элемента
// /// @param[in] a Массив
// /// @param[in] a_size Размер массива
// /// @param[in] i Индекс с которого начинать поиск
// /// @return Индекс минимального элемента
// int find_min_index(int a[], size_t a_size, size_t i)
// {
//     size_t min_j = i;
//     for (size_t j = i; j < a_size; j++)
//     {
//         if (a[j] < a[min_j])
//         {
//             min_j = j;
//         }
//     }
//     return min_j;
// }

/// @brief Поиск указателя на минимальный элемент массива
/// @param p_s Указатель на начало массива [in]
/// @param p_e Указатель на конец массива [in]
/// @return Указатель на минимальный элемент
int *find_min_index(int *p_s, int *p_e)
{
    int *p_min = p_s;
    while (p_s < p_e)
    {
        if (*p_min > *p_s)
        {
            p_min = p_s;
        }
        p_s++;
    }
    return p_min;    
}



/// @brief Сортировка выбором
/// @param[in, out] a Массив
/// @param[in] a_size Размер массива
void selection_sort(int a[], size_t a_size)
{
    for (size_t i = 0; i < a_size - 1; i++)
    {
        int rep_el;
        int *p_min = find_min_index(a + i, a + a_size);
        
        rep_el = a[i];
        a[i] = *p_min;
        *p_min = rep_el;
    }
}
int main(void)
{
    int a[N]; // Массив
    size_t a_size; // Размер массива
    int input_exit_code; // Код завершения функции ввода
    
    input_exit_code = input(a, &a_size);
    if (input_exit_code != OK && input_exit_code != OK_OVERFLOW)
    {
        printf("Input error\n");
        return input_exit_code;
    }
    
    selection_sort(a, a_size);

    printf("New array: ");
    output(a, a_size);
    printf("\n");
    return input_exit_code;
}
