#include "polygonmodelbuilder.h"

PolygonModelBuilder::PolygonModelBuilder(std::shared_ptr<BasePolygonModelReader> reader)
{
    _reader = reader;
}

void PolygonModelBuilder::build()
{
    _model = std::make_shared<PolygonData>();
    _reader->open();
}

void PolygonModelBuilder::buildPolygons()
{
    if (!isBuild()) { build(); }

    _model->addPolygons(_reader->readPolygons());
}


bool PolygonModelBuilder::isBuild() const
{
    return nullptr != _model;
}

std::shared_ptr<PolygonModel> PolygonModelBuilder::get()
{
    return std::make_shared<PolygonModel>(PolygonModel(*_model));
}
