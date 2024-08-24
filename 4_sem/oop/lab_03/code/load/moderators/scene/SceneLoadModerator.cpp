#include "SceneLoadModerator.h"
#include "Exceptions.h"


SceneLoadModerator::SceneLoadModerator(std::shared_ptr<BaseSceneBuildDirector> director)
    : _builder(std::make_shared<SceneBuilder>(std::make_shared<FileCarcassModelReader>())),
    _director(std::move(director))
{
}/*:
    _builder(new SceneBuilder(std::make_shared<FileCarcassModelReader>()))
{
    _director = director;
}*/

std::shared_ptr<Scene> SceneLoadModerator::load(std::string &fileName)
{
    std::shared_ptr<Scene> scene;

    try
    {
        scene = _director->create(_builder);
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

    return scene;
}

void SceneLoadModerator::setDirector(std::shared_ptr<BaseSceneBuildDirector> director)
{
    _director = director;
}
