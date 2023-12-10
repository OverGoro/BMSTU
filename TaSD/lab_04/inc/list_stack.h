#ifndef LIST_STACK_H__
#define LIST_STACK_H__

#include "error.h"
#include "stack_def.h"

#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Элемент стека на односвязнои списке
typedef struct list_stack_node_t
{
    size_t node_num; // Индекс в стеке
    void *value; // Значение
    struct list_stack_node_t *previous; // Указатель на предыдущий элемент
} list_stack_node_t;

// Стек на односвязном стеке
typedef struct 
{
    size_t max_nodes_num;   // Максимальное допустимое кол-во элементов в стеке
    list_stack_node_t *top; // Вершина стека
} list_stack_t;


/**
* @brief Инициализация стека списком
*
* @param stack[in, out] стек
*/
void ls_init_stack(list_stack_t *stack, size_t max_nodes_num);

/** 
* @brief Получение элемента стека списком
*
* @param stack[in] стек
*
* @return Последний элемент стека
*/
int ls_pop(list_stack_t *stack, void **el);

/**
* @brief Запись элемента стека списком
*
* @param stack[in] стек
* @param el[in] Элемент
*
* @return Код ошибки
*/
int ls_push(list_stack_t *stack, void *el);

/**
* @brief Проверка пустоты стека списком
*
* @param stack[in] стек
*
* @return true - пустой
* false - не пустой
*/
bool ls_empty(list_stack_t *stack);

/**
* @brief Проверка заполненности стек списком
*
* @param stack Стек
*
* @return true - полностью заполнен
* false - не заполнен
*/
bool ls_full(list_stack_t *stack);

/**
* @brief Ввод стека на списке
*
* @param stack[in, out] Стек
*
* @return Код ошибки
*/
int ls_input(list_stack_t *stack);

/**
* @brief Вывод состояния стека списком
*
* @param f[in, out] Файловый поток
* @param stack[in] стек
*/
void ls_print_info(FILE *f, list_stack_t *stack);

/**
* @brief Вывод элемнтов стека списком
*
* @param stack[in] стек
*/
void ls_print(list_stack_t *stack);

/**
* @brief Очистка стека на списке
*
* @param stack[in, out] Стек
*/
void ls_clear(list_stack_t *stack);

/**
* @brief Освобождение памяти стека на списке
*
* @param stack[in, out] Стек
*/
void ls_free(list_stack_t *stack);

#endif // !LIST_STACK_H__
