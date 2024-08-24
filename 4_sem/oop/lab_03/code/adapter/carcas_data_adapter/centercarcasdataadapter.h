#ifndef CENTERCARCASDATAADAPTER_H
#define CENTERCARCASDATAADAPTER_H

#include "BaseCarcasDataAdapter.h"
class CenterCarcasDataAdapter : public BaseCarcasDataAdapter
{
public:
    CenterCarcasDataAdapter() = default;
    ~CenterCarcasDataAdapter() = default;
    CenterCarcasDataAdapter(std::shared_ptr<CarcasData> data, const std::shared_ptr<Point> &center)
    {
        this->carcas_data = data;
        this->center = center;
    };

    void request();


protected:
    std::shared_ptr<Point> center;
};

#endif // CENTERCARCASDATAADAPTER_H
