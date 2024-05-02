#ifndef __BASE_EXCEPTION_HPP__
#define __BASE_EXCEPTION_HPP__
#include "base_exception.h"

BaseException::BaseException(const char *msg) noexcept
{
    strcpy(err_info, msg);
}

BaseException::BaseException(const char *filename,
                             const char *classname,
                             int line,
                             const char *time,
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
    strcat(err_info, "Time: ");
    strcat(err_info, time);
    strcat(err_info, "Info: ");
    strcat(err_info, info);
    strcat(err_info, "\n");
}

const char *BaseException::what() const noexcept
{
    return err_info;
}

#endif // __BASE_EXCEPTION_H__