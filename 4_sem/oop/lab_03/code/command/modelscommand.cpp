#include "modelscommand.h"
#include "centeradaptersolution.h"

MoveModels::MoveModels(const double dx, const double dy, const double dz) : _dx(dx), _dy(dy), _dz(dz) {}

void MoveModels::execute()
{
    auto models = _scene->getModels();
    MoveParams params(_dx, _dy, _dz);
    for (auto &model : models)
    {
        _transformManager->setObject(*model);
        _transformManager->setParams(std::make_shared<MoveParams>(params));
        _transformManager->execute();
    }
}

std::shared_ptr<BaseCommand> MoveModels::clone() const
{
    return std::make_shared<MoveModels>(*this);
}

ScaleModels::ScaleModels(const double kx, const double ky, const double kz) : _kx(kx), _ky(ky), _kz(kz) {}

void ScaleModels::execute()
{
    auto models = _scene->getModels();
    for (auto model : models)
    {
        auto center = std::make_shared<Point>();
        CenterAdapterSolution().create(*model, center)->request();
        ScaleParams params(_kx, _ky, _kz, *center);
        _transformManager->setObject(*model);
        _transformManager->setParams(std::make_shared<ScaleParams>(params));
        _transformManager->execute();
    }
}

std::shared_ptr<BaseCommand> ScaleModels::clone() const
{
    return std::make_shared<ScaleModels>(*this);
}

RotateModels::RotateModels(const double ox, const double oy, const double oz) : _ox(ox), _oy(oy), _oz(oz) {}

void RotateModels::execute()
{
    auto models = _scene->getModels();
    for (auto model : models)
    {
        auto center = std::make_shared<Point>();
        CenterAdapterSolution().create(*model, center)->request();
        RotateParams params(_ox, _oy, _oz, *center);
        _transformManager->setObject(*model);
        _transformManager->setParams(std::make_shared<RotateParams>(params));
        _transformManager->execute();
    }
}

std::shared_ptr<BaseCommand> RotateModels::clone() const
{
    return std::make_shared<RotateModels>(*this);
}
