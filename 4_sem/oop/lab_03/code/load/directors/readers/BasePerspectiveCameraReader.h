#ifndef BASECAMERAREADERREADER_H
#define BASECAMERAREADERREADER_H

#include <string>
#include <vector>

#include "Point.h"


class BasePerspectiveCameraReader
{
public:
    BasePerspectiveCameraReader() = default;
    ~BasePerspectiveCameraReader() = default;
    virtual void open() = 0;
    virtual void close() = 0;
    virtual int readSize() = 0;
    virtual Point readPoint() = 0;
};

#endif // BASECAMERAREADERREADER_H
