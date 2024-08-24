#ifndef __TRANSFORMMANAGER_H__
#define __TRANSFORMMANAGER_H__

#include "TransformAdapterSolution.h"
#include "BaseManager.h"
#include "BaseObject.h"


#include <memory>

class TransformManager
{
public:
    TransformManager() = default;
    explicit TransformManager(std::shared_ptr<BaseObject> object, std::shared_ptr<BaseTransformParams> params)
        : object(object), params(params) {};
    TransformManager(const TransformManager&) = default;
    TransformManager& operator=(const TransformManager&) = default;
    TransformManager(TransformManager&&) noexcept = default;
    TransformManager& operator=(TransformManager&&) noexcept = default;
    ~TransformManager() = default;
    void execute();
    std::shared_ptr<BaseObject> getObject() const { return object; }
    void setObject(const std::shared_ptr<BaseObject> &object_) { object = object_; }
    std::shared_ptr<BaseTransformParams> getParams() const { return params; }
    void setParams(const std::shared_ptr<BaseTransformParams> &params_) { params = params_; }
protected:
    std::shared_ptr<BaseObject> object;
    std::shared_ptr<BaseTransformParams> params;
};


#endif // __TRANSFORMMANAGER_H__