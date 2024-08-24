#include "polygonmodelbuilddirector.h"


std::shared_ptr<PolygonModel> PolygonModelBuildDirector::create(std::shared_ptr<PolygonModelBuilder> builder)
{
    builder->build();
    builder->buildPolygons();
    return builder->get();
}
