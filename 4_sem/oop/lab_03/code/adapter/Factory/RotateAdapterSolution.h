#ifndef __RotateADAPTERSOLUTION_H__
#define __RotateADAPTERSOLUTION_H__

#include <map>
#include <unordered_map>
#include <functional>
#include <typeindex>
#include <memory>

#include "BaseObject.h"
#include "BaseAdapter.h"
#include "../../auxillary_classes/TransformParams.hpp"

#include "RotateCarcasModelAdapter.h"
#include "RotatePerspectiveCameraAdapter.h"
#include "RotateCompositeAdapter.h"

class RotateAdapterSolution
{
public:
    RotateAdapterSolution();

    std::shared_ptr<BaseAdapter> create(const std::shared_ptr<BaseObject> &obj,
                                        const std::shared_ptr<RotateParams> &params);
    void registrate(const std::type_index &type,
                    std::function<std::shared_ptr<BaseAdapter>(const std::shared_ptr<BaseObject> &obj,
                                                               const std::shared_ptr<RotateParams> &params)>
                        func);

private:
    std::unordered_map<std::type_index,
                       std::function<std::shared_ptr<BaseAdapter>(const std::shared_ptr<BaseObject> &obj,
                                                                  const std::shared_ptr<RotateParams> &params)>>
        map;
};

class BaseRotateAdapterCreator
{
public:
    virtual std::shared_ptr<BaseAdapter> create(const std::shared_ptr<BaseObject> &obj,
                                                const std::shared_ptr<RotateParams> &params) = 0;
};

class RotateCarcasModelAdapterCreator : public BaseRotateAdapterCreator
{
public:
    std::shared_ptr<BaseAdapter> create(const std::shared_ptr<BaseObject> &obj,
                                        const std::shared_ptr<RotateParams> &params) override;
};

class RotatePolygonModelAdapterCreator : public BaseRotateAdapterCreator
{
public:
    std::shared_ptr<BaseAdapter> create(const std::shared_ptr<BaseObject> &obj,
                                        const std::shared_ptr<RotateParams> &params) override;
};


class RotatePerspectiveCameraAdapterCreator : public BaseRotateAdapterCreator
{
public:
    std::shared_ptr<BaseAdapter> create(const std::shared_ptr<BaseObject> &obj,
                                        const std::shared_ptr<RotateParams> &params) override;
};

class RotateCompositeAdapterCreator : public BaseRotateAdapterCreator
{
public:
    std::shared_ptr<BaseAdapter> create(const std::shared_ptr<BaseObject> &obj,
                                        const std::shared_ptr<RotateParams> &params) override;
};

#endif // __RotateADAPTERSOLUTION_H__
