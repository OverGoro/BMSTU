#ifndef __CenterADAPTERSOLUTION_H__
#define __CenterADAPTERSOLUTION_H__

#include <unordered_map>
#include <functional>
#include <typeindex>
#include <memory>

#include "BaseObject.h"
#include "BaseAdapter.h"
#include "Point.h"


class CenterAdapterSolution
{
public:
    CenterAdapterSolution();

    std::shared_ptr<BaseAdapter> create(const std::shared_ptr<BaseObject> &obj,
                                        const std::shared_ptr<Point> &center);
    void registrate(const std::type_index &type,
                    std::function<std::shared_ptr<BaseAdapter>(const std::shared_ptr<BaseObject> &obj,
                                                               const std::shared_ptr<Point> &center)>
                        func);

private:
    std::unordered_map<std::type_index,
                       std::function<std::shared_ptr<BaseAdapter>(const std::shared_ptr<BaseObject> &obj,
                                                                  const std::shared_ptr<Point> &center)>>
        map;
};

class BaseCenterAdapterCreator
{
public:
    virtual std::shared_ptr<BaseAdapter> create(const std::shared_ptr<BaseObject> &obj,
                                                const std::shared_ptr<Point> &center) = 0;
};

class CenterCarcasModelAdapterCreator : public BaseCenterAdapterCreator
{
public:
    std::shared_ptr<BaseAdapter> create(const std::shared_ptr<BaseObject> &obj,
                                        const std::shared_ptr<Point> &center) override;
};

class CenterPolygonModelAdapterCreator : public BaseCenterAdapterCreator
{
public:
    std::shared_ptr<BaseAdapter> create(const std::shared_ptr<BaseObject> &obj,
                                        const std::shared_ptr<Point> &center) override;
};

class CenterPerspectiveCameraAdapterCreator : public BaseCenterAdapterCreator
{
public:
    std::shared_ptr<BaseAdapter> create(const std::shared_ptr<BaseObject> &obj,
                                        const std::shared_ptr<Point> &center) override;
};

class CenterCompositeAdapterCreator : public BaseCenterAdapterCreator
{
public:
    std::shared_ptr<BaseAdapter> create(const std::shared_ptr<BaseObject> &obj,
                                        const std::shared_ptr<Point> &center) override;
};

#endif // __CenterADAPTERSOLUTION_H__
