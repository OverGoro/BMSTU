#ifndef BASECARCASSMODELREADER_H
#define BASECARCASSMODELREADER_H

#include <string>
#include <vector>

#include "Point.h"
#include "Edge.h"
#include <VectorContainer.h>


class BaseCarcassModelReader
{
public:
    BaseCarcassModelReader() = default;
    virtual ~BaseCarcassModelReader() = default;

    virtual void open() = 0;
    virtual void close() = 0;

    virtual Point readPoint() = 0;
    virtual Edge readEdge(const int &pointNum) = 0;
    virtual Vector<Point> readPointes() = 0;
    virtual Vector<Edge> readEdges(const int &pointNum) = 0;
};

#endif // BASECARCASSMODELREADER_H
