#ifndef MENU_H__
#define MENU_H__

#include "tree.h"
#include "../inc/measure.h"

#define MENU_TEXT "\
\033[036mДвоичные деревья\033[0m\n\
1) Добавить элемент\n\
2) Удалить элемент по дате\n\
3) Вывести состояние дерева\n\
4) Перестроить дерево до даты\n\
5) Перестроить дерево по имени\n\
6) Обход дерева сверху вниз (по названию файла)\n\
7) Обход дерева снизу вверх (по названию файла)\n\
8) Обход дерева слева направо (по названию файла)\n\
9) Замерный эксперимент\n\
0) Выйти\n"

enum Commands 
{
    EXIT,
    ADD,
    REMOVE,
    DRAW,
    REBUILD_DATE,
    REBUILD_NAME,
    TRAV_FRONT,
    TRAV_BACK,
    TRAV_LEFT,
    MEASURE
};

/**
* @brief Обработка кода ошибки
*
* @param err[in] Код ошибки
*/
void handle_err(int err);

int menu_add(tree_t **tree);

int menu_remove(tree_t **tree);

int menu_rebuild(tree_t **tree, int comporator(void *, void *));

int menu_draw(tree_t *tree);

int menu_traversal_front(tree_t *tree);
int menu_traversal_back(tree_t *tree);
int menu_traversal_left(tree_t *tree);

void menu_print_text(void);

int menu_measure(void);

#endif

