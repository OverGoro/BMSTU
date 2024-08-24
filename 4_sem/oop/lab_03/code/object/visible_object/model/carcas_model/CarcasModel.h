#ifndef __CARCASMODEL_H__
#define __CARCASMODEL_H__
#include "BaseModel.h"
#include "CarcasData.h"

class CarcasModel : public BaseModel
{
    friend class MoveCarcasModelAdapter;
    friend class ScaleCarcasModelAdapter;
    friend class RotateCarcasModelAdapter;
    friend class CenterCarcasModelAdapter;
    friend class DrawCarcasModelAdapter;
public:
    CarcasModel() { data = CarcasData(); };
    CarcasModel(const CarcasModel &model) : data(model.data){};
    CarcasModel &operator=(const CarcasModel &model);
    CarcasModel(const CarcasData &data)
    {
        this->data = data;
    };
    ~CarcasModel() = default;

protected:
    CarcasData data;
};

#endif // __CARCASMODEL_H__
