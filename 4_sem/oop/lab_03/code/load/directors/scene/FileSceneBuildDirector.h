#ifndef FILESCENEBUILDDIRECTOR_H
#define FILESCENEBUILDDIRECTOR_H


#include "BaseSceneBuildDirector.h"
#include "FileCarcasModelReader.h"

class FileSceneBuildDirector : public BaseSceneBuildDirector
{
public:
    FileSceneBuildDirector();

    ~FileSceneBuildDirector() = default;

    std::shared_ptr<Scene> create(std::shared_ptr<SceneBuilder> builder) override;

};

#endif // FILESCENEBUILDDIRECTOR_H
