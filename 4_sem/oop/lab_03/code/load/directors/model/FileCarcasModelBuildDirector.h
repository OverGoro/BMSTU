#ifndef FILEMODELBUILDDIRECTOR_H
#define FILEMODELBUILDDIRECTOR_H

#include "BaseCarcasModelBuildDirector.h"
#include "CarcasModel.h"
#include <memory>

class FileModelBuildDirector : public BaseModelBuildDirector
{
public:
    FileModelBuildDirector();
    ~FileModelBuildDirector() override = default;

    std::shared_ptr<CarcasModel> create(std::shared_ptr<BaseCarcasModelBuilder> builder) override;
};

#endif // FILEMODELBUILDDIRECTOR_H
