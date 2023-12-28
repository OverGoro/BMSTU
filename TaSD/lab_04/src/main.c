#include "menu.h"
#include "stack_def.h"
#include "static_stack.h"
#include "list_stack.h"
#include <stdio.h>

int main(void)
{
    list_stack_t l_stack;
    static_stack_t s_stack;

    ls_init_stack(&l_stack, STATIC_STACK_SIZE);
    ss_init_stack(&s_stack);

    while (true)
    {
        menu_commands_print();
        // Ввод команды
        printf("\033[93mВведите команду: \033[0m");
        size_t command;
        char cur_char = '\0';
        int rc = scanf("%lu", &command);
        while ( rc != 1 || command > MEASURE)
        {
            printf("\033[91mНеверная команда\033[0m\n");
            printf("\033[93mВведите команду: \033[0m");
            while ((cur_char = getchar()) != '\n' && cur_char != '\0');
            rc = scanf("%lu", &command);
        }
        switch (command) 
        {
            case EXIT:
                break;

            case INPUT_LIST:
                rc = menu_input_list(&l_stack);
                break;
            case PUSH_LIST:
                rc = menu_push_list(&l_stack);
                break;
            case POP_LIST:
                rc = menu_pop_list(&l_stack);
                break;
            case CLEAR_LIST:
                rc = menu_clear_list(&l_stack);
                break;
            case PRINT_INFO_LIST:
                rc = menu_print_info_list(&l_stack);
                break;

            case INPUT_STATIC:
                rc = menu_input_static(&s_stack);
                break;
            case PUSH_STATIC:
                rc = menu_push_static(&s_stack);
                break;
            case POP_STATIC:
                rc = menu_pop_static(&s_stack);
                break;
            case CLEAR_STATIC:
                rc = menu_clear_static(&s_stack);
                break;
            case PRINT_INFO_STATIC:
                rc = menu_print_info_static(&s_stack);
                break;

            case MEASURE:
                rc = menu_measure();
                break;
        }
        if (command == EXIT)
            break;
        handle_err(rc);
    }
    ls_clear(&l_stack);
    ss_clear(&s_stack);
    return ERR_OK;
}

