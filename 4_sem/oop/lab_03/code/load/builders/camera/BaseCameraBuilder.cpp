#include "BaseCameraBuilder.h"

BaseCameraBuilder::BaseCameraBuilder(std::shared_ptr<BasePerspectiveCameraReader> &reader)
    : _reader(reader) {}
