#ifndef SCENEBUILDER_H
#define SCENEBUILDER_H

#include "BaseSceneBuilder.h"

class SceneBuilder : public BaseSceneBuilder
{
public:
    SceneBuilder() = default;
    explicit SceneBuilder(std::shared_ptr<FileCarcassModelReader> reader);
    ~SceneBuilder() = default;

    void build() override;
    virtual void buildModel() override;
    virtual void buildModels() override;
    virtual void buildCamera() override;
    virtual void buildCameras() override;
    bool isBuild() const override;

    std::shared_ptr<Scene> get() override;
};


#endif //SCENEBUILDER_H
