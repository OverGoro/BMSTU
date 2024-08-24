#include "RotateAdapterSolution.h"
#include "polygon_model_adapter/RotatePolygonModelAdapter.h"
#include <Exceptions.h>

std::shared_ptr<BaseAdapter> RotateCarcasModelAdapterCreator::create(const std::shared_ptr<BaseObject> &obj, const std::shared_ptr<RotateParams> &params)
{
    auto adapter = RotateCarcasModelAdapter(std::dynamic_pointer_cast<CarcasModel>(obj), *params);
    return std::make_shared<RotateCarcasModelAdapter>(adapter);
}

std::shared_ptr<BaseAdapter> RotatePolygonModelAdapterCreator::create(const std::shared_ptr<BaseObject> &obj, const std::shared_ptr<RotateParams> &params)
{
    auto adapter = RotatePolygonModelAdapter(std::dynamic_pointer_cast<PolygonModel>(obj), *params);
    return std::make_shared<RotatePolygonModelAdapter>(adapter);
}

std::shared_ptr<BaseAdapter> RotatePerspectiveCameraAdapterCreator::create(const std::shared_ptr<BaseObject> &obj, const std::shared_ptr<RotateParams> &params)
{
    auto adapter = RotatePerspectiveCameraAdapter(std::dynamic_pointer_cast<PerspectiveCamera>(obj), *params);
    return std::make_shared<RotatePerspectiveCameraAdapter>(adapter);
}
std::shared_ptr<BaseAdapter> RotateCompositeAdapterCreator::create(const std::shared_ptr<BaseObject> &obj, const std::shared_ptr<RotateParams> &params)
{
    auto adapter = RotateCompositeAdapter(std::dynamic_pointer_cast<CompositeObject>(obj), *params);
    return std::make_shared<RotateCompositeAdapter>(adapter);
}

RotateAdapterSolution::RotateAdapterSolution()
{
    map[typeid(CarcasModel)] = [](const std::shared_ptr<BaseObject> &obj,
                                  const std::shared_ptr<RotateParams> &params)
    {
        return RotateCarcasModelAdapterCreator().create(obj, params);
    };

    map[typeid(PolygonModel)] = [](const std::shared_ptr<BaseObject> &obj,
                                  const std::shared_ptr<RotateParams> &params)
    {
        return RotatePolygonModelAdapterCreator().create(obj, params);
    };
    map[typeid(PerspectiveCamera)] = [](const std::shared_ptr<BaseObject> &obj,
                                         const std::shared_ptr<RotateParams> &params)
    {
        return RotatePerspectiveCameraAdapterCreator().create(obj, params);
    };
    map[typeid(CompositeObject)] = [](const std::shared_ptr<BaseObject> &obj,
                                      const std::shared_ptr<RotateParams> &params)
    {
        return RotateCompositeAdapterCreator().create(obj, params);
    };
}

std::shared_ptr<BaseAdapter> RotateAdapterSolution::create(const std::shared_ptr<BaseObject> &obj, const std::shared_ptr<RotateParams> &params)
{
    auto it = map.find(typeid(*obj));
    if (it != map.end())
    {
        return it->second(obj, params);
    }
    throw NoSuitableFactoryException();
}

void RotateAdapterSolution::registrate(const std::type_index &type, std::function<std::shared_ptr<BaseAdapter>(const std::shared_ptr<BaseObject> &obj, const std::shared_ptr<RotateParams> &params)> func)
{
    map[type] = func;
}
