#include "FileCarcasModelReader.h"
#include "Exceptions.h"

std::string FileCarcassModelReader::_tag = "txt";

FileCarcassModelReader::FileCarcassModelReader()
{
    _file = std::make_shared<std::ifstream>();
}

FileCarcassModelReader::FileCarcassModelReader(const std::shared_ptr<std::ifstream> &file)
{
    _file = file;
}

void FileCarcassModelReader::open()
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

void FileCarcassModelReader::close()
{
    if (!_file)
    {
        std::string msg = "Error : File open";
        throw SourceException(msg);
    }

    _file->close();
}

std::size_t FileCarcassModelReader::readCount()
{
    int count;

    *_file >> count;

    return count;
}

Point FileCarcassModelReader::readPoint()
{
    double x, y, z;

    *_file >> x >> y >> z;

    return Point(x, y, z);
}

Edge FileCarcassModelReader::readEdge(const int &pointNum)
{
    int point1Index, point2Index;
    *_file >> point1Index >> point2Index;

    if (point1Index <= 0 or point2Index <= 0 or
        point1Index > pointNum or point2Index > pointNum)
    {
        std::string msg = "wrong edge data";
        throw SourceException(msg);
    }
    return Edge(point1Index - 1, point2Index - 1);
}

Vector<Point> FileCarcassModelReader::readPointes()
{
    Vector<Point> points;

    int pointNum;
    *_file >> pointNum;

    if (pointNum <= 0)
    {
        std::string msg = "wrong point num";
        throw SourceException(msg);
    }

    double x, y, z;

    for (int i = 0; i < pointNum; i++)
    {
       *_file >> x >> y >> z;
       points.push_back(Point(x, y, z));
    }

    return points;
}

Vector<Edge> FileCarcassModelReader::readEdges(const int &pointNum)
{
    Vector<Edge> edges;

    int edgesNum;
    *_file >> edgesNum;

    if (edgesNum <= 0)
    {
        std::string msg = "wrong edges num";
        throw SourceException(msg);
    }


    for (int i = 0; i < edgesNum; i++)
    {
        edges.push_back(readEdge(pointNum));
    }

    return edges;
}

std::shared_ptr<std::ifstream> FileCarcassModelReader::file() const
{
    return _file;
}

void FileCarcassModelReader::setFile(const std::shared_ptr<std::ifstream> &newFile)
{
    _file = newFile;
}
