#ifndef __FILEORTHGAPHICCAMERAREADER_H__
#define __FILEORTHGAPHICCAMERAREADER_H__

#include <fstream>
#include <memory>
#include "BasePerspectiveCameraReader.h"


class FilePerspectiveCameraReader : public BasePerspectiveCameraReader
{
public:
    FilePerspectiveCameraReader();
    FilePerspectiveCameraReader(const std::string &filename)
        :filename(filename){};

    FilePerspectiveCameraReader(const std::shared_ptr<std::ifstream> &file);

    virtual void open() override;
    virtual void close() override;

    virtual Point readPoint() override;
    virtual int readSize() override;

    static std::string _tag;
    std::shared_ptr<std::ifstream> file() const;
    void setFile(const std::shared_ptr<std::ifstream> &newFile);

private:
    std::shared_ptr<std::ifstream> _file;
    std::string filename;

};


#endif // __FILEORTHGAPHICCAMERAREADER_H__
