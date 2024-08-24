#ifndef CAMERABUILDER_H
#define CAMERABUILDER_H

#include "BasePerspectiveCameraBuilder.h"

class PerspectiveCameraBuilder : public BasePerspectiveCameraBuilder
{
public:
    PerspectiveCameraBuilder() = default;
    explicit PerspectiveCameraBuilder(const std::shared_ptr<BasePerspectiveCameraReader> &reader);
    ~PerspectiveCameraBuilder() = default;

    void build() override;
    void buildPosition() override;
    void buildDirection() override;
    void buildUp() override;
    void buildXFOV() override;
    void buildYFOV() override;
    bool isBuild() const override;

    std::shared_ptr<BaseCamera> get() override;
};

#endif //CAMERABUILDER_H
