#include "basecommand.h"

void BaseCommand::setManagers(std::shared_ptr<DrawManager> drawManager,
                              std::shared_ptr<LoadManager> loadManager,
                              std::shared_ptr<SceneManager> sceneManager,
                              std::shared_ptr<TransformManager> transformManager,
                              std::shared_ptr<ModelLoadModerator> modelLoadModerator,
                              std::shared_ptr<SceneLoadModerator> sceneLoadModerator,
                              std::shared_ptr<DrawCompositeAdapter> drawCompositeAdapter)
{
    _drawManager = drawManager;
    _loadManager = loadManager;
    _sceneManager = sceneManager;
    _transformManager = transformManager;
    _modelLoadModerator = modelLoadModerator;
    _sceneLoadModerator = sceneLoadModerator;
    _drawCompositeAdapter = drawCompositeAdapter;
}

void BaseCommand::setScene(std::shared_ptr<Scene> scene)
{
    _scene = scene;
}

std::shared_ptr<DrawManager> BaseCommand::drawManager() const
{
    return _drawManager;
}

void BaseCommand::setDrawManager(const std::shared_ptr<DrawManager> &newDrawManager)
{
    _drawManager = newDrawManager;
}

std::shared_ptr<LoadManager> BaseCommand::loadManager() const
{
    return _loadManager;
}

void BaseCommand::setLoadManager(const std::shared_ptr<LoadManager> &newLoadManager)
{
    _loadManager = newLoadManager;
}

std::shared_ptr<TransformManager> BaseCommand::transformManager() const
{
    return _transformManager;
}

void BaseCommand::setTransformManager(const std::shared_ptr<TransformManager> &newTransformManager)
{
    _transformManager = newTransformManager;
}

std::shared_ptr<ModelLoadModerator> BaseCommand::modelLoadModerator() const
{
    return _modelLoadModerator;
}

void BaseCommand::setModelLoadModerator(const std::shared_ptr<ModelLoadModerator> &newModelLoadModerator)
{
    _modelLoadModerator = newModelLoadModerator;
}

std::shared_ptr<SceneLoadModerator> BaseCommand::sceneLoadModerator() const
{
    return _sceneLoadModerator;
}

void BaseCommand::setSceneLoadModerator(const std::shared_ptr<SceneLoadModerator> &newSceneLoadModerator)
{
    _sceneLoadModerator = newSceneLoadModerator;
}

std::shared_ptr<DrawCompositeAdapter> BaseCommand::drawCompositeAdapter() const
{
    return _drawCompositeAdapter;
}

void BaseCommand::setDrawCompositeAdapter(const std::shared_ptr<DrawCompositeAdapter> &newDrawCompositeAdapter)
{
    _drawCompositeAdapter = newDrawCompositeAdapter;
}

std::shared_ptr<Scene> BaseCommand::scene() const
{
    return _scene;
}

std::shared_ptr<SceneManager> BaseCommand::sceneManager() const
{
    return _sceneManager;
}

void BaseCommand::setSceneManager(const std::shared_ptr<SceneManager> &newSceneManager)
{
    _sceneManager = newSceneManager;
}
