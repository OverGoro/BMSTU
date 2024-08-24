// #include <QDebug>

#include "cameracommand.h"
#include "centeradaptersolution.h"


void AddCamera::execute()
{
    auto cam = PerspectiveCamera(position, direction, up, _x_fov, _y_fov, _screen_distantion);
    auto cam_ptr = std::make_shared<PerspectiveCamera>(cam);
    _scene->addObject(cam_ptr);
}

std::shared_ptr<BaseCommand> AddCamera::clone() const
{
    return std::make_shared<AddCamera>(*this);
}


DeleteCamera::DeleteCamera(const std::size_t id) : _id(id) {}

void DeleteCamera::execute()
{
    auto objIt = _scene->getCameraIterator(_id);
    _scene->removeObject(objIt);
}


std::shared_ptr<BaseCommand> DeleteCamera::clone() const
{
    return std::make_shared<DeleteCamera>(*this);
}



MoveCamera::MoveCamera(const double dx, const double dy, const double dz, const std::size_t id) :
    _dx(dx), _dy(dy), _dz(dz), _id(id) {}

void MoveCamera::execute()
{
    auto camera = *_scene->getIterator(_id);
    _transformManager->setObject(camera);
    _transformManager->setParams(std::make_shared<MoveParams>(MoveParams(_dx, _dy, _dz)));
    _transformManager->execute();
}

std::shared_ptr<BaseCommand> MoveCamera::clone() const
{
    return std::make_shared<MoveCamera>(*this);
}


SetCamera::SetCamera(const std::size_t id) : _id(id) {}

void SetCamera::execute()
{
    _sceneManager->setCamera(std::dynamic_pointer_cast<BaseCamera>(*_scene->getCameraIterator(_id)));
}

std::shared_ptr<BaseCommand> SetCamera::clone() const
{
    return std::make_shared<SetCamera>(*this);
}

RotateCamera::RotateCamera(const double ax, const double ay, const double az, const std::size_t id)
    :_ax(ax), _ay(ay), _az(az), _id(id){}

void RotateCamera::execute()
{
    auto camera = *_scene->getCameraIterator(_id);
    auto center = std::make_shared<Point>();
    CenterAdapterSolution().create(camera, center)->request();
    _transformManager->setObject(camera);
    _transformManager->setParams(std::make_shared<RotateParams>(RotateParams(_ax, _ay, _az, *center)));
    _transformManager->execute();
}

std::shared_ptr<BaseCommand> RotateCamera::clone() const
{
    return std::make_shared<RotateCamera>(*this);
}
