#ifndef MENU_H__
#define MENU_H__

#include "error.h"
#include <stdio.h>

enum
{
    READ_FILE = 1,
    PRINT_TABLE,
    ADD_ENTRY,
    DELETE_ENTRY,
    LOAD_BUF,
    QSORT_TABLE,
    BUBBLE_SORT_TABLE,
    QSORT_ARR,
    BUBBLE_SORT_ARR,
    PRINT_ARR,
    PRINT_TABLE_BY_ARR,
    SEARCH,
    SAVE,
    TIME_EXPERIMENT,
    EXIT
};

/**
* @brief Вывод меню команд
*/
void menu_print(void);

#endif

