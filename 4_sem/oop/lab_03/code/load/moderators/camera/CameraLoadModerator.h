#ifndef CAMERALOADMODERATOR_H
#define CAMERALOADMODERATOR_H

#include "BaseLoadModerator.h"
#include "BasePerspectiveCameraBuildDirector.h"

class CameraLoadModerator : public BaseLoadModerator
{
public:
    explicit CameraLoadModerator(std::shared_ptr<BaseCameraBuildDirector> director);
    ~CameraLoadModerator() = default;

    std::shared_ptr<BaseObject> load(std::string &fileName) override;

private:
    std::shared_ptr<BasePerspectiveCameraBuilder> _builder;
    std::shared_ptr<BaseCameraBuildDirector> _director;
};

#endif // CAMERALOADMODERATOR_H
