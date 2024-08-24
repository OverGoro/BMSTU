#ifndef FACADE_H
#define FACADE_H

#include <memory>
#include "basecommand.h"
#include "ManagerSolution.h"
#include "DrawManagerCreator.h"
#include "SceneManagerCreator.h"
#include "TransformManagerCreator.h"
#include "LoadManagerCreator.h"
#include "ModeratorSolution.h"
#include "ModelLoadModeratorCreator.h"
#include "SceneLoadModeratorCraetor.h"
#include <DrawCompositeAdapter.h>

class Facade
{
public:
    Facade();
    ~Facade() = default;

    void execute(BaseCommand &command);

private:
    std::shared_ptr<DrawManager> _drawManager;
    std::shared_ptr<LoadManager> _loadManager;
    std::shared_ptr<SceneManager> _sceneManager;
    std::shared_ptr<TransformManager> _transformManager;
    std::shared_ptr<ModelLoadModerator> _modelLoadModerator;
    std::shared_ptr<SceneLoadModerator> _sceneLoadModerator;
};

#endif //FACADE_H
