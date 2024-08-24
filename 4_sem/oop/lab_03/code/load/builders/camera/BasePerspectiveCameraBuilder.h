#ifndef BASEPerspectiveCEMAERABUILDER_H__
#define BASEPerspectiveCEMAERABUILDER_H__

#include "BaseBuilder.h"
#include "BasePerspectiveCameraReader.h"
#include "BaseCamera.h"

class BasePerspectiveCameraBuilder : public BaseBuilder
{
public:
    BasePerspectiveCameraBuilder() = default;
    explicit BasePerspectiveCameraBuilder(const std::shared_ptr<BasePerspectiveCameraReader> &reader);
    virtual ~BasePerspectiveCameraBuilder() = default;

    virtual void buildPosition() = 0;
    virtual void buildDirection() = 0;
    virtual void buildUp() = 0;
    virtual void buildXFOV() = 0;
    virtual void buildYFOV() = 0;

    virtual std::shared_ptr<BaseCamera> get() = 0;

protected:
    std::shared_ptr<BasePerspectiveCameraReader> _reader;
    std::shared_ptr<BaseCamera> _camera;
};

#endif // BASEPerspectiveCEMAERABUILDER_H__
