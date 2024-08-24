#include "ScaleAdapterSolution.h"
#include "polygon_model_adapter/ScalePolygonModelAdapter.h"
#include <Exceptions.h>

std::shared_ptr<BaseAdapter> ScaleCarcasModelAdapterCreator::create(const std::shared_ptr<BaseObject> &obj, const std::shared_ptr<ScaleParams> &params)
{
    auto adapter = ScaleCarcasModelAdapter(std::dynamic_pointer_cast<CarcasModel>(obj), *params);
    return std::make_shared<ScaleCarcasModelAdapter>(adapter);
}
std::shared_ptr<BaseAdapter> ScalePolygonModelAdapterCreator::create(const std::shared_ptr<BaseObject> &obj, const std::shared_ptr<ScaleParams> &params)
{
    auto adapter = ScalePolygonModelAdapter(std::dynamic_pointer_cast<PolygonModel>(obj), *params);
    return std::make_shared<ScalePolygonModelAdapter>(adapter);
}
std::shared_ptr<BaseAdapter> ScalePerspectiveCameraAdapterCreator::create(const std::shared_ptr<BaseObject> &obj, const std::shared_ptr<ScaleParams> &params)
{
    auto adapter = ScalePerspectiveCameraAdapter(std::dynamic_pointer_cast<PerspectiveCamera>(obj), *params);
    return std::make_shared<ScalePerspectiveCameraAdapter>(adapter);
}
std::shared_ptr<BaseAdapter> ScaleCompositeAdapterCreator::create(const std::shared_ptr<BaseObject> &obj, const std::shared_ptr<ScaleParams> &params)
{
    auto adapter = ScaleCompositeAdapter(std::dynamic_pointer_cast<CompositeObject>(obj), *params);
    return std::make_shared<ScaleCompositeAdapter>(adapter);
}

ScaleAdapterSolution::ScaleAdapterSolution()
{
    map[typeid(CarcasModel)] = [](const std::shared_ptr<BaseObject> &obj,
                                  const std::shared_ptr<ScaleParams> &params)
    {
        return ScaleCarcasModelAdapterCreator().create(obj, params);
    };
    map[typeid(PolygonModel)] = [](const std::shared_ptr<BaseObject> &obj,
                                  const std::shared_ptr<ScaleParams> &params)
    {
        return ScalePolygonModelAdapterCreator().create(obj, params);
    };
    map[typeid(PerspectiveCamera)] = [](const std::shared_ptr<BaseObject> &obj,
                                         const std::shared_ptr<ScaleParams> &params)
    {
        return ScalePerspectiveCameraAdapterCreator().create(obj, params);
    };
    map[typeid(CompositeObject)] = [](const std::shared_ptr<BaseObject> &obj,
                                      const std::shared_ptr<ScaleParams> &params)
    {
        return ScaleCompositeAdapterCreator().create(obj, params);
    };
}

std::shared_ptr<BaseAdapter> ScaleAdapterSolution::create(const std::shared_ptr<BaseObject> &obj, const std::shared_ptr<ScaleParams> &params)
{
    auto it = map.find(typeid(*obj));
    if (it != map.end())
    {
        return it->second(obj, params);
    }
    throw NoSuitableFactoryException();
}

void ScaleAdapterSolution::registrate(const std::type_index &type, std::function<std::shared_ptr<BaseAdapter>(const std::shared_ptr<BaseObject> &obj, const std::shared_ptr<ScaleParams> &params)> func)
{
    map[type] = func;
}

