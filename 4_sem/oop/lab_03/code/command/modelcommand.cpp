#include "modelcommand.h"
#include "centeradaptersolution.h"

MoveModel::MoveModel(const double dx, const double dy, const double dz, const std::size_t id) : _dx(dx), _dy(dy), _dz(dz), _id(id) {}

void MoveModel::execute()
{
    auto model = *_scene->getModelIterator(_id);
    _transformManager->setObject(model);
    _transformManager->setParams(std::make_shared<MoveParams>(MoveParams(_dx, _dy, _dz)));
    _transformManager->execute();
}

std::shared_ptr<BaseCommand> MoveModel::clone() const
{
    return std::make_shared<MoveModel>(*this);
}

ScaleModel::ScaleModel(const double kx, const double ky, const double kz, const std::size_t id) : _kx(kx), _ky(ky), _kz(kz), _id(id) {}

void ScaleModel::execute()
{
    auto model = *_scene->getModelIterator(_id);
    _transformManager->setObject(model);
    std::shared_ptr<Point> center = std::make_shared<Point>();
    CenterAdapterSolution().create(model, center)->request();
    _transformManager->setParams(std::make_shared<ScaleParams>(ScaleParams(_kx, _ky, _kz, *center)));
    _transformManager->execute();
}

std::shared_ptr<BaseCommand> ScaleModel::clone() const
{
    return std::make_shared<ScaleModel>(*this);
}

RotateModel::RotateModel(const double ox, const double oy, const double oz, const std::size_t id) : _ox(ox), _oy(oy), _oz(oz), _id(id) {}

void RotateModel::execute()
{
    auto model = *_scene->getModelIterator(_id);
    _transformManager->setObject(model);
    std::shared_ptr<Point> center = std::make_shared<Point>();
    CenterAdapterSolution().create(model, center)->request();
    _transformManager->setParams(std::make_shared<RotateParams>(RotateParams(_ox, _oy, _oz, *center)));
    _transformManager->execute();
}
std::shared_ptr<BaseCommand> RotateModel::clone() const
{
    return std::make_shared<RotateModel>(*this);
}

DeleteModel::DeleteModel(const std::size_t id) : _id(id) {}

void DeleteModel::execute()
{
    auto objIt = _scene->getModelIterator(_id);
    _scene->removeObject(objIt);
}

std::shared_ptr<BaseCommand> DeleteModel::clone() const
{
    return std::make_shared<DeleteModel>(*this);
}

LoadModel::LoadModel(std::string &fileName) : _fileName(fileName) {}

void LoadModel::execute()
{
    auto model = _loadManager->load(_fileName);
    _scene->addObject(model);
}

std::shared_ptr<BaseCommand> LoadModel::clone() const
{
    return std::make_shared<LoadModel>(*this);
}
