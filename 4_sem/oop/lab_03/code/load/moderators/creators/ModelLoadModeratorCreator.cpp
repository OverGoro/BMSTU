#include "ModelLoadModeratorCreator.h"
#include "FileCarcasModelBuildDirector.h"

std::shared_ptr<ModelLoadModerator> ModelLoadModeratorCreator::createModerator()
{
    if (nullptr == _moderator)
        createInstance();

    return _moderator;
}

void ModelLoadModeratorCreator::createInstance()
{
    static std::shared_ptr<ModelLoadModerator> moderator;

    if (!moderator)
    {
        auto director = std::make_shared<FileModelBuildDirector>();
        moderator = std::make_shared<ModelLoadModerator>(director);
    }

    _moderator = moderator;
}
