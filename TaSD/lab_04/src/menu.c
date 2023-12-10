#include "menu.h"
#include "error.h"
#include "static_stack.h"
#include <stdio.h>
#include <stdlib.h>

void handle_err(int err)
{
    switch (err) 
    {
    case ERR_OK:
        printf("\033[92mОперация завершена\033[0m\n");
        break;
    case ERR_IO:
        printf("\033[91mОшибка ввода\033[0m\n");
        break;
    case ERR_RANGE:
        printf("\033[91mОшибка диапазона данных\033[0m\n");
        break;
    case ERR_MEM:
        printf("\033[91mОшибка работы с динамической памятью\033[0m\n");
        break;
    case ERR_STACK_FULL:
        printf("\033[91mОшибка: стек заполнен\033[0m\n");
        break;
    case ERR_STACK_EMPTY:
        printf("\033[91mОшибка: стек пуст\033[0m\n");
        break;
    case ERR_FILE:
        printf("\033[91mОшибка работы с файлом\033[0m\n");
        break;
    default:
        printf("\033[91mНеизвестная ошибка\033[0m\n");
        break;
    }
}

void menu_commands_print(void)
{
    printf(MENU_TEXT);
}



int menu_input_static(static_stack_t *stack)
{
    ss_init_stack(stack);
    int rc = ss_input(stack);
    return rc;
}

int menu_push_static(static_stack_t *stack)
{
    void *el;
    int rc = ERR_OK;
    printf("Введите адрес: ");
    if (scanf("%p", &el) != 1)
        rc = ERR_IO;
    if (!rc)
        rc = ss_push(stack, el);
    return rc;
}

int menu_pop_static(static_stack_t *stack)
{
    int rc = ERR_OK;
    void *el;
    rc = ss_pop(stack, &el);
    if (!rc)
        printf("Удаленный элемент: %p", el);
    return rc;
}

int menu_clear_static(static_stack_t *stack)
{
    ss_clear(stack);
    return ERR_OK;
}

int menu_print_info_static(static_stack_t *stack)
{
    ss_print_info(stdout, stack);
    return ERR_OK;
}


int menu_input_list(list_stack_t *stack)
{
    int rc = ls_input(stack);
    return rc;
}


int menu_push_list(list_stack_t *stack)
{
    void *el;
    int rc = ERR_OK;
    printf("Введите адрес: ");
    if (scanf("%p", &el) != 1)
        rc = ERR_IO;
    if (!rc)
        rc = ls_push(stack, el);
    return rc;
}

int menu_pop_list(list_stack_t *stack)
{
    int rc = ERR_OK;
    void *el;
    rc = ls_pop(stack, &el);
    if (!rc)
        printf("Удаленный элемент: %p", el);
    return rc;
}

int menu_print_info_list(list_stack_t *stack)
{
    ls_print_info(stdout, stack);
    return ERR_OK;
}

int menu_clear_list(list_stack_t *stack)
{
    ls_clear(stack);
    return ERR_OK;
}

int menu_measure(void)
{
    return measure();
}

