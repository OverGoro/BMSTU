#include "strio.h"

int input_string(char *buff, size_t buff_size)
{
    if (fgets(buff, buff_size, stdin) != buff)
    {
        return ERR_IO;
    }
    char *p = strrchr(buff, '\n');
    if (p != NULL)
    {
        *p = 0;
        return OK;
    }
    return ERR_TOO_LONG_INPUT;
}
