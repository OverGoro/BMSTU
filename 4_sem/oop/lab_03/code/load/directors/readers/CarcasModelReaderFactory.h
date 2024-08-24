#ifndef CARCASSMODELREADERFACTORY_H
#define CARCASSMODELREADERFACTORY_H

#include <memory>
#include <string>
#include <stdexcept>
#include <unordered_map>
#include <functional>
#include "Exceptions.h"
#include "BaseCarcasModelReader.h"
#include "FileCarcasModelReader.h"

class CarcasModelReaderSolution
{
public:
    CarcasModelReaderSolution();

    std::shared_ptr<BaseCarcassModelReader> createReader(const std::string& fileName);

private:
    std::string getFileExtension(const std::string& fileName);

    using ReaderCreator = std::function<std::shared_ptr<BaseCarcassModelReader>(const std::string &fileName)>;

    std::unordered_map<std::string, ReaderCreator> readerCreators;
};

class BaseCarcasModelReaderCreator
{
public:
    virtual std::shared_ptr<BaseCarcassModelReader> create(const std::string &filename) = 0;
};

class FileCarcasModelReaderCreator : BaseCarcasModelReaderCreator
{
public:
    virtual std::shared_ptr<BaseCarcassModelReader> create(const std::string &filename) override;
};

class ObjCarcasModelReaderCreator : BaseCarcasModelReaderCreator
{
public:
    virtual std::shared_ptr<BaseCarcassModelReader> create(const std::string &filename) override;
};



#endif // CARCASSMODELREADERFACTORY_H
