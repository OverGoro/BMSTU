#ifndef BASECAMERABUILDER_H
#define BASECAMERABUILDER_H

#include "BaseCamera.h"
#include "BaseBuilder.h"

class BaseCameraBuilder : public BaseBuilder
{
public:
    BaseCameraBuilder() = default;
    explicit BaseCameraBuilder(const std::shared_ptr<BasePerspectiveCameraReader> &reader);
    virtual ~BaseCameraBuilder() = default;

    virtual void build() override = 0;
    virtual bool isBuild() const override = 0;

    virtual std::shared_ptr<BaseCamera> get() = 0;

    std::shared_ptr<BasePerspectiveCameraReader> reader() const { return _reader; }
    void setReader(const std::shared_ptr<BasePerspectiveCameraReader> &reader) { _reader = reader; }

protected:
// TODO Добавить Camera reader
    std::shared_ptr<BasePerspectiveCameraReader> _reader;
    std::shared_ptr<BaseCamera> _camera;
};

#endif // BASECAMERABUILDER_H
