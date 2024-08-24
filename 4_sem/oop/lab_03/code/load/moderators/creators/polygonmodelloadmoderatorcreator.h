#ifndef PolygonModelLOADMODERATORCREATOR_H
#define PolygonModelLOADMODERATORCREATOR_H

#include "polygonmodelloadmoderator.h"
#include <memory>
class PolygonModelLoadModeratorCreator
{
public:
    std::shared_ptr<PolygonModelLoadModerator> createModerator();

private:
    void createInstance();

    std::shared_ptr<PolygonModelLoadModerator> _moderator;
};

#endif // PolygonModelLOADMODERATORCREATOR_H
