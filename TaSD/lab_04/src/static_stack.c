#include "static_stack.h"
#include <stdio.h>
   
void ss_init_stack(static_stack_t *stack)   
{
    stack->start = stack->arr - 1;
    stack->end = stack->arr + STATIC_STACK_SIZE - 1;
    stack->cur = stack->start;
}

bool ss_is_empty(static_stack_t *stack)
{
    if (stack->cur <= stack->start)
        return true;
    return false;
}

bool ss_is_full(static_stack_t *stack)
{
    if(stack->cur >= stack->end)
        return true;
    return false;
}

int ss_push(static_stack_t *stack, void *el)
{
    if (ss_is_full(stack))
        return ERR_STACK_FULL;

    stack->cur++;
    *(stack->cur) = el;
    return ERR_OK;
}

int ss_pop(static_stack_t *stack, void **el)
{
    if (ss_is_empty(stack))
        return ERR_STACK_EMPTY;
    *el = stack->cur;
    stack->cur--;
    return ERR_OK;
}

int ss_input(static_stack_t *stack)
{
    printf("Количество элементов (максимум %d): ", STATIC_STACK_SIZE);
    int n = 0;
    if (scanf("%d", &n) != 1)
        return ERR_IO;
    else if (n < 0 || n > STATIC_STACK_SIZE)
        return ERR_RANGE;

    ss_clear(stack);

    for (size_t i = 0; i < (size_t)n; i++)
    {
        printf("Элемент %lu: ", i);
        void *p;
        if (scanf("%p", &p) != 1)
            return ERR_IO;
        ss_push(stack, p);
    }
    return ERR_OK;
}

void ss_print_info(FILE *f, static_stack_t *stack)
{
    fprintf(f, "\033[1;36mСтек - статический массив\033[0m\n");
    if (ss_is_empty(stack))
        fprintf(f, "\033[092mПустой стек\033[0m\n");
    else 
    {
        fprintf(f, "Адрес элемента  | значение элемента\n");
        void **cur_el = stack->cur;
        while (cur_el > stack->start)
        {
            fprintf(f, " %p | \033[93m%p\033[0m\n", (void *)cur_el, *cur_el);
            cur_el--;
        }
    }
}

void ss_clear(static_stack_t *stack)
{
    stack->cur = stack->start;
}

