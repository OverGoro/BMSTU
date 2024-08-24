#include "TransformAdapterSolution.h"
#include "BaseAdapter.h"

#include "MoveAdapterSolution.h"
#include "ScaleAdapterSolution.h"
#include "RotateAdapterSolution.h"

#include "Exceptions.h"

TransformAdapterSolution::TransformAdapterSolution()
{
    map[typeid(MoveParams)] = [](const std::shared_ptr<BaseObject> &obj,
                                 const std::shared_ptr<BaseTransformParams> &params)
    {
        std::shared_ptr<MoveParams> tmp_params = std::dynamic_pointer_cast<MoveParams>(params);
        return std::make_shared<MoveAdapterSolution>()->create(obj, tmp_params);
    };
    map[typeid(ScaleParams)] = [](const std::shared_ptr<BaseObject> &obj,
                                  const std::shared_ptr<BaseTransformParams> &params)
    {
        std::shared_ptr<ScaleParams> tmp_params = std::dynamic_pointer_cast<ScaleParams>(params);
        return std::make_shared<ScaleAdapterSolution>()->create(obj, tmp_params);
    };
    map[typeid(RotateParams)] = [](const std::shared_ptr<BaseObject> &obj,
                                   const std::shared_ptr<BaseTransformParams> &params)
    {
        std::shared_ptr<RotateParams> tmp_params = std::dynamic_pointer_cast<RotateParams>(params);
        return std::make_shared<RotateAdapterSolution>()->create(obj, tmp_params);
    };
}

void TransformAdapterSolution::registrate(std::type_index type, std::function<std::shared_ptr<BaseAdapter>(const std::shared_ptr<BaseObject> &, const std::shared_ptr<BaseTransformParams> &)> func)
{
    map[type] = func;
}

std::shared_ptr<BaseAdapter> TransformAdapterSolution::create(const std::shared_ptr<BaseObject> &obj, const std::shared_ptr<BaseTransformParams> &params)
{
    auto it = map.find(typeid(*params));
    if (it != map.end())
    {
        return it->second(obj, params);
    }
    throw NoSuitableAdapterException();
}
