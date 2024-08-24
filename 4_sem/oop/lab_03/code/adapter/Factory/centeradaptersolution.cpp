#include "centeradaptersolution.h"
#include <Exceptions.h>
#include <PerspectiveCamera.h>
#include "CarcasModel.h"
#include "CompositeObject.h"
#include "centercarcasmodeladapter.h"
#include "centerperspectivecameraadapter.h"
#include "centercompositeadapter.h"
#include "polygon_model_adapter/centerpolygonmodeladapter.h"

std::shared_ptr<BaseAdapter> CenterCarcasModelAdapterCreator::create(const std::shared_ptr<BaseObject> &obj, const std::shared_ptr<Point> &center)
{
    auto adapter = CenterCarcasModelAdapter(std::dynamic_pointer_cast<CarcasModel>(obj), center);
    return std::make_shared<CenterCarcasModelAdapter>(adapter);
}
std::shared_ptr<BaseAdapter> CenterPerspectiveCameraAdapterCreator::create(const std::shared_ptr<BaseObject> &obj, const std::shared_ptr<Point> &center)
{
    auto adapter = CenterPerspectiveCameraAdapter(std::dynamic_pointer_cast<PerspectiveCamera>(obj), center);
    return std::make_shared<CenterPerspectiveCameraAdapter>(adapter);
}
std::shared_ptr<BaseAdapter> CenterCompositeAdapterCreator::create(const std::shared_ptr<BaseObject> &obj, const std::shared_ptr<Point> &center)
{
    auto adapter = CenterCompositeAdapter(std::dynamic_pointer_cast<CompositeObject>(obj), center);
    return std::make_shared<CenterCompositeAdapter>(adapter);
}

std::shared_ptr<BaseAdapter> CenterPolygonModelAdapterCreator::create(const std::shared_ptr<BaseObject> &obj, const std::shared_ptr<Point> &center)
{
    auto adapter = CenterPolygonModelAdapter(std::dynamic_pointer_cast<PolygonModel>(obj), center);
    return std::make_shared<CenterPolygonModelAdapter>(adapter);
}

CenterAdapterSolution::CenterAdapterSolution()
{
    map[typeid(CarcasModel)] = [](const std::shared_ptr<BaseObject> &obj,
                                  const std::shared_ptr<Point> &center)
    {
        return CenterCarcasModelAdapterCreator().create(obj, center);
    };
    map[typeid(PerspectiveCamera)] = [](const std::shared_ptr<BaseObject> &obj,
                                         const std::shared_ptr<Point> &center)
    {
        return CenterPerspectiveCameraAdapterCreator().create(obj, center);
    };
    map[typeid(CompositeObject)] = [](const std::shared_ptr<BaseObject> &obj,
                                      const std::shared_ptr<Point> &center)
    {
        return CenterCompositeAdapterCreator().create(obj, center);
    };
    map[typeid(PolygonModel)] = [](const std::shared_ptr<BaseObject> &obj,
                                      const std::shared_ptr<Point> &center)
    {
        return CenterPolygonModelAdapterCreator().create(obj, center);
    };
}

std::shared_ptr<BaseAdapter> CenterAdapterSolution::create(const std::shared_ptr<BaseObject> &obj, const std::shared_ptr<Point> &center)
{
    auto it = map.find(typeid(*obj));
    if (it != map.end())
    {
        return it->second(obj, center);
    }
    throw NoSuitableFactoryException();
}

void CenterAdapterSolution::registrate(const std::type_index &type, std::function<std::shared_ptr<BaseAdapter>(const std::shared_ptr<BaseObject> &obj, const std::shared_ptr<Point> &center)> func)
{
    map[type] = func;
}


