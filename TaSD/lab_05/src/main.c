#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "error.h"
#include "menu.h"
#include "process.h"
#include "process_array.h"
#include "object.h"

int main(void)
{
    while (true)
    {
        menu_print();
        // Ввод команды
        printf("\033[93mВведите команду: \033[0m");
        size_t command;
        char cur_char = '\0';
        int rc_cmnd = scanf("%lu", &command);
        while ( rc_cmnd != 1 || command > MEASURE)
        {
            printf("\033[91mНеверная команда\033[0m\n");
            printf("\033[93mВведите команду: \033[0m");
            while ((cur_char = getchar()) != '\n' && cur_char != '\0');
            rc_cmnd = scanf("%lu", &command);
        }
        int rc = ERR_OK;
        switch (command) 
        {
            case EXIT:
                break;

            case SIMULATE_ARRAY:
                rc = menu_simulate_array();
                break;
            case SIMULATE_LIST:
                rc = menu_simulate_list();
                break;
            case MEASURE:
                rc = menu_measure();
                break;
        }
        if (command == EXIT)
            break;
        handle_err(rc);
    }
    return ERR_OK;
}
