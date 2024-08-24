#ifndef BASESCENEBUILDDIRECTOR_H
#define BASESCENEBUILDDIRECTOR_H


#include "SceneBuilder.h"

class BaseSceneBuildDirector
{
public:
    virtual std::shared_ptr<Scene> create(std::shared_ptr<SceneBuilder> builder) = 0;
};

#endif // BASESCENEBUILDDIRECTOR_H
