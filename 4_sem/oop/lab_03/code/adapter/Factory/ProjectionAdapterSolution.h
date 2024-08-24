#ifndef __ProjectionADAPTERSOLUTION_H__
#define __ProjectionADAPTERSOLUTION_H__

#include <unordered_map>
#include <functional>
#include <typeindex>
#include <memory>

#include "BaseObject.h"
#include "BaseAdapter.h"
#include "Point.h"


class ProjectionAdapterSolution
{
public:
    ProjectionAdapterSolution();

    std::shared_ptr<BaseAdapter> create(const std::shared_ptr<BaseObject> &obj,
                                        std::shared_ptr<Point> &projected,
                                        const Point &point);
    void registrate(const std::type_index &type,
                    std::function<std::shared_ptr<BaseAdapter>(const std::shared_ptr<BaseObject> &obj,
                                                               std::shared_ptr<Point> &projected,
                                                               const Point &point)>
                        func);

private:
    std::unordered_map<std::type_index,
                       std::function<std::shared_ptr<BaseAdapter>(const std::shared_ptr<BaseObject> &obj,
                                                                  std::shared_ptr<Point> &projected,
                                                                  const Point &point)>>
        map;
};

class BaseProjectionAdapterCreator
{
public:
    virtual std::shared_ptr<BaseAdapter> create(const std::shared_ptr<BaseObject> &obj,
                                                std::shared_ptr<Point> &projected,
                                                const Point &point) = 0;
};

class ProjectionPerspectiveCameraAdapterCreator : public BaseProjectionAdapterCreator
{
public:
    std::shared_ptr<BaseAdapter> create(const std::shared_ptr<BaseObject> &obj,
                                        std::shared_ptr<Point> &projected,
                                        const Point &point) override;
};

#endif // __ProjectionADAPTERSOLUTION_H__
