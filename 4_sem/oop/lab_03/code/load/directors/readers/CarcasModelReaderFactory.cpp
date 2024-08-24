#include "CarcasModelReaderFactory.h"
#include "objcarcasmodelreader.h"
#include <cstddef>
CarcasModelReaderSolution::CarcasModelReaderSolution()
{
    readerCreators[FileCarcassModelReader::_tag] = [](const std::string &fn) -> std::shared_ptr<BaseCarcassModelReader>
    {
        return FileCarcasModelReaderCreator().create(fn);
    };
    readerCreators[ObjCarcassModelReader::_tag] = [](const std::string &fn) -> std::shared_ptr<BaseCarcassModelReader>
    {
        return ObjCarcasModelReaderCreator().create(fn);
    };
}

std::shared_ptr<BaseCarcassModelReader> CarcasModelReaderSolution::createReader(const std::string& fileName)
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

std::string CarcasModelReaderSolution::getFileExtension(const std::string& fileName)
{
    std::size_t pos = fileName.find_last_of('.');
    if (pos != std::string::npos)
        return fileName.substr(pos + 1);
    return "";
}

std::shared_ptr<BaseCarcassModelReader> FileCarcasModelReaderCreator::create(const std::string &filename)
{
    return std::make_shared<FileCarcassModelReader>(filename);
}

std::shared_ptr<BaseCarcassModelReader> ObjCarcasModelReaderCreator::create(const std::string &filename)
{
    return std::make_shared<ObjCarcassModelReader>(filename);
}
