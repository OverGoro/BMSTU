#include "list_stack.h"
#include <stdbool.h>
#include <stdio.h>

static list_stack_t free_stack = {0, NULL}; // Стек свободных адресов

/**
* @brief Добавление элементов в стек свободных областей
*
* @param node[in] Удаленный узел
*/
void fs_push(list_stack_node_t *node)
{
    if (ls_empty(&free_stack))
    {
        free_stack.top = node;
        free_stack.top->node_num = 0;
        free_stack.top->previous = NULL;
        free_stack.top->value = NULL;
    }
    else 
    {
        node->previous = free_stack.top;
        node->node_num = free_stack.top->node_num + 1;
        node->value = NULL;
        free_stack.top = node;
    }
}

/**
* @brief Удаление элемента из стека свободных областей
*
* @return Удаленный узел
*/
list_stack_node_t *fs_pop(void)
{
    if (ls_empty(&free_stack))
        return NULL;
    list_stack_node_t *node = free_stack.top;
    free_stack.top = free_stack.top->previous;
    return node;
}

void ls_init_stack(list_stack_t *stack, size_t max_nodes_num)
{
    if (ls_empty(&free_stack))
        ls_clear(&free_stack);

    free_stack.top = NULL;
    free_stack.max_nodes_num = max_nodes_num;

    stack->top = NULL;
    stack->max_nodes_num = max_nodes_num;
}

bool ls_empty(list_stack_t *stack)
{
    if (stack->top == NULL)
    {
        return true;
    }
    return false;
}

bool ls_full(list_stack_t *stack)
{
    if (stack->top == NULL)
        return false;
    if(stack->top->node_num == stack->max_nodes_num - 1)
    {
        return true;
    }
    return false;
}

int ls_push(list_stack_t *stack, void *el)
{
    if (ls_full(stack))
        return ERR_STACK_FULL;

    list_stack_node_t *node;

    if (ls_empty(&free_stack))
        node = malloc(sizeof(list_stack_node_t));
    else
    {
        node = fs_pop();
    }

    if (node == NULL)
        return ERR_MEM;

    if (stack->top != NULL)
    {
        node->previous = stack->top;
        node->node_num = stack->top->node_num + 1;
        node->value = el;
        stack->top = node;
    }
    else
    {
        node->previous = NULL;
        node->node_num = 0;
        node->value = el;
        stack->top = node;
    }
    return  ERR_OK;
}

int ls_pop(list_stack_t *stack, void **el)
{
    if (ls_empty(stack))
        return ERR_STACK_EMPTY;
    
    *el = stack->top;
    
    list_stack_node_t *top = stack->top;
    stack->top = top->previous;

    fs_push(top);

    return ERR_OK; 
}

void ls_print_info(FILE *f, list_stack_t *stack)
{
    fprintf(f, "\033[1;036mСтек на списке\033[0m\n");
    if (ls_empty(stack))
        fprintf(f, "\033[92mПустой стек\033[0m\n");
    else
    {
        fprintf(f, "%s|%s|%s|%s\n", "  Адрес элемента   ", "   Значение эл-та   ", "  n  ", " Предыдущий");
        list_stack_node_t *node = stack->top;
        while (node != NULL)
        {
            printf("%18p | \033[93m%18p\033[0m | %3lu | %18p\n", 
                   (void *)node,
                   node->value,
                   node->node_num,
                   (void *)node->previous);
            node = node->previous;
        }
    }

    fprintf(f, "\033[1;036mСтек свободных областей\033[0m\n");
    if (ls_empty(&free_stack))
        fprintf(f, "\033[92mПустой стек\033[0m\n");
    else
    {
        fprintf(f, "%s|%s|%s|%s\n", "  Адрес элемента   ", "   Значение эл-та   ", "  n  ", " Предыдущий");
        list_stack_node_t *node = free_stack.top;
        while (node != NULL)
        {
            printf("%18p | \033[93m%18p\033[0m | %3lu | %18p\n", 
                   (void *)node,
                   node->value,
                   node->node_num,
                   (void *)node->previous);
            node = node->previous;
        }
    }
}

int ls_input(list_stack_t *stack)
{
    ls_clear(stack);
    int n = 0;

    printf("Количество элементов (максимум %lu): ", stack->max_nodes_num);
    if (scanf("%d", &n) != 1)
        return ERR_IO;
    if (n < 0 || n > (int)stack->max_nodes_num)
        return ERR_RANGE;

    for (int i = 0; i < n; i++)
    {
        int rc = ls_push(stack, NULL);
        if (rc)
        {
            ls_clear(stack);
            return rc;
        }
        stack->top->value = (void *)stack->top;
    }
    return ERR_OK;
}

void ls_clear(list_stack_t *stack)
{
    while (stack->top != NULL)
    {
        list_stack_node_t *node = stack->top;
        stack->top = stack->top->previous;
        fs_push(node);
    }
}

void ls_free(list_stack_t *stack)
{
    while (stack->top != NULL)
    {
        list_stack_node_t *node = stack->top;
        stack->top = stack->top->previous;
        free(node);
    }
    while (free_stack.top != NULL)
    {
        list_stack_node_t *node = free_stack.top;
        free_stack.top = free_stack.top->previous;
        free(node);
    }   
}

