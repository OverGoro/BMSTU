#include "polygonmodelloadmoderatorcreator.h"

std::shared_ptr<PolygonModelLoadModerator> PolygonModelLoadModeratorCreator::createModerator()
{
    if (nullptr == _moderator)
        createInstance();

    return _moderator;
}

void PolygonModelLoadModeratorCreator::createInstance()
{
    static std::shared_ptr<PolygonModelLoadModerator> moderator;

    if (!moderator)
    {
        auto director = std::make_shared<PolygonModelBuildDirector>();
        moderator = std::make_shared<PolygonModelLoadModerator>(director);
    }

    _moderator = moderator;
}
