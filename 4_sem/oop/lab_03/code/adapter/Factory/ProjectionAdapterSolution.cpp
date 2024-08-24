#include "ProjectionAdapterSolution.h"
#include <Exceptions.h>
#include <PerspectiveCamera.h>
#include "projectionperspectivecameraadapter.h"

std::shared_ptr<BaseAdapter> ProjectionPerspectiveCameraAdapterCreator::create(const std::shared_ptr<BaseObject> &obj,
                                                                                std::shared_ptr<Point> &projected,
                                                                                const Point &point)
{
    auto adapter = ProjectionPerspectiveCameraAdapter(std::dynamic_pointer_cast<PerspectiveCamera>(obj), projected, point);
    return std::make_shared<ProjectionPerspectiveCameraAdapter>(adapter);
}

ProjectionAdapterSolution::ProjectionAdapterSolution()
{
    map[typeid(PerspectiveCamera)] = [](const std::shared_ptr<BaseObject> &obj,
                                         std::shared_ptr<Point> &projected,
                                         const Point &point)
    {
        return ProjectionPerspectiveCameraAdapterCreator().create(obj, projected, point);
    };
}

std::shared_ptr<BaseAdapter> ProjectionAdapterSolution::create(const std::shared_ptr<BaseObject> &obj,
                                                               std::shared_ptr<Point> &projected,
                                                               const Point &point)
{
    auto it = map.find(typeid(*obj));
    if (it != map.end())
    {
        return it->second(obj, projected, point);
    }
    throw NoSuitableFactoryException();
}

void ProjectionAdapterSolution::registrate(const std::type_index &type,
                                           std::function<std::shared_ptr<BaseAdapter>(const std::shared_ptr<BaseObject> &obj,
                                                                                      std::shared_ptr<Point> &projected,
                                                                                      const Point &point)> func)
{
    map[type] = func;
}
