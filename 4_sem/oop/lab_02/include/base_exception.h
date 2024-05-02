#ifndef _BASE_EXCEPTION
#define _BASE_EXCEPTION

#include <exception>
#include <string.h>


class BaseException : public std::exception
{
protected:
    char err_info[512];


public:
    BaseException() noexcept = default;
    explicit BaseException(const char *msg) noexcept;
    BaseException(const char *filename,
                  const char *classname,
                  int line,
                  const char *time,
                  const char *info = "ERROR") noexcept;
    virtual ~BaseException() = default;

    const char *what() const noexcept override;
};

#include "base_exception.hpp"

#endif
