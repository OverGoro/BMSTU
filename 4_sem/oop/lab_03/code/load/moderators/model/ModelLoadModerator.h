#ifndef MODELLOADMODERATOR_H
#define MODELLOADMODERATOR_H

#include "../BaseLoadModerator.h"
#include "BaseCarcasModelBuildDirector.h"
#include "FileCarcasModelReader.h"
#include "BaseCarcasModelBuilder.h"
#include "CarcasModelReaderFactory.h"

class ModelLoadModerator : public BaseLoadModerator
{
public:
    ModelLoadModerator() = default;
    explicit ModelLoadModerator(std::shared_ptr<BaseModelBuildDirector> director);

    ~ModelLoadModerator() = default;

    std::shared_ptr<BaseObject> load(std::string &fileName) override;

private:
    std::shared_ptr<BaseModelBuildDirector> _director;
};

#endif // MODELLOADMODERATOR_H
