#ifndef __SCALEADAPTERSOLUTION_H__
#define __SCALEADAPTERSOLUTION_H__

#include <map>
#include <unordered_map>
#include <functional>
#include <typeindex>
#include <memory>

#include "BaseObject.h"
#include "BaseAdapter.h"
#include "../../auxillary_classes/TransformParams.hpp"

#include "ScaleCarcasModelAdapter.h"
#include "ScalePerspectiveCameraAdapter.h"
#include "ScaleCompositeAdapter.h"

class ScaleAdapterSolution
{
public:
    ScaleAdapterSolution();

    std::shared_ptr<BaseAdapter> create(const std::shared_ptr<BaseObject> &obj,
                                        const std::shared_ptr<ScaleParams> &params);
    void registrate(const std::type_index &type,
                    std::function<std::shared_ptr<BaseAdapter>(const std::shared_ptr<BaseObject> &obj,
                                                               const std::shared_ptr<ScaleParams> &params)>
                        func);

private:
    std::unordered_map<std::type_index,
                       std::function<std::shared_ptr<BaseAdapter>(const std::shared_ptr<BaseObject> &obj,
                                                                  const std::shared_ptr<ScaleParams> &params)>>
        map;
};

class BaseScaleAdapterCreator
{
public:
    virtual std::shared_ptr<BaseAdapter> create(const std::shared_ptr<BaseObject> &obj,
                                                const std::shared_ptr<ScaleParams> &params) = 0;
};

class ScaleCarcasModelAdapterCreator : public BaseScaleAdapterCreator
{
public:
    std::shared_ptr<BaseAdapter> create(const std::shared_ptr<BaseObject> &obj,
                                        const std::shared_ptr<ScaleParams> &params) override;
};

class ScalePolygonModelAdapterCreator : public BaseScaleAdapterCreator
{
public:
    std::shared_ptr<BaseAdapter> create(const std::shared_ptr<BaseObject> &obj,
                                        const std::shared_ptr<ScaleParams> &params) override;
};

class ScalePerspectiveCameraAdapterCreator : public BaseScaleAdapterCreator
{
public:
    std::shared_ptr<BaseAdapter> create(const std::shared_ptr<BaseObject> &obj,
                                        const std::shared_ptr<ScaleParams> &params) override;
};

class ScaleCompositeAdapterCreator : public BaseScaleAdapterCreator
{
public:
    std::shared_ptr<BaseAdapter> create(const std::shared_ptr<BaseObject> &obj,
                                        const std::shared_ptr<ScaleParams> &params) override;
};

#endif // __SCALEADAPTERSOLUTION_H__
