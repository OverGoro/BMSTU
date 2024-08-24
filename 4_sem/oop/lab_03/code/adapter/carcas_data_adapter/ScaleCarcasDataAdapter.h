#ifndef __SCALECARCASDATAADAPTER_H__
#define __SCALECARCASDATAADAPTER_H__
#include "BaseCarcasDataAdapter.h"
#include "../../auxillary_classes/TransformParams.hpp"
class ScaleCarcasDataAdapter : public BaseCarcasDataAdapter
{
public:
    ScaleCarcasDataAdapter() = default;
    ScaleCarcasDataAdapter(std::shared_ptr<CarcasData> data, const ScaleParams& params )
        : params(params)
    {
        carcas_data = data;
    };
    ~ScaleCarcasDataAdapter() = default;

    void request() override;
protected:
    ScaleParams params;
};

#endif // __SCALECARCASDATAADAPTER_H__