#include "perspectivecamerareaderfactory.h"
#include <cstddef>
PerspectiveCameraReaderSolution::PerspectiveCameraReaderSolution()
{
    readerCreators[FilePerspectiveCameraReader::_tag] = [](const std::string &fn) -> std::shared_ptr<BasePerspectiveCameraReader> {
        return FilePerspectiveCameraReaderCreator().create(fn);
    };
}

std::shared_ptr<BasePerspectiveCameraReader> PerspectiveCameraReaderSolution::createReader(const std::string& fileName)
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

std::string PerspectiveCameraReaderSolution::getFileExtension(const std::string& fileName)
{
    std::size_t pos = fileName.find_last_of('.');
    if (pos != std::string::npos)
        return fileName.substr(pos + 1);
    return "";
}

std::shared_ptr<BasePerspectiveCameraReader> FilePerspectiveCameraReaderCreator::create(const std::string &filename)
{
    return std::make_shared<FilePerspectiveCameraReader>(filename);
}
