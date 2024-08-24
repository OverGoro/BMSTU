#ifndef ObjPolygonMODELREADER_H
#define ObjPolygonMODELREADER_H

#include <fstream>
#include <memory>
#include "basepolygonmodelreader.h"


class ObjPolygonModelReader : public BasePolygonModelReader
{
public:
    ObjPolygonModelReader();
    ObjPolygonModelReader(const std::string &Objname)
        :_stream(std::make_shared<std::ifstream>()), _filename(Objname){};
    ObjPolygonModelReader(const std::shared_ptr<std::ifstream> &Obj);

    virtual void open() override;
    virtual void close() override;

    virtual Polygon readPolygon() override;
    virtual Vector<Polygon> readPolygons() override;

    static std::string _tag;
private:
    std::shared_ptr<std::ifstream> _stream;
    std::string _filename;
};

#endif // ObjPolygonMODELREADER_H
