#define _GNU_SOURCE
#include "../inc/menu.h"
#include <stdio.h>

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
        printf("\033[91mОшибка: пусто\033[0m\n");
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

int menu_read(hash_table_t *ht, closed_hash_table_t *cht, tree_t **tree, avl_tree_t **avl_tree)
{
    char *file_name = NULL;
    int len_file_name;

    int rc = ERR_OK;
    size_t read = 0;

    // Чтение file_name
    fprintf(stdout, "\nВведите имя файла: ");
    if ((len_file_name = getline(&file_name, &read, stdin)) == -1 || len_file_name <= 1)
    {
        rc = ERR_IO;
    }
    else
    {
        file_name[--len_file_name] = '\0';
        if (len_file_name == 0)
            rc = ERR_RANGE;
    }

    if (!rc) rc = ht_read_from_file(ht, file_name);
    if (!rc) rc = cht_read_from_file(cht, file_name);
    if (!rc) rc = tree_read(tree, file_name);
    if (!rc) rc = avl_tree_read(avl_tree, file_name);
    return rc;
}

int menu_print_hash(FILE *f, hash_table_t *ht)
{
    ht_print(f, ht);
    return ERR_OK;
}

int menu_print_closed_hash(FILE *f, closed_hash_table_t *cht)
{
    cht_print(f, cht);
    return ERR_OK;
}
int menu_print_tree(tree_t *tree, char *file_name)
{
    return tree_draw(file_name, tree);
}

int menu_print_avl_tree(avl_tree_t *tree, char *file_name)
{
    return avl_tree_draw(file_name, tree);
}

int menu_measure(void)
{
    return measure();
}

int menu_find(hash_table_t *ht) 
{
    char *name = NULL;
    int rc = ERR_OK;
    int name_len;
    size_t read = 0;

    // Чтение name
    if ((name_len = getline(&name, &read, stdin)) == -1 || name_len <= 1)
    {
        rc = ERR_IO;
    }
    else
    {
        name[--name_len] = '\0';
        if (name_len == 0)
            rc = ERR_RANGE;
    }
    const char *manual = NULL;
    if (!rc) manual = ht_get_manual(ht, name);
    fprintf(stdout, "Описание: ");
    if (manual)
        fprintf(stdout, "%s\n", manual);
    else
        fprintf(stdout, "\033[036mНе найдено\033[0m\n");
    return rc;
}

int menu_add(tree_t **tree, avl_tree_t **avl_tree, hash_table_t *ht, closed_hash_table_t *cht)
{

    char *name = NULL, *manual = NULL;
    int rc = ERR_OK;
    int name_len, manual_len;
    size_t read = 0;

    // Чтение name
    printf("Слово: ");
    if ((name_len = getline(&name, &read, stdin)) == -1 || name_len <= 1)
    {
        rc = ERR_IO;
    }
    else
    {
        name[--name_len] = '\0';
        if (name_len == 0)
            rc = ERR_RANGE;
    }
    // Чтение manual
    printf("HELP: ");
    if (rc == ERR_OK && ((manual_len = getline(&manual, &read, stdin)) == -1 || manual_len <= 1))
    {
        rc = ERR_IO;
    }
    else if (rc == ERR_OK)
    {
        manual[--manual_len] = '\0';
        if (manual_len == 0)
            rc = ERR_RANGE;
    }

    if (!rc) rc = ht_insert(ht, name, manual, 3);
    if (!rc) rc = cht_insert(cht, name, manual, 3);
    tree_t *node = NULL;
    if (!rc) node = tree_node_create(name, manual);
    if (!rc && node == NULL) rc = ERR_MEM;
    avl_tree_t *avl_node = NULL;
    if (!rc) avl_node = avl_tree_node_create(name, manual);
    if (!rc && avl_node == NULL)  rc = ERR_MEM;

    if (!rc) *tree = tree_insert_node(*tree, node, tree_node_cmp_name);
    if (!rc) *avl_tree = avl_tree_insert_node(*avl_tree, avl_node, avl_tree_node_cmp_name);
    

    return rc;
}

