#ifndef MENU_H__
#define MENU_H__

#include "list_stack.h"
#include "static_stack.h"
#include "measure.h"
#define MENU_TEXT "\
\033[036mСтек\033[0m\n\
1) Ввести стек - список\n\
2) Добавить элемент в стек - список\n\
3) Удалить элемент из стека - списка\n\
4) Вывести состояние стека - списка\n\
5) Очистить стек - список\n\n\
6) Ввести стек - статический массив\n\
7) Добавить элемент в стек - статический массив\n\
8) Удалить элемент из стека - статического массива\n\
9) Вывести состояние стека - статического массива\n\
10) Очистить стек - статический массив\n\n\
11) Замерный эксперимент\n\n\
0) Выйти\n"

enum Commands 
{
    EXIT,
    INPUT_LIST,
    PUSH_LIST,
    POP_LIST,
    PRINT_INFO_LIST,
    CLEAR_LIST,
    INPUT_STATIC,
    PUSH_STATIC,
    POP_STATIC,
    PRINT_INFO_STATIC,
    CLEAR_STATIC,
    MEASURE
};

/**
* @brief Обработка кода ошибки
*
* @param err[in] Код ошибки
*/
void handle_err(int err);

/**
* @brief Выводит список команд
*/
void menu_commands_print(void);

/**
* @brief Ввод стека на статическом массиве
*
* @param stack[out] Стек
*
* @return Код ошибки
*/
int menu_input_static(static_stack_t *stack);

/**
* @brief Добавление элемента стека на статическом массиве
*
* @param stack[out] Стек
*
* @return Код ошибки
*/
int menu_push_static(static_stack_t *stack);

/**
* @brief Удаление элемента стека на статическом массиве
*
* @param stack[out] Стек
*
* @return Код ошибки
*/
int menu_pop_static(static_stack_t *stack);

/**
* @brief Очистка стека на статическом массиве
*
* @param stack[in, out] Стек
*
* @return Код ошибки
*/
int menu_clear_static(static_stack_t *stack);

/**
* @brief Очистка стека на статическом массиве
*
* @param stack[in, out] Стек
*
* @return Код ошибки
*/
int menu_print_info_static(static_stack_t *stack);

/**
* @brief Ввод стека на списке
*
* @param stack[out] Стек
*
* @return Код ошибки
*/
int menu_input_list(list_stack_t *stack);

/**
* @brief Добавление элемента стека на списке
*
* @param stack[out] Стек
*
* @return Код ошибки
*/
int menu_push_list(list_stack_t *stack);

/**
* @brief Удаление элемента стека на списке
*
* @param stack[out] Стек
*
* @return Код ошибки
*/
int menu_pop_list(list_stack_t *stack);



/**
* @brief Ввод стека на списке
*
* @param stack[out] Стек
*
* @return Код ошибки
*/
int menu_print_info_list(list_stack_t *stack);

/**
* @brief Очистка стека на списке
*
* @param stack[out] Стек
*
* @return Код ошибки
*/
int menu_clear_list(list_stack_t *stack);

/**
* @brief Ввод стека на списке
*
* @param stack[out] Стек
*
* @return Код ошибки
*/
int menu_print_info_list(list_stack_t *stack);

/**
* @brief Очистка стека на списке
*
* @param stack[out] Стек
*
* @return Код ошибки
*/
int menu_clear_list(list_stack_t *stack);

/**
* @brief Замерный эксперимент 
*
* @param f[in,out] Выходной файловый поток с текстовой информацией
* @param f_normal[in,out] Выходной файловый поток графика нормального умножения
* @param f_sparse[in,out] Выходной файловый поток графика разреженного умножения
*
* @return Код ошикбки
*/
int menu_measure(void);
#endif

