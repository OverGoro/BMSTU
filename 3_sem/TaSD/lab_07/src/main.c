#include "../inc/tree.h"
#include "../inc/menu.h"
#include "error.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(void)
{
    hash_table_t ht = {0, 0};
    closed_hash_table_t cht = {0, 0};
    tree_t *tree = NULL;
    avl_tree_t *avl_tree = NULL;

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

            case READ:
                rc = menu_read(&ht, &cht, &tree, &avl_tree);
                break;
            case PRT_HASH:
                rc = menu_print_hash(stdout, &ht);
                break;
            case PRT_CLSD_HASH:
                rc = menu_print_closed_hash(stdout, &cht);
                break;
            case PRT_BIN:
                rc = menu_print_tree(tree, "tree.gv");
                break;
            case PRT_AVL:
                rc = menu_print_avl_tree(avl_tree, "avl_tree.gv");
                break;
            case ADD:
                rc = menu_add(&tree, &avl_tree, &ht, &cht);
                break;
            case FIND:
                rc = menu_find(&ht);
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



