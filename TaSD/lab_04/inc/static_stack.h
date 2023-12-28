#ifndef STATIC_STACK_H__
#define STATIC_STACK_H__

#include "error.h"
#include "stack_def.h"
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>

// Стек - статический массив
typedef struct 
{
    void *arr[STATIC_STACK_SIZE]; // Массив значений
    void **start; // Начало массива
    void **end;   // Конец массива
    void **cur;   // Текущий элемент массива
} static_stack_t;

/**
* @brief Инициализация статического стека
*
* @param stack[in, out] Статический стек
*/
void ss_init_stack(static_stack_t *stack);

/**
* @brief Получение элемента статического стека
*
* @param stack[in] Статический стек
*
* @return Последний элемент стека
*/
int ss_pop(static_stack_t *stack, void **el);

/**
* @brief Запись элемента статического стека
*
* @param stack[in] Статический стек
* @param el[in] Элемент
*
* @return Код ошибки
*/
int ss_push(static_stack_t *stack, void *el);

/**
* @brief Проверка пустоты статического стека
*
* @param stack[in] Статические стек
*
* @return true - пустой
* false - не пустой
*/
bool ss_is_empty(static_stack_t *stack);

/**
* @brief Проверка полной заполненности статического стека
*
* @param stack[in] Статический стек
*
* @return true - полность заполнен
*/
bool ss_is_full(static_stack_t *stack);

/**
* @brief Ввод стека на статическом массиве
*
* @param stack[in, out] Стек
*
* @return Код ошибки
*/
int ss_input(static_stack_t *stack);

/**
* @brief Вывод состояния статического стека
*
* @param f[in, out] Файловый поток
* @param stack[in] Статический стек
*/
void ss_print_info(FILE *f, static_stack_t *stack);

/**
* @brief Вывод элемнтов статического стека
*
* @param stack[in] Статический стек
*/
void ss_print(static_stack_t *stack);

/**
* @brief Очистка статического стека
*
* @param stack[in, out] Статический стек
*/
void ss_clear(static_stack_t *stack);


#endif // !LIST_STACK_H__
