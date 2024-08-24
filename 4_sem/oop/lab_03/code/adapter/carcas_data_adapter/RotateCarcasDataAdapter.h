#ifndef __ROTATECARCASDATAADAPTER_H__
#define __ROTATECARCASDATAADAPTER_H__


#include "BaseCarcasDataAdapter.h"
#include "../../auxillary_classes/TransformParams.hpp"

class RotateCarcasDataAdapter : public BaseCarcasDataAdapter
{
public:
    RotateCarcasDataAdapter() = default;
    RotateCarcasDataAdapter(std::shared_ptr<CarcasData> data, const RotateParams &params)
        : params(params)
    {
        this->carcas_data = data;
    };
    ~RotateCarcasDataAdapter() = default;

    void request() override;
protected:
    RotateParams params;

};


#endif // __ROTATECARCASDATAADAPTER_H__
