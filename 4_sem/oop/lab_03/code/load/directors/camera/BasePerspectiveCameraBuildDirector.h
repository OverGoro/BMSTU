#ifndef BASECAMERABUILDDIRECTOR_H
#define BASECAMERABUILDDIRECTOR_H


#include "BaseDirector.h"
#include "BasePerspectiveCameraBuilder.h"

class BaseCameraBuildDirector : public BaseDirector
{
public:
    virtual std::shared_ptr<BaseCamera> create(std::shared_ptr<BasePerspectiveCameraBuilder> builder) = 0;
};

#endif // BASECAMERABUILDDIRECTOR_H
