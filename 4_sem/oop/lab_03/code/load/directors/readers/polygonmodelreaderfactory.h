#ifndef PolygonMODELREADERFACTORY_H
#define PolygonMODELREADERFACTORY_H

#include <memory>
#include <string>
#include <stdexcept>
#include <unordered_map>
#include <functional>
#include "Exceptions.h"
#include "basepolygonmodelreader.h"

class PolygonModelReaderSolution
{
public:
    PolygonModelReaderSolution();

    std::shared_ptr<BasePolygonModelReader> createReader(const std::string& fileName);

private:
    std::string getFileExtension(const std::string& fileName);

    using ReaderCreator = std::function<std::shared_ptr<BasePolygonModelReader>(const std::string &fileName)>;

    std::unordered_map<std::string, ReaderCreator> readerCreators;
};

class BasePolygonModelReaderCreator
{
public:
    virtual std::shared_ptr<BasePolygonModelReader> create(const std::string &filename) = 0;
};

class FilePolygonModelReaderCreator : BasePolygonModelReaderCreator
{
public:
    virtual std::shared_ptr<BasePolygonModelReader> create(const std::string &filename) override;
};

class ObjPolygonModelReaderCreator : BasePolygonModelReaderCreator
{
public:
    virtual std::shared_ptr<BasePolygonModelReader> create(const std::string &filename) override;
};



#endif // PolygonMODELREADERFACTORY_H
