#ifndef __SET_EXCEPTION_H__
#define __SET_EXCEPTION_H__
#include "set_exception.h"
ErrorSetIndex::ErrorSetIndex(const char *filename,
                             const char *classname,
                             int line,
                             const char *time,
                             int index,
                             const char *info)
{
    this->index = index;
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

ErrorSetWrongAllocSize::ErrorSetWrongAllocSize(const char *filename,
                                               const char *classname,
                                               int line,
                                               const char *time,
                                               int len,
                                               const char *info)
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

#endif // __SET_EXCEPTION_H__