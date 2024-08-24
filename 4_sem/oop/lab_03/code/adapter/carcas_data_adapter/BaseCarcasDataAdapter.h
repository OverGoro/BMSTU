#ifndef __BASECARCASDATAADAPTER_H__
#define __BASECARCASDATAADAPTER_H__

#include "CarcasData.h"
#include "BaseAdapter.h"
#include <memory>
class BaseCarcasDataAdapter : public BaseAdapter
{
public:
    BaseCarcasDataAdapter() = default;
    ~BaseCarcasDataAdapter() = default;
protected:
    std::shared_ptr<CarcasData> carcas_data;
};

#endif // __BASECARCASDATAADAPTER_H__