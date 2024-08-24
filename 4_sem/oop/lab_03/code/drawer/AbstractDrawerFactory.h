#ifndef ABSTRACTFACTORY_H
#define ABSTRACTFACTORY_H

#include <memory>
#include "BaseDrawer.h"
class AbstractDrawerFactory
{
public:
    virtual std::unique_ptr<BaseDrawer> createDrawer() = 0;
};

#endif // ABSTRACTFACTORY_H
