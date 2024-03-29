#ifndef ERROR_H
#define ERROR_H

#include <iostream>

enum errors
{
    OK,
    ERR_IO,
    ERR_FILE,
    ERR_RANGE,
    ERR_UNKNOWN_COMMAND
};

void handle_rc(int rc);

#endif // ERROR_H

