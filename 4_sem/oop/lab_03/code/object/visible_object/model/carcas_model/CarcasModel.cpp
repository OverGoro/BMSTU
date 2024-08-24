#include "CarcasModel.h"
CarcasModel &CarcasModel::operator=(const CarcasModel &model)
{
    data = model.data;
    return *this;
}

// CarcasModel::CarcasModel(const CarcasData &data)
// {
//     this->data = data;
//
