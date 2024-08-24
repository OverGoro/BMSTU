#include "ModelLoadModerator.h"

ModelLoadModerator::ModelLoadModerator(std::shared_ptr<BaseModelBuildDirector> director)
    : _director(director)
{
}

std::shared_ptr<BaseObject> ModelLoadModerator::load(std::string &fileName)
{
    CarcasModelReaderSolution CMreaderFactory;
    auto reader = CMreaderFactory.createReader(fileName);
    auto builder = std::make_shared<CarcasModelBuilder>(reader);
    return _director->create(builder);
}
