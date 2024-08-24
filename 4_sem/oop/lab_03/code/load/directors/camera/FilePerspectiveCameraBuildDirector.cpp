#include "FilePerspectiveCameraBuildDirector.h"
#include "Exceptions.h"

FileCameraBuildDirector::FileCameraBuildDirector() {}

std::shared_ptr<BaseCamera> FileCameraBuildDirector::create(std::shared_ptr<BasePerspectiveCameraBuilder> builder)
{
    builder->build();
    builder->buildPosition();
    builder->buildDirection();
    builder->buildUp();
    builder->buildXFOV();
    builder->buildYFOV();

    return builder->get();
}
