#ifndef _SET_EXCEPTION_HPP
#define _SET_EXCEPTION_HPP

#include "base_exception.h"

#include <exception>
#include <string>

class ErrorSetIndex : public BaseException
{
protected:
    int index;

public:
    ErrorSetIndex(const char * filename,
                  const char * classname,
                  int line,
                  const char *time,
                  int index,
                  const char * info = "Index out of range");
};

class ErrorSetEmpty : public BaseException
{
public:
    ErrorSetEmpty(const char * filename,
                  const char * classname,
                  int line,
                  const char *time,
                  const char * info = "Set is empty") : BaseException(filename, classname, line, time, info){};
};

class ErrorSetWrongAllocSize : public BaseException
{
public:
    ErrorSetWrongAllocSize(const char * filename,
                           const char * classname,
                           int line,
                           const char *time,
                           int len,
                           const char * info = "Wrong set size");
};

class ErrorSetAllocate : public BaseException
{
public:
    ErrorSetAllocate(const char * filename,
                     const char * classname,
                     int line,
                     const char *time,
                     const char * info = "Cannot allocate memory") : BaseException(filename, classname, line, time, info){};
};

class ErrorSetNoElement : public BaseException
{
public:
    ErrorSetNoElement(const char * filename,
                      const char * classname,
                      int line,
                      const char *time,
                      const char * info = "No such element in set") : BaseException(filename, classname, line, time, info){};
};

class ErrorSetDivisionByZero : public BaseException
{
public:
    ErrorSetDivisionByZero(const char * filename,
                           const char * classname,
                           int line,
                           const char *time,
                           const char * info = "Division by zero") : BaseException(filename, classname, line, time, info){};
};

#include "set_exception.hpp"

#endif
