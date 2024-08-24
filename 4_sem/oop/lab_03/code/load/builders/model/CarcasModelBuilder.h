#ifndef MODELBUILDER_H
#define MODELBUILDER_H

#include "BaseCarcasModelBuilder.h"

#include "CarcasModel.h"
class CarcasModelBuilder : public BaseCarcasModelBuilder
{
public:
    CarcasModelBuilder() = default;
    explicit CarcasModelBuilder(std::shared_ptr<BaseCarcassModelReader> reader);
    ~CarcasModelBuilder() = default;

    void build() override;
    void buildPoints() override;
    void buildEdges() override;
    void buildPoint() override;
    void buildEdge() override;
    bool isBuild() const override;

    std::shared_ptr<CarcasModel> get() override;
};

#endif //BUILDER_MODEL_H
