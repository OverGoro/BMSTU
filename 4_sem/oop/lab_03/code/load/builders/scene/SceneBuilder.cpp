#include "SceneBuilder.h"
#include "FileCarcasModelBuildDirector.h"
#include "FilePerspectiveCameraBuildDirector.h"
#include "FilePerspectiveCameraReader.h"
#include "ModelLoadModeratorCreator.h"
#include "ModeratorSolution.h"
#include "PerspectiveCameraBuilder.h"

SceneBuilder::SceneBuilder(std::shared_ptr<FileCarcassModelReader> reader)
{
    _reader = reader;
}

void SceneBuilder::build()
{
    _scene = std::make_shared<Scene>();
    _reader->open();
}

void SceneBuilder::buildModel()
{
    if (!isBuild()) {build();}
    auto model_builder = std::make_shared<CarcasModelBuilder>(std::make_shared<FileCarcassModelReader>(_reader->file()));
    _scene->addObject(FileModelBuildDirector().create(model_builder));
}

void SceneBuilder::buildModels()
{
    if (!isBuild()) {build();}
    // std::size_t size = _reader->readCount();
    // for (std::size_t i = 0; i < size; i++)
    // {
    //     buildModel();
    // }
}

void SceneBuilder::buildCamera()
{
    if (!isBuild()) {build();}
    auto camera_builder = std::make_shared<PerspectiveCameraBuilder>();
    _scene->addObject(FileCameraBuildDirector().create(camera_builder));

}

void SceneBuilder::buildCameras()
{
    if (!isBuild()) {build();}
    // std::size_t size = _reader->readCount();
    // for (std::size_t i = 0; i < size; i++)
    // {
    //     buildCamera();
    // }
}


bool SceneBuilder::isBuild() const
{
    return nullptr != _scene;
}


std::shared_ptr<Scene> SceneBuilder::get()
{
    if (!isBuild()) {build();}
    _reader->close();
    return _scene;
}
