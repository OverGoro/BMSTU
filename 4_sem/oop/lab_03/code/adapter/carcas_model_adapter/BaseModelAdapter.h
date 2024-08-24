#ifndef __BASEMODELADAPTER_H__
#define __BASEMODELADAPTER_H__
#include <memory>
#include "BaseModel.h"
#include "BaseAdapter.h"
class BaseModelAdapter : public BaseAdapter
{
public:
    BaseModelAdapter() = default;
    BaseModelAdapter(const std::shared_ptr<BaseModel> &model);
    BaseModelAdapter(const BaseModelAdapter &other);
    BaseModelAdapter &operator=(const BaseModelAdapter &other);
    ~BaseModelAdapter() = default;

protected:
    std::shared_ptr<BaseModel> model;
};

#endif // __BASEMODELADAPTER_H__
