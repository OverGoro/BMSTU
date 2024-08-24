#include "Exceptions.h"
#include <cstring>
#include <stdio.h>
BaseException::BaseException(const char *msg) noexcept
{
    strcpy(err_info, msg);
}

BaseException::BaseException(const char *filename,
                             const char *classname,
                             int line,
                             const char *info) noexcept
{
    strcpy(err_info, "File: ");
    strcat(err_info, filename);
    strcat(err_info, "\n");
    strcat(err_info, "Class: ");
    strcat(err_info, classname);
    strcat(err_info, "\n");
    strcat(err_info, "Line: ");
    sprintf(err_info + strlen(err_info), "%d", line);
    strcat(err_info, "\n");
    strcat(err_info, "Info: ");
    strcat(err_info, info);
    strcat(err_info, "\n");
}

const char *BaseException::what() const noexcept
{
    return err_info;
}