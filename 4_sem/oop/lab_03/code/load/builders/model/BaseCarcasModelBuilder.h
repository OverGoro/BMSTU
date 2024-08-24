#ifndef BASEMODELBUILDER_H
#define BASEMODELBUILDER_H


#include "CarcasData.h"
#include "CarcasModel.h"
#include "FileCarcasModelReader.h"
#include "BaseBuilder.h"

class BaseCarcasModelBuilder : public BaseBuilder
{
public:
    BaseCarcasModelBuilder() = default;
    explicit BaseCarcasModelBuilder(std::shared_ptr<FileCarcassModelReader> &reader);
    virtual ~BaseCarcasModelBuilder() = default;

    virtual void build() override = 0;
    virtual void buildPoints() = 0;
    virtual void buildEdges() = 0;
    virtual void buildPoint() = 0;
    virtual void buildEdge() = 0;
    virtual bool isBuild() const override = 0;

    virtual std::shared_ptr<CarcasModel> get() = 0;

protected:
    std::shared_ptr<BaseCarcassModelReader> _reader;
    std::shared_ptr<CarcasData> _model;

};

#endif // BASEMODELBUILDER_H
