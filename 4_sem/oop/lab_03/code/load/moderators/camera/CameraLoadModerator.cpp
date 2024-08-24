#include "CameraLoadModerator.h"
#include "Exceptions.h"
#include "FilePerspectiveCameraReader.h"
#include "PerspectiveCameraBuilder.h"


CameraLoadModerator::CameraLoadModerator(std::shared_ptr<BaseCameraBuildDirector> director)
    : _director(std::move(director))
{
    _builder = std::make_shared<PerspectiveCameraBuilder>(PerspectiveCameraBuilder());
}
/*:
    _builder(new PerspectiveCameraBuilder(std::make_shared<FileCarcassModelReader>()))
{
    _director = director;
}*/

std::shared_ptr<BaseObject> CameraLoadModerator::load(std::string &fileName)
{
    std::shared_ptr<BaseCamera> camera_sh_ptr;

    try
    {
        auto reader = std::make_shared<FilePerspectiveCameraReader>(fileName);
        auto builder = PerspectiveCameraBuilder(reader);
        _builder = std::make_shared<PerspectiveCameraBuilder>(PerspectiveCameraBuilder(reader));
        camera_sh_ptr = _director->create(_builder);
    }
    catch (SourceException &error)
    {
        std::string msg = "Error : Open file";
        throw SourceException(msg);
    }
    catch (std::exception &error)
    {
        std::string msg = "Error : Read model";
        throw SourceException(msg);
    }

    return std::shared_ptr<BaseObject>(camera_sh_ptr);
}
