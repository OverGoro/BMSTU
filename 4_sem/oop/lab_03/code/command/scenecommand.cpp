#include "scenecommand.h"


ClearScene::ClearScene(std::shared_ptr<BaseDrawer> drawer) : _drawer(drawer) {}

void ClearScene::execute()
{
    _drawer->clear();
    _drawer->clearZBuffer();
}


std::shared_ptr<BaseCommand> ClearScene::clone() const
{
    return std::make_shared<ClearScene>(*this);
}



DrawScene::DrawScene(std::shared_ptr<BaseDrawer> drawer) : _drawer(drawer) { }

void DrawScene::execute()
{
    _drawManager->setCamera(_sceneManager->getCamera());
    _drawManager->drawScene(_scene, _drawer);
}

std::shared_ptr<BaseCommand> DrawScene::clone() const
{
    return std::make_shared<DrawScene>(*this);
}



LoadScene::LoadScene(const std::string fileName) : _fileName(fileName) { }

void LoadScene::execute()
{
    _scene = _loadManager->loadScene(_fileName);
    _sceneManager->setScene(_scene);
}

std::shared_ptr<BaseCommand> LoadScene::clone() const
{
    return std::make_shared<LoadScene>(*this);
}
