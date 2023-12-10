#include "../inc/menu.h"

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
    case ERR_EMPTY:
        printf("\033[91mОшибка: дерево пусто\033[0m\n");
        break;
    case ERR_FILE:
        printf("\033[91mОшибка работы с файлом\033[0m\n");
        break;
    default:
        printf("\033[91mНеизвестная ошибка: %d\033[0m\n", err);
        break;
    }
}
void menu_print_text(void)
{
    printf(MENU_TEXT);
}

int menu_add(tree_t **tree)
{
    tree_t *new_node = tree_node_create(0, "");
    
    if (new_node == NULL)
        return ERR_EMPTY_NODE;
    int rc = tree_node_read(stdin, stdout, new_node);
    if (rc)
        tree_node_destroy(&new_node);
    if (!rc)
        *tree = tree_insert_node(*tree, new_node, tree_node_cmp_name);
    return rc;
}

int menu_remove(tree_t **tree)
{
    tree_t *prototype = tree_node_create(0, "");
    
    if (prototype == NULL)
        return ERR_EMPTY_NODE;
    int rc = tree_node_read(stdin, stdout, prototype);
    if (rc)
        tree_node_destroy(&prototype);
    if (!rc)
        tree_remove_by_cmp(tree, prototype, tree_node_cmp_date, tree_node_cmp_name);
    return rc;

}

int menu_rebuild(tree_t **tree, int (*comporator)(void *, void *))  
{
    tree_t *tree_copy =  NULL;
    int rc = tree_rebuild(&tree_copy, *tree, comporator);
    if (rc)
        tree_destroy(&tree_copy);
    else
    {
        tree_destroy(tree);
        *tree = tree_copy;
    }
    return rc;
}

int menu_traversal_front(tree_t *tree)
{
    tree_traversal(tree, tree_node_print_simple, stdout);
    return ERR_OK;
}

int menu_traversal_back(tree_t *tree)
{
    tree_traversal_back(tree, tree_node_print_simple, stdout);
    return ERR_OK;
}

int menu_traversal_left(tree_t *tree)
{
    tree_traversal_left(tree, tree_node_print_simple, stdout);
    return ERR_OK;
}

int menu_draw(tree_t *tree)
{
    tree_draw("tree.gv", tree);
    return ERR_OK;
}

int menu_measure(void)
{
    return measure();
}
