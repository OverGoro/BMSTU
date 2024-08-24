#include "FileCarcasModelBuildDirector.h"

FileModelBuildDirector::FileModelBuildDirector() {}

std::shared_ptr<CarcasModel> FileModelBuildDirector::create(std::shared_ptr<BaseCarcasModelBuilder> builder)
{
    builder->build();
    builder->buildPoints();
    builder->buildEdges();

    return builder->get();
}
