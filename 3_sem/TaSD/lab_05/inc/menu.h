#ifndef MENU_H__
#define MENU_H__

#include "process.h"
#include "process_array.h"
#include "measure.h"

#define MENU_TEXT "\
\033[036mОчереди\033[0m\n\
1) Симуляция на очереди - статическом массиве\n\
2) Симуляция на очереди - списке\n\
3) Замерный эксперимент\n\
0) Выйти\n"

enum Commands 
{
    EXIT,
    SIMULATE_ARRAY,
    SIMULATE_LIST,
    MEASURE
};

/**
* @brief Обработка кода ошибки
*
* @param err[in] Код ошибки
*/
void handle_err(int err);

void menu_print(void);

int menu_simulate_array(void);

int menu_simulate_list(void);

int menu_measure(void);

#endif

