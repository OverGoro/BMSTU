#include "TransformManager.hpp"
#include "TransformAdapterSolution.h"
void TransformManager::execute()
{
    auto ad = TransformAdapterSolution().create(object, params);
    ad->request();
}
