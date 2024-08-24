#ifndef CAMERALOADMODERATORCREATOR_H
#define CAMERALOADMODERATORCREATOR_H

#include "CameraLoadModerator.h"
#include "BasePerspectiveCameraBuildDirector.h"

class CameraLoadModeratorCreator
{
public:
    std::shared_ptr<CameraLoadModerator> createModerator();

private:
    void createInstance();

    std::shared_ptr<CameraLoadModerator> _moderator;
};


#endif // CAMERALOADMODERATORCREATOR_H
