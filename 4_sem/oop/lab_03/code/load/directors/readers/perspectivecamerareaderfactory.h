#ifndef PerspectiveCAMERAREADERFACTORY_H
#define PerspectiveCAMERAREADERFACTORY_H

#include <memory>
#include <string>
#include <stdexcept>
#include <unordered_map>
#include <functional>
#include "Exceptions.h"
#include "BasePerspectiveCameraReader.h"
#include "FilePerspectiveCameraReader.h"

class PerspectiveCameraReaderSolution
{
public:
    PerspectiveCameraReaderSolution();

    std::shared_ptr<BasePerspectiveCameraReader> createReader(const std::string& fileName);

private:
    std::string getFileExtension(const std::string& fileName);

    using ReaderCreator = std::function<std::shared_ptr<BasePerspectiveCameraReader>(const std::string &fileName)>;

    std::unordered_map<std::string, ReaderCreator> readerCreators;
};

class BasePerspectiveCameraReaderCreator
{
public:
    virtual std::shared_ptr<BasePerspectiveCameraReader> create(const std::string &filename) = 0;
};

class FilePerspectiveCameraReaderCreator
{
public:
    virtual std::shared_ptr<BasePerspectiveCameraReader> create(const std::string &filename);
};

#endif // PerspectiveCAMERAREADERFACTORY_H
