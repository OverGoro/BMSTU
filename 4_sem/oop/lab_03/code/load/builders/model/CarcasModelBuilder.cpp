#include "CarcasModelBuilder.h"

CarcasModelBuilder::CarcasModelBuilder(std::shared_ptr<BaseCarcassModelReader> reader)
{
    _reader = reader;
}

void CarcasModelBuilder::build()
{
    _model = std::make_shared<CarcasData>();
    _reader->open();
}

void CarcasModelBuilder::buildPoints()
{
    if (!isBuild()) { build(); }
    auto points = _reader->readPointes();
    for (auto p : points)
    {
        _model->addPoint(p);
    }
}


void CarcasModelBuilder::buildPoint()
{
    if (!isBuild()) { build(); }

    _model->addPoint(_reader->readPoint());
}

void CarcasModelBuilder::buildEdges()
{
    if (!isBuild()) { build(); }
    auto edges = _reader->readEdges(_model->getPoints().size());
    for (auto e : edges)
    {
        _model->addEdge(e);
    }
}

void CarcasModelBuilder::buildEdge()
{
    if (!isBuild()) { build(); }

    _model->addEdge(_reader->readEdge(_model->getPoints().size()));
}


bool CarcasModelBuilder::isBuild() const
{
    return nullptr != _model;
}

std::shared_ptr<CarcasModel> CarcasModelBuilder::get()
{
    return std::make_shared<CarcasModel>(CarcasModel(*_model));
}
