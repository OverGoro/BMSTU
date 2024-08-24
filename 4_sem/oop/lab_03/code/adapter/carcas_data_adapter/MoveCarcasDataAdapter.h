#ifndef __MOVECARCASDATAADAPTER_H__
#define __MOVECARCASDATAADAPTER_H__

#include "BaseCarcasDataAdapter.h"
class MoveCarcasDataAdapter : public BaseCarcasDataAdapter
{
public:
    MoveCarcasDataAdapter() = default;
    ~MoveCarcasDataAdapter() = default;
    MoveCarcasDataAdapter(std::shared_ptr<CarcasData> data, const MoveParams &params)
        : params(params)
    {
        this->carcas_data = data;
    };

    void request();


protected:
    MoveParams params;
};
#endif // __MOVECARCASDATAADAPTER_H__