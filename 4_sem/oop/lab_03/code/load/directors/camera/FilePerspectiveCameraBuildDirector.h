#ifndef FILECAMERABUILDDIRECTOR_H
#define FILECAMERABUILDDIRECTOR_H


#include "BasePerspectiveCameraBuildDirector.h"
#include "FileCarcasModelReader.h"

class FileCameraBuildDirector : public BaseCameraBuildDirector
{
public:
    FileCameraBuildDirector();

    ~FileCameraBuildDirector() override = default;

    std::shared_ptr<BaseCamera> create(std::shared_ptr<BasePerspectiveCameraBuilder> builder) override;
};

#endif // FILECAMERABUILDDIRECTOR_H
