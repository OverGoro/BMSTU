#include "filepolygonmodelreader.h"
#include "Exceptions.h"

std::string FilePolygonModelReader::_tag = "txt";

FilePolygonModelReader::FilePolygonModelReader()
{
    _file = std::make_shared<std::ifstream>();
}

FilePolygonModelReader::FilePolygonModelReader(const std::shared_ptr<std::ifstream> &file)
{
    _file = file;
}

void FilePolygonModelReader::open()
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

void FilePolygonModelReader::close()
{
    if (!_file)
    {
        std::string msg = "Error : File open";
        throw SourceException(msg);
    }

    _file->close();
}

Polygon FilePolygonModelReader::readPolygon()
{
    Point p1,p2,p3;
    double x,y,z;
    *_file >> x >> y >> z;
    p1 = {x,y,z};

    *_file >> x >> y >> z;
    p2 = {x,y,z};

    *_file >> x >> y >> z;
    p3 = {x,y,z};

    return Polygon(p1,p2,p3);
}

std::size_t FilePolygonModelReader::readCount()
{
    int count;

    *_file >> count;

    return count;
}

Vector<Polygon> FilePolygonModelReader::readPolygons()
{
    Vector<Polygon> polygons;

    int polygonsNum = readCount();


    for (int i = 0; i < polygonsNum; i++)
    {
        polygons.push_back(readPolygon());
    }

    return polygons;
}

std::shared_ptr<std::ifstream> FilePolygonModelReader::file() const
{
    return _file;
}

void FilePolygonModelReader::setFile(const std::shared_ptr<std::ifstream> &newFile)
{
    _file = newFile;
}
