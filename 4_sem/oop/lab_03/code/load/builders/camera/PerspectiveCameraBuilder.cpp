#include "PerspectiveCameraBuilder.h"
#include <PerspectiveCamera.h>

PerspectiveCameraBuilder::PerspectiveCameraBuilder(const std::shared_ptr<BasePerspectiveCameraReader> &reader)
    : BasePerspectiveCameraBuilder(reader) {}

void PerspectiveCameraBuilder::build()
{
    _camera = std::make_shared<PerspectiveCamera>();
    _reader->open();
}

void PerspectiveCameraBuilder::buildPosition()
{
    std::dynamic_pointer_cast<PerspectiveCamera>(_camera)->_position_point = _reader->readPoint();
}

void PerspectiveCameraBuilder::buildDirection()
{
    std::dynamic_pointer_cast<PerspectiveCamera>(_camera)->_direction_point = (_reader->readPoint());
}

void PerspectiveCameraBuilder::buildUp()
{
    std::dynamic_pointer_cast<PerspectiveCamera>(_camera)->_up_point = (_reader->readPoint());
}

void PerspectiveCameraBuilder::buildXFOV()
{
    std::dynamic_pointer_cast<PerspectiveCamera>(_camera)->_x_fov = (_reader->readSize());
}

void PerspectiveCameraBuilder::buildYFOV()
{
    std::dynamic_pointer_cast<PerspectiveCamera>(_camera)->_y_fov = (_reader->readSize());
}

bool PerspectiveCameraBuilder::isBuild() const
{
    return nullptr != _camera;
}

std::shared_ptr<BaseCamera> PerspectiveCameraBuilder::get()
{
    _reader->close();
    return _camera;
}
