#include <SceneManagerCreator.h>

std::shared_ptr<SceneManager> SceneManagerCreator::createManager() {
    if (nullptr == _manager)
        createInstance();

    return _manager;
}


void SceneManagerCreator::createInstance()
{
    static std::shared_ptr<SceneManager> manager(new SceneManager());
    manager->setScene(std::make_shared<Scene>());
    _manager = manager;
}
