#ifndef _ITERATOR_EXCEPTION_HPP
#define _ITERATOR_EXCEPTION_HPP

#include "base_exception.h"

class IteratorExpiredPtrException : public BaseException
{
    public:
        IteratorExpiredPtrException(const char * filename,
                                  const char * classname,
                                  int line,
                                  const char *time,
                                  const char * info = "Iterator expired ptr")
        :BaseException(filename, classname, line, time, info){}
};



#endif
