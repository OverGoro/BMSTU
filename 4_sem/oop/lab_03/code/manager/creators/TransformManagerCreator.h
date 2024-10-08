#ifndef TRANSFORMMANAGERCREATOR_H
#define TRANSFORMMANAGERCREATOR_H

#include "TransformManager.hpp"


class TransformManagerCreator
{
public:
    std::shared_ptr<TransformManager> createManager();

private:
    void createInstance();

    std::shared_ptr<TransformManager> _manager;
};


#endif //TRANSFORMMANAGERCREATOR_H
