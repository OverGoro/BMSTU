#ifndef ObjCARCASSMODELREADER_H
#define ObjCARCASSMODELREADER_H

#include <fstream>
#include <memory>
#include "BaseCarcasModelReader.h"


class ObjCarcassModelReader : public BaseCarcassModelReader
{
public:
    ObjCarcassModelReader();
    ObjCarcassModelReader(const std::string &Objname)
        :_stream(std::make_shared<std::ifstream>()), _filename(Objname){};
    ObjCarcassModelReader(const std::shared_ptr<std::ifstream> &Obj);

    virtual void open() override;
    virtual void close() override;

    virtual Point readPoint() override;
    virtual Edge readEdge(const int &pointNum) override;
    virtual Vector<Point> readPointes() override;
    virtual Vector<Edge> readEdges(const int &pointNum) override;

    static std::string _tag;
private:
    std::shared_ptr<std::ifstream> _stream;
    std::string _filename;
};

#endif // ObjCARCASSMODELREADER_H
