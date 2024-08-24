#include "polygonmodelloadmoderator.h"

PolygonModelLoadModerator::PolygonModelLoadModerator(std::shared_ptr<PolygonModelBuildDirector> director)
    : _director(director)
{
}

std::shared_ptr<BaseObject> PolygonModelLoadModerator::load(std::string &fileName)
{
    PolygonModelReaderSolution CMreaderFactory;
    auto reader = CMreaderFactory.createReader(fileName);
    auto builder = std::make_shared<PolygonModelBuilder>(reader);
    return _director->create(builder);
}
