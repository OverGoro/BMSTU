#ifndef __DrawADAPTERSOLUTION_H__
#define __DrawADAPTERSOLUTION_H__

#include <unordered_map>
#include <functional>
#include <typeindex>
#include <memory>

#include "BaseObject.h"
#include "BaseAdapter.h"

#include "DrawCarcasModelAdapter.h"
#include "DrawCompositeAdapter.h"

class DrawAdapterSolution
{
public:
    DrawAdapterSolution();

    std::shared_ptr<BaseAdapter> create(const std::shared_ptr<BaseObject> &obj,
                                        const std::shared_ptr<BaseDrawer> &drawer,
                                        const std::shared_ptr<BaseCamera> &camera);
    void registrate(const std::type_index &type,
                    std::function<std::shared_ptr<BaseAdapter>(const std::shared_ptr<BaseObject> &obj,
                                                               const std::shared_ptr<BaseDrawer> &drawer,
                                                               const std::shared_ptr<BaseCamera> &camera)>
                        func);

private:
    std::unordered_map<std::type_index,
                       std::function<std::shared_ptr<BaseAdapter>(const std::shared_ptr<BaseObject> &obj,
                                                                  const std::shared_ptr<BaseDrawer> &drawer,
                                                                  const std::shared_ptr<BaseCamera> &camera)>>
        map;
};

class BaseDrawAdapterCreator
{
public:
    virtual std::shared_ptr<BaseAdapter> create(const std::shared_ptr<BaseObject> &obj,
                                                const std::shared_ptr<BaseDrawer> &drawer,
                                                const std::shared_ptr<BaseCamera> &camera) = 0;
};

class DrawCarcasModelAdapterCreator : public BaseDrawAdapterCreator
{
public:
    std::shared_ptr<BaseAdapter> create(const std::shared_ptr<BaseObject> &obj,
                                        const std::shared_ptr<BaseDrawer> &drawer,
                                        const std::shared_ptr<BaseCamera> &camera) override;
};

class DrawPolygonModelAdapterCreator : public BaseDrawAdapterCreator
{
public:
    std::shared_ptr<BaseAdapter> create(const std::shared_ptr<BaseObject> &obj,
                                        const std::shared_ptr<BaseDrawer> &drawer,
                                        const std::shared_ptr<BaseCamera> &camera) override;
};

class DrawCompositeAdapterCreator : public BaseDrawAdapterCreator
{
public:
    std::shared_ptr<BaseAdapter> create(const std::shared_ptr<BaseObject> &obj,
                                        const std::shared_ptr<BaseDrawer> &drawer,
                                        const std::shared_ptr<BaseCamera> &camera) override;
};

#endif // __DrawADAPTERSOLUTION_H__
