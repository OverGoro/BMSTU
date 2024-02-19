#ifndef MENU_H__
#define MENU_H__

#include "avl_tree.h"
#include "hash_table.h"
#include "closed_hash_table.h"
#include "tree.h"
#include "../inc/measure.h"
#include "tree_node.h"

#define MENU_TEXT "\
\033[036mДеревья и хэш таблицы\033[0m\n\
1) Прочитать данные из файла\n\
2) Вывести хэш таблицу с внешним хешированием\n\
3) Вывести хэш таблицу с внутренним хешированием\n\
4) Вывести двоичное дерево поиска\n\
5) Вывести авл дерево\n\
6) Найти HELP\n\
7) Добавить элемент\n\
8) Замерный эксперимент\n\
0) Выйти\n"

enum Commands 
{
    EXIT,
    READ,
    PRT_HASH,
    PRT_CLSD_HASH,
    PRT_BIN,
    PRT_AVL,
    FIND,
    ADD,
    MEASURE
};

/**
* @brief Обработка кода ошибки
*
* @param err[in] Код ошибки
*/
void handle_err(int err);

void menu_print_text(void);

int menu_read(hash_table_t *ht, closed_hash_table_t *cht, tree_t **tree, avl_tree_t **avl_tree);

int menu_print_hash(FILE *f, hash_table_t *ht);

int menu_print_closed_hash(FILE *f, closed_hash_table_t *cht);

int menu_print_tree(tree_t *tree, char *file_name);

int menu_print_avl_tree(avl_tree_t *tree, char *file_name);

int menu_find(hash_table_t *ht);

int menu_measure(void);
int menu_add(tree_t **tree, avl_tree_t **avl_tree, hash_table_t *ht, closed_hash_table_t *cht);
#endif

