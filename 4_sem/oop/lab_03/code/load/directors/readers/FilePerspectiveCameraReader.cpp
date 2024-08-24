#include "FilePerspectiveCameraReader.h"
#include "Exceptions.h"

std::string FilePerspectiveCameraReader::_tag = "txt";

FilePerspectiveCameraReader::FilePerspectiveCameraReader()
{
    _file = std::make_shared<std::ifstream>();
}

FilePerspectiveCameraReader::FilePerspectiveCameraReader(const std::shared_ptr<std::ifstream> &file)
{
    _file = file;
}

void FilePerspectiveCameraReader::open()
{
    if (!_file)
    {
        std::string msg = "Error : File open";
        throw SourceException(msg);
    }

    _file->open(filename);

    if (!_file)
    {
        std::string msg = "Error : File open";
        throw SourceException(msg);
    }
}

void FilePerspectiveCameraReader::close()
{
    if (!_file)
    {
        std::string msg = "Error : File open";
        throw SourceException(msg);
    }

    _file->close();
}

int FilePerspectiveCameraReader::readSize()
{
    int count;

    *_file >> count;

    return count;
}

std::shared_ptr<std::ifstream> FilePerspectiveCameraReader::file() const
{
    return _file;
}

void FilePerspectiveCameraReader::setFile(const std::shared_ptr<std::ifstream> &newFile)
{
    _file = newFile;
}

Point FilePerspectiveCameraReader::readPoint()
{
    double x, y, z;

    *_file >> x >> y >> z;

    return Point(x, y, z);
}
