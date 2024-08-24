#include "FileSceneBuildDirector.h"
#include "Exceptions.h"
#include "CarcasModelBuilder.h"
#include <FileCarcasModelBuildDirector.h>
#include <PerspectiveCameraBuilder.h>
#include <FilePerspectiveCameraBuildDirector.h>
FileSceneBuildDirector::FileSceneBuildDirector() {}

std::shared_ptr<Scene> FileSceneBuildDirector::create(std::shared_ptr<SceneBuilder> builder)
{
    builder->build();

    builder->buildModels();
    builder->buildCameras();

    return builder->get();
}
