#include "BasePerspectiveCameraBuilder.h"

BasePerspectiveCameraBuilder::BasePerspectiveCameraBuilder(const std::shared_ptr<BasePerspectiveCameraReader> &reader)
    : _reader(reader) {}
