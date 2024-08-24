#ifndef PolygonModelLOADMODERATOR_H
#define PolygonModelLOADMODERATOR_H

#include "../BaseLoadModerator.h"
#include "polygonmodelbuilddirector.h"
#include "polygonmodelreaderfactory.h"

class PolygonModelLoadModerator : public BaseLoadModerator
{
public:
    PolygonModelLoadModerator() = default;
    explicit PolygonModelLoadModerator(std::shared_ptr<PolygonModelBuildDirector> director);

    ~PolygonModelLoadModerator() = default;

    std::shared_ptr<BaseObject> load(std::string &fileName) override;

private:
    std::shared_ptr<PolygonModelBuildDirector> _director;
};

#endif // PolygonModelLOADMODERATOR_H
