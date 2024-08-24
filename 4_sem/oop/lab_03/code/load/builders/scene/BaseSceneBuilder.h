#ifndef BASESCENEBUILDER_H
#define BASESCENEBUILDER_H


#include "Scene.h"
#include "FileCarcasModelReader.h"
#include "BaseBuilder.h"

class BaseSceneBuilder : public BaseBuilder
{
public:
    BaseSceneBuilder() = default;
    explicit BaseSceneBuilder(std::shared_ptr<FileCarcassModelReader> &reader);
    virtual ~BaseSceneBuilder() = default;

    virtual void build() override = 0;
    virtual void buildModel() = 0;
    virtual void buildModels() = 0;
    virtual void buildCamera() = 0;
    virtual void buildCameras() = 0;
    virtual bool isBuild() const override = 0;

    virtual std::shared_ptr<Scene> get() = 0;

protected:
    std::shared_ptr<FileCarcassModelReader> _reader;

    std::shared_ptr<Scene> _scene;

};

#endif // BASESCENEBUILDER_H
