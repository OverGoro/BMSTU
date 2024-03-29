#ifndef MENU_H
#define MENU_H

#include "../headers/error.hpp"

#include <iostream>
#include <limits>
#include <vector>
#include <functional>

enum
{
    EXIT,
    GET_TABLE,
    GET_ROOT,
    SOLVE_SYSTEM,
};

void print_menu();

int get_command(int &command);

int command_get_table();

int command_get_root();

int command_solve_system();

int command_plot();

#endif // MENU_H

