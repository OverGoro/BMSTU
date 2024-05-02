#include "error.h"

int error_get_file_error()
{
    int rc = ERR_FILE;
    if (errno == ENOENT)
        rc = ERR_FILE_NOT_EXIST;
    else if (errno == EACCES)
        rc = ERR_FILE_ACCESS;
    else
        rc = ERR_FILE;
    return rc;
};
