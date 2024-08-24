#ifndef __LOADMANAGER_H__
#define __LOADMANAGER_H__

#include "BaseManager.h"
#include <BaseObject.h>
#include <Scene.h>
#include <SceneLoadModerator.h>
class LoadManager : BaseManager
{
public:
    LoadManager() = default;
    LoadManager(const LoadManager &manager) = delete;
    LoadManager &operator = (const LoadManager &manager) = delete;

    ~LoadManager() = default;

    std::shared_ptr<BaseObject> load(std::string &name);
    std::shared_ptr<Scene> loadScene(std::string &name);
    std::shared_ptr<SceneLoadModerator> sceneModerator() const { return _sceneModerator; }
    void setSceneModerator(const std::shared_ptr<SceneLoadModerator> &sceneModerator) { _sceneModerator = sceneModerator; }

    std::shared_ptr<BaseLoadModerator> moderator() const { return _moderator; }
    void setModerator(const std::shared_ptr<BaseLoadModerator> &moderator) { _moderator = moderator; }

private:
    std::shared_ptr<BaseLoadModerator> _moderator;
    std::shared_ptr<SceneLoadModerator> _sceneModerator;
};
#endif // __LOADMANAGER_H__
