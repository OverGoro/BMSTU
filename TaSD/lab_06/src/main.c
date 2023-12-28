#include "../inc/tree.h"
#include "../inc/menu.h"
#include "error.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(void)
{
    tree_t *tree = NULL;
    while (true)
    {
        menu_print_text();
        // Ввод команды
        char cur_char = '\0';
        printf("\033[93mВведите команду: \033[0m");
        size_t command;
        int rc_cmnd = scanf("%lu", &command);
        while ((cur_char = getchar()) != '\n' && cur_char != '\0');
        while ( rc_cmnd != 1 || command > MEASURE)
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

            case ADD:
                rc = menu_add(&tree);
                break;
            case REMOVE:
                rc = menu_remove(&tree);
                break;
            case DRAW:
                rc = menu_draw(tree);
                break;
            case REBUILD_DATE:
                rc = menu_rebuild(&tree, tree_node_cmp_date);
                break;
            case REBUILD_NAME:
                rc = menu_rebuild(&tree, tree_node_cmp_name);
                break;
            case TRAV_FRONT:
                rc = menu_traversal_front(tree);
                break;
            case TRAV_BACK:
                rc = menu_traversal_back(tree);
                break;
            case TRAV_LEFT:
                rc = menu_traversal_left(tree);
                break;
            case MEASURE:
                rc = menu_measure();
                break;
        }
        if (command == EXIT)
            break;
        handle_err(rc);
    }
    tree_node_destroy(&tree);
    return ERR_OK;
}
