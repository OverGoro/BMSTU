#ifndef BASEMODELBUILDDIRECTOR_H
#define BASEMODELBUILDDIRECTOR_H


#include "BaseDirector.h"
#include "CarcasModelBuilder.h"

class BaseModelBuildDirector : public BaseDirector
{
public:
    virtual std::shared_ptr<CarcasModel> create(std::shared_ptr<BaseCarcasModelBuilder> builder) = 0;
};

#endif // BASEMODELBUILDDIRECTOR_H
