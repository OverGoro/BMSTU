#include "Facade.h"

Facade::Facade()
{
    _drawManager = ManagerSolution<DrawManagerCreator>().create();
    _loadManager = ManagerSolution<LoadManagerCreator>().create();
    _sceneManager = ManagerSolution<SceneManagerCreator>().create();
    _transformManager = ManagerSolution<TransformManagerCreator>().create();
    _modelLoadModerator = ModeratorSolution<ModelLoadModeratorCreator>().create();
    _sceneLoadModerator = ModeratorSolution<SceneLoadModeratorCreator>().create();

    _loadManager->setModerator(_modelLoadModerator);
    _loadManager->setSceneModerator(_sceneLoadModerator);
    // _drawManager->setAdapter(_drawCompositeAdapter);
}

void Facade::execute(BaseCommand &command)
{
    command.setDrawManager(_drawManager);
    command.setLoadManager(_loadManager);
    command.setSceneManager(_sceneManager);
    command.setTransformManager(_transformManager);
    command.setSceneLoadModerator(_sceneLoadModerator);
    auto scene = _sceneManager->getScene();
    command.setScene(scene);

    command.execute();
}
