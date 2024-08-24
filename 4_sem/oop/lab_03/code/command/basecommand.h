#ifndef BASECOMMAND_H
#define BASECOMMAND_H

#include "DrawManager.h"
#include "LoadManager.h"
#include "SceneManager.h"
#include "TransformManager.hpp"
#include "CameraLoadModerator.h"
#include "ModelLoadModerator.h"
#include "SceneLoadModerator.h"
#include "DrawCompositeAdapter.h"


class BaseCommand
{
public:
    BaseCommand() = default;
    virtual ~BaseCommand() = default;

    virtual void setManagers(std::shared_ptr<DrawManager> drawManager,
                             std::shared_ptr<LoadManager> loadManager,
                             std::shared_ptr<SceneManager> sceneManager,
                             std::shared_ptr<TransformManager> transformManager,
                             std::shared_ptr<ModelLoadModerator> modelLoadModerator,
                             std::shared_ptr<SceneLoadModerator> sceneLoadModerator,
                             std::shared_ptr<DrawCompositeAdapter> drawCompositeAdapter);

    virtual void setScene(std::shared_ptr<Scene> scene);

    virtual std::shared_ptr<BaseCommand> clone() const = 0;

    virtual void execute() = 0;

    std::shared_ptr<DrawManager> drawManager() const;
    void setDrawManager(const std::shared_ptr<DrawManager> &newDrawManager);

    std::shared_ptr<LoadManager> loadManager() const;
    void setLoadManager(const std::shared_ptr<LoadManager> &newLoadManager);

    std::shared_ptr<TransformManager> transformManager() const;
    void setTransformManager(const std::shared_ptr<TransformManager> &newTransformManager);

    std::shared_ptr<ModelLoadModerator> modelLoadModerator() const;
    void setModelLoadModerator(const std::shared_ptr<ModelLoadModerator> &newModelLoadModerator);

    std::shared_ptr<SceneLoadModerator> sceneLoadModerator() const;
    void setSceneLoadModerator(const std::shared_ptr<SceneLoadModerator> &newSceneLoadModerator);

    std::shared_ptr<DrawCompositeAdapter> drawCompositeAdapter() const;
    void setDrawCompositeAdapter(const std::shared_ptr<DrawCompositeAdapter> &newDrawCompositeAdapter);

    std::shared_ptr<Scene> scene() const;

    std::shared_ptr<SceneManager> sceneManager() const;
    void setSceneManager(const std::shared_ptr<SceneManager> &newSceneManager);

protected:
    std::shared_ptr<DrawManager> _drawManager;
    std::shared_ptr<LoadManager> _loadManager;
    std::shared_ptr<SceneManager> _sceneManager;
    std::shared_ptr<TransformManager> _transformManager;
    std::shared_ptr<ModelLoadModerator> _modelLoadModerator;
    std::shared_ptr<SceneLoadModerator> _sceneLoadModerator;
    std::shared_ptr<DrawCompositeAdapter> _drawCompositeAdapter;
    std::shared_ptr<Scene> _scene;
};


#endif //BASECOMMAND_H
