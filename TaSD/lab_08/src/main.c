#include "../inc/error.h"
#include "../inc/graph.h"
#include "../inc/menu.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(void)
{
    graph_t **graph_nodes = NULL;
    size_t n = 0;

    while (true)
    {
        menu_print_text();
        // Ввод команды
        char cur_char = '\0';
        printf("\033[93mВведите команду: \033[0m");
        size_t command;
        int rc_cmnd = scanf("%lu", &command);
        while ((cur_char = getchar()) != '\n' && cur_char != '\0');
        while ( rc_cmnd != 1 || command > FIND)
        {
            printf("\033[91mНеверная команда\033[0m\n");
            printf("\033[93mВведите команду: \033[0m");
            rc_cmnd = scanf("%lu", &command);
            while ((cur_char = getchar()) != '\n' && cur_char != '\0');
        }
        int rc = ERR_OK;
        switch (command) 
        {
            case EXIT:
                break;

            case READ:
                rc = menu_read(&graph_nodes, &n);
                break;
            case PRINT:
                rc = menu_print(graph_nodes, n);
                break;
            case FIND:
                rc = menu_find(graph_nodes, n);
                break;
        }
        if (command == EXIT)
            break;
        handle_err(rc);
    }
    graph_destroy(&graph_nodes, &n);
    return ERR_OK;
}



