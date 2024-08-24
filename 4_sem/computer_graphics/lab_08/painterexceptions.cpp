#include "painterexceptions.h"
#include <string.h>
#include <string>

BaseException::BaseException(const char *msg) noexcept
{
    strncpy(err_info, msg, sizeof(err_info));
}
const char *BaseException::what() const noexcept
{
    return err_info;
}
