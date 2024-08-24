#ifndef __BASECAMERAADAPTER_H__
#define __BASECAMERAADAPTER_H__

#include "BaseAdapter.h"
#include "BaseCamera.h"
#include <memory>
class BaseCameraAdapter : public BaseAdapter
{
public:
    BaseCameraAdapter() = default;
    ~BaseCameraAdapter() = default;
protected:
    std::shared_ptr<BaseCamera> camera;
};

#endif // __BASECAMERAADAPTER_H__
