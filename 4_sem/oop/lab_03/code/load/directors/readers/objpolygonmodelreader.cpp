#include "objpolygonmodelreader.h".h"
#include "Exceptions.h"
#include <sstream>
std::string ObjPolygonModelReader::_tag = "obj";

ObjPolygonModelReader::ObjPolygonModelReader()
{
    _stream = std::make_shared<std::ifstream>();
}

ObjPolygonModelReader::ObjPolygonModelReader(const std::shared_ptr<std::ifstream> &Obj)
{
    _stream = Obj;
}

void ObjPolygonModelReader::open()
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

void ObjPolygonModelReader::close()
{
    if (!_stream)
    {
        std::string msg = "Error : Obj open";
        throw SourceException(msg);
    }

    _stream->close();
}

Polygon ObjPolygonModelReader::readPolygon() {
    std::string line;
    Vector<Point> points;
    while (std::getline(*_stream, line)) {
        if (line.substr(0, 2) == "f ") {
            std::istringstream s(line.substr(2));
            std::vector<int> indices;
            std::string vertex;

            while (s >> vertex) {
                size_t pos = vertex.find("//");
                if (pos != std::string::npos) {
                    vertex = vertex.substr(0, pos); // Ignore everything after the first //
                } else {
                    pos = vertex.find('/');
                    if (pos != std::string::npos) {
                        vertex = vertex.substr(0, pos); // Ignore everything after the first /
                    }
                }

                int index = std::stoi(vertex) - 1; // OBJ indices are 1-based
                indices.push_back(index);
            }

            if (indices.size() < 3) {
                throw std::runtime_error("Polygon has less than 3 vertices");
            }

            Point p1 = points[indices[0]];
            Point p2 = points[indices[1]];
            Point p3 = points[indices[2]];
            return Polygon(p1, p2, p3);
        }
    }

    throw std::runtime_error("No polygon found");
}

Vector<Polygon> ObjPolygonModelReader::readPolygons()
{
    Vector<Polygon> polygons;
    Vector<Point> points;

    std::string line;
    close();
    open();

    // Считывание всех вершин из файла
    while (std::getline(*_stream, line)) {
        if (line.substr(0, 2) == "v ") {
            std::istringstream s(line.substr(2));
            double x, y, z;
            s >> x >> y >> z;
            points.emplace_back(x, y, z);
        }
    }

    // Возвращаемся в начало файла для считывания полигонов
    _stream->clear();
    _stream->seekg(0, std::ios::beg);

    // Считывание полигонов
    while (std::getline(*_stream, line)) {
        if (line.substr(0, 2) == "f ") {
            std::istringstream s(line.substr(2));
            std::vector<int> indices;
            std::string vertex;

            while (s >> vertex) {
                size_t pos = vertex.find("//");
                if (pos != std::string::npos) {
                    vertex = vertex.substr(0, pos); // Ignore everything after the first //
                } else {
                    pos = vertex.find('/');
                    if (pos != std::string::npos) {
                        vertex = vertex.substr(0, pos); // Ignore everything after the first /
                    }
                }

                int index = std::stoi(vertex) - 1; // OBJ indices are 1-based
                indices.push_back(index);
            }

            if (indices.size() != 3) {
                std::string msg = "face does not have exactly 3 vertices";
                throw SourceException(msg);
            }

            polygons.emplace_back(points[indices[0]], points[indices[1]], points[indices[2]]);
        }
    }

    return polygons;
}
