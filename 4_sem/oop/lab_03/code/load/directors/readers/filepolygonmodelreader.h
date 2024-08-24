#ifndef FilePolygonModelReader_H
#define FilePolygonModelReader_H

#include <fstream>
#include <memory>
#include "basepolygonmodelreader.h"


class FilePolygonModelReader : public BasePolygonModelReader
{
public:
    FilePolygonModelReader();
    FilePolygonModelReader(const std::string &filename)
        :_file(std::make_shared<std::ifstream>()), filename(filename){};
    FilePolygonModelReader(const std::shared_ptr<std::ifstream> &file);

    virtual void open() override;
    virtual void close() override;

    virtual Polygon readPolygon() override;
    virtual Vector<Polygon> readPolygons() override;

    static std::string _tag;
    std::shared_ptr<std::ifstream> file() const;
    void setFile(const std::shared_ptr<std::ifstream> &newFile);

private:
    std::size_t readCount();
    std::shared_ptr<std::ifstream> _file;
    std::string filename;
};

#endif // FilePolygonModelReader_H
