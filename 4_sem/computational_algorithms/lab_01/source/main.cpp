#include <iostream>

#include "../headers/menu.hpp"

int main()
{
    
    int command = -1, rc = OK;
    while (command != EXIT)
    {
        print_menu();
        do
        {
            rc = get_command(command);
            if (rc)
            {
                handle_rc(rc);
                std::cout << "Введите команду: ";
            }
        } while (rc != OK);

        if (command == GET_TABLE)
            rc = command_get_table();
        else if (command == GET_ROOT)
            rc = command_get_root();
        else if (command == SOLVE_SYSTEM)
            rc = command_solve_system();
        else if (command != EXIT)
            rc = ERR_UNKNOWN_COMMAND;
        handle_rc(rc);
    }
    return rc;
}

