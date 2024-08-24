#include "MoveAdapterSolution.h"
#include "polygon_model/polygonmodel.h"
#include "polygon_model_adapter/MovePolygonModelAdapter.h"
#include <Exceptions.h>
#include <PerspectiveCamera.h>

std::shared_ptr<BaseAdapter> MoveCarcasModelAdapterCreator::create(const std::shared_ptr<BaseObject> &obj, const std::shared_ptr<MoveParams> &params)
{
    auto adapter = MoveCarcasModelAdapter(std::dynamic_pointer_cast<CarcasModel>(obj), *params);
    return std::make_shared<MoveCarcasModelAdapter>(adapter);
}

std::shared_ptr<BaseAdapter> MovePolygonModelAdapterCreator::create(const std::shared_ptr<BaseObject> &obj, const std::shared_ptr<MoveParams> &params)
{
    auto adapter = MovePolygonModelAdapter(std::dynamic_pointer_cast<PolygonModel>(obj), *params);
    return std::make_shared<MovePolygonModelAdapter>(adapter);
}


std::shared_ptr<BaseAdapter> MovePerspectiveCameraAdapterCreator::create(const std::shared_ptr<BaseObject> &obj, const std::shared_ptr<MoveParams> &params)
{
    auto adapter = MovePerspectiveCameraAdapter(std::dynamic_pointer_cast<PerspectiveCamera>(obj), *params);
    return std::make_shared<MovePerspectiveCameraAdapter>(adapter);
}
std::shared_ptr<BaseAdapter> MoveCompositeAdapterCreator::create(const std::shared_ptr<BaseObject> &obj, const std::shared_ptr<MoveParams> &params)
{
    auto adapter = MoveCompositeAdapter(std::dynamic_pointer_cast<CompositeObject>(obj), *params);
    return std::make_shared<MoveCompositeAdapter>(adapter);
}

MoveAdapterSolution::MoveAdapterSolution()
{
    map[typeid(CarcasModel)] = [](const std::shared_ptr<BaseObject> &obj,
                                  const std::shared_ptr<MoveParams> &params)
    {
        return MoveCarcasModelAdapterCreator().create(obj, params);
    };
    map[typeid(PolygonModel)] = [](const std::shared_ptr<BaseObject> &obj,
                                  const std::shared_ptr<MoveParams> &params)
    {
        return MovePolygonModelAdapterCreator().create(obj, params);
    };
    map[typeid(PerspectiveCamera)] = [](const std::shared_ptr<BaseObject> &obj,
                                         const std::shared_ptr<MoveParams> &params)
    {
        return MovePerspectiveCameraAdapterCreator().create(obj, params);
    };
    map[typeid(CompositeObject)] = [](const std::shared_ptr<BaseObject> &obj,
                                      const std::shared_ptr<MoveParams> &params)
    {
        return MoveCompositeAdapterCreator().create(obj, params);
    };
}

std::shared_ptr<BaseAdapter> MoveAdapterSolution::create(const std::shared_ptr<BaseObject> &obj, const std::shared_ptr<MoveParams> &params)
{
    auto it = map.find(typeid(*obj));
    if (it != map.end())
    {
        return it->second(obj, params);
    }
    throw NoSuitableFactoryException();
}

void MoveAdapterSolution::registrate(const std::type_index &type, std::function<std::shared_ptr<BaseAdapter>(const std::shared_ptr<BaseObject> &obj, const std::shared_ptr<MoveParams> &params)> func)
{
    map[type] = func;
}

