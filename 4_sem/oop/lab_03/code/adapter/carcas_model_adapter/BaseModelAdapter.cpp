#include "BaseModelAdapter.h"

BaseModelAdapter::BaseModelAdapter(const std::shared_ptr<BaseModel> &model)
{
    this->model = model;
}

BaseModelAdapter::BaseModelAdapter(const BaseModelAdapter &other)
{
    model = other.model;
}

BaseModelAdapter &BaseModelAdapter::operator=(const BaseModelAdapter &other)
{
    model = other.model;
}
