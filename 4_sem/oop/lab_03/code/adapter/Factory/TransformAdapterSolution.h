#ifndef __BASEADAPTERFACTORY_H__
#define __BASEADAPTERFACTORY_H__

#include "BaseAdapter.h"
#include "BaseObject.h"
#include "../../auxillary_classes/TransformParams.hpp"

#include <map>
#include <typeindex>
#include <memory>
#include <functional>

#include "PerspectiveCamera.h"
#include "CarcasModel.h"
#include "CompositeObject.h"

class TransformAdapterSolution
{
public:
    TransformAdapterSolution();
    void registrate(std::type_index,
                    std::function<std::shared_ptr<BaseAdapter>(const std::shared_ptr<BaseObject> &,
                                                               const std::shared_ptr<BaseTransformParams> &)>);

    std::shared_ptr<BaseAdapter> create(const std::shared_ptr<BaseObject> &obj, const std::shared_ptr<BaseTransformParams> &params);

private:
    std::unordered_map<std::type_index,
                       std::function<std::shared_ptr<BaseAdapter>(const std::shared_ptr<BaseObject> &,
                                                                  const std::shared_ptr<BaseTransformParams> &)>>
        map;
};

#endif
