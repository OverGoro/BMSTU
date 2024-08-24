#include "objcarcasmodelreader.h"
#include "Exceptions.h"
#include <sstream>
std::string ObjCarcassModelReader::_tag = "obj";

ObjCarcassModelReader::ObjCarcassModelReader()
{
    _stream = std::make_shared<std::ifstream>();
}

ObjCarcassModelReader::ObjCarcassModelReader(const std::shared_ptr<std::ifstream> &Obj)
{
    _stream = Obj;
}

void ObjCarcassModelReader::open()
{
    if (!_stream)
    {
        std::string msg = "Error : Obj open";
        throw SourceException(msg);
    }

    _stream->open(_filename);

    if (!_stream)
    {
        std::string msg = "Error : Obj open";
        throw SourceException(msg);
    }
}

void ObjCarcassModelReader::close()
{
    if (!_stream)
    {
        std::string msg = "Error : Obj open";
        throw SourceException(msg);
    }

    _stream->close();
}

Point ObjCarcassModelReader::readPoint()
{
    std::string line;

    if (std::getline(*_stream, line))
    {
        if (line.substr(0, 2) == "v ")
        {
            std::istringstream s(line.substr(2));
            double x, y, z;
            s >> x >> y >> z;
            return(Point(x, y, z));
        }
    }
    throw SourceException("No points in file");
}

Vector<Point> ObjCarcassModelReader::readPointes()
{
    Vector<Point> vertices;
    std::string line;
    close();
    open();

    while (std::getline(*_stream, line))
    {
        if (line.substr(0, 2) == "v ")
        {
            std::istringstream s(line.substr(2));
            double x, y, z;
            s >> x >> y >> z;
            vertices.push_back(Point(x, y, z));
        }
    }

    if (vertices.empty())
    {
        std::string msg = "no vertices found";
        throw SourceException(msg);
    }

    return vertices;
}


Edge ObjCarcassModelReader::readEdge(const int &pointNum)
{
    std::string line;

    while (std::getline(*_stream, line))
    {
        if (line.substr(0, 2) == "f ")
        {
            std::istringstream s(line.substr(2));
            std::vector<int> indices;
            int index;
            while (s >> index)
            {
                indices.push_back(index - 1); // OBJ indices are 1-based
            }

            if (indices.size() < 2)
            {
                std::string msg = "face has less than 2 vertices";
                throw SourceException(msg);
            }

            for (size_t i = 0; i < indices.size(); ++i)
            {
                for (size_t j = i + 1; j < indices.size(); ++j)
                {
                    if (indices[i] >= pointNum || indices[j] >= pointNum)
                        throw SourceException("Edge index out of range");
                    return(Edge(indices[i], indices[j]));
                }
            }
        }
    }
    throw SourceException("No edges in file");

}
Vector<Edge> ObjCarcassModelReader::readEdges(const int &pointNum)
{
    Vector<Edge> edges;
    std::string line;
    close();
    open();
    while (std::getline(*_stream, line))
    {
        if (line.substr(0, 2) == "f ")
        {
            std::istringstream s(line.substr(2));
            std::vector<int> indices;
            std::string vertex;

            while (s >> vertex)
            {
                size_t pos = vertex.find("//");
                if (pos != std::string::npos)
                {
                    vertex = vertex.substr(0, pos); // Ignore everything after the first //
                }
                else
                {
                    pos = vertex.find('/');
                    if (pos != std::string::npos)
                    {
                        vertex = vertex.substr(0, pos); // Ignore everything after the first /
                    }
                }

                int index = std::stoi(vertex) - 1; // OBJ indices are 1-based
                indices.push_back(index);
            }

            if (indices.size() < 2)
            {
                std::string msg = "face has less than 2 vertices";
                throw SourceException(msg);
            }

            for (size_t i = 0; i < indices.size(); ++i)
            {
                for (size_t j = i + 1; j < indices.size(); ++j)
                {
                    if (indices[i] >= pointNum || indices[j] >= pointNum)
                        throw SourceException("Edge index out of range");
                    edges.push_back(Edge(indices[i], indices[j]));
                }
            }
        }
    }

    if (edges.empty())
    {
        std::string msg = "no edges found";
        throw SourceException(msg);
    }

    return edges;
}
