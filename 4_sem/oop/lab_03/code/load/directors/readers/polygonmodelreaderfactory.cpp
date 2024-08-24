#include "polygonmodelreaderfactory.h"
#include "objpolygonmodelreader.h"
#include "filepolygonmodelreader.h"
#include <cstddef>
PolygonModelReaderSolution::PolygonModelReaderSolution()
{
    readerCreators[FilePolygonModelReader::_tag] = [](const std::string &fn) -> std::shared_ptr<BasePolygonModelReader>
    {
        return FilePolygonModelReaderCreator().create(fn);
    };
    readerCreators[ObjPolygonModelReader::_tag] = [](const std::string &fn) -> std::shared_ptr<BasePolygonModelReader>
    {
        return ObjPolygonModelReaderCreator().create(fn);
    };
}

std::shared_ptr<BasePolygonModelReader> PolygonModelReaderSolution::createReader(const std::string& fileName)
{
    std::string extension = getFileExtension(fileName);
    auto it = readerCreators.find(extension);
    if (it != readerCreators.end())
        return it->second(fileName);
    else {
        std::string msg = "Unsupported file extension";
        throw SourceException(msg);
    }
}

std::string PolygonModelReaderSolution::getFileExtension(const std::string& fileName)
{
    std::size_t pos = fileName.find_last_of('.');
    if (pos != std::string::npos)
        return fileName.substr(pos + 1);
    return "";
}

std::shared_ptr<BasePolygonModelReader> FilePolygonModelReaderCreator::create(const std::string &filename)
{
    return std::make_shared<FilePolygonModelReader>(filename);
}

std::shared_ptr<BasePolygonModelReader> ObjPolygonModelReaderCreator::create(const std::string &filename)
{
    return std::make_shared<ObjPolygonModelReader>(filename);
}
