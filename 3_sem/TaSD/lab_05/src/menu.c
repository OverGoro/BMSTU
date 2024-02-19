#include "menu.h"
#include "measure.h"
#include "process.h"
#include "process_array.h"

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
        printf("\033[91mОшибка: очередь пуста\033[0m\n");
        break;
    case ERR_FILE:
        printf("\033[91mОшибка работы с файлом\033[0m\n");
        break;
    default:
        printf("\033[91mНеизвестная ошибка: %d\033[0m\n", err);
        break;
    }
}
void menu_print(void)
{
    printf(MENU_TEXT);
}

int menu_simulate_array(void)    
{
    process_array_t *pr = process_array_init();
    int rc = process_array_simulate(pr);
    return rc;
}

int menu_simulate_list(void)
{
    process_t *pr = process_init();
    int rc = process_simulate(pr);
    return rc;
}

int menu_measure(void)
{
    return measure();
}
