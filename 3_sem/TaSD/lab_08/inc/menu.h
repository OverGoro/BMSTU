#ifndef MENU_H__
#define MENU_H__

#include "graph.h"

#define MENU_TEXT "\
\033[036mГрафы\033[0m\n\
1) Прочитать данные из файла\n\
2) Вывести граф\n\
3) Найти достпуные вершины\n\
0) Выйти\n"

enum Commands 
{
    EXIT,
    READ,
    PRINT,
    FIND
};

/**
* @brief Обработка кода ошибки
*
* @param err[in] Код ошибки
*/
void handle_err(int err);

void menu_print_text(void);

int menu_read(graph_t ***graph_nodes, size_t *n);

int menu_print(graph_t **graph_nodes, size_t n);

int menu_find(graph_t **graph_nodes, size_t n);

#endif

