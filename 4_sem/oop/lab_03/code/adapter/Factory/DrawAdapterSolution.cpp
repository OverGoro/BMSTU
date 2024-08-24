#include "DrawAdapterSolution.h"
#include "polygon_model/polygonmodel.h"
#include "polygon_model_adapter/DrawPolygonModelAdapter.h"
#include <Exceptions.h>
#include <PerspectiveCamera.h>

DrawAdapterSolution::DrawAdapterSolution()
{
    map[typeid(CarcasModel)] = [](const std::shared_ptr<BaseObject> &obj,
                                  const std::shared_ptr<BaseDrawer> &drawer,
                                  const std::shared_ptr<BaseCamera> &camera)
    {
        return DrawCarcasModelAdapterCreator().create(obj, drawer, camera);
    };
    map[typeid(PolygonModel)] = [](const std::shared_ptr<BaseObject> &obj,
                                  const std::shared_ptr<BaseDrawer> &drawer,
                                  const std::shared_ptr<BaseCamera> &camera)
    {
        return DrawPolygonModelAdapterCreator().create(obj, drawer, camera);
    };
    map[typeid(CompositeObject)] = [](const std::shared_ptr<BaseObject> &obj,
                                  const std::shared_ptr<BaseDrawer> &drawer,
                                  const std::shared_ptr<BaseCamera> &camera)
    {
        return DrawCompositeAdapterCreator().create(obj, drawer, camera);
    };
}

std::shared_ptr<BaseAdapter> DrawAdapterSolution::create(const std::shared_ptr<BaseObject> &obj, const std::shared_ptr<BaseDrawer> &drawer, const std::shared_ptr<BaseCamera> &camera)
{
    auto it = map.find(typeid(*obj));
    if (it!= map.end())
    {
        return it->second(obj, drawer, camera);
    }
    throw NoSuitableAdapterException();
}

void DrawAdapterSolution::registrate(const std::type_index &type, std::function<std::shared_ptr<BaseAdapter>(const std::shared_ptr<BaseObject> &obj, const std::shared_ptr<BaseDrawer> &drawer, const std::shared_ptr<BaseCamera> &camera)> func)
{
    map[type] = func;
}

std::shared_ptr<BaseAdapter> DrawCarcasModelAdapterCreator::create(const std::shared_ptr<BaseObject> &obj, const std::shared_ptr<BaseDrawer> &drawer, const std::shared_ptr<BaseCamera> &camera)
{
    DrawCarcasModelAdapter adapter(std::dynamic_pointer_cast<CarcasModel>(obj), drawer, camera);
    return std::make_shared<DrawCarcasModelAdapter>(adapter);
}

std::shared_ptr<BaseAdapter> DrawCompositeAdapterCreator::create(const std::shared_ptr<BaseObject> &obj, const std::shared_ptr<BaseDrawer> &drawer, const std::shared_ptr<BaseCamera> &camera)
{
    DrawCompositeAdapter adapter(std::dynamic_pointer_cast<CompositeObject>(obj), drawer, camera);
    return std::make_shared<DrawCompositeAdapter>(adapter);
}

std::shared_ptr<BaseAdapter> DrawPolygonModelAdapterCreator::create(const std::shared_ptr<BaseObject> &obj, const std::shared_ptr<BaseDrawer> &drawer, const std::shared_ptr<BaseCamera> &camera)
{
    DrawPolygonModelAdapter adapter(std::dynamic_pointer_cast<PolygonModel>(obj), drawer, camera);
    return std::make_shared<DrawPolygonModelAdapter>(adapter);
}
