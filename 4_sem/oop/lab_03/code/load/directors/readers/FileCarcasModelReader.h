#ifndef FILECARCASSMODELREADER_H
#define FILECARCASSMODELREADER_H

#include <fstream>
#include <memory>
#include "BaseCarcasModelReader.h"


class FileCarcassModelReader : public BaseCarcassModelReader
{
public:
    FileCarcassModelReader();
    FileCarcassModelReader(const std::string &filename)
        :_file(std::make_shared<std::ifstream>()), filename(filename){};
    FileCarcassModelReader(const std::shared_ptr<std::ifstream> &file);

    virtual void open() override;
    virtual void close() override;

    virtual Point readPoint() override;
    virtual Edge readEdge(const int &pointNum) override;
    virtual Vector<Point> readPointes() override;
    virtual Vector<Edge> readEdges(const int &pointNum) override;

    static std::string _tag;
    std::shared_ptr<std::ifstream> file() const;
    void setFile(const std::shared_ptr<std::ifstream> &newFile);

private:
    std::size_t readCount();
    std::shared_ptr<std::ifstream> _file;
    std::string filename;
};

#endif // FILECARCASSMODELREADER_H
