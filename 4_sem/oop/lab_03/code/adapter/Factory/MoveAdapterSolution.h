#ifndef __MoveADAPTERSOLUTION_H__
#define __MoveADAPTERSOLUTION_H__

#include <map>
#include <unordered_map>
#include <functional>
#include <typeindex>
#include <memory>

#include "BaseObject.h"
#include "BaseAdapter.h"
#include "../../auxillary_classes/TransformParams.hpp"

#include "MoveCarcasModelAdapter.h"
#include "MovePerspectiveCameraAdapter.h"
#include "MoveCompositeAdapter.h"

class MoveAdapterSolution
{
public:
    MoveAdapterSolution();

    std::shared_ptr<BaseAdapter> create(const std::shared_ptr<BaseObject> &obj,
                                        const std::shared_ptr<MoveParams> &params);
    void registrate(const std::type_index &type,
                    std::function<std::shared_ptr<BaseAdapter>(const std::shared_ptr<BaseObject> &obj,
                                                               const std::shared_ptr<MoveParams> &params)>
                        func);

private:
    std::unordered_map<std::type_index,
                       std::function<std::shared_ptr<BaseAdapter>(const std::shared_ptr<BaseObject> &obj,
                                                                  const std::shared_ptr<MoveParams> &params)>>
        map;
};

class BaseMoveAdapterCreator
{
public:
    virtual std::shared_ptr<BaseAdapter> create(const std::shared_ptr<BaseObject> &obj,
                                                const std::shared_ptr<MoveParams> &params) = 0;
};

class MoveCarcasModelAdapterCreator : public BaseMoveAdapterCreator
{
public:
    std::shared_ptr<BaseAdapter> create(const std::shared_ptr<BaseObject> &obj,
                                        const std::shared_ptr<MoveParams> &params) override;
};

class MovePolygonModelAdapterCreator : public BaseMoveAdapterCreator
{
public:
    std::shared_ptr<BaseAdapter> create(const std::shared_ptr<BaseObject> &obj,
                                        const std::shared_ptr<MoveParams> &params) override;
};

class MovePerspectiveCameraAdapterCreator : public BaseMoveAdapterCreator
{
public:
    std::shared_ptr<BaseAdapter> create(const std::shared_ptr<BaseObject> &obj,
                                        const std::shared_ptr<MoveParams> &params) override;
};

class MoveCompositeAdapterCreator : public BaseMoveAdapterCreator
{
public:
    std::shared_ptr<BaseAdapter> create(const std::shared_ptr<BaseObject> &obj,
                                        const std::shared_ptr<MoveParams> &params) override;
};

#endif // __MoveADAPTERSOLUTION_H__
