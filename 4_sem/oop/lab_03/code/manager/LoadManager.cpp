#include "LoadManager.h"

std::shared_ptr<BaseObject> LoadManager::load(std::string &name)
{
    return _moderator->load(name);
}

std::shared_ptr<Scene> LoadManager::loadScene(std::string &name)
{
    return _sceneModerator->load(name);
}

